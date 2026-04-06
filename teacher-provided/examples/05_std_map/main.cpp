/*

Shows how to create a map (dictionary) with string to int lookup
Shows how to set values in a map using the key as index
Shows how to iterate a map to get key and value
Shows how to manually search for a value in a map
Shows how to use std::find_if and a lambda expression to search for a value (C++11)

Note: A map iterator iterates over std::pair objects, which contain two members:
    first:  Map key
    second: Map value

*/

#include <iostream>
#include <map>
#include <algorithm>

// Create an alias type for a map with string to int lookup.
// std::map is a template that takes two typenames as parameters:
// key type:  The type used to look up values in the map
// Value type: The type stored in the map
typedef std::map<std::string, int> Strings;

int main()
{
    // Create container key / value pairs
    Strings strings;

    // Add values using literal strings as keys
    strings["one"] = 1;
    strings["ten"] = 10;
    strings["fifty"] = 50;

    // Print all key / value pairs (std::pair)
    for(const auto &val: strings)
    {
        std::cout << "Key: " << val.first << std::endl;
        std::cout << "Val: " << val.second << std::endl;
    }

    // Iterator to store search results
    Strings::const_iterator position;

    // Search for a specific key that exists
    position = strings.find("ten");
    // position->second is now 10

    // Search for a specific key that does not exist
    position = strings.find("eighty");
    // position is now strings.end()

    // Search for value, manual search
    for(auto it = strings.begin(); it != strings.end(); it++)
    {
        if(it->second == 10)
        {
            // it->first is now "ten"
        }
    }

    // Below are some advanced samples from later lectures

    // Search for value, using std::find_if and a lambda expression (C++11)
    position = std::find_if(strings.begin(), strings.end(), [] (const Strings::value_type& pair) { return pair.second == 10; });
    // position->first is now "ten"

    // Create a pair copy by dereferencing an iterator
    Strings::value_type pair1 = *strings.find("ten");
    pair1.second = 11;
    // strings["ten"] is still 10

    // Create a pair reference by dereferencing an iterator
    Strings::value_type& pair2 = *strings.find("ten");
    pair2.second = 11;
    // strings["ten"] is now 11

    return 0;
}
