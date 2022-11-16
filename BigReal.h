#ifndef BigReal_h
#define BigReal_h
#include <iostream>
#include "BigDecimalIntClass.h"
using namespace std;

class BigReal
{
private:
    pair<BigDecimalInt, BigDecimalInt> number; // pair of BigDecimalInts
    char SIGN;                                 // sign of the number

public:
    BigReal(double realNumber = 0.0){};  // Default constructor
    BigReal(string realNumber);          // Constructor that takes a string as an input
    BigReal(BigDecimalInt bigInteger);   // Constructor that takes a BigDecimalInt as an input
    BigReal(const BigReal &other);       // Copy constructor
    BigReal(BigReal &&other);            // Move constructor
    BigReal &operator=(BigReal &other);  // Assignment operator
    BigReal &operator=(BigReal &&other); // Move assignment
    BigReal operator+(const BigReal &other);
    BigReal operator-(const BigReal &other);
    bool operator<(BigReal anotherReal);
    bool operator>(BigReal anotherReal);
    bool operator==(BigReal anotherReal);
    int size();
    int sign();
    friend ostream &operator<<(ostream &out, BigReal num);
    friend istream &operator>>(istream &in, BigReal &num);

    friend BigReal addtion(BigReal num1, BigReal num2);
    friend BigReal subtraction(BigReal num1, BigReal num2);
    friend bool firstBiggerSecond(BigReal num1, BigReal num2);
};

#endif /* BigReal_h */