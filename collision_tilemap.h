#pragma once

#include "output_tilemap.h"

class CollisionTilemap : public OutputTilemap
{
	public:
		CollisionTilemap(Tilemap *tilemap): OutputTilemap(tilemap) {}
		virtual ~CollisionTilemap() {}

		void writeFile(const std::string &filename, const std::string &layername, const int &disable_paloffset = 0) const override;
};

class CollisionTilemapFileException : public OutputTilemapException
{
	public:
		CollisionTilemapFileException(const std::string &message)
			: OutputTilemapException(message) { }
};
