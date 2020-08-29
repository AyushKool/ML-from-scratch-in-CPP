#include "DataHandler.h"
#include <algorithm>
#include <map>
#include <fstream>

std::vector<Data> DataHandler::dataArray; // all of the data
std::vector<Data> DataHandler::trainingData;
std::vector<Data> DataHandler::testData;
std::vector<Data> DataHandler::validationData;
std::map<uint8_t, int> DataHandler::fLabel;

DataHandler::DataHandler(const char* train_images_path, const char* train_labels_path)
{
    readInputData(train_images_path);
    readLabelData(train_labels_path);
    splitData();
    countLabels();
}

void DataHandler::readInputData(const char* path)
{
    uint32_t headers[4]; //Magic Num | nImages | Rows | Cols
    unsigned char bytes[4];
    std::ifstream file;
    file.open(path, std::ios::binary | std::ios::in);
    if (file)
    {
        uint32_t i = 0;
        while (i < 4)//4 headers
        {
            file.read((char *) bytes, sizeof(bytes));
            headers[i++] = format(bytes);
        }
        printf("Done getting images file header.\n");
        
        uint32_t image_size = headers[2] * headers[3];
        printf("%u\n", headers[1]);
        for (i = 0; i < headers[1]; i++)
        {
            if (i%10000 == 0) printf("%d images read.\n", i);
            Data d;
            uint8_t element[1];
            for (uint32_t j = 0; j < image_size; j++)
            {
                file.read((char*)element, sizeof(element));
                d.appendToFeatureVector(*element);
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

void DataHandler::readLabelData(const char* path)
{
    uint32_t headers[4];
    unsigned char bytes[4];
    std::ifstream file;
    file.open(path, std::ios::binary | std::ios::in);
    if (file)
    {
        uint32_t i = 0;
        while (i < 2)//2 Headers
        {
            file.read((char*)bytes, sizeof(bytes));
            headers[i++] = format(bytes);
        }

        printf("\nDone getting labels file header.\n");
        for (i = 0; i < headers[1]; i++)
        {
            uint8_t element[1];
            file.read((char*)element, sizeof(element));
            dataArray[i].setLabel(*element);
        }
    }
    else
    {
        printf("Invalid Label File Path.\n");
        exit(1);
    }
}

void DataHandler::splitData()
{
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
    printf("Validation Data Size: %lu.\n\n", validationData.size());
}

void DataHandler::countLabels()
{
    for (size_t i = 0; i < dataArray.size(); i++)
    {
        if (fLabel.find(dataArray[i].getLabel()) == fLabel.end())
        {
            fLabel[dataArray[i].getLabel()] = 1;
        }
        else
        {
            fLabel[dataArray[i].getLabel()]++;
        }
    }

    printf("Successfully Extraced %d Unique Labels:\n", fLabel.size());
    //for (auto i = fLabel.begin(); i != fLabel.end(); i++)
    //    printf("%u : %u\n", i->first, i->second);
}

//converts high endian to little indian (required for Intel Processors)
uint32_t DataHandler::format(const unsigned char(&bytes)[4]) const
{
    return (uint32_t)((bytes[0] << 24) |
        (bytes[1] << 16) |
        (bytes[2] << 8) |
        (bytes[3]));
}

size_t DataHandler::getDataArraySize()
{
    return dataArray.size();
}

size_t DataHandler::getTrainingDataSize()
{
    return trainingData.size();
}

size_t DataHandler::getTestDataSize()
{
    return testData.size();
}

size_t DataHandler::getValidationDataSize()
{
    return validationData.size();
}

const std::vector<Data>& DataHandler::getTrainingData()
{
    return trainingData;
}

const std::vector<Data>& DataHandler::getTestData()
{
    return testData;
}

const std::vector<Data>& DataHandler::getValidationData()
{
    return validationData;
}

const std::map<uint8_t, int>& DataHandler::getFLabel()
{
    return fLabel;
}

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