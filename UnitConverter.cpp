// UnitConverter.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif // _WIN32

#include <algorithm>
#include <array>
#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <vector>
#include "Conversions.h"
#include "Calculator.h"
#include "PrintMessages.h"

const std::array<std::string, 5> MATH_OPS = { "*", "/", "+", "-", "^"};

std::vector<std::string> parseStringToVector(std::string user_input) {
    std::vector<std::string> result;
    std::stringstream stringStream(user_input);
    std::string parsedInput;
    while (stringStream >> parsedInput) {
        result.push_back(parsedInput);
    }

    return result;
}

int main()
{
    printOpeningMessage();
    auto lineNumbers = 1;
    auto conversion = Conversions();
    auto calculator = Calculator();
    auto keepLooping = true;

    string result = "";
    string lastResult = "";
    auto userResult = false;
    auto doMath = false;

    std::string userString;
    std::vector<std::string> userStringVector;

    while (keepLooping) {
        doMath = false;
        std::cout << lineNumbers;
        std::cout << "> ";
        std::getline(std::cin, userString);
        userStringVector = parseStringToVector(userString);

        //quit when user prompts
        if (userStringVector[0].compare("q") == 0 ||
            userStringVector[0].compare("Q") == 0 ||
            userStringVector[0].compare("quit") == 0 ||
            userStringVector[0].compare("QUIT") == 0){
            break;
        }
        if (userStringVector[0].compare("clear") == 0 ||
            userStringVector[0].compare("cls") == 0) {
            system(CLEAR);
            continue;
        }
        if (userStringVector[0].compare("-h") == 0 ||
            userStringVector[0].compare("help") == 0) {
            printHelpMenu();
            continue;
        }

        //logic to determine if we should reuse last result or use all new input
        try {
            if (userStringVector[0].compare("(") != 0) {
                std::stod(userStringVector[0]);
            }
        }
        catch (const std::invalid_argument) {
            if (userResult) {
                auto tempData = userStringVector;
                userStringVector.clear();
                userStringVector.push_back(lastResult);
                for (auto it = tempData.begin(); it != tempData.end(); ++it) {
                    userStringVector.push_back(*it);
                }
            }
        }

        for (auto it = userStringVector.begin(); it != userStringVector.end(); ++it) {
            if (std::find(MATH_OPS.begin(), MATH_OPS.end(), *it) != MATH_OPS.end()) {
                doMath = true;
                break;
            }
        }

        if (doMath) {
            result = calculator.calculate(userStringVector);
            userResult = false;
            if (lastResult != ERROR) {
                lastResult = result;
                userResult = true;
            }
            printMathResult(userStringVector, result);
        } 
        else {
            result = conversion.convert(userStringVector);
            userResult = false;
            if (lastResult != ERROR) {
                lastResult = result;
                userResult = true;
            }
            printConversionResult(userStringVector, result);
        }
        lineNumbers++;
    }
    return 0;
}

