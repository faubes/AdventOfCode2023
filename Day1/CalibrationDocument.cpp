#include "CalibrationDocument.h"
#include <numeric>
#include <algorithm>

int CalibrationDocument::SumCalibrationValues()
{
	std::vector<int> codes;
	std::for_each(lines.cbegin(), lines.cend(), [&codes](const string& line) { codes.push_back(CalibrationDocument::GetTwoDigitNumber(line)); });
	return std::accumulate(codes.cbegin(), codes.cend(), 0);
}


char CalibrationDocument::ExtractDigit(string line, bool bReverseDirection)
{
	char digit{};
	// awkward but iterator & reverse_iterator are different types soooo
	if (bReverseDirection)
	{
		auto result = std::find_if(line.crbegin(), line.crend(), std::isdigit);
		if (result != line.crend())
		{
			digit = *result;
		}
	}
	else
	{
		auto result = std::find_if(line.cbegin(), line.cend(), std::isdigit);
		if (result != line.cend())
		{
			digit = *result;
		}
	}
	return digit;
}

int CalibrationDocument::GetTwoDigitNumber(string line)
{
	char firstDigit = ExtractDigit(line, false);
	char secondDigit = ExtractDigit(line, true);
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
	return twoDigitNumber;
}
