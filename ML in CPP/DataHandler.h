#pragma once
#include "Data.h"
#include <stdint.h>
#include <vector>
#include <map>
class DataHandler
{
private:
	static std::vector<Data> dataArray; // all of the data
	static std::vector<Data> trainingData;
	static std::vector<Data> testData;
	static std::vector<Data> validationData;
	static std::map<uint8_t, int> fLabel; // k:label v:frequency of label
	
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
	
	uint32_t format(const unsigned char(&bytes)[4]) const;
	static size_t getDataArraySize();
	static size_t getTrainingDataSize();
	static size_t getTestDataSize();
	static size_t getValidationDataSize();
	static const std::vector<Data>& getTrainingData();
	static const std::vector<Data>& getTestData();
	static const std::vector<Data>& getValidationData();
	static const std::map<uint8_t, int>& getFLabel();
};
