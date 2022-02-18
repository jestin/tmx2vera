#pragma once

#include "tilemap.h"

class VeraTilemap
{
	public:
		VeraTilemap(const Tilemap &tilemap, const std::string &layerName);
		virtual ~VeraTilemap();

		void writeFile(const std::string &filename) const;

	private:
};

