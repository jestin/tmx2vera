#include "vera_tilemap.h"

#include <iostream>

VeraTilemap::VeraTilemap(Layer *layer)
	:layer(layer)
{
}

VeraTilemap::~VeraTilemap()
{
}

void VeraTilemap::writeFile(const std::string &filename) const
{
	std::cout << layer->Name() << std::endl;
}
