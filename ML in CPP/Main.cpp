#include "DataHandler.h"
#include <iostream>

int main()
{
	DataHandler dh;
	dh.readInputData("../train-images-idx3-ubyte");
	dh.readLabelData("../train_labels");
}