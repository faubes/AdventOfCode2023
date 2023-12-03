#pragma once
#include "Utilities.h"

class CalibrationDocument : public InputLoader
{

public:
	CalibrationDocument(std::string filepath) : InputLoader(filepath) {}

	int SumCalibrationValues();

private:
	static char ExtractDigit(string line, bool bReverseDirection);

	static int GetTwoDigitNumber(string line);

};
