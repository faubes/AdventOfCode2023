#include "GridGraph.h"
#include <sstream>

std::vector<Coordinates> GridGraph::GridNeighbourhood(Coordinates coordinates)
{
	std::vector<Coordinates> GridNeighbours{};
	for (size_t rowOffset = 0; rowOffset <= 2; rowOffset++)
	{
		for (size_t colOffset = 0; colOffset <= 2; colOffset++)
		{
			// remap [0,2] -> [-1,1]
			int i = (int)rowOffset - 1;
			int j = (int)colOffset - 1;
			if (i == 0 && j == 0)
				continue;

			if ((i >= 0 && i < Dimensions.x) &&
				(j >= 0 && j < Dimensions.y))
			{
				GridNeighbours.push_back({ (size_t)i + coordinates.x, (size_t)j + coordinates.y });
			}
		}
	}


	return GridNeighbours;
}

void GridGraph::Construct(std::vector<string> Input, std::function<bool(char)> validSymbol, std::function<bool(char, char)> mergeNextSymbol)
{
	if (Input.empty())
	{
		return;
	}
	Dimensions.x = Input.size();
	Dimensions.y = Input[0].size();

	// add nodes
	for (size_t i = 0; i < Dimensions.x; i++)
	{
		for (size_t j = 0; j < Dimensions.y; j++)
		{
			std::cout << Input[i][j];
			
			if (validSymbol(Input[i][j]))
			{
				std::stringstream value{};
				value << Input[i][j];
				for (auto nextindex = j + 1; nextindex < Dimensions.y && mergeNextSymbol(Input[i][j], Input[i][nextindex]); nextindex++)
				{
					std::cout << Input[i][nextindex];
					value << Input[i][nextindex];
					j++;
				}
				AddNode(Coordinates{ i,j }, value.str());
			}
		}
		std::cout << std::endl;
	}

	// add links
	for (auto& elem : AdjacencyList)
	{
		const Node& node = elem.first;
		std::vector<Coordinates> neighbours = GridNeighbourhood(node.Id);
		for (const auto& neighbouringCoordinate : neighbours)
		{
			if (ContainsNode(neighbouringCoordinate))
			{
				const Node& otherNode = GetNode(neighbouringCoordinate)->first;
				LinkNodes(node, otherNode);
			}
		}
	}
}
