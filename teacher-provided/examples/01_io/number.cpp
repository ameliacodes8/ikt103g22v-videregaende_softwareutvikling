/*

 .cpp files will need to include their own headers. Try to keep the number
of headers included to a minimum as your program will compile faster and
 the chance of naming conflicts will be lower.

*/
#include <iostream>
#include <limits>

// This include is not actually required, but it helps the compiler to
// give proper error messages if the function signature is mismatching.
#include "number.h"

int getInt()
{
    int number = 0;

    std::cout << "Please provide a number: ";

    std::cin >> number;

    // std::cin will validate as boolean 'true' as long as everything is OK in the stream
    if(std::cin)
        std::cout << "Got int '" << std::dec << number << "' which in hex is '0x" << std::hex << number << "'" << std::endl << std::endl;
    else
        std::cout << "Invalid input, someone crossed the streams :(" << std::endl << std::endl;

    // Clear resets the stream in case of an error when reading above.
    // This must be done after an error has occurred before using the stream again
    std::cin.clear();

    // Then flush the rest of the contents
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    /*
     * Even with clearing errors and ignoring the remaining input it's hard to ensure
     * that the stream behaves as expected. A more robust solution could be to use
     * std::getline instead.
     */

    return number;
}
