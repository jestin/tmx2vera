#include "tilemap.h"

#include<iostream>
#include<stdlib.h>

Tilemap::Tilemap(const char *filename)
{
	xmlpp::TextReader reader(filename);
	
	readMap(reader);
}

Tilemap::~Tilemap()
{
	for(auto it = layers.begin(); it != layers.end(); ++it)
	{
		delete (*it);
	}
}

void Tilemap::readMap(xmlpp::TextReader& reader)
{
	reader.read();

	Glib::ustring name = reader.get_name();

	// make sure that map is the first element
	if(name != "map")
	{
		throw new TilemapFileException();
	}
	
	xmlpp::TextReader::xmlNodeType nodeType = reader.get_node_type();

	// make sure it's a start element
	if(nodeType != xmlpp::TextReader::xmlNodeType::Element)
	{
		throw new TilemapFileException();
	}

	// set the attribute values
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

	// read child elements
	while(reader.read())
	{
		name = reader.get_name();
		nodeType = reader.get_node_type();

		// check for map end
		if(name == "map" && nodeType == xmlpp::TextReader::xmlNodeType::EndElement)
			break;

		switch(getElement(name))
		{
			case TMX_ELEMENT::LAYER:
				layers.push_back(readLayer(reader));
				break;
			default:
				break;
		}
	}
}

Layer* Tilemap::readLayer(xmlpp::TextReader& reader)
{
	Glib::ustring name = reader.get_name();
	xmlpp::TextReader::xmlNodeType nodeType = reader.get_node_type();
	int id, width, height;
	std::string layerName;

	// make sure it's a start element
	if(nodeType != xmlpp::TextReader::xmlNodeType::Element)
	{
		throw new TilemapFileException();
	}

	if(!reader.has_attributes())
	{
		throw new TilemapFileException();
	}

	reader.move_to_first_attribute();
	do{
		switch(getLayerAttribute(reader.get_name()))
		{
			case LAYER_ATTRIBUTE::LAYER_ID:
				id = atoi(reader.get_value().c_str());
				break;
			case LAYER_ATTRIBUTE::LAYER_NAME:
				layerName = reader.get_value();
				break;
			case LAYER_ATTRIBUTE::LAYER_WIDTH:
				width = atoi(reader.get_value().c_str());
				break;
			case LAYER_ATTRIBUTE::LAYER_HEIGHT:
				height = atoi(reader.get_value().c_str());
				break;
			default:
				break;
		}
	} while(reader.move_to_next_attribute());

	// create the layer
	Layer* layer = new Layer(id, layerName, width, height);

	// advance to the next element
	reader.move_to_element();

	// read child elements
	while(reader.read())
	{
		name = reader.get_name();
		nodeType = reader.get_node_type();

		// check for map end
		if(name == "layer" && nodeType == xmlpp::TextReader::xmlNodeType::EndElement)
			break;
	}

	switch(getElement(name))
	{
		case TMX_ELEMENT::DATA:
			break;
		default:
			break;
	}

	return layer;
}

int* Tilemap::readLayerData(xmlpp::TextReader& reader)
{
	return nullptr;
}
