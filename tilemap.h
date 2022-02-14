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

		std::string MapVersion() const { return std::string(version); }
		std::string TiledVersion() const { return std::string(tiledVersion); }
		int Width() const { return width; }
		int Height() const { return height; }
		std::vector<Layer> const &Layers() const { return layers; }

	private:
		Glib::ustring version;
		Glib::ustring tiledVersion;
		int width;
		int height;
		int tileWidth;
		int tileHeight;

		void readMap(xmlpp::TextReader& reader);
		Layer readLayer(xmlpp::TextReader& reader);

		std::vector<Layer> layers;

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

