#include "layer.h"

#include<sstream>
#include<iostream>

Layer::Layer(int id, std::string name, int width, int height)
	:id(id), name(name), width(width), height(height)
{
	data = (uint32_t*) malloc(sizeof(uint32_t) * width * height);
}

Layer::~Layer()
{
	free(data);
}

void Layer::setDataFromCsv(const std::string &csvData)
{
	// stream the string
	std::stringstream csvStream(csvData);
	std::string cell;

	int index = 0;

	while(std::getline(csvStream, cell, ','))
	{
		data[index] = (uint32_t) atoi(cell.c_str());
		index++;
	}

	std::cout << "index: " << index << std::endl;
}
