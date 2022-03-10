#include "Conversions.h"
#include <iostream>
#include <vector>
string Conversions::getBaseMetricUnit(string unit)
{
	string baseUnit = unit.substr(1, string::npos);
	if (unit.length() == 1) {
		baseUnit = ERROR;
		if (find(DEFAULT_SINGLE_METRIC_UNITS.begin(), DEFAULT_SINGLE_METRIC_UNITS.end(), unit)
			!= DEFAULT_SINGLE_METRIC_UNITS.end()) {
			baseUnit = unit;
		}
	}
	else if (find(DEFAULT_SINGLE_METRIC_UNITS.begin(), DEFAULT_SINGLE_METRIC_UNITS.end(), baseUnit)
		== DEFAULT_SINGLE_METRIC_UNITS.end()) {
		baseUnit = ERROR;
	}

	return baseUnit;
}

bool Conversions::isImperialUnit(string unit)
{
	bool isLength = (find(IMPERIAL_UNITS_LENGTH.begin(), IMPERIAL_UNITS_LENGTH.end(), unit)
					!= IMPERIAL_UNITS_LENGTH.end());
	bool isWeight = (find(IMPERIAL_UNITS_MASS.begin(), IMPERIAL_UNITS_MASS.end(), unit)
					!= IMPERIAL_UNITS_MASS.end());

	return (isLength || isWeight);
}

bool Conversions::isMetricToMetric(vector<string> user_input)
{
	string firstUnitBase = getBaseMetricUnit(user_input[1]);
	string secondUnitBase = getBaseMetricUnit(user_input[2]);
	return (firstUnitBase.compare(secondUnitBase) == 0) && 
		(firstUnitBase.compare(ERROR) != 0) &&
		(secondUnitBase.compare(ERROR) != 0);
}

bool Conversions::isMetricAndImperial(vector<string> user_input) {
	bool firstIsImperial = isImperialUnit(user_input[1]);
	bool secondIsImperial = isImperialUnit(user_input[2]);
	bool firstIsMetric = (getBaseMetricUnit(user_input[1]).compare(ERROR) != 0);
	bool secondIsMetric = (getBaseMetricUnit(user_input[2]).compare(ERROR) != 0);

	return (firstIsMetric && secondIsImperial) || (firstIsImperial && secondIsMetric);
}

bool Conversions::isImperialAndImperial(vector<string> user_input) {
	return isImperialUnit(user_input[1]) && isImperialUnit(user_input[2]);
}


double Conversions::imperialToImperialLengthFactor(vector<string> user_input) {
	double factor = 1.0;
	string first_unit = user_input[1];
	string second_unit = user_input[2];
	if (first_unit.compare(second_unit) == 0) {
		return factor;
	}
	string key = first_unit + "_" + second_unit;
	try {
		factor = IMPERIAL_UNITS_LENGTH_CONVERSIONS.at(key);
	}
	catch(const std::out_of_range) {
		std::cout << "Unsupported units\n";
		factor = 1.0;
	}

	return factor;
}

double Conversions::imperialToImperialMassFactor(vector<string> user_input) {
	double factor = 1.0;
	string first_unit = user_input[1];
	string second_unit = user_input[2];
	if (first_unit.compare(second_unit) == 0) {
		return factor;
	}
	string key = first_unit + "_" + second_unit;
	try {
		factor = IMPERIAL_UNITS_MASS_CONVERSIONS.at(key);
	}
	catch (const std::out_of_range) {
		std::cout << "Unsupported units\n";
		factor = 1.0;
	}

	return factor;
}

double Conversions::imperialToImperialFactor(vector<string> user_input) {
	double firstFactor = 1.0;
	double secondFactor = 1.0;
	bool isLength = false;
	bool isMass = false;
	//check if this is converting length
	if (find(IMPERIAL_UNITS_LENGTH.begin(),
		IMPERIAL_UNITS_LENGTH.end(),
		user_input[1])
		!= IMPERIAL_UNITS_LENGTH.end()) {
		if (find(IMPERIAL_UNITS_LENGTH.begin(),
			IMPERIAL_UNITS_LENGTH.end(),
			user_input[2])
			!= IMPERIAL_UNITS_LENGTH.end()) {
			isLength = true;
		}
	}

	//check if this is converting mass
	if (find(IMPERIAL_UNITS_MASS.begin(),
		IMPERIAL_UNITS_MASS.end(),
		user_input[1])
		!= IMPERIAL_UNITS_MASS.end()) {
		if (find(IMPERIAL_UNITS_MASS.begin(),
			IMPERIAL_UNITS_MASS.end(),
			user_input[2])
			!= IMPERIAL_UNITS_MASS.end()) {
			isMass = true;
		}
	}
	
	if (isLength) {
		vector<string> temp1 { "1","in", user_input[1] };
		vector<string> temp2 { "1", user_input[2], "in" };
		firstFactor = imperialToImperialLengthFactor(temp1);
		secondFactor = imperialToImperialLengthFactor(temp2);
		return firstFactor * secondFactor;
	}

	if (isMass) {
		vector<string> temp1{ "1","lb", user_input[1] };
		vector<string> temp2{ "1", user_input[2], "lb" };
		firstFactor = imperialToImperialMassFactor(temp1);
		secondFactor = imperialToImperialMassFactor(temp2);
		return firstFactor * secondFactor;
	}
	return 1.0;
}

