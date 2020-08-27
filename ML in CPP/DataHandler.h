#pragma once
#include "Data.h"
#include <vector>
#include <string>
#include <map>
#include <unordered_set>
#include <math.h>
#include <fstream>
#include <stdint.h>

class DataHandler
{
	std::vector<Data> dataArray; // all of the data
	std::vector<Data> trainingData;
	std::vector<Data> testData;
	std::vector<Data> validationData;

public:
	const float TRAIN_SET_PERCENT = 0.75f;
	const float TEST_SET_PERCENT = 0.20f;
	const float VALID_SET_PERCENT = 0.05f;

	DataHandler();
	~DataHandler();

	//void readCsv(std::string, std::string);
	void readInputData(std::string path);
	void readLabelData(std::string path);
	void splitData();
	//void countClasses();
	//void normalize();
	//void print();

	//getters
	//int getClassCounts();
	int getDataArraySize() const;
	int getTrainingDataSize() const;
	int getTestDataSize() const;
	int getValidationSize() const;
	uint32_t format(const char(&bytes)[4]) const;
	const std::vector<Data>& getTrainingData() const;
	const std::vector<Data>& getTestData() const;
	const std::vector<Data>& getValidationData() const;
	//std::map<uint8_t, int> getClassMap();
};
