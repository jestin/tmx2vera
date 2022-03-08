#pragma once

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

enum LAYER_ATTRIBUTE
{
	LAYER_ID = 1,
	LAYER_NAME,
	LAYER_WIDTH,
	LAYER_HEIGHT
};

static std::map<Glib::ustring, LAYER_ATTRIBUTE> layerAttributeMap = {
	{ "id", LAYER_ATTRIBUTE::LAYER_ID },
	{ "name", LAYER_ATTRIBUTE::LAYER_NAME },
	{ "width", LAYER_ATTRIBUTE::LAYER_WIDTH },
	{ "height", LAYER_ATTRIBUTE::LAYER_HEIGHT }
};

enum LAYER_DATA_ATTRIBUTE
{
	ENCODING = 1,
	COMPRESSION
};

static std::map<Glib::ustring, LAYER_DATA_ATTRIBUTE> layerDataAttributeMap = {
	{ "encoding", LAYER_DATA_ATTRIBUTE::ENCODING },
	{ "compression", LAYER_DATA_ATTRIBUTE::COMPRESSION }
};

enum TILESET_ATTRIBUTE
{
	SOURCE = 1,
	FIRSTGID
};

static std::map<Glib::ustring, TILESET_ATTRIBUTE> tilesetAttributeMap = {
	{ "source", TILESET_ATTRIBUTE::SOURCE },
	{ "firstgid", TILESET_ATTRIBUTE::FIRSTGID }
};
