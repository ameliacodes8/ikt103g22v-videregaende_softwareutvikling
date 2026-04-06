/*
 * Contains definition/implementation of class StringValue
 *
 * this-> isn't required to access text, but it's often
 * used to make it clear you are accessing a member variable.
 */

#include <string>
#include <ostream>

#include "string_value.h"

StringValue::StringValue()
{
    this->text = "Hello, world!";
}

StringValue::StringValue(std::string s)
{
    this->text = std::move(s);
}

std::string StringValue::Get() const
{
    return this->text;
}

void StringValue::Set(std::string s)
{
    this->text = s;
}

StringValue operator+(const StringValue& hw1, const StringValue& hw2)
{
    return StringValue(hw1.Get() + hw2.Get());
}

void operator+=(StringValue& hw1, const StringValue& hw2)
{
    hw1.Set(hw1.Get() + hw2.Get());
}

std::ostream& operator<<(std::ostream& stream, const StringValue& hw)
{
    stream << hw.Get() << std::endl;
    return stream;
}
