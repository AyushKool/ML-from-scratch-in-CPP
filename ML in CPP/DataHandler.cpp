#define _CRT_SECURE_NO_DEPRECATE
#include "DataHandler.h"
#include <algorithm>
#include <random>
#include <iostream>


DataHandler::DataHandler()
{
}

DataHandler::~DataHandler()
{
    // FIX ME
}
//
//void DataHandler::readCsv(std::string path, std::string delimiter)
//{
//    class_counts = 0;
//    std::ifstream data_file;
//    data_file.open(path.c_str());
//    std::string line;
//
//    while (std::getline(data_file, line))
//    {
//        if (line.length() == 0) continue;
//        Data* d = new Data();
//        d->setNormalizedFeatureVector(new std::vector<double>());
//        size_t position = 0;
//        std::string token;
//        while ((position = line.find(delimiter)) != std::string::npos)
//        {
//            token = line.substr(0, position);
//            d->appendToFeatureVector(std::stod(token));
//            line.erase(0, position + delimiter.length());
//        }
//
//        if (classFromString.find(line) != classFromString.end())
//        {
//            d->setLabel(classFromString[line]);
//        }
//        else
//        {
//            classFromString[line] = class_counts;
//            d->setLabel(classFromString[token]);
//            class_counts++;
//        }
//        dataArray->push_back(d);
//    }
//    for (Data* data : *dataArray)
//        data->setClassVector(class_counts);;
//    //normalize();
//    featureVectorSize = dataArray->at(0)->getNormalizedFeatureVector()->size();
//}

void DataHandler::readInputData(std::string path)
{
    uint32_t magic = 0;
    uint32_t nImages = 0;
    uint32_t rows = 0;
    uint32_t cols = 0;

    uint32_t headers[4];
    char bytes[4];
    FILE* f = fopen(path.c_str(), "rb");
    if (f)
    {
        uint32_t i = 0;
        while (i < 4)//4 headers
        {
            if (fread(bytes, sizeof(bytes), 1, f))
            {
                /*switch (i)
                {
                case 0:
                    magic = format(bytes);
                    break;
                case 1:
                    nImages = format(bytes);
                    break;
                case 2:
                    rows = format(bytes);
                    break;
                case 3:
                    cols = format(bytes);
                    break;
                }*/
                headers[i] = format(bytes);
                ++i;
            }
        }
        printf("Done getting images file header.\n");
        printf("magic: 0x%08x\n", headers[0]);

        printf("nImages: 0x%08x\n", headers[1]);

        printf("rows: 0x%08x\n", headers[2]);

        printf("cols: 0x%08x\n", headers[3]);
        exit(1);
        uint32_t image_size = rows * cols;
        for (i = 0; i < nImages; i++)
        {
            if (i%10000 == 0)std::cout << i << "\n";
            Data d;
            d.setFeatureVector(std::vector<uint8_t>());
            uint8_t element[1];
            for (int j = 0; j < image_size; j++)
            {
                //std::cout << "\t" << j << "\n";
                if (fread(element, sizeof(element), 1, f))
                {
                    d.appendToFeatureVector(*element);
                }
            }
            dataArray.push_back(d);
        }
        printf("Successfully read %lu data entries.\n", dataArray.size());
        printf("The Feature Vector Size is: %d\n", dataArray[0].getFeatureVectorSize());
    }
    else
    {
        printf("Invalid Input File Path\n");
        exit(1);
    }
}
void DataHandler::readLabelData(std::string path)
{
    uint32_t magic = 0;
    uint32_t nLabels = 0;
    char bytes[4];
    FILE* f = fopen(path.c_str(), "rb");
    if (f)
    {
        int i = 0;
        while (i < 2)//2 Headers
        {
            if (fread(bytes, sizeof(bytes), 1, f))
            {
                switch (i)
                {
                case 0:
                    magic = format(bytes);
                    break;
                case 1:
                    nLabels = format(bytes);
                    break;
                }
                ++i;
            }
        }

        for (i = 0; i < nLabels; i++)
        {
            uint8_t element[1];
            if (fread(element, sizeof(element), 1, f))
                dataArray[i].setLabel(*element);
        }
        printf("Done getting labels file header.\n");
    }
    else
    {
        printf("Invalid Label File Path\n");
        exit(1);
    }
}
void DataHandler::splitData()
{
    std::unordered_set<int> used_indexes;
    int train_size = dataArray.size() * TRAIN_SET_PERCENT;
    int test_size = dataArray.size() * TEST_SET_PERCENT;
    int valid_size = dataArray.size() * VALID_SET_PERCENT;

    std::random_shuffle(dataArray.begin(), dataArray.end());
    int index = 0;
    // Training Data
    while (train_size--)
        trainingData.push_back(dataArray[index++]);

    // Test Data
    while (test_size--)
        testData.push_back(dataArray[index++]);

    // Test Data
    while (valid_size--)
        validationData.push_back(dataArray[index++]);

    printf("Training Data Size: %lu.\n", trainingData.size());
    printf("Test Data Size: %lu.\n", testData.size());
    printf("Validation Data Size: %lu.\n", validationData.size());
}
//
//void DataHandler::countClasses()
//{
//    int count = 0;
//    for (unsigned i = 0; i < dataArray->size(); i++)
//    {
//        if (classFromInt.find(dataArray->at(i)->getLabel()) == classFromInt.end())
//        {
//            classFromInt[dataArray->at(i)->getLabel()] = count;
//            dataArray->at(i)->setEnumeratedLabel(count);
//            count++;
//        }
//        else
//        {
//            dataArray->at(i)->setEnumeratedLabel(classFromInt[dataArray->at(i)->getLabel()]);
//        }
//    }
//
//    class_counts = count;
//    for (Data* data : *dataArray)
//        data->setClassVector(class_counts);
//    printf("Successfully Extraced %d Unique Classes.\n", class_counts);
//}

