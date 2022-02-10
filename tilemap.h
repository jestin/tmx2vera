#pragma once

#include<vector>
#include<string>

#include <libxml/encoding.h>
#include <libxml/xmlreader.h>

#include"layer.h"

class Tilemap
{
	public:
		Tilemap(const char *filename);
		virtual ~Tilemap();

	private:
		std::vector<layer> layers;

		void processNode(xmlTextReaderPtr reader);
};

