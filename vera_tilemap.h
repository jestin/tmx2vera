#pragma once

#include "layer.h"

#define HFLIP_FLAG 0x80000000
#define VFLIP_FLAG 0x40000000

class VeraTilemap
{
	public:
		VeraTilemap(Layer *layer);
		virtual ~VeraTilemap();

		void writeFile(const std::string &filename) const;

	private:
		Layer *layer;
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
