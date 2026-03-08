#include "rational_calc.hpp"
#include <iostream>
#include <sstream>
#include <fstream>

// Calculate takes the raw text expression and processes the mathematics
bool calculate(std::string expression, Rational &result) {
    std::istringstream iss(expression);
    std::string first_token;

    if (!(iss >> first_token)) {
        return false; // empty expression
    }

    // Case 1: Square root format (e.g. "sqrt 144/9")
    if (first_token == "sqrt") {
        std::string num_str;
        if (iss >> num_str) {
            Rational r(num_str);
            result = r.sqrt();
            return true;
        } else {
            return false; // missing number
        }
    }

    // Case 2: Arithmetic expression format
    std::string op, second_token;

    Rational r1(first_token);

    if (iss >> op >> second_token) {

        if (op == "+") {
            Rational r2(second_token);
            result = r1.add(r2);
            return true;

        } else if (op == "-") {
            Rational r2(second_token);
            result = r1.sub(r2);
            return true;

        } else if (op == "*") {
            Rational r2(second_token);
            result = r1.mul(r2);
            return true;

        } else if (op == "/") {
            Rational r2(second_token);
            result = r1.div(r2);
            return true;

        } else if (op == "^") {

            std::istringstream exp_stream(second_token);
            int exp;

            if (!(exp_stream >> exp)) {
                return false; // invalid exponent
            }

            result = r1.pow(exp);
            return true;

        } else {
            return false; // unknown operator
        }
    }

    result = r1;
    return true;
}

// Concept: File Processing and I/O Streams
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

    std::ofstream outfile(out_filename);
    if (!outfile.is_open()) 
    {
        std::cerr << "Error: Cannot open output file " << out_filename << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(infile, line)) {
        if (line.empty()) continue;

        Rational result("0/1"); // placeholder

        if (calculate(line, result))
        {
            outfile << result.str() << "\n";
        } else {
            outfile << "invalid\n";
        }
    }

    infile.close();
    outfile.close();
    return true;
}