#include "Data.h"

void Data::setFeatureVector(const std::vector<uint8_t> &vect)
{
    featureVector = vect;
    for (auto pixel : featureVector)
        normalizedFeatureVector.emplace_back(pixel / 255.0f);
}

void Data::setLabel(const uint8_t &val)
{
    label = val;
}

void Data::appendToFeatureVector(uint8_t val)
{
    featureVector.emplace_back(val);
}

int Data::getFeatureVectorSize() const
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