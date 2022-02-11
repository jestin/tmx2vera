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
	xmlpp::TextReader::xmlNodeType nodeType = reader.get_node_type();

	switch(nodeType)
	{
		case xmlpp::TextReader::xmlNodeType::Element:
			switch(getElement(reader.get_name()))
			{
				case TMX_ELEMENT::MAP:
					processMapElement(reader);
					break;
				case TMX_ELEMENT::LAYER:
					processLayerElement(reader);
					break;
				default:
					break;
			}
			break;
		case xmlpp::TextReader::xmlNodeType::EndElement:
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
				break;
			case MAP_ATTRIBUTE::TILED_VERSION:
				tiledVersion = reader.get_value();
				break;
			case MAP_ATTRIBUTE::WIDTH:
				width = atoi(reader.get_value().c_str());
				break;
			case MAP_ATTRIBUTE::HEIGHT:
				height = atoi(reader.get_value().c_str());
				break;
			default:
				break;
		}
	} while(reader.move_to_next_attribute());

	// advance to the next element
	reader.move_to_element();
}

void Tilemap::processLayerElement(xmlpp::TextReader&  reader)
{
	if(!reader.has_attributes())
	{
		throw new TilemapFileException();
	}

	// create the layer
	Layer layer;

	reader.move_to_first_attribute();
	do{
		switch(getLayerAttribute(reader.get_name()))
		{
			case LAYER_ATTRIBUTE::LAYER_ID:
				layer.setId(atoi(reader.get_value().c_str()));
				break;
			case LAYER_ATTRIBUTE::LAYER_NAME:
				layer.setName(reader.get_value());
				break;
			case LAYER_ATTRIBUTE::LAYER_WIDTH:
				layer.setWidth(atoi(reader.get_value().c_str()));
				break;
			case LAYER_ATTRIBUTE::LAYER_HEIGHT:
				layer.setHeight(atoi(reader.get_value().c_str()));
				break;
			default:
				break;
		}
	} while(reader.move_to_next_attribute());

	layers.push_back(layer);

	// advance to the next element
	reader.move_to_element();
}
