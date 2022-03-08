#pragma once

#include "tilemap.h"

#define HFLIP_FLAG 0x80000000
#define VFLIP_FLAG 0x40000000

class VeraTilemap
{
	public:
		VeraTilemap(Tilemap *tilemap);
		virtual ~VeraTilemap();

		void writeFile(const std::string &filename, const std::string &layername) const;

	private:
		Tilemap *tilemap;
};

class VeraTilemapException
{
	public:
		VeraTilemapException(const std::string &message): message(message) { }
		std::string message;

};

class VeraTilemapFileException : public VeraTilemapException
{
	public:
		VeraTilemapFileException(const std::string &message)
			: VeraTilemapException(message) { }
};
