#include <iostream>
#include <regex>
#include "BigReal.h"
using namespace std;

//=====================================================================================================================================//
/* free functions */

// function to remove zeros from the right of the fraction part
void removeZeroatEnd(BigDecimalInt &num)
{
    int i = num.size() - 1;
    string temp = num.getNumber();
    while (temp[i] == '0' && i != 0)
    {
        temp.erase(i, 1);
        i--;
    }
    num.setNumber(temp);
}

// function to remove zeros from the left of the integer part
void removeZeroatFront(BigDecimalInt &num)
{
    int i = 0;
    string temp = num.getNumber();
    while (temp[i] == '0' && i != temp.size() - 1)
    {
        temp.erase(i, 1);
    }
    num.setNumber(temp);
}

// function to fill zeros.
void fillZeros(BigDecimalInt &num, int nZeros)
{
    string zeros;
    for (int i = 0; i < nZeros; i++)
    {
        zeros.append("0");
    }
    num.setNumber(num.getNumber() + zeros);
}

// function to add zeros to the right of the fraction part.
void equal_length(BigDecimalInt &num1, BigDecimalInt &num2)
{
    int len1 = num1.size(), len2 = num2.size();
    if (len1 < len2)
    {
        fillZeros(num1, len2 - len1);
    }
    else if (len2 < len1)
    {
        fillZeros(num2, len1 - len2);
    }
}

// regex function that checks the validation of the input.
bool isValidInput(string input)
{
    regex validInput("[-+]?[0-9]*[.][0-9]*");
    return regex_match(input, validInput);
}

//=====================================================================================================================================//
/* class friend funcrions */

