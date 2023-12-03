// Day2.h : Header file for your target.

#pragma once

#include "Utilities.h"
#include <map>


enum class CubeColour : int8_t
{
	RED,
	GREEN,
	BLUE,
};

typedef std::map<CubeColour, size_t> CubeCountMap;
struct CubeGameDataPoint
{

	CubeCountMap CubeCount;
	string input;

	CubeGameDataPoint(string input);
	static CubeColour fromString(string input);

	static int32_t CalculatePower(CubeCountMap CubeCount);
};


struct CubeGame
{
	size_t id = 0;
	std::vector<CubeGameDataPoint> dataPoints;

	bool isValid(uint32_t max_red, uint32_t max_green, uint32_t max_blue) const;
	CubeCountMap MinimumPossibleCubeCount() const;
};

class CubeGameRecords : public InputLoader
{

	std::vector<CubeGame> games;

public:
	CubeGameRecords(string filename);

	size_t CountValidGames() const;

	vector<size_t> GetValidGameIds() const;

	size_t GetSumOfValidGameIds() const;

	int64_t CalculatePowerOfMinimumSets() const;
};