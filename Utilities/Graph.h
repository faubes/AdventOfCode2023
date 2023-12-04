#pragma once

#include <ostream>
#include <string>
#include <vector>
#include <map>

#include "Utilities.h"


using std::string;
using std::map;
using std::vector;
using std::ostream;


template<typename IdType, typename ValueType>
class Graph 
{
public:
	class Node 
	{
		IdType Id{};
		ValueType Value{};

	public:
		Node(IdType _Id, ValueType _Value) : Id(_Id), Value(_Value) {}

		bool operator<(const Node& other) const
		{
			return Id < other.Id;
		}
		friend ostream& operator<<(ostream& out, const Node& node)
		{
			out << "[" << node.Id << " : " << node.Value << "]";
			return out;
		}
	};

private:
	map<IdType, Node> NodeList{};
	map<Node, vector<Node>> AdjacencyList{};

public:

	Node& GetNode(IdType Id);
	bool ContainsNode(IdType Id);
	bool AddNode(IdType Id, ValueType Value);
	bool LinkNodes(Node First, Node Second);
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
	auto foundNode = NodeList.find(Id);
	if (foundNode != NodeList.end())
	{
		return false; // node already exists?
	}
	Node NewNode(Id, Value);
	NodeList.insert(std::make_pair(Id, NewNode));
	AdjacencyList.insert(std::make_pair(NewNode, std::vector<Node>{}));

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

	firstNode->second.push_back(Second);
	secondNode->second.push_back(First);
	return true;
}

template<typename IdType, typename ValueType>
auto Graph<IdType, ValueType>::GetNode(IdType Id) -> Node&
{
	auto foundNode = NodeList.find(Id);
	return foundNode->second;
}

template<typename IdType, typename ValueType>
inline bool Graph<IdType, ValueType>::ContainsNode(IdType Id)
{
	auto foundNode = NodeList.find(Id);
	return foudNode != NodeList.end();
}
