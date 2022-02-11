#include "tilemap.h"

#include<iostream>
#include<stdlib.h>

struct indent {
	int depth_;
	indent(int depth): depth_(depth) {};
};

std::ostream & operator<<(std::ostream & o, indent const & in)
{
	for(int i = 0; i != in.depth_; ++i)
	{
		o << "  ";
	}
	return o;
}

Tilemap::Tilemap(const char *filename)
{
	xmlpp::TextReader reader(filename);

	while(reader.read())
	{
		processNode(reader);
	}
}

Tilemap::~Tilemap()
{
}

void Tilemap::processNode(xmlpp::TextReader&  reader)
{
	int depth = reader.get_depth();
	std::cout << indent(depth) << "--- node ---" << std::endl;
	std::cout << indent(depth) << "name: " << reader.get_name() << std::endl;
	std::cout << indent(depth) << "depth: " << reader.get_depth() << std::endl;

	if(reader.has_attributes())
	{
		std::cout << indent(depth) << "attributes: " << std::endl;
		reader.move_to_first_attribute();
		do
		{
			std::cout << indent(depth) << "  " << reader.get_name() << ": " << reader.get_value() << std::endl;
		} while(reader.move_to_next_attribute());
		reader.move_to_element();
	}
	else
	{
		std::cout << indent(depth) << "no attributes" << std::endl;
	}

	if(reader.has_value())
		std::cout << indent(depth) << "value: '" << reader.get_value() << "'" << std::endl;
	else
		std::cout << indent(depth) << "novalue" << std::endl;

}
