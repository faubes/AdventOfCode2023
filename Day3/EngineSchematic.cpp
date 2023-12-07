#include "EngineSchematic.h"

EngineSchematic::EngineSchematic(string filename) : InputLoader(filename)
{
	EngineGraph.Construct(lines, [](const char& a) { return a != '.';  });
}
