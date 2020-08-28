#pragma once
#include "Data.h"
#include <stdint.h>
#include <vector>
#include <map>
class DataHandler
{
private:
	std::vector<Data> dataArray; // all of the data
	std::vector<Data> trainingData;
	std::vector<Data> testData;
	std::vector<Data> validationData;
	std::map<uint8_t, int> fLabel; // k:label v:frequency of label

	void readInputData(const char* path);
	void readLabelData(const char* path);
	void splitData();
	void countLabels();

public:
	const float TRAIN_SET_PERCENT = 0.75f;
	const float TEST_SET_PERCENT = 0.20f;
	const float VALID_SET_PERCENT = 0.05f;

	DataHandler(const char* train_images_path, const char* train_labels_path);

	//void readCsv(std::string, std::string);
	int getDataArraySize() const;
	int getTrainingDataSize() const;
	int getTestDataSize() const;
	int getValidationSize() const;
	uint32_t format(const unsigned char(&bytes)[4]) const;
	const std::vector<Data>& getTrainingData() const;
	const std::vector<Data>& getTestData() const;
	const std::vector<Data>& getValidationData() const;
	const std::map<uint8_t, int>& getFLabel() const;
};
