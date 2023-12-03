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
	while (getline(in, line))
	{
		if (line.empty())
		{
			break; // input divided by empty line
		}
		loader.lines.push_back(line);
	}
	return in;
}

vector<string> InputLoader::split(string input, string delimiters)
{
	vector<string> result{};
	string::size_type offset = 0;
	string::size_type findPosition = string::npos;
	while ((findPosition = input.find_first_of(delimiters, offset)) && findPosition != string::npos)
	{
		result.push_back(input.substr(offset, findPosition - offset));
		offset = findPosition + 1;
	}
	result.push_back(input.substr(offset, findPosition));
	return result;
}
