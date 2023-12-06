#pragma once
#include <functional>

#include "GridGraph.h"
#include "Utilities.h"

class EngineSchematic : public InputLoader
{
	GridGraph EngineGraph;

	friend ostream& operator<<(ostream& out, const EngineSchematic& schematic)
	{
		return out << schematic.EngineGraph;
	}

public:
	EngineSchematic(string filename);

	int32_t SumOfPartNumbers() const;
};
