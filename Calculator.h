#pragma once
#include <string>
#include <map>
#include <vector>
#include <array>
#include <iterator>
#include <stdexcept>
#include <algorithm>

#define ERROR "Error"

using std::string;
using std::array;
using std::map;
using std::find;
using std::vector;

class Calculator {
private:
	//sorted based on order of operation. i.e. a symbol in position 1
	//is higher than position 3 etc.
	const array<string, 5> MATH_OPS = {"^", "*", "/", "+", "-" };

	void doExponents(vector<string>& user_input);
	void doMultOrDivis(vector<string>& user_input);
	void doAddOrSubtract(vector<string>& user_input);

	bool validInput(vector<string> user_input);

	size_t vectorPositionFinder(vector<string> user_input, string searchItem);

	vector<string> extractSubVector(vector<string> user_input, size_t position);
public:
	string calculate(const vector<string> user_input);
};