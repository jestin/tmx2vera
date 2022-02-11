#include "tilemap.h"

#include<iostream>
#include<stdlib.h>

Tilemap::Tilemap(const char *filename)
{
	xmlpp::TextReader reader(filename);

	while(reader.read())
	{
		processNode(reader);
	}
}

Tilemap::~Tilemap()
{
}

void Tilemap::processNode(xmlpp::TextReader&  reader)
{
	switch(getElement(reader.get_name()))
	{
		case TMX_ELEMENT::MAP:
			processMapElement(reader);
			break;
		default:
			break;
	}
}

void Tilemap::processMapElement(xmlpp::TextReader&  reader)
{
	if(!reader.has_attributes())
	{
		throw new TilemapFileException();
	}
	
	reader.move_to_first_attribute();
	do{
		switch(getMapAttribute(reader.get_name()))
		{
			case MAP_ATTRIBUTE::VERSION:
				version = reader.get_value();
			case MAP_ATTRIBUTE::TILED_VERSION:
				tiledVersion = reader.get_value();
			default:
				break;
		}
	} while(reader.move_to_next_attribute());

	// advance to the next element
	reader.move_to_element();
}
