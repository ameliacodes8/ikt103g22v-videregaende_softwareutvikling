/*

Shows how to create an alias for a type
Shows how to create a list and put some strings in it
Shows how to iterate a list to get its contents
Shows how to use the auto keyword (C++11)
Shows how to use the range based for loop (C++11)

Typedef vs auto keyword: IMO personal taste.
Both can greatly improve code readability
A typedef is often useful even if auto / ranged based for is used for iteration.

Rule of thumb: Only use auto for short lived variables

Note: After this example iteration will mostly be done with C++11 for loops.

*/

#include <iostream>
#include <list>

// Create an alias type for a list of strings called Strings.
// std::list is a template that takes one typename as parameter:
// the type of the variables it will store. In this case std::string.
typedef std::list<std::string> Strings;

int main()
{
    // Create list container for strings using the type alias. This is the same as writing:
    // std::list<std::string> strings;
    Strings strings;

    // Add some strings to it
    strings.push_back("one");
    strings.push_back("two");
    strings.push_back("three");

    // Print strings using an iterator to const elements.
    // Here the iterator is auto-promoted to const in the assignment.
    for(Strings::const_iterator it = strings.begin(); it != strings.end(); it++)
        std::cout << *it << std::endl;

    std::cout << std::endl;

    // Change all strings to "one", using an iterator to mutable elements
    for(Strings::iterator it = strings.begin(); it != strings.end(); it++)
        *it = "one";

    // Print strings using an iterator to const elements, with the auto keyword from C++11.
    // Note that we have to use the cbegin and cend functions in this case.
    for(auto it = strings.cbegin(); it != strings.cend(); it++)
        std::cout << *it << std::endl;

    std::cout << std::endl;

    // Change all strings to "two", using an auto type iterator to mutable elements
    for(auto it = strings.begin(); it != strings.end(); it++)
        *it = "two";

    // Print the modified list
    for(auto it = strings.cbegin(); it != strings.cend(); it++)
        std::cout << *it << std::endl;

    std::cout << std::endl;

    // Print them again using the new range based for loop from C++11.
    // "const auto&" means an immutable reference to whatever type is being iterated.
    // It's equivalent to "const int&". If you want to change the value remove const.
    for(const auto& val: strings)
        std::cout << val << std::endl;

    std::cout << std::endl;

    return 0;
}
