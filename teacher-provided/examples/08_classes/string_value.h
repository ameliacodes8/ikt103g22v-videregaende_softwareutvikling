/*
 * Contains declaration of class StringValue
 */

#ifndef HELLO_WORLD_H
#define HELLO_WORLD_H

#include <string>
#include <ostream>

// Class storing a string
class StringValue
{
public:
    // Constructors
    StringValue();
    explicit StringValue(std::string s);

    // Const member functions can not change the object
    std::string Get() const;

    // Regular member functions can access protected / private member variables
    void Set(std::string s);

protected:
    std::string text;
};

// Arithmetic operators. These could have been members also.
// & means pass by reference instead of copy, more on this later.
StringValue operator+(const StringValue& hw1, const StringValue& hw2);
void operator+=(StringValue& hw1, const StringValue& hw2);

// Stream operator. Prints object to stream.
std::ostream& operator<<(std::ostream& stream, const StringValue& hw);

#endif
