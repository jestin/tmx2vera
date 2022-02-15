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
			readLayerData(reader, layer);
			break;
		default:
			break;
	}

	return layer;
}

void Tilemap::readLayerData(xmlpp::TextReader& reader, Layer *layer)
{
	Glib::ustring name = reader.get_name();
	xmlpp::TextReader::xmlNodeType nodeType = reader.get_node_type();
	std::string encoding;
	std::string compression;

	if(name != "data")
	{
		throw new TilemapFileException();
	}

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
		switch(getLayerDataAttribute(reader.get_name()))
		{
			case LAYER_DATA_ATTRIBUTE::ENCODING:
				 encoding = reader.get_value();
				break;
			case LAYER_DATA_ATTRIBUTE::COMPRESSION:
				 compression = reader.get_value();
				break;
			default:
				break;
		}
	} while(reader.move_to_next_attribute());

	if(encoding == "csv")
	{
		// TODO: set layer->Data() to CSV values
	}
	else if (encoding == "base64" && compression == "gzip")
	{
		// TODO: set layer->Data() to gzipped BASE64 values
	}
	else if (encoding == "base64" && compression == "zlib")
	{
		// TODO: set layer->Data() to zlib compressed BASE64 values
	}
	else if (encoding == "base64")
	{
		// TODO: set layer->Data() to uncompressed BASE64 values
	}
}
