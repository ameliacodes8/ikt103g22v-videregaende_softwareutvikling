#include <iostream>
#include <algorithm>
#include <map>

int main()
{
    std::map<int, std::string> names;

    names[0] = "Lise";
    names[1] = "Knut";
    names[2] = "Arne";

    // Erase from a map with a range based for. Not legal, but might run.
    /*
    for (auto& name: names)
    {
        if (name.second == "Christian")
            names.erase(name.first); // Doesn't work. Modifies the map while it is iterated.
    }

    // Erase from a map and continue using the iterator. Not legal but might run.
    for (auto it = names.begin(); it != names.end(); it++)
    {
        if (it->second == "Knut")
            names.erase(it); // Doesn't work. Modifies the map while it is iterated.
    }
*/

    // Erase from a map with a regular for loop with iterators. Increment the iterator when erasing it. Works!
    for (auto it = names.begin(); it != names.end();) // Note: No it++
    {
        if (it->second == "Knut")
            names.erase(it++); // Works, because it is copied and increment before erase
        else
            it++;

    }

    // Use find_if and erase the result, if any. Works!
    auto it = std::find_if(names.begin(), names.end(), [](auto& name) { return name.second == "Arne"; });

    if (it != names.end())
        names.erase(it);

    return 0;
}
