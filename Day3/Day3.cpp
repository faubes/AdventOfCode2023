// Day3.cpp : Source file for your target.
//

#include "Day3.h"

#include "EngineSchematic.h"

int main()
{
	//typedef Graph<size_t, string> StringGraph;
	//typedef StringGraph::Node Node;
	//StringGraph testGraph{};

	//testGraph.AddNode(1, "a");
	//testGraph.AddNode(2, "b");
	//Node& node1 = testGraph.GetNode(1);
	//Node& node2 = testGraph.GetNode(2);

	//testGraph.LinkNodes(node1, node2);
	 
	EngineSchematic TestSchematic = EngineSchematic("test_input.txt");

	std::cout << TestSchematic << std::endl;

	std::cout << TestSchematic.SumOfPartNumbers() << std::endl;
	return 0;
}
