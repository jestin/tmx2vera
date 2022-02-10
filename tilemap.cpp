#include "tilemap.h"

#include<iostream>

Tilemap::Tilemap(const char *filename)
{
	int ret;
	xmlTextReaderPtr reader;
	reader = xmlReaderForFile(filename, NULL, 0);

	if(reader != NULL)
	{
		while((ret = xmlTextReaderRead(reader)) == 1)
		{
			processNode(reader);
		}
	}
}

Tilemap::~Tilemap()
{
}

void Tilemap::processNode(xmlTextReaderPtr reader)
{
	const xmlChar *name;
	const xmlChar *value;

	name = xmlTextReaderConstName(reader);

	if(name == NULL)
		name = BAD_CAST "--";

	value = xmlTextReaderConstValue(reader);

	std::cout << xmlTextReaderDepth(reader) << " "
		<< xmlTextReaderNodeType(reader) << " "
		<< name << " "
		<< xmlTextReaderIsEmptyElement(reader) << " "
		<< xmlTextReaderHasValue(reader);

	if(value == NULL)
	{
		std::cout << std::endl;
	}
	else
	{
		std::cout << " " << value << std::endl;
	}
}
