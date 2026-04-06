#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "models/library.h"

class MainMenu
{
public:
    explicit MainMenu(const Library &library);

    int GetChoice();

protected:
    const Library &library;
};

#endif //MAIN_MENU_H
