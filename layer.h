#pragma once

#include<string>
#include<cstdint>

#define HFLIP_FLAG 0x80000000
#define VFLIP_FLAG 0x40000000

class Layer
{
	public:
		Layer();
		virtual ~Layer();

		int Id() const { return id; }
		void setId(uint32_t id) { this->id = id; }

		std::string Name() const { return name; }
		void setName(std::string name) { this->name = name; }

		int Width() const { return width; }
		void setWidth(uint32_t width) { this->width = width; }

		int Height() const { return height; }
		void setHeight(uint32_t height) { this->height = height; }

	private:
		uint32_t id;
		std::string name;
		int width;
		int height;
		// uint32_t data[];
};
