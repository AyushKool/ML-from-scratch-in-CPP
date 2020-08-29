#pragma once
#include "Data.h"

class KNN
{
	int k;
	std::vector<int> neighbor_indexes;

public:
	KNN(int new_k = 1);

	void findKNearest(const Data &queryPoint);
	void setK(const int &k);
	uint8_t findMostFrequentClass();
	float calculateDistance(const Data &queryPoint, const Data &input);
	float validatePerformance();
	float testPerformance();
};
