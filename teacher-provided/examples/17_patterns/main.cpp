/*
 * This application uses the following design patterns:
 *
 * - Structural pattern: MVC. Splits the code in models, views and controllers.
 * - Dependency injection: Objects are sent as parameters to other objects in constructors
 * - Composition: The Library class is built out of other, smaller classes
 */

#include "controllers/author_controller.h"
#include "models/library.h"
#include "views/main_menu.h"
#include "views/author_menu.h"

#include <iostream>

int main()
{
    // Create an instance of the library class.
    // This is a composite model with all the data of our application.
    Library library;

    // Create instances of our controller classes.
    // The model is sent to the controllers as a reference with dependency injection so that the data can be modified.
    AuthorController authorController(library);

    // Create instances of our view classes.
    // The model is sent to the views as a const reference with dependency injection so that the data can be displayed.
    MainMenu mainMenu(library);
    AuthorMenu authorMenu(library, authorController);

    bool running = true;

    // Main application loop. Runs until the user chooses "Exit" in the main menu.
    while (running)
    {
        int choice = mainMenu.GetChoice();

        // Each main menu choice is handled in a separate view class
        switch (choice)
        {
            // Authors
            case 1:
                authorMenu.Show();
                break;

            case 2:
            case 3:
                std::cout << "Not implemented yet." << std::endl;
                break;

            // Exit program
            case 4:
                running = false;
                break;

            default:
                std::cout << "Unexpected menu choice: " << choice << std::endl;
                break;
        }
    };

    return 0;
}
