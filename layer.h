#pragma once

#include<string>
#include<cstdint>

class Layer
{
	public:
		Layer(int id, std::string name, int width, int height);
		virtual ~Layer();

		int Id() const { return id; }
		void setId(int id) { this->id = id; }

		std::string Name() const { return name; }
		void setName(std::string name) { this->name = name; }

		int Width() const { return width; }
		void setWidth(int width) { this->width = width; }

		int Height() const { return height; }
		void setHeight(int height) { this->height = height; }

		const uint32_t* Data() const { return data; }
		void setDataFromCsv(const std::string &csvData);

	private:
		int id;
		std::string name;
		int width;
		int height;
		uint32_t* data;
};
