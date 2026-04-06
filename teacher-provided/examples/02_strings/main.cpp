/*

Shows how to manipulate strings as std::string objects

Note that this project gets two warnings about unused variables.
This is to be expected as they are in fact unused.

*/

#include <iostream>
#include <string>

int main()
{
    // Create string object
    std::string s("Hello, world!");

    // Read the first character
    char c = s[0];
    // c is now 'H'
    std::cout << "c is: " << c << std::endl;
    // Note: The compiler gives us a warning that c is unused. This is often useful information.

    // Read the length of the string
    size_t length = s.length();
    // Length is now 13
    std::cout << "Length is: " << length << std::endl;
    // Note: The compiler gives us a warning that length is unused. This is often useful information.

    // Set first character to 'o'
    s[0] = 'o';
    // s is now "oello, world!";
    std::cout << "s is: " << s << std::endl;

    // Create two std::strings
    std::string s1("one ");
    std::string s2("two");

    // Add both strings into s3
    std::string s3 = s1 + s2;
    // s3 is now "one two"
    std::cout << "s3 is: " << s3 << std::endl;

    // Increment the first value of s3
    s3[0]++;
    // s3 is now "pne two"
    std::cout << "s3 is: " << s3 << std::endl;

    return 0;
}
