#ifndef RATIONAL_H
#define RATIONAL_H

#include <string>

// A class defines a new data type. Think of it as a blueprint for creating objects.
// Our class represents a rational number (a fraction).
class Rational {
public: // Public members are accessible from outside the class (e.g., from main.cpp).
    /* Constructors are special functions used to initialize a new object when it's created. */
    
    // Default constructor: Initializes with default values (0/1).
    Rational();
    
    // Parameterized constructors: Allow setting specific values upon creation.
    Rational(int num, int den);
    Rational(int num); // Assumes denominator is 1
    Rational(std::string str); // Parses a string like "-34/2"
    Rational(double d); // Optional: accepts a double

    /* Accessors (Getters): Functions that just read data and don't modify the object.
       We mark them with 'const' at the end to promise the compiler we won't change data members here. */
    int num() const;
    int den() const;
    std::string str() const;

    // Functions answering true/false questions about our number.
    bool is_pos() const;
    bool is_neg() const;
    bool is_inf() const;
    bool is_nan() const;

    /* Modifiers (Setters): Functions that change the internal state of the object. */
    void set(int num, int den);
    void str(std::string s);

    /* Mathematical Operations */
    // These functions take another Rational number as input and return a new Rational number as the result.
    // They are marked 'const' because arithmetic shouldn't change the original number.
    Rational add(Rational other) const;
    Rational sub(Rational other) const;
    Rational mul(Rational other) const;
    Rational div(Rational other) const;
    Rational pow(int n) const;
    Rational sqrt() const;

private: // Private members are hidden from the outside. Only functions inside this class can access them.
    int num_; // Stores the numerator
    int den_; // Stores the denominator

    // A helper function to find the Greatest Common Divisor.
    // Making it private means users of our class don't need to worry about it.
    int gcd(int a, int b) const; 
    
    // A helper function to reduce fractions to their simplest form.
    void simplify();
};

#endif // RATIONAL_H
