#pragma once

#include "layer.h"

class VeraTilemap
{
	public:
		VeraTilemap(Layer *layer);
		virtual ~VeraTilemap();

		void writeFile(const std::string &filename) const;

	private:
		Layer *layer;
};

