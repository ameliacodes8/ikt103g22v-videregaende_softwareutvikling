#ifndef AUTHOR_MENU_H
#define AUTHOR_MENU_H

#include "controllers/author_controller.h"
#include "models/library.h"

class AuthorMenu
{
public:
    explicit AuthorMenu(const Library &library, AuthorController &authorController);

    void Show();

protected:
    const Library &library;
    AuthorController &authorController;
};

#endif //AUTHOR_MENU_H
