#include "author_menu.h"

#include <iostream>

AuthorMenu::AuthorMenu(const Library &library, AuthorController &authorController)
        : authorController(authorController), library(library)
{}

void AuthorMenu::Show()
{
    std::cout << "1. List authors" << std::endl;
    std::cout << "2. Add author" << std::endl;
    std::cout << "3. Edit author" << std::endl;
    std::cout << "4. back" << std::endl;

    int choice;
    std::cin >> choice;

    switch (choice)
    {
        // List authors
        case 1:
            for (auto &author: library.authors)
                std::cout << author.family_name << ", " << author.given_name << std::endl;

            break;

        // Add author
        case 2:
        {
            // The view code handles the user interface
            std::string family_name;

            std::cout << "Family name: ";
            std::cin >> family_name;

            std::string given_name;

            std::cout << "Given name: ";
            std::cin >> given_name;

            // Send the author we want to add to the controller
            authorController.AddAuthor(family_name, given_name);
            break;
        }
            // Edit author
        case 3:
            std::cout << "Not implemented yet." << std::endl;
            break;

            // Back
        case 4:
            break;
    }
}
