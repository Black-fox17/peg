#include <iostream>
#include <string>
#include "rational_calc.hpp"

//run with g++ -Wall -Wextra -pedantic -std=c++14 -o rational main.cpp rational.cpp rational_calc.cpp
int main(int argc, char* argv[]) {
    // Concept: Command Line Arguments
    // argc (argument count) holds the number of inputs passed to the program
    // argv (argument vector) holds the actual text of the inputs
    
    if (argc > 1) {
        std::string filename = argv[1];

        if (!process(filename)) {
            // Return non-zero to signal failure to the operating system
            return 1;
        }

    } else {
        // Concept: Interactive Mode (Standard Input)
        std::string line;

        while (std::getline(std::cin, line)) {
            if (line.empty()) continue; // Skip empty presses

            Rational result("0/1");  // placeholder result

            // Process the equation using our calculator helper
            if (calculate(line, result)) {
                std::cout << result.str() << std::endl;
            } else {
                // If the math or parsing is invalid
                std::cout << "invalid" << std::endl;
            }
        }
    }

    // Return 0 means the program ran without crashing
    return 0;
}