#pragma once

#include<string>
#include<cstdint>

#define HFLIP_FLAG 0x80000000
#define VFLIP_FLAG 0x40000000

class layer
{
	public:
		layer();
		virtual ~layer();

		const std::string Name() { return name; }
		const int Width() { return width; }
		const int Height() { return height; }

	private:
		std::string name;
		int width;
		int height;
		uint32_t data[];
};
