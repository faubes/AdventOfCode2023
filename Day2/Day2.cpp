// Day2.cpp : Source file for your target.
//

#include "Day2.h"
#include <algorithm>
#include <numeric>
#include <cassert>
//#include <strstream>
#include <sstream>




CubeGameRecords::CubeGameRecords(string filename) : InputLoader(filename)
{
	for (const auto& line : lines)
	{
		CubeGame game{};
		std::istringstream stream(line);
		string gametext;
		stream >> gametext;
		stream >> game.id;
		char colon;
		stream >> colon; // discarding
		
		string dataPointString{};
		if (getline(stream, dataPointString))
		{
			vector<string> splitGameInput{};
			splitGameInput = InputLoader::split(dataPointString, ";");
			
			for (auto gameInput : splitGameInput)
			{
				CubeGameDataPoint dataPoint(gameInput);
				game.dataPoints.push_back(dataPoint);
			}
		}
		
		games.push_back(game);
	}
}



CubeGameDataPoint::CubeGameDataPoint(string input)
{
	vector<string> splitDataInput = InputLoader::split(input, ",");
	for (auto dataInput : splitDataInput)
	{
		try
		{
			auto firstNumber = std::find_if(dataInput.begin(), dataInput.end(), [](unsigned char c){ return std::isdigit(c); });
			auto distance = std::distance(dataInput.begin(), firstNumber);
			int count = std::stoi(dataInput.substr(distance, distance+1));
			CubeColour colour = fromString(dataInput);
			CubeCount.insert(std::make_pair(colour, count));
		}
		catch (std::invalid_argument const& ex)
		{
			std::cout << "std::invalid_argument::what(): " << ex.what() << '\n';
		}
		catch (std::out_of_range const& ex)
		{
			std::cout << "std::out_of_range::what(): " << ex.what() << '\n';
		}
	}
}

CubeColour CubeGameDataPoint::fromString(string input)
{
	static vector<string> colours = { "red", "green", "blue" };

	for (CubeColour c = CubeColour::RED; c <= CubeColour::BLUE; c = CubeColour(size_t(c) + 1))
	{
		if (input.find(colours[size_t(c)]) != string::npos)
		{
			return c;
		}
	}
	assert(false);
	return CubeColour();
}

int32_t CubeGameDataPoint::CalculatePower(CubeCountMap CubeCount)
{
	int32_t result = 1;
	for (CubeColour c = CubeColour::RED; c <= CubeColour::BLUE; c = CubeColour(size_t(c) + 1))
	{
		auto search = CubeCount.find(c);
		if (search != CubeCount.end())
		{
			result *= search->second;
		}
	}
	return result;
}


bool CubeGame::isValid(uint32_t max_red, uint32_t max_green, uint32_t max_blue) const
{
	for (const auto& dataPoint : dataPoints)
	{
		auto search = dataPoint.CubeCount.find(CubeColour::RED);
		if (search != dataPoint.CubeCount.end() && search->second > max_red)
		{
			return false;
		}
		search = dataPoint.CubeCount.find(CubeColour::GREEN);
		if (search != dataPoint.CubeCount.end() && search->second > max_green)
		{
			return false;
		}
		search = dataPoint.CubeCount.find(CubeColour::BLUE);
		if (search != dataPoint.CubeCount.end() && search->second > max_blue)
		{
			return false;
		}
	}

	return true;
}

std::map<CubeColour, size_t> CubeGame::MinimumPossibleCubeCount() const
{
	std::map<CubeColour, size_t> minimumPossibleCount
	{
		{CubeColour::RED, 0},
		{CubeColour::GREEN, 0},
		{CubeColour::BLUE, 0},
	};

	for (const auto& dataPoint : dataPoints)
	{
		for (CubeColour c = CubeColour::RED; c <= CubeColour::BLUE; c = CubeColour(size_t(c) + 1))
		{
			auto search = dataPoint.CubeCount.find(c);
			if (search != dataPoint.CubeCount.end() && search->second > minimumPossibleCount[c])
			{
				minimumPossibleCount[c] = search->second;
			}
		}
	}

	return minimumPossibleCount;
}

size_t CubeGameRecords::CountValidGames() const
{
	size_t validCount = std::count_if(games.begin(), games.end(), [](const auto& game) { return game.isValid(12, 13, 14); });
	return validCount;
}

vector<size_t> CubeGameRecords::GetValidGameIds() const
{
	vector<size_t> result{};
	std::for_each(games.begin(), games.end(), [&result](const auto& game) 
	{
		if (game.isValid(12, 13, 14))
		{
			result.push_back(game.id);
		}
	});
	return result;
}

size_t CubeGameRecords::GetSumOfValidGameIds() const
{
	auto validGameIds = GetValidGameIds();
	return std::accumulate(validGameIds.begin(), validGameIds.end(), 0);
}

int64_t CubeGameRecords::CalculatePowerOfMinimumSets() const
{
	vector<CubeCountMap> minimumCubeCounts{};
	std::for_each(games.begin(), games.end(), [&minimumCubeCounts](const auto& game)
	{
		minimumCubeCounts.push_back(game.MinimumPossibleCubeCount());
	});

	vector<int32_t> cubeCountProducts{};
	std::for_each(minimumCubeCounts.begin(), minimumCubeCounts.end(), [&cubeCountProducts](const auto& CubeCountMap)
	{
		cubeCountProducts.push_back(CubeGameDataPoint::CalculatePower(CubeCountMap));
	});

	int64_t sum = std::accumulate(cubeCountProducts.begin(), cubeCountProducts.end(), 0);
	return sum;
}

int main()
{
	//CubeGameRecords gameRecords("test_input.txt");
	CubeGameRecords gameRecords("input.txt");
	std::cout << "There are " << gameRecords.CountValidGames() << " valid games" << std::endl;
	std::cout << "The sum of ids is " << gameRecords.GetSumOfValidGameIds() << std::endl;
	std::cout << "The power of minimum sets is " << gameRecords.CalculatePowerOfMinimumSets() << std::endl;
	return 0;
}

