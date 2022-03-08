#pragma once

#include<string>
#include<cstdint>

class Tileset
{
	public:
		Tileset(int id, std::string name);
		virtual ~Tileset();

		int FirstGid() const { return firstGid; }
		void setFirstGid(int firstGid) { this->firstGid = firstGid; }

		std::string Source() const { return source; }
		void setSource(std::string source) { this->source = source; }

		// overlaod < operator so we can use this in a auto-sorted set
		bool operator<(const Tileset &a) const { return firstGid < a.FirstGid(); }

	private:
		int firstGid;
		std::string source;
};
