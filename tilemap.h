#pragma once

#include<vector>
#include<string>
#include<cstdint>

#include <libxml++/libxml++.h>
#include <libxml++/parsers/textreader.h>

#include"tmx_data.h"

#include"layer.h"

class Tilemap
{
	public:
		Tilemap(const char *filename);
		virtual ~Tilemap();

		Glib::ustring MapVersion() const { return version; }
		Glib::ustring TiledVersion() const { return tiledVersion; }
		uint32_t Width() const { return width; }
		uint32_t Height() const { return height; }
		std::vector<Layer> Layers() const { return layers; }

	private:
		Glib::ustring version;
		Glib::ustring tiledVersion;
		uint32_t width;
		uint32_t height;
		uint32_t tileWidth;
		uint32_t tileHeight;

		void processMapElement(xmlpp::TextReader&  reader);
		void processLayerElement(xmlpp::TextReader&  reader);

		std::vector<Layer> layers;

		void processNode(xmlpp::TextReader&  reader);

		// create lookup map functions
#define GET_ELEMENT(funcName, enumType, mapName) \
		static enumType funcName(const Glib::ustring& name) \
		{ \
			auto it = mapName.find(name); \
			if(it != mapName.end()) \
				return it->second; \
			return (enumType) 0; \
		}

		GET_ELEMENT(getElement, TMX_ELEMENT, elementMap)
		GET_ELEMENT(getMapAttribute, MAP_ATTRIBUTE, mapAttributeMap)
		GET_ELEMENT(getLayerAttribute, LAYER_ATTRIBUTE, layerAttributeMap)

#undef GET_ELEMENT
};

class TilemapException
{
	public:
		TilemapException() { }
};

class TilemapFileException : public TilemapException
{
	public:
		TilemapFileException()
			: TilemapException() { }
};

