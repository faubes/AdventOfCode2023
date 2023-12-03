// Utilites.cpp : Source file for your target.
//

#include "Utilities.h"

InputLoader::InputLoader(std::string filepath) 
{
	ifstream inputFile = ifstream(filepath);
	if (!inputFile)
	{
		std::cout << "Failed to load input: " << filepath << std::endl;
		return;
	}
	inputFile >> *this;
	inputFile.close();
}

std::istream& operator>>(std::istream& in, InputLoader& loader)
{
	std::string line;
	while (in >> line)
	{
		if (line.empty())
		{
			break; // input divided by empty line
		}
		loader.lines.push_back(line);
	}
	return in;
}