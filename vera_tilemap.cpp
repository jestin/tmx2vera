#include "vera_tilemap.h"

#include <iostream>
#include <fstream>
#include <cstdint>

#include "tilemap.h"

using namespace std;

void VeraTilemap::writeFile(const std::string &filename, const std::string &layername) const
{
	Layer *layer = tilemap->Layers()[std::string(layername)];

	if(!layer)
	{
		throw VeraTilemapFileException("Could not find layer");
	}

	ofstream file;
	file.open(filename, ios::out | ios::binary);

	uint32_t width = layer->Width();
	uint32_t height = layer->Height();

	if(width != 32 && width != 64 && width != 64 && width != 128 && width != 256)
	{
		throw VeraTilemapFileException( "Vera maps must be 32/64/128/256 tiles wide");
	}

	if(height != 32 && height != 64 && height != 64 && height != 128 && height != 256) {
		throw VeraTilemapFileException( "Vera maps must be 32/64/128/256 tiles high");
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
					firstgid = (tileset->FirstGid()) & 0x03FF;
				}
			}

			// make 0 based
			// capture just the lower 10 bits
			uint16_t tileId = rawTile - firstgid;

			// no tile
			if(tileId == 0)
			{
				file << (uint8_t)0;
				file << (uint8_t)0;
				continue;
			}

			// first byte: tile index (0:7)
			file << (uint8_t) tileId;

			// start off by putting bits 9:8 of the index in the lower two bits
			uint8_t secondByte = tileId >> 8;

			// OR a 1 into bit 2 if flipped horizontally
			if((rawTile & HFLIP_FLAG) == HFLIP_FLAG)
			{
				secondByte |= 0b00000100;
			}

			// OR a 1 into bit 3 if flipped vertically
			if((rawTile & VFLIP_FLAG) == VFLIP_FLAG)
			{
				secondByte |= 0b00001000;
			}

			file << secondByte;
		}
	}
	
	file.close();
}