//void DataHandler::normalize()
//{
//    std::vector<double> mins, maxs;
//    // fill min and max lists
//
//    Data* d = dataArray->at(0);
//    for (auto val : *d->getFeatureVector())
//    {
//        mins.push_back(val);
//        maxs.push_back(val);
//    }
//
//    for (int i = 1; i < dataArray->size(); i++)
//    {
//        d = dataArray->at(i);
//        for (int j = 0; j < d->getFeatureVectorSize(); j++)
//        {
//            double value = (double)d->getFeatureVector()->at(j);
//            if (value < mins.at(j)) mins[j] = value;
//            if (value > maxs.at(j)) maxs[j] = value;
//        }
//    }
//    // normalize data array
//
//    for (int i = 0; i < dataArray->size(); i++)
//    {
//        dataArray->at(i)->setNormalizedFeatureVector(new std::vector<double>());
//        dataArray->at(i)->setClassVector(class_counts);
//        for (int j = 0; j < dataArray->at(i)->getFeatureVectorSize(); j++)
//        {
//            if (maxs[j] - mins[j] == 0) dataArray->at(i)->appendToFeatureVector(0.0);
//            else
//                dataArray->at(i)->appendToFeatureVector(
//                    (double)(dataArray->at(i)->getFeatureVector()->at(j) - mins[j]) / (maxs[j] - mins[j]));
//        }
//    }
//}
//
//int DataHandler::getClassCounts()
//{
//    return class_counts;
//}

int DataHandler::getDataArraySize() const
{
    return dataArray.size();
}
int DataHandler::getTrainingDataSize() const
{
    return trainingData.size();
}
int DataHandler::getTestDataSize() const
{
    return testData.size();
}
int DataHandler::getValidationSize() const
{
    return validationData.size();
}

//converts high endian to little indian (required for Intel Processors)
uint32_t DataHandler::format(const char (&bytes)[4]) const
{
    return (uint32_t)((bytes[0] << 24) |
        (bytes[1] << 16) |
        (bytes[2] << 8) |
        (bytes[3]));
}

const std::vector<Data>& DataHandler::getTrainingData() const
{
    return trainingData;
}
const std::vector<Data>& DataHandler::getTestData() const
{
    return testData;
}
const std::vector<Data>& DataHandler::getValidationData() const
{
    return validationData;
}

//std::map<uint8_t, int> DataHandler::getClassMap()
//{
//    return classFromInt;
//}

//void DataHandler::print()
//{
//    printf("Training Data:\n");
//    for (auto data : *trainingData)
//    {
//        for (auto value : *data->getNormalizedFeatureVector())
//        {
//            printf("%.3f,", value);
//        }
//        printf(" ->   %d\n", data->getLabel());
//    }
//    return;
//
//    printf("Test Data:\n");
//    for (auto data : *testData)
//    {
//        for (auto value : *data->getNormalizedFeatureVector())
//        {
//            printf("%.3f,", value);
//        }
//        printf(" ->   %d\n", data->getLabel());
//    }
//
//    printf("Validation Data:\n");
//    for (auto data : *validationData)
//    {
//        for (auto value : *data->getNormalizedFeatureVector())
//        {
//            printf("%.3f,", value);
//        }
//        printf(" ->   %d\n", data->getLabel());
//    }
//
//}