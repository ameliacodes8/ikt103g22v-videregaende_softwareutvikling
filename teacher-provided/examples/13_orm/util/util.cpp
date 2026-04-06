#include "util.h"

#include <iostream>
#include <string>

void print_header(const std::string &header)
{
    std::string border(header.length(), '=');

    std::cout << std::endl;
    std::cout << border << std::endl;
    std::cout << header << std::endl;
    std::cout << border << std::endl << std::endl;
}
