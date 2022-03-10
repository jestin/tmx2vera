#pragma once

#include "output_tilemap.h"

#define HFLIP_FLAG 0x80000000
#define VFLIP_FLAG 0x40000000

class VeraTilemap : public OutputTilemap
{
	public:
		VeraTilemap(Tilemap *tilemap): OutputTilemap(tilemap) {}
		virtual ~VeraTilemap() {}

		void writeFile(const std::string &filename, const std::string &layername) const override;
};

class VeraTilemapFileException : public OutputTilemapException
{
	public:
		VeraTilemapFileException(const std::string &message)
			: OutputTilemapException(message) { }
};
