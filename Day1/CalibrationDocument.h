#pragma once
#include "Utilities.h"

class CalibrationDocument : public InputLoader
{

public:
	CalibrationDocument(std::string filepath) : InputLoader(filepath) {}

	static std::vector<string> spelledOutNumbers;

	int SumCalibrationValues();

private:
	static char ExtractFirstDigit(string line);
	static char ExtractLastDigit(string line);
	static int GetTwoDigitNumber(string line);

};
