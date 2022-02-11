#pragma once

#include<vector>
#include<string>
#include<cstdint>

#include <libxml++/libxml++.h>
#include <libxml++/parsers/textreader.h>


#include"layer.h"

enum TMX_ELEMENT
{
	MAP = 1,
	TILESET,
	LAYER,
	DATA
};

static std::map<Glib::ustring, TMX_ELEMENT> elementMap = {
	{ "map", TMX_ELEMENT::MAP },
	{ "tileset", TMX_ELEMENT::TILESET },
	{ "layer", TMX_ELEMENT::LAYER },
	{ "data", TMX_ELEMENT::DATA }
};

enum MAP_ATTRIBUTE
{
	VERSION = 1,
	TILED_VERSION,
	WIDTH,
	HEIGHT,
	TILE_WIDTH,
	TILE_HEIGHT
};

static std::map<Glib::ustring, MAP_ATTRIBUTE> mapAttributeMap = {
	{ "version", MAP_ATTRIBUTE::VERSION },
	{ "tiledversion", MAP_ATTRIBUTE::TILED_VERSION },
	{ "width", MAP_ATTRIBUTE::WIDTH },
	{ "height", MAP_ATTRIBUTE::HEIGHT },
	{ "tilewidth", MAP_ATTRIBUTE::TILE_WIDTH },
	{ "tileheight", MAP_ATTRIBUTE::TILE_HEIGHT }
};

class Tilemap
{
	public:
		Tilemap(const char *filename);
		virtual ~Tilemap();

		const Glib::ustring getMapVersion() { return version; }

	private:
		Glib::ustring version;
		Glib::ustring tiledVersion;
		uint32_t width;
		uint32_t height;
		uint32_t tileWidth;
		uint32_t tileHeight;

		void processMapElement(xmlpp::TextReader&  reader);

		std::vector<layer> layers;

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