double Conversions::metricToMetricFactor(vector<string> user_input)
{
	double first_factor = 1.0;
	double second_factor = 1.0;

	if (find(METRIC_PREFIX.begin(), METRIC_PREFIX.end(), user_input[1].substr(0,1))
		!= METRIC_PREFIX.end() && user_input[1].length() > 1) {
		first_factor = METRIC_PREFIX_FACTORS.at(user_input[1].substr(0, 1));
	}
	if (find(METRIC_PREFIX.begin(), METRIC_PREFIX.end(), user_input[2].substr(0,1))
		!= METRIC_PREFIX.end() && user_input[2].length() > 1) {
		second_factor = METRIC_PREFIX_FACTORS.at(user_input[2].substr(0, 1));
	}
	return first_factor / second_factor;
}

double Conversions::imperialAndMetricFactor(vector<string> user_input)
{
	bool firstIsImperialLength = find(IMPERIAL_UNITS_LENGTH.begin(),
		IMPERIAL_UNITS_LENGTH.end(), user_input[1])
		!= IMPERIAL_UNITS_LENGTH.end();

	bool secondIsImperialLength = find(IMPERIAL_UNITS_LENGTH.begin(),
		IMPERIAL_UNITS_LENGTH.end(), user_input[2])
		!= IMPERIAL_UNITS_LENGTH.end();

	bool firstIsImperialMass = find(IMPERIAL_UNITS_MASS.begin(),
		IMPERIAL_UNITS_MASS.end(), user_input[1])
		!= IMPERIAL_UNITS_MASS.end();

	bool secondIsImperialMass = find(IMPERIAL_UNITS_MASS.begin(),
		IMPERIAL_UNITS_MASS.end(), user_input[2])
		!= IMPERIAL_UNITS_MASS.end();

	if (firstIsImperialLength || secondIsImperialLength) {
		return imperialAndMetricLengthFactor(user_input);
	}
	else if (firstIsImperialMass || secondIsImperialMass) {
		return imperialAndMetricMassFactor(user_input);
	}
	return 1.0;
}

double Conversions::imperialAndMetricLengthFactor(vector<string> user_input) {
	double first_factor = 1.0;
	double second_factor = 1.0;
	if (isImperialUnit(user_input[1])) {
		std::vector<string> convertToBaseIn{ "1" , "in", user_input[1]};
		std::vector<string> convertToBaseMm{ "1" , user_input[2], "mm"};
		first_factor = imperialToImperialLengthFactor(convertToBaseIn);
		second_factor = metricToMetricFactor(convertToBaseMm);
		return LENGTH_CONVERSION_BRIDGE.at("in_mm") * first_factor / second_factor;
	}
	vector<string> convertToBaseIn{ "1" ,user_input[2], "in"};
	vector<string> convertToBaseMm{ "1" , user_input[1], "mm" };
	first_factor = metricToMetricFactor(convertToBaseMm);
	second_factor = imperialToImperialLengthFactor(convertToBaseIn);

	return LENGTH_CONVERSION_BRIDGE.at("mm_in") * first_factor * second_factor;
}

double Conversions::imperialAndMetricMassFactor(vector<string> user_input) {
	double first_factor = 1.0;
	double second_factor = 1.0;
	if (isImperialUnit(user_input[1])) {
		std::vector<string> convertToBaseLb{ "1" , "lb", user_input[1] };
		std::vector<string> convertToBaseG{ "1" , user_input[2], "g" };
		first_factor = imperialToImperialMassFactor(convertToBaseLb);
		second_factor = metricToMetricFactor(convertToBaseG);
		return MASS_CONVERSION_BRIDGE.at("lb_g") * first_factor / second_factor;
	}
	vector<string> convertToBaseLb{ "1" ,user_input[2], "lb" };
	vector<string> convertToBaseG{ "1" , user_input[1], "g" };
	first_factor = metricToMetricFactor(convertToBaseLb);
	second_factor = imperialToImperialMassFactor(convertToBaseG);

	return MASS_CONVERSION_BRIDGE.at("g_lb") * first_factor * second_factor;
}

string Conversions::convert(vector<string> user_input) {
	
	double conversionFactor = 1.0;
	double result = 0;
	string resultString = ERROR;
	bool converted = false;
	if (user_input.size() < 3) {
		return resultString;
	}
	if (isImperialAndImperial(user_input)) {
		conversionFactor = imperialToImperialFactor(user_input);
		converted = true;
	}
	else if (isMetricToMetric(user_input)) {
		conversionFactor = metricToMetricFactor(user_input);
		converted = true;
	}
	else if (isMetricAndImperial(user_input)) {
		conversionFactor = imperialAndMetricFactor(user_input);
		converted = true;
	}
	if (converted) {
		result = std::stod(user_input[0]) * conversionFactor;
		resultString = std::to_string(result);
	}

	return resultString;
}


