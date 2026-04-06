/*

Shows how to put a function in a separate file

Shows how to read an integer from stdin, verify that it was read
successfully and lastly remove any remaining input before the next read.

*/

// #include <...> is used for standard library includes
#include <iostream>

// #include "..." is used for local project includes
// The line below allows us to use the getInt() function in this file
#include "number.h"

int main(int argc, char* args[])
{
    // A while loop does not require a body
    while(getInt() != 42);

    std::cout << "Magic number received. Application will exit." << std::endl << std::endl;

    return 0;
}
