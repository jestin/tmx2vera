#pragma once

#include "tilemap.h"

class OutputTilemap
{
	public:
		OutputTilemap(Tilemap *tilemap): tilemap(tilemap) {}
		virtual ~OutputTilemap() {}

		virtual void writeFile(const std::string &filename, const std::string &layername, const int &disable_paloffset = 0) const = 0;

	protected:
		Tilemap *tilemap;
};

class OutputTilemapException : public TilemapException
{
	public:
		OutputTilemapException(const std::string &message): TilemapException(message) { }
		std::string message;

};
