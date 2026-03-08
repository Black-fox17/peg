#include <iostream>
#include <string>
#include <exception>
#include "rational_calc.h"

//run with g++ -Wall -Wextra -pedantic -std=c++14 -o rational main.cpp rational.cpp rational_calc.cpp
int main(int argc, char* argv[]) {
    // Concept: Command Line Arguments
    // argc (argument count) holds the number of inputs passed to the program
    // argv (argument vector) holds the actual text of the inputs
    
    // If argc > 1, the user provided a file name (e.g., ./rational my_file.in)
    // The first argument argv[0] is usually the program's own name.
    if (argc > 1) {
        std::string filename = argv[1];
        try {
            if (!process(filename)) {
                // Return non-zero to signal failure to the operating system
                return 1;
            }
        } catch (const std::exception& e) {
            std::cerr << "Exception occurred while processing file: " << e.what() << std::endl;
            return 1;
        }
    } else {
        // Concept: Interactive Mode (Standard Input)
        // If no file was given, we accept expressions typed directly into the console
        std::string line;
        
        // This loop runs continuously, waiting for the user to type and press Enter
        while (std::getline(std::cin, line)) {
            if (line.empty()) continue; // Skip empty presses
            
            try {
                // Process the equation using our calculator helper
                Rational result = calculate(line);
                std::cout << result.str() << std::endl;
            } catch (const std::exception& e) {
                // If the math or parsing is invalid, catch it and write "invalid"
                std::cout << "invalid" << std::endl;
            }
        }
    }
    
    // Return 0 means the program ran without crashing
    return 0;
}
