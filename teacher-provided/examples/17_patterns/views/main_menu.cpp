#include "main_menu.h"

#include <iostream>

MainMenu::MainMenu(const Library &library) : library(library)
{}

int MainMenu::GetChoice()
{
    while (true)
    {
        std::cout << std::endl;
        std::cout << "=========" << std::endl;
        std::cout << "Main menu" << std::endl;
        std::cout << "=========" << std::endl << std::endl;

        std::cout << "1. Authors" << std::endl;
        std::cout << "2. Books" << std::endl;
        std::cout << "3. Users" << std::endl;
        std::cout << "4. Exit" << std::endl;

        int choice;

        std::cin >> choice;

        if (choice >= 1 && choice <= 4)
            return choice;
    }
}
