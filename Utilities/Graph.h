#pragma once

#include <algorithm>
#include <ostream>
#include <string>
#include <vector>
#include <numeric>
#include <set>
#include <map>

#include "Utilities.h"


using std::string;
using std::map;
using std::vector;
using std::ostream;
using std::pair;

template<typename IdType, typename ValueType>
class Graph 
{
public:
	struct Node 
	{
		IdType Id{};
		ValueType Value{};

		Node(IdType _Id, ValueType _Value) : Id(_Id), Value(_Value) {}

		bool operator<(const Node& other) const
		{
			return Id < other.Id;
		}

		bool operator==(const Node& other) const
		{
			return Id == other.Id && Value == other.Value;
		}

		friend ostream& operator<<(ostream& out, const Node& node)
		{
			out << "[" << node.Id << " : " << node.Value << "]";
			return out;
		}
	};

	typedef Graph<IdType, ValueType>::Node NodeType;


public:

	map<Node, vector<Node>> AdjacencyList{};
	auto GetNode(IdType Id);
	bool ContainsNode(IdType Id) const;
	bool AddNode(IdType Id, ValueType Value);
	bool LinkNodes(Node First, Node Second);
	bool MergeNodes(Node First, Node Second);
	bool RemoveNode(IdType Id);

	friend ostream& operator<<(ostream& out, const Graph<IdType, ValueType>& g)
	{
		for (const auto& elem : g.AdjacencyList)
		{
			const Node& node = elem.first;
			out << node << "{ ";
			vector<Node> neighbours = elem.second;
			for (const Node& neighbour : neighbours)
			{
				out << neighbour;
			}
			out << " } " << std::endl;
		}
		return out;
	}
};



template<typename IdType, typename ValueType>
inline bool Graph<IdType, ValueType>::AddNode(IdType Id, ValueType Value)
{
	auto foundNode = std::find_if(AdjacencyList.begin(), AdjacencyList.end(), [&Id](const auto& elem) { return elem.first.Id == Id; });
	if (foundNode != std::end(AdjacencyList))
	{
		return false; // node already exists?
	}

	Node NewNode(Id, Value);
	AdjacencyList.insert(std::make_pair(NewNode, vector<Node>{}));
	return true;
}

template<typename IdType, typename ValueType>
inline bool Graph<IdType, ValueType>::LinkNodes(Node First, Node Second)
{
	auto firstNode = AdjacencyList.find(First);
	auto secondNode = AdjacencyList.find(Second);

	if (firstNode == AdjacencyList.end() || secondNode == AdjacencyList.end())
	{
		return false; // failed, don't have both nodes
	}
	vector<Node>& firstNodeAdjacencyList = firstNode->second;
	auto secondNodeAlreadyInFirstList = std::find(firstNodeAdjacencyList.begin(), firstNodeAdjacencyList.end(), secondNode->first);
	if (secondNodeAlreadyInFirstList == firstNodeAdjacencyList.end())
	{
		firstNodeAdjacencyList.push_back(Second);
	}
	
	vector<Node>& secondNodeAdjacencyList = secondNode->second;
	auto firstNodeAlreadyInSecondList = std::find(secondNodeAdjacencyList.begin(), secondNodeAdjacencyList.end(), firstNode->first);
	if (firstNodeAlreadyInSecondList == secondNodeAdjacencyList.end())
	{
		secondNodeAdjacencyList.push_back(First);
	}

	return true;
}

template<typename IdType, typename ValueType>
inline bool Graph<IdType, ValueType>::MergeNodes(Node First, Node Second)
{
	auto firstNode = AdjacencyList.find(First);
	auto secondNode = AdjacencyList.find(Second);

	if (firstNode == AdjacencyList.end() || secondNode == AdjacencyList.end())
	{
		return false; // failed, don't have both nodes
	}
	auto NewId = First.Id;
	auto NewValue = First.Value + Second.Value;
	
	vector<Node>& firstNodeAdjacencyList = firstNode->second;
	vector<Node>& secondNodeAdjacencyList = secondNode->second;
	vector<Node> mergedAdjacencyList{};
	std::set_union(firstNodeAdjacencyList.begin(), firstNodeAdjacencyList.end(), secondNodeAdjacencyList.begin(), secondNodeAdjacencyList.end(), std::back_inserter(mergedAdjacencyList));

	RemoveNode(First.Id);
	RemoveNode(Second.Id);

	AddNode(NewId, NewValue);
	auto NewNode = GetNode(NewId);

	for (auto& node : mergedAdjacencyList)
	{
		LinkNodes(NewNode->first, node);
	}
	return true;
}

template<typename IdType, typename ValueType>
inline bool Graph<IdType, ValueType>::RemoveNode(IdType Id)
{
	auto foundNode = std::find_if(AdjacencyList.begin(), AdjacencyList.end(), [&Id](const auto& elem) { return elem.first.Id == Id; });
	if (foundNode == AdjacencyList.end())
	{
		return false; // node not found?
	}

	const Node& nodeToRemove = foundNode->first;
	vector<Node>& neighbours = foundNode->second;
	for (auto& elem : neighbours)
	{
		auto neighbourNode = AdjacencyList.find(elem);
		if (neighbourNode != AdjacencyList.end())
		{
			std::remove(neighbourNode->second.begin(), neighbourNode->second.end(), nodeToRemove);
		}
	}
		
	AdjacencyList.erase(nodeToRemove);
	return true;
}


template<typename IdType, typename ValueType>
inline auto Graph<IdType, ValueType>::GetNode(IdType Id)
{
	auto foundNode = std::find_if(AdjacencyList.begin(), AdjacencyList.end(), [&Id](const auto& elem) { return elem.first.Id == Id; });
	return foundNode;
}

template<typename IdType, typename ValueType>
inline bool Graph<IdType, ValueType>::ContainsNode(IdType Id) const
{
	auto foundNode = std::find_if(AdjacencyList.begin(), AdjacencyList.end(), [&Id](const auto& elem) { return elem.first.Id == Id; });
	return foundNode != AdjacencyList.end();
}
