#pragma once
#include <functional>
#include <utility>
#include <string>

#include "Graph.h"

struct Coordinates
{
	size_t x = 0;
	size_t y = 0;

	friend ostream& operator<<(ostream& out, const Coordinates& coords)
	{
		return out << "{" << coords.x << "," << coords.y << "}";
	}

	bool operator<(const Coordinates& other) const
	{
		return x < other.x || ((x == other.x) && y < other.y);
	}

	bool operator==(const Coordinates& other) const
	{
		return x == other.x && y == other.y;
	}
};


class GridGraph : public Graph< Coordinates, string > 
{
public:
	Coordinates Dimensions{};

	std::vector<Coordinates> GridNeighbourhood(Coordinates coordinates);
	void Construct(std::vector<string> Input, std::function<bool(char)> validSymbol);

	void MergeNeighbouringNodes(std::function<bool(char)> validSymbol);
};
