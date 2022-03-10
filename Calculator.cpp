#include "Calculator.h"

#include <cmath>

//TODO support multiparenthesis operations

void Calculator::doExponents(vector<string>& user_input) {
	double first = std::stod(user_input[0]);
	double second = std::stod(user_input[2]);
	double result = pow(first, second);
	string resultString = std::to_string(result);
	user_input[0] = resultString;
	user_input.pop_back();
	user_input.pop_back();
}

void Calculator::doMultOrDivis(vector<string>& user_input) {
	double first = std::stod(user_input[0]);
	double second = std::stod(user_input[2]);
	double result;
	if (user_input[1].compare("/") == 0) {
		result = first / second;
	}
	else {
		result = first * second;
	}
	string resultString = std::to_string(result);
	user_input[0] = resultString;
	user_input.pop_back();
	user_input.pop_back();
}

void Calculator::doAddOrSubtract(vector<string>& user_input) {
	double first = std::stod(user_input[0]);
	double second = std::stod(user_input[2]);
	double result;
	if (user_input[1].compare("-") == 0) {
		result = first - second;
	}
	else {
		result = first + second;
	}
	string resultString = std::to_string(result);
	user_input[0] = resultString;
	user_input.pop_back();
	user_input.pop_back();
}

size_t Calculator::vectorPositionFinder(vector<string> user_input, string searchItem) {
	size_t pos = 0;
	for (auto it = user_input.begin(); it != user_input.end(); ++it) {
		if ((*it).compare(searchItem) == 0) {
			break;
		}
		pos++;
	}

	return pos;
}

vector<string> Calculator::extractSubVector(vector<string> user_input, size_t position) {
	vector<string> temp;
	temp.push_back(*(user_input.begin() + position - 1));
	temp.push_back(*(user_input.begin() + position));
	temp.push_back(*(user_input.begin() + position + 1));

	return temp;
}

bool Calculator::validInput(vector<string> user_input) {
	bool result = false;
	size_t countMathSymbols = 0;
	size_t countParenthesis = 0;
	for (auto it = user_input.begin(); it != user_input.end(); ++it) {
		if (find(MATH_OPS.begin(), MATH_OPS.end(), *it) != MATH_OPS.end()) {
			countMathSymbols++;
		}
		if ((*it).compare("(") == 0) {
			countParenthesis++;
		}
		if ((*it).compare(")") == 0) {
			countParenthesis++;
		}
	}
	size_t inputSizeNumbersOnly = user_input.size() - countParenthesis - countMathSymbols;
	result = (inputSizeNumbersOnly - countMathSymbols) == 1;

	return result;
}

string Calculator::calculate(const vector<string> user_input) {
	if (!validInput(user_input)) {
		return ERROR;
	}
	vector<string> modifiableInput = user_input;
	string result = "";
	while (modifiableInput.size() > 1) {
		//solve for all operations inside parenthesis operations if exists
		while (find(modifiableInput.begin(), modifiableInput.end(), "(") != modifiableInput.end()) {

			vector<string> parenthVector;
			size_t openingParenth = 0;
			size_t endingParenth = 0;
			size_t pos = 0;

			for (auto it = modifiableInput.begin(); it != modifiableInput.end(); ++it) {
				if ((*it).compare("(") == 0) {
					openingParenth = pos;
				}
				if ((*it).compare(")") == 0) {
					endingParenth = pos;
					break;					//adding break here finds first closing parenthesis
				}
				pos++;
			}

			//create sub vector to perform operations and trim the parenthesis
			if (openingParenth != endingParenth) {
				auto counter = openingParenth + 1;
				while (counter < endingParenth) {
					parenthVector.push_back(modifiableInput[counter]);
					counter++;
				}
				string parenthValue = calculate(parenthVector);
				//erase elements from original vector 
				auto beginningIterator = modifiableInput.begin() + openingParenth;
				modifiableInput[openingParenth] = parenthValue;
				modifiableInput.erase(beginningIterator + 1, modifiableInput.begin() + endingParenth + 1);
			}
		}

		// do all exponent functions first
		while (std::find(modifiableInput.begin(), modifiableInput.end(), "^") != modifiableInput.end()) {
			//extract subvector
			auto position = vectorPositionFinder(modifiableInput, "^");
			auto tempVector = extractSubVector(modifiableInput, position);
			doExponents(tempVector);

			//replace value with calculated value
			modifiableInput[position - 1] = tempVector[0];

			//erase sign and second number from original vector 
			auto symbolLocation = modifiableInput.begin() + position;
			modifiableInput.erase(symbolLocation, symbolLocation + 2);
		}

		// do all multiplication and division functions
		while (std::find(modifiableInput.begin(), modifiableInput.end(), "*") != modifiableInput.end()) {
			//extract subvector
			auto position = vectorPositionFinder(modifiableInput, "*");
			auto tempVector = extractSubVector(modifiableInput, position);
			doMultOrDivis(tempVector);

			//replace value with calculated value
			modifiableInput[position - 1] = tempVector[0];

			//erase sign and second number from original vector 
			auto symbolLocation = modifiableInput.begin() + position;
			modifiableInput.erase(symbolLocation, symbolLocation + 2);
		}

		while (std::find(modifiableInput.begin(), modifiableInput.end(), "/") != modifiableInput.end()) {
			//extract subvector
			auto position = vectorPositionFinder(modifiableInput, "/");
			auto tempVector = extractSubVector(modifiableInput, position);
			doMultOrDivis(tempVector);

			//replace value with calculated value
			modifiableInput[position - 1] = tempVector[0];

			//erase sign and second number from original vector 
			auto symbolLocation = modifiableInput.begin() + position;
			modifiableInput.erase(symbolLocation, symbolLocation + 2);
		}

		// do all addition and subtraction functions
		while (std::find(modifiableInput.begin(), modifiableInput.end(), "+") != modifiableInput.end()) {
			//extract subvector
			auto position = vectorPositionFinder(modifiableInput, "+");
			auto tempVector = extractSubVector(modifiableInput, position);
			doAddOrSubtract(tempVector);

			//replace value with calculated value
			modifiableInput[position - 1] = tempVector[0];

			//erase sign and second number from original vector 
			auto symbolLocation = modifiableInput.begin() + position;
			modifiableInput.erase(symbolLocation, symbolLocation + 2);
		}

		while (std::find(modifiableInput.begin(), modifiableInput.end(), "-") != modifiableInput.end()) {
			//extract subvector
			auto position = vectorPositionFinder(modifiableInput, "-");
			auto tempVector = extractSubVector(modifiableInput, position);
			doAddOrSubtract(tempVector);

			//replace value with calculated value
			modifiableInput[position - 1] = tempVector[0];

			//erase sign and second number from original vector 
			auto symbolLocation = modifiableInput.begin() + position;
			modifiableInput.erase(symbolLocation, symbolLocation + 2);
		}
	}
	result = modifiableInput[0];

	return result;
}
