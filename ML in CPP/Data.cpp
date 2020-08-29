#include "Data.h"

void Data::setLabel(const uint8_t &val)
{
    label = val;
}

void Data::appendToFeatureVector(uint8_t val)
{
    featureVector.emplace_back(val);
    normalizedFeatureVector.emplace_back(val / 255.0f);
}

size_t Data::getFeatureVectorSize() const
{
    return featureVector.size();
}

const uint8_t& Data::getLabel() const
{
    return label;
}

const std::vector<uint8_t>& Data::getFeatureVector() const
{
    return featureVector;
}

const std::vector<float>& Data::getNormalizedFeatureVector() const
{
    return normalizedFeatureVector;
}