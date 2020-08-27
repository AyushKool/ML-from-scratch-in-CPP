#include "DataHandler.h"
#include <iostream>

int main()
{
	DataHandler dh;
	dh.readInputData("../train_images");
	dh.readLabelData("../train_labels");
}