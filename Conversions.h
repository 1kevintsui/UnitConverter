#pragma once

#include <array>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

#define ERROR "Error"

using std::string;
using std::array;
using std::map;
using std::find;
using std::vector;



class Conversions {
private:
	//Metric Constants
	array<string, 8> const METRIC_PREFIX = 
	{ "T", "G", "M", "k", "h", "c", "m", "u"};
	//gram
	//meter
	//litre
	array<string, 3> const DEFAULT_SINGLE_METRIC_UNITS =
	{ "g", "m", "l"};

	//Stupid Imperial Units
	array<string, 3> const IMPERIAL_UNITS_LENGTH = { "in", "ft", "yd" };
	array<string, 2> const IMPERIAL_UNITS_MASS = { "oz", "lb" };

	map<string, long double> const LENGTH_CONVERSION_BRIDGE = {
		{"mm_in", (1 / 25.4)},
		{"in_mm", 25.4}
	};

	/*https://www.metric-conversions.org/weight/pounds-to-kilograms.htm
	*/
	map<string, long double> const MASS_CONVERSION_BRIDGE = {
		{"g_lb", (1/ 453.59237)},
		{"lb_g", 453.59237}
	};

	map<string, double> const IMPERIAL_UNITS_LENGTH_CONVERSIONS = {
		{"in_ft", 12.0},
		{"in_yd", 36.0},
		{"ft_in", (1.0 / 12.0)},
		{"yd_in", (1.0 / 36.0)}
	};

	map<string, double> const IMPERIAL_UNITS_MASS_CONVERSIONS = {
		{"oz_lb", 16.0},
		{"lb_oz", 1/16.0},
	};

	map<string, double> const METRIC_PREFIX_FACTORS = {
		{"T", 1000000000000.0},
		{"G", 1000000000.0},
		{"M", 1000000.0},
		{"k", 1000.0},
		{"h", 100.0},
		{"c", (1.0 / 100.0)},
		{"m", (1.0 / 1000.0)},
		{"u", (1.0 / 1000000.0)},
	};

	string getBaseMetricUnit(string unit);
	
	bool isImperialUnit(string unit);
	bool isMetricToMetric(vector<string> user_input);
	bool isMetricAndImperial(vector<string> user_input);
	bool isImperialAndImperial(vector<string> user_input);

	double imperialToImperialFactor(vector<string> user_input);
	double imperialToImperialLengthFactor(vector<string> user_input);
	double imperialToImperialMassFactor(vector<string> user_input);

	double metricToMetricFactor(vector<string> user_input);

	double imperialAndMetricFactor(vector<string> user_input);
	double imperialAndMetricLengthFactor(vector<string> user_input);
	double imperialAndMetricMassFactor(vector<string> user_input);

public:
	string convert(vector<string> user_input);

};

