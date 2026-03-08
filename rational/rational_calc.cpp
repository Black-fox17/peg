#include "rational_calc.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdexcept>

// Calculate takes the raw text expression and processes the mathematics
Rational calculate(std::string expression) {
    // We use istringstream to easily extract parts separated by spaces
    std::istringstream iss(expression);
    std::string first_token;
    
    if (!(iss >> first_token)) {
        throw std::invalid_argument("Empty expression");
    }
    
    // Case 1: Square root format (e.g. "sqrt 144/9")
    if (first_token == "sqrt") {
        std::string num_str;
        if (iss >> num_str) {
            Rational r(num_str);
            return r.sqrt();
        } else {
            throw std::invalid_argument("Missing number after sqrt");
        }
    }
    
    // Case 2: Arithmetic expression format (e.g. "3/4 + 67/-3")
    std::string op, second_token;
    
    // Extract the first number
    Rational r1(first_token);
    
    // Try to extract an operator and the second number
    if (iss >> op >> second_token) {
        if (op == "+") {
            Rational r2(second_token);
            return r1.add(r2);
        } else if (op == "-") {
            Rational r2(second_token);
            return r1.sub(r2);
        } else if (op == "*") {
            Rational r2(second_token);
            return r1.mul(r2);
        } else if (op == "/") {
            Rational r2(second_token);
            return r1.div(r2);
        } else if (op == "^") {
            // Exponent uses an integer representation
            try {
                int exp = std::stoi(second_token);
                return r1.pow(exp);
            } catch (...) {
                throw std::invalid_argument("Invalid exponent given");
            }
        } else {
            throw std::invalid_argument(std::string("Unknown operator: ") + op);
        }
    }
    
    // If we only have one token with no operator (e.g. valid inputs with just a number)
    return r1;
}

// Concept: File Processing and I/O Streams
bool process(std::string filename) {
    // Open the incoming file to read from
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cerr << "Error: Cannot open input file " << filename << std::endl;
        return false;
    }
    
    // Concept: String Formatting & Extraction 
    // Construct our output file name by changing ".in" into ".out"
    std::string out_filename = filename;
    size_t last_dot = out_filename.find_last_of(".");
    if (last_dot == std::string::npos) {
        // No dot found, just append .out
        out_filename += ".out";
    } else {
        // Replace extension with .out
        out_filename = out_filename.substr(0, last_dot) + ".out";
    }
    
    // Open the new file to write to
    std::ofstream outfile(out_filename);
    if (!outfile.is_open()) {
        std::cerr << "Error: Cannot open output file " << out_filename << std::endl;
        return false;
    }
    
    // Read the file line by line
    std::string line;
    while (std::getline(infile, line)) {
        if (line.empty()) continue; // Skip blank lines
        
        try {
            // Concept: Exception Handling using Try/Catch Blocks
            Rational result = calculate(line);
            outfile << result.str() << "\n";
        } catch (const std::exception& e) {
            // In case of invalid algebraic inputs, write "invalid" and safely continue
            outfile << "invalid\n"; 
        }
    }
    
    // Good practice: Always safely close your files!
    infile.close();
    outfile.close();
    return true;
}
