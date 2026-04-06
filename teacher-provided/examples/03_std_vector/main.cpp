/*

Shows how to create a vector and put some strings on it
Shows how to access the elements on a vector with both index and iterator

*/

#include <iostream>
#include <vector>

// Create an alias type for a vector of strings called Strings.
// As with std::list it's a template that takes one typename as parameter:
// the type of the variables it will store. In this case std::string.
typedef std::vector<std::string> Strings;

int main()
{
    // Create container for strings
    Strings strings;

    // Add some strings to it
    strings.push_back("one");
    strings.push_back("two");
    strings.push_back("three");

    // Print strings using a regular loop and index
    for(std::size_t i = 0; i < strings.size(); i++)
        std::cout << strings[i] << std::endl;

    std::cout << std::endl;

    // Print strings using an iterator to const elements
    for(Strings::const_iterator it = strings.begin(); it != strings.end(); it++)
        std::cout << *it << std::endl;

    std::cout << std::endl;

    // Print strings using an iterator to const elements using the auto keyword
    for(auto it = strings.cbegin(); it != strings.cend(); it++)
        std::cout << *it << std::endl;

    std::cout << std::endl;

    // Print strings using the range based for loop (C++11)
    for(const auto& val: strings)
        std::cout << val << std::endl;

    return 0;
}
