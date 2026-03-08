#include <iostream>
#include <string>
#include <exception>
#include "rational_calc.h"

int main(int argc, char* argv[]) {

    if (argc > 1) {
        std::string filename = argv[1];
        try {
            if (!process(filename)) {
                return 1;
            }
        } catch (const std::exception& e) {
            std::cerr << "Exception occurred while processing file: " << e.what() << std::endl;
            return 1;
        }
    } else {
 
        std::string line;
        
        while (std::getline(std::cin, line)) {
            if (line.empty()) continue; 
            
            try {
                Rational result = calculate(line);
                std::cout << result.str() << std::endl;
            } catch (const std::exception& e) {
                std::cout << "invalid" << std::endl;
            }
        }
    }
    
    return 0;
}