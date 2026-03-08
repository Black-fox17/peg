#include "rational.h"
#include <sstream>
#include <cmath>
#include <stdexcept>
#include <string>
#include <algorithm>

// Concept: Helper Functions
// Helper: Greatest Common Divisor using the Euclidean algorithm
// This is used to reduce our fractions (e.g., 4/8 becomes 1/2)
int Rational::gcd(int a, int b) const {
    a = std::abs(a);
    b = std::abs(b);
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Concept: Class Methods
// Helper to simplify the rational number (runs every time values change)
void Rational::simplify() {
    // Handling NaN (0/0)
    if (num_ == 0 && den_ == 0) {
        return; 
    }
    // Handling Infinity (n / 0). The sign of infinity depends on numerator.
    if (den_ == 0) {
        // Keep sign of numerator, make it 1 or -1 for consistency (e.g., 1/0 or -1/0)
        num_ = (num_ > 0) ? 1 : -1;
        return;
    }
    
    // Concept: Data normalization
    // Ensure the sign is only kept in the numerator. E.g. 5/-4 becomes -5/4
    if (den_ < 0) {
        num_ = -num_;
        den_ = -den_;
    }
    
    // Simplify using GCD. E.g. -4/8 becomes -1/2
    int div = gcd(num_, den_);
    if (div != 0) {
        num_ /= div;
        den_ /= div;
    }
}

// Concept: Constructors
// Default constructor: creates 0/1
Rational::Rational() : num_(0), den_(1) {}

// Parameterized constructor (two args)
Rational::Rational(int num, int den) : num_(num), den_(den) {
    simplify();
}

// Parameterized constructor (one arg)
Rational::Rational(int num) : num_(num), den_(1) {}

// Parameterized constructor (string)
// Concept: Object delegation (calling a member function from constructor)
Rational::Rational(std::string str) {
    this->str(str); // We can reuse the set-from-string modifier logic here
}


Rational::Rational(double d) {
    if (std::isnan(d)) {
        num_ = 0; den_ = 0;
    } else if (std::isinf(d)) {
        num_ = (d > 0) ? 1 : -1;
        den_ = 0;
    } else {
       
        double intPart;
        double fracPart = std::modf(std::abs(d), &intPart);
        int sign = (d < 0) ? -1 : 1;
        
        int denom = 1;
       
        while (std::abs(fracPart - std::round(fracPart)) > 1e-9 && denom <= 1000000) {
            fracPart *= 10;
            denom *= 10;
        }
        
        num_ = sign * (static_cast<int>(intPart) * denom + static_cast<int>(std::round(fracPart)));
        den_ = denom;
        simplify();
    }
}

// Concept: Accessors (Retrieving private data without changing it)
int Rational::num() const { return num_; }
int Rational::den() const { return den_; }

// Convert the number back into a string representation
std::string Rational::str() const {
    if (is_nan()) return "0/0 (NaN)";
    if (is_inf()) return (num_ > 0 ? "1/0 (+inf)" : "-1/0 (-inf)");
    
   
    std::ostringstream oss;
    oss << num_ << "/" << den_;
    return oss.str();
}

// Concept: Boolean logical checks
bool Rational::is_pos() const { return (!is_nan() && !is_inf() && num_ > 0) || (is_inf() && num_ > 0); }
bool Rational::is_neg() const { return (!is_nan() && !is_inf() && num_ < 0) || (is_inf() && num_ < 0); }
bool Rational::is_inf() const { return den_ == 0 && num_ != 0; }
bool Rational::is_nan() const { return den_ == 0 && num_ == 0; }


void Rational::set(int num, int den) {
    num_ = num;
    den_ = den;
    simplify();
}

void Rational::str(std::string s) {
    if (s.empty()) {
        num_ = 0; den_ = 1;
        return;
    }
    
    if (s.front() == '(' && s.back() == ')') {
        s = s.substr(1, s.length() - 2);
    }
    
    std::istringstream iss(s);
    char slash;
    int numerator, denominator;
    
 
    if (iss >> numerator >> slash >> denominator && slash == '/') {
        num_ = numerator;
        den_ = denominator;
    } else {
       
        iss.clear(); 
        iss.str(s);  
        if (iss >> numerator) {
            num_ = numerator;
            den_ = 1;
        } else {
            // Invalid input (e.g. random letters): create a NaN
            num_ = 0; den_ = 0; 
        }
    }
    simplify();
}

// Concept: Operator Logic (Arithmetic)
// Addition: a/b + c/d = (ad + bc) / bd
Rational Rational::add(Rational other) const {
    // If either is NaN, result is NaN
    if (is_nan() || other.is_nan()) return Rational(0, 0);
    
    // Handling infinities
    if (is_inf() && other.is_inf()) {
        if ((num_ > 0 && other.num_ < 0) || (num_ < 0 && other.num_ > 0)) {
            return Rational(0, 0); // +inf + (-inf) = NaN
        }
        return *this; // inf + inf = inf, -inf + -inf = -inf
    }
    
    // prevents numbers from overflowing during multiplication
    long long n1 = num_, d1 = den_;
    long long n2 = other.num_, d2 = other.den_;
    return Rational(n1 * d2 + n2 * d1, d1 * d2);
}

// Subtraction: a/b - c/d = (ad - bc) / bd
Rational Rational::sub(Rational other) const {
    if (is_nan() || other.is_nan()) return Rational(0, 0);
    
    if (is_inf() && other.is_inf()) {
        if ((num_ > 0 && other.num_ > 0) || (num_ < 0 && other.num_ < 0)) {
            return Rational(0, 0); // inf - inf = NaN
        }
        return *this; 
    }
    
    long long n1 = num_, d1 = den_;
    long long n2 = other.num_, d2 = other.den_;
    return Rational(n1 * d2 - n2 * d1, d1 * d2);
}

// Multiplication: a/b * c/d = ac / bd 
Rational Rational::mul(Rational other) const {
    if (is_nan() || other.is_nan()) return Rational(0, 0);
    
    long long n1 = num_, d1 = den_;
    long long n2 = other.num_, d2 = other.den_;
    return Rational(n1 * n2, d1 * d2);
}


Rational Rational::div(Rational other) const {
    if (is_nan() || other.is_nan()) return Rational(0, 0);
    
    long long n1 = num_, d1 = den_;
    long long n2 = other.num_, d2 = other.den_;
    return Rational(n1 * d2, d1 * n2);
}

// Power function: (a/b)^n
Rational Rational::pow(int n) const {
    if (is_nan()) return *this; // NaN^n is NaN
    if (n == 0) return Rational(1, 1); // anything^0 is 1
    
    long long p = n;
    long long base_n = num_;
    long long base_d = den_;
    
    if (p < 0) {
        p = -p;
        std::swap(base_n, base_d);
    }
    
    long long res_n = 1;
    long long res_d = 1;
    for (int i = 0; i < p; ++i) {
        res_n *= base_n;
        res_d *= base_d;
    }
    
    return Rational(static_cast<int>(res_n), static_cast<int>(res_d));
}

 Rational Rational::sqrt() const {
    if (is_neg() || is_inf() || is_nan()) {
        return Rational(0, 0); 
    }
    
    int n_root = std::round(std::sqrt(num_));
    int d_root = std::round(std::sqrt(den_));
    
   
    if (n_root * n_root == num_ && d_root * d_root == den_) {
        return Rational(n_root, d_root);
    }
    
    
    return Rational(0, 0); 
}