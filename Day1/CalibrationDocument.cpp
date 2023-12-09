#include "CalibrationDocument.h"
#include <numeric>
#include <algorithm>
#include <cassert>
#include <cctype>

std::vector<string> CalibrationDocument::spelledOutNumbers = { "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };


int CalibrationDocument::SumCalibrationValues()
{
	std::vector<int> codes;
	std::for_each(lines.cbegin(), lines.cend(), 
		[&codes](const string& line) { codes.push_back(CalibrationDocument::GetTwoDigitNumber(line)); });


	for (size_t lineCount = 0; lineCount < lines.size(); lineCount++)
	{
		std::cout << lines[lineCount] << " " << codes[lineCount] << std::endl;
	}

	return std::accumulate(codes.cbegin(), codes.cend(), 0);
}


char CalibrationDocument::ExtractFirstDigit(string line)
{
	char digit{};

	auto foundFirstDigit = std::find_if(line.cbegin(), line.cend(), [](unsigned char c){ return std::isdigit(c); });
	if (foundFirstDigit != line.cend())
	{
		digit = *foundFirstDigit;
	}

	string::size_type firstNumberOccurrence = string::npos;
	size_t firstNumberIndex{};

	// naive implementation ; should probably use std::search, std::boyer_moore_searcher
	// or an FDA to do faster substring parsing
	for (size_t numberIndex = 0; numberIndex < spelledOutNumbers.size(); numberIndex++)
	{
		string number = spelledOutNumbers[numberIndex];
		size_t numberLength = number.length();
		auto first = line.find(number);
		if (first < string::npos && first < firstNumberOccurrence)
		{
			firstNumberOccurrence = first;
			firstNumberIndex = numberIndex;
		}
	}
	if (firstNumberOccurrence < string::npos && 
		firstNumberOccurrence < std::distance(line.cbegin(), foundFirstDigit))
	{
		digit = std::to_string(firstNumberIndex + 1).front();
	}
	return digit;
}

char CalibrationDocument::ExtractLastDigit(string line)
{
	char digit{};
	auto foundLastDigit = std::find_if(line.crbegin(), line.crend(), [](unsigned char c){ return std::isdigit(c); });
	if (foundLastDigit != line.crend())
	{
		digit = *foundLastDigit;
	}

	string::size_type lastNumberOccurrence = string::npos;
	size_t lastNumberIndex{};

	for (size_t numberIndex = 0; numberIndex < spelledOutNumbers.size(); numberIndex++)
	{
		string number = spelledOutNumbers[numberIndex];
		auto last = line.rfind(number);
		if (last != string::npos && (lastNumberOccurrence == string::npos || last > lastNumberOccurrence))
		{
			lastNumberOccurrence = last;
			lastNumberIndex = numberIndex;
		}
	}
	size_t distance = std::distance(line.crbegin(), foundLastDigit);
	string::size_type lastDigitOccurrence = line.size() - distance;
	if (lastNumberOccurrence < string::npos &&
		lastNumberOccurrence >= lastDigitOccurrence)
	{
		digit = std::to_string(lastNumberIndex + 1).front();
	}
	return digit;
}


int CalibrationDocument::GetTwoDigitNumber(string line)
{
	char firstDigit = ExtractFirstDigit(line);
	char secondDigit = ExtractLastDigit(line);
	string twoDigitString{ firstDigit };
	twoDigitString += secondDigit;

	int twoDigitNumber{};
	try 
	{
		twoDigitNumber = std::stoi(twoDigitString);
	}
	catch (std::invalid_argument const& ex)
	{
		std::cout << "std::invalid_argument::what(): " << ex.what() << '\n';
	}
	catch (std::out_of_range const& ex)
	{
		std::cout << "std::out_of_range::what(): " << ex.what() << '\n';
	}
	
	//std::cout << line << " --> " << twoDigitNumber << std::endl;
	return twoDigitNumber;
}
