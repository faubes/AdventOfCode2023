// Utilites.h : Header file for your target.

#pragma once

#include <iostream>
#include <iterator>
#include <fstream>
#include <string>
#include <vector>

using std::istream;
using std::ifstream;
using std::string;
using std::vector;


struct InputLoader
{

	InputLoader(string filepath);

	friend istream& operator>>(istream& in, InputLoader& loader);

public:
	vector<string> lines;
};