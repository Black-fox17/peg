#ifndef RATIONAL_CALC_H
#define RATIONAL_CALC_H

#include <string>
#include "rational.hpp"

// Concept: Free Functions
// These functions live outside of any specific class because they manage 
// operations between several objects or interact with strings/files directly.

// Takes an expression like "3/4 + 67/-3" and calculates the answer
bool calculate(std::string expression, Rational &result);

// Processes a text file containing one expression per line, evaluating 
// each and writing the result out to a new file.
bool process(std::string filename);

#endif // RATIONAL_CALC_H