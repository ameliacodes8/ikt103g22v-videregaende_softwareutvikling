/*
 * Shows how to put the definition of a class in a header file
 * Shows how to put the implementation of a class in a cpp file
 * Shows how to use this class in the application
 *
 * The StringValue class has constructors and member functions
 */

#include <iostream>
#include <string>

#include "string_value.h"

int main()
{
    // Instantiate using default constructor.
    // Remember: StringValue is a class (recipe), hw1 is an instance/object of that class
    StringValue hw1;

    // Assign to value
    hw1.Set("one ");

    // Instantiate using constructor taking a string argument
    StringValue hw2("two ");
    StringValue hw3("three");

    // Use addition operator
    StringValue hw4 = hw1 + hw2;

    // Use addition assignment operator
    hw4 += hw3;

    // Use operator<< to output StringValue as text
    std::cout << "StringValue to stream: " << hw4 << std::endl;

    return 0;
}
