#include "layer.h"

Layer::Layer(int id, std::string name, int width, int height)
	:id(id), name(name), width(width), height(height)
{
	data = (uint32_t*) malloc(sizeof(uint32_t) * width * height);
}

Layer::~Layer()
{
	free(data);
}

