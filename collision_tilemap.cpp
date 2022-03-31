#include "collision_tilemap.h"

#include <iostream>
#include <fstream>
#include <cstdint>

#include "tilemap.h"

using namespace std;

void CollisionTilemap::writeFile(const std::string &filename, const std::string &layername) const
{
	Layer *layer = tilemap->Layers()[std::string(layername)];

	if(!layer)
	{
		throw CollisionTilemapFileException("Could not find layer");
	}

	ofstream file;
	file.open(filename, ios::out | ios::binary);

	uint32_t width = layer->Width();
	uint32_t height = layer->Height();

	// TODO: Decide if these checks are even necessary for collision maps

	if(width != 32 && width != 64 && width != 64 && width != 128 && width != 256)
	{
		throw CollisionTilemapFileException( "Collision maps must be 32/64/128/256 tiles wide");
	}

	if(height != 32 && height != 64 && height != 64 && height != 128 && height != 256) {
		throw CollisionTilemapFileException( "Collision maps must be 32/64/128/256 tiles high");
	}

	// write out 2 byte header
	file << (uint8_t)0 << (uint8_t)0;

	for (uint32_t y = 0; y < height; ++y) {
		for (uint32_t x = 0; x < width; ++x) {
			const int index = (y * width) + x;
			const uint32_t rawTile = layer->Data()[index];
			int firstgid = 1;

			// determine firstgid
			for(auto tileset : tilemap->Tilesets())
			{
				// the set of tilesets are sorted, so we only have to check if
				// it's greater than
				if(rawTile >= tileset->FirstGid())
				{
					firstgid = tileset->FirstGid();
				}
			}

			// if the raw tile is 0, write 0
			if(rawTile == 0)
			{
				file << (uint8_t)0;
				continue;
			}

			// make 0 based
			uint8_t tileId = rawTile - firstgid;

			// no tile
			if(tileId == 0)
			{
				file << (uint8_t)0;
				continue;
			}

			// write the byte out
			file << (uint8_t) tileId;
		}
	}
}
