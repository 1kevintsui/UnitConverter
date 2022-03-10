#pragma once
#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;
using std::cout;

#define ERROR "Error"

void printConversionResult(vector<string> user_input, string result);
void printMathResult(vector<string> user_input, string result);

void printOpeningMessage();
void printHelpMenu();