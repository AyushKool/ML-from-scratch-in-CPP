#include "DataHandler.h"
#include "KNN.h"
#include <algorithm>
#include <utility> //required for pair
#include <cmath>
#define EUCLID
#define all(c) (c).begin(), (c).end()

KNN::KNN(int new_k) : k(new_k){}

void KNN::setK(const int& k)
{
    this->k = k;
}

void KNN::findKNearest(const Data& queryPoint)
{
    std::vector<std::pair<int, float>> distVect(DataHandler::getTrainingDataSize());//k:index v:distance
    for (size_t i = 0; i != distVect.size(); ++i)
        distVect[i] = std::pair<int, float>(i, calculateDistance(DataHandler::getTrainingData()[i], queryPoint));

    std::sort(all(distVect),
    [](const std::pair<int, float>& a, const std::pair<int, float>& b) {
        return a.second < b.second;
    });
    
    int i = 0;
    for (auto pair : distVect)
    {
        neighbor_indexes.emplace_back(pair.first);
        ++i;
        if (i == k) break;
    }
}

uint8_t KNN::findMostFrequentClass()
{
    std::map<uint8_t, int> freqMap; //k:label v:frequency of label
    uint8_t label;
    for (int ind : neighbor_indexes)
    {
        label = DataHandler::getTrainingData()[ind].getLabel();
        if (freqMap.find(label) == freqMap.end()) freqMap[label] = 1;
        else freqMap[label]++;
    }
    neighbor_indexes.clear();
    return std::max_element(all(freqMap))->first;
}

float KNN::calculateDistance(const Data& queryPoint, const Data& input)
{
    float value = 0;
    if (queryPoint.getFeatureVectorSize() != input.getFeatureVectorSize())
    {
        printf("Error: Vector size mismatch.\n");
        exit(1);
    }
#ifdef EUCLID
    for (size_t i = 0; i < queryPoint.getFeatureVectorSize(); i++)
    {
        value += pow(queryPoint.getNormalizedFeatureVector().at(i) - input.getNormalizedFeatureVector().at(i), 2);
    }
    return sqrt(value);
#elif defined MANHATTAN
    //TODO
#endif
}

float KNN::validatePerformance()
{
    float current_performance = 0;
    int count = 0;
    int data_index = 0;
    for (auto d : DataHandler::getValidationData())
    {
        findKNearest(d);
        int prediction = findMostFrequentClass();
        if (prediction == d.getLabel()) count++;
        //printf("\n%d -> %d\n", d.getLabel(), prediction);
        data_index++;
        if(data_index % 25 == 0 || data_index == 1)
            printf("Current Performance: %.3f %%.\n", (count * 100.0f / data_index));
    }
    current_performance = count * 100.0f / DataHandler::getValidationDataSize();
    printf("Validation Performance for K = %d: %.3f.\n", k, current_performance);
    return current_performance;
}

float KNN::testPerformance()
{
    float current_performance = 0;
    int count = 0;
    for (Data d : DataHandler::getTestData())
    {
        findKNearest(d);
        int prediction = findMostFrequentClass();
        if (prediction == d.getLabel()) count++;
    }
    current_performance = count * 100.0f / DataHandler::getTestDataSize();
    printf("Test Performance for K = %d: %.3f\n", k, current_performance);
    return current_performance;
}