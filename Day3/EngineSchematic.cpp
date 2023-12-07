#include "EngineSchematic.h"

EngineSchematic::EngineSchematic(string filename) : InputLoader(filename)
{
	EngineGraph.Construct(lines, 
		[](const char& a) { return a != '.';  },
		[](const char& a, const char& b) { return std::isdigit(a) && std::isdigit(b); }
	);


}