// comparison implementation.
bool firstBiggerSecond(BigReal num1, BigReal num2)
{
    if (num1.number.first > num2.number.first)
    {
        return true;
    }

    else if (num1.number.first < num2.number.first)
    {
        return false;
    }

    else
    {
        equal_length(num1.number.second, num2.number.second);

        if (num1.number.second > num2.number.second)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

// addition implementation.
BigReal addtion(BigReal num1, BigReal num2)
{
    equal_length(num1.number.second, num2.number.second); // two fractions of the same length.
    int frac_len = num1.number.second.size();             // to detrmine postion of the decimal point after addtion.

    string temp1 = num1.number.first.getNumber() + num1.number.second.getNumber(); // concatenate the real number to be an integer.
    string temp2 = num2.number.first.getNumber() + num2.number.second.getNumber(); // concatenate the real number to be an integer.
    string temp_int = (BigDecimalInt(temp1) + BigDecimalInt(temp2)).getNumber();   // add the two real as integer.
    temp_int.insert(temp_int.size() - frac_len, 1, '.');                           // add the decimal point.

    BigReal res(temp_int);
    return res;
}

// subtraction implementation.
// assuming that num1 is bigger than num2 as value ignoring the sign.
BigReal subtraction(BigReal num1, BigReal num2)
{
    equal_length(num1.number.second, num2.number.second); // two fractions of the same length.
    int frac_len = num1.number.second.size();             // to detrmine postion of the decimal point after subtraction.

    string temp1 = num1.number.first.getNumber() + num1.number.second.getNumber(); // concatenate the real number to be an integer.
    string temp2 = num2.number.first.getNumber() + num2.number.second.getNumber(); // concatenate the real number to be an integer.
    string temp_int = (BigDecimalInt(temp1) - BigDecimalInt(temp2)).getNumber();   // subtract the two real as integer.
    temp_int.insert(temp_int.size() - frac_len, 1, '.');                           // add the decimal point.

    BigReal res(temp_int);
    return res;
}

//=====================================================================================================================================//
/* class member functions */

// constructor that takes a string as an input.
BigReal::BigReal(string realNumber)
{
    if (isValidInput(realNumber))
    {
        if (realNumber[0] == '+')
        {
            realNumber.erase(0, 1);
            SIGN = '+';
        }
        else if (realNumber[0] == '-')
        {
            realNumber.erase(0, 1);
            SIGN = '-';
        }
        else
        {
            SIGN = '+';
        }

        string integerPart = realNumber.substr(0, realNumber.find('.'));
        string decimalPart = realNumber.substr(realNumber.find('.') + 1, realNumber.size() - 1);
        if (integerPart.empty())
        {
            integerPart = "0";
        }
        if (decimalPart.empty())
        {
            decimalPart = "0";
        }
        number.first = BigDecimalInt(integerPart);
        removeZeroatFront(number.first);
        number.second = BigDecimalInt(decimalPart);
        removeZeroatEnd(number.second);
    }
    else
    {
        // if the input is not valid as a real number, it will be treated as an integer (also it will be checked if is valid integer).
        // delgating the constructor to the BigDecimalInt constructor.
        *this = BigReal(BigDecimalInt(realNumber));
    }
}

// constructor that takes a BigDecimalInt as an input.
BigReal::BigReal(BigDecimalInt bigInteger)
{
    number.first = bigInteger;
    number.second = BigDecimalInt("0");
    if (bigInteger.sign() == 1)
    {
        SIGN = '+';
    }
    else
    {
        SIGN = '-';
    }
    removeZeroatFront(number.first);
}

// copy constructor.
BigReal::BigReal(const BigReal &anotherReal)
{
    number.first = anotherReal.number.first;
    number.second = anotherReal.number.second;
    SIGN = anotherReal.SIGN;
}

// move constructor.
BigReal::BigReal(BigReal &&anotherReal)
{
    number.first = anotherReal.number.first;
    number.second = anotherReal.number.second;
    SIGN = anotherReal.SIGN;
}

// copy assignment operator.
BigReal &BigReal::operator=(BigReal &anotherReal)
{
    number.first = anotherReal.number.first;
    number.second = anotherReal.number.second;
    SIGN = anotherReal.SIGN;
    return *this;
}

// move assignment operator.
BigReal &BigReal::operator=(BigReal &&anotherReal)
{
    number.first = anotherReal.number.first;
    number.second = anotherReal.number.second;
    SIGN = anotherReal.SIGN;
    return *this;
}

// operator + overloading function.
BigReal BigReal::operator+(const BigReal &anotherReal)
{
    BigReal res;
    if (SIGN == anotherReal.SIGN)
    {
        res = addtion(*this, anotherReal);
        res.SIGN = SIGN;
    }

    else
    {
        if (firstBiggerSecond(*this, anotherReal))
        {
            res = subtraction(*this, anotherReal);
            res.SIGN = SIGN;
        }

        else if (firstBiggerSecond(anotherReal, *this))
        {
            res = subtraction(anotherReal, *this);
            res.SIGN = anotherReal.SIGN;
        }
        else
        {
            res = BigReal("0.0");
            res.SIGN = '+';
        }
    }
    return res;
}

// operator - overloading function.
BigReal BigReal::operator-(const BigReal &anotherReal)
{
    BigReal res;
    if (SIGN == anotherReal.SIGN)
    {
        if (firstBiggerSecond(*this, anotherReal))
        {
            res = subtraction(*this, anotherReal);
            res.SIGN = SIGN;
        }

        else if (firstBiggerSecond(anotherReal, *this))
        {
            res = subtraction(anotherReal, *this);
            if (anotherReal.SIGN == '+')
            {
                res.SIGN = '-';
            }
            else if (anotherReal.SIGN == '-')
            {
                res.SIGN = '+';
            }
        }
        else
        {
            res = BigReal("0.0");
            res.SIGN = '+';
        }
    }

    else
    {
        res = addtion(*this, anotherReal);
        res.SIGN = SIGN;
    }
    return res;
}

// operator < overloading function.
bool BigReal::operator<(BigReal anotherReal)
{
    if (SIGN == '+' && anotherReal.SIGN == '-')
    {
        return false;
    }

    else if (SIGN == '-' && anotherReal.SIGN == '+')
    {
        return true;
    }

    else if (SIGN == '+' && anotherReal.SIGN == '+')
    {
        return (anotherReal > *this);
    }

    else if (SIGN == '-' && anotherReal.SIGN == '-')
    {
        if (firstBiggerSecond(*this, anotherReal))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}

// operator > overloading function.
bool BigReal::operator>(BigReal anotherReal)
{
    if (SIGN == '+' && anotherReal.SIGN == '-')
    {
        return true;
    }

    else if (SIGN == '-' && anotherReal.SIGN == '+')
    {
        return false;
    }

    else if (SIGN == '-' && anotherReal.SIGN == '-')
    {
        return (anotherReal < *this);
    }

    else if (SIGN == '+' && anotherReal.SIGN == '+')
    {
        if (firstBiggerSecond(*this, anotherReal))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}

// operator == overloading function.
bool BigReal::operator==(BigReal anotherReal)
{
    if (*this > anotherReal || *this < anotherReal)
    {
        return false;
    }
    else
    {
        return true;
    }
    return false;
}

// function to return the size of number. done
int BigReal::size()
{
    return number.first.size() + number.second.size();
}

// function to return the sign of number.
int BigReal::sign()
{
    if (SIGN == '+')
    {
        return 1;
    }
    else
    {
        return -1;
    }
}

// operator << overloading function. done
ostream &operator<<(ostream &out, BigReal num)
{
    if (num.SIGN == '-')
    {
        out << num.SIGN << num.number.first << '.' << num.number.second;
    }
    else
    {
        out << num.number.first << '.' << num.number.second;
    }
    return out;
}

// operator >> overloading function.
istream &operator>>(istream &in, BigReal &num)
{
    string realNumber;
    in >> realNumber;
    if (isValidInput(realNumber))
    {
        num = BigReal(realNumber);
    }
    else
    {
        num = BigReal(BigDecimalInt(realNumber));
    }
    return in;
}