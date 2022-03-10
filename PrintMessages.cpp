#include "PrintMessages.h"

void printConversionResult(vector<string> user_input, string result) {
    if (result.compare(ERROR) == 0) {
        cout << "\n";
        cout << "Invalid units or entry format\n";
        cout << "\n";
    }
    else {
        cout << "\n";
        cout << "* ";
        cout << user_input[0];
        cout << " ";
        cout << user_input[1];
        cout << " ==> ";
        cout << result;
        cout << " ";
        cout << user_input[2];
        cout << '\n';
        cout << "\n";
    }
}

void printMathResult(vector<string> user_input, string result) {
    if (result.compare(ERROR) == 0) {
        cout << "\n";
        cout << "Can't do that =(\n";
        cout << "\n";
    }
    else {
        cout << "\n";
        cout << "* ";
        for (auto it = user_input.begin(); it != user_input.end(); ++it) {
            cout << *it;
        }
        cout << " = ";
        cout << result;
        cout << '\n';
        cout << "\n";
    }
}

void printOpeningMessage() {
    cout << "A utility to do everyday unit conversions with a built in calculator.\n";
    cout << "Basic commands:\n";
    cout << "-h or help             Open help menu\n";
    cout << "clear or cls           Clear terminal\n";
    cout << "q, Q, quit, QUIT       Quit this program\n\n";
    cout << std::flush;
}

void printHelpMenu() {
    cout << "To convert units:\n";
    cout << "## unit_type1 unit_type2\n";
    cout << "i.e. \"12 in ft\" will output 1.000000 ft";
    cout << "\n\n";
    cout << "To use calculator, basic math operations are supported (+, -, *, /, ^):\n";
    cout << "Supports multiple in line operations. Separate each input with a space:\n";
    cout << "i.e. \"5 + 2 * (6 / 2) ^ 2\" will output 23.000000";
    cout << "\n\n";
    cout << std::flush;
}