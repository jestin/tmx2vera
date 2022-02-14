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
		void setId(int id) { this->id = id; }

		std::string Name() const { return name; }
		void setName(std::string name) { this->name = name; }

		int Width() const { return width; }
		void setWidth(int width) { this->width = width; }

		int Height() const { return height; }
		void setHeight(int height) { this->height = height; }

	private:
		int id;
		std::string name;
		int width;
		int height;
		// int data[];
};
