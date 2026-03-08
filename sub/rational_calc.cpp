#include "rational_calc.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdexcept>

Rational calculate(std::string expression) {
    // I use istringstream to easily extract parts separated by spaces
    std::istringstream iss(expression);
    std::string first_token;
    
    if (!(iss >> first_token)) {
        throw std::invalid_argument("Empty expression");
    }
    
    if (first_token == "sqrt") {
        std::string num_str;
        if (iss >> num_str) {
            Rational r(num_str);
            return r.sqrt();
        } else {
            throw std::invalid_argument("Missing number after sqrt");
        }
    }
    
    std::string op, second_token;
    
    Rational r1(first_token);
    
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
    
    return r1;
}

bool process(std::string filename) {
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cerr << "Error: Cannot open input file " << filename << std::endl;
        return false;
    }
    
   
    std::string out_filename = filename;
    size_t last_dot = out_filename.find_last_of(".");
    if (last_dot == std::string::npos) {
       
        out_filename += ".out";
    } else {
       
        out_filename = out_filename.substr(0, last_dot) + ".out";
    }
    
    // Open the new file to write to
    std::ofstream outfile(out_filename);
    if (!outfile.is_open()) {
        std::cerr << "Error: Cannot open output file " << out_filename << std::endl;
        return false;
    }
    
 
    std::string line;
    while (std::getline(infile, line)) {
        if (line.empty()) continue; // Skip blank lines
        
        try {
            Rational result = calculate(line);
            outfile << result.str() << "\n";
        } catch (const std::exception& e) {
            // In case of invalid algebraic inputs, write "invalid" and safely continue
            outfile << "invalid\n"; 
        }
    }
    
    
    infile.close();
    outfile.close();
    return true;
}