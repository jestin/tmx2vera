#pragma once

#include<vector>
#include<string>

#include <libxml++/libxml++.h>
#include <libxml++/parsers/textreader.h>


#include"layer.h"

class Tilemap
{
	public:
		Tilemap(const char *filename);
		virtual ~Tilemap();

	private:
		std::vector<layer> layers;

		void processNode(xmlpp::TextReader&  reader);
};

