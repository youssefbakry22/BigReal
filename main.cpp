/*
 * FCAI – OOP – 2022 - Assignment 2
 * Program Name: A2_Task1_S7_20210481.cpp
 * Program Description: It provides us the ability to store big reals with some operations.
 * Last Modification Date: 12/11/2022
 * Author1 and ID and Group: Youssef Bakry , 20210481 , S7
 * Teaching Assistant: Dr. Mohammad El-Ramly
 * Purpose: store big integers with some operations.
 */

#include <iostream>
#include "BigReal.h"

using namespace std;
int main()
{
    BigReal a;
    BigReal b;
    cout << "Enter the first number: ";
    cin >> a;
    cout << "Enter the second number: ";
    cin >> b;
    cout << "The first number is: " << a << endl;
    cout << "The second number is: " << b << endl;
    cout << "a - b = " << a - b << endl;
    cout << "b - a = " << b - a << endl;
    cout << "a + b = " << a + b << endl;
    cout << "a < b = " << (a < b) << endl;
    cout << "a > b = " << (a > b) << endl;
    cout << "a == b = " << (a == b) << endl;
    cout << "a.size() = " << a.size() << endl;
    cout << "b.size() = " << b.size() << endl;
    cout << "a.sign() = " << a.sign() << endl;
    cout << "b.sign() = " << b.sign() << endl;
    return 0;
}