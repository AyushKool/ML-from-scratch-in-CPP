#pragma once
#include <vector>
#include <stdint.h> // uint8_t
class Data
{
	std::vector<uint8_t> featureVector;
	std::vector<float> normalizedFeatureVector;
	uint8_t label;

public:
	void setLabel(const uint8_t&);
	void appendToFeatureVector(uint8_t val);

	int getFeatureVectorSize() const;
	const uint8_t& getLabel() const;
	const std::vector<uint8_t>& getFeatureVector() const;
	const std::vector<float>& getNormalizedFeatureVector() const;
};