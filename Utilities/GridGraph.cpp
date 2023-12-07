#include "GridGraph.h"


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
				GridNeighbours.push_back({ (size_t)i, (size_t)j });
			}
		}
	}


	return GridNeighbours;
}

void GridGraph::Construct(std::vector<string> Input, std::function<bool(char)> validSymbol)
{
	if (Input.empty())
	{
		return;
	}
	Dimensions.x = Input[0].size();
	Dimensions.y = Input.size();

	// add nodes
	for (size_t i = 0; i < Dimensions.x; i++)
	{
		for (size_t j = 0; j < Dimensions.y; j++)
		{
			std::cout << Input[i][j];
			if (validSymbol(Input[i][j]))
			{
				AddNode(Coordinates{ i,j }, string{ Input[i][j] });
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

