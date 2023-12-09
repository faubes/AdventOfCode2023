#include "EngineSchematic.h"

#include <numeric>
#include <set>

using std::set; 


EngineSchematic::EngineSchematic(string filename) : InputLoader(filename)
{
	EngineGraph.Construct(lines, [](const char& a) { return a != '.';  });


/*
	vector<pair<GridGraph::Node, GridGraph::Node>> NodesToMerge;
	for (auto& elem : EngineGraph.AdjacencyList)
	{
		Coordinates currentCoordinates = elem.first.Id;
		auto nextCoordinate = Coordinates{ currentCoordinates.x, currentCoordinates.y + 1 };
		if (nextCoordinate.y >= EngineGraph.Dimensions.y)
		{
			continue;
		}
		auto nextNodeIt = EngineGraph.GetNode(nextCoordinate);
		if (nextNodeIt == EngineGraph.AdjacencyList.end())
		{
			continue;
		}
		auto nextNode = nextNodeIt->first;
		if (std::isdigit(nextNode.Value[0]))
		{
			NodesToMerge.push_back(std::make_pair(elem.first, nextNode));
		}
	}
	
	for (auto it = NodesToMerge.rbegin(); it < NodesToMerge.rend(); it++)
	{
		EngineGraph.MergeNodes(it->first, it->second);
	}
*/
}

int32_t EngineSchematic::SumOfPartNumbers() const
{
	vector<pair<GridGraph::Node, vector<GridGraph::Node>>> symbolNodes;
	std::for_each(EngineGraph.AdjacencyList.begin(), EngineGraph.AdjacencyList.end(), 
		[&symbolNodes](auto& elem)
	{
		if (!std::isdigit(elem.first.Value[0]))
		{
			symbolNodes.push_back(elem);
		}
	});

	set<GridGraph::Node> partNodes;
	std::for_each(symbolNodes.begin(), symbolNodes.end(),
		[&partNodes, this](auto& elem)
	{
		for (const auto& neighbour : elem.second)
		{
			partNodes.insert(neighbour);
		}
	});

	vector<int32_t> partNumbers;
	std::for_each(partNodes.begin(), partNodes.end(),
		[&partNumbers](auto& node)
	{
		int32_t partNumber{};
		try
		{
			partNumber = std::stoi(node.Value);
			partNumbers.push_back(partNumber);
		}
		catch (std::invalid_argument const& ex)
		{
			std::cout << "std::invalid_argument::what(): " << ex.what() << '\n';
		}
		catch (std::out_of_range const& ex)
		{
			std::cout << "std::out_of_range::what(): " << ex.what() << '\n';
		}
	});

	return std::accumulate(partNumbers.begin(), partNumbers.end(), 0);
}
