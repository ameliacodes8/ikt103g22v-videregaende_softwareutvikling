#ifndef ITEM_H
#define ITEM_H

#include <string>

// Base class implementation
class Item
{
public:
    // Constructor.
    // explicit: Prevents the constructor from being used for implicit conversion
    explicit Item(std::string owner);

    // Destructor.
    // virtual: Mark functions intended to be replaced by derived classes as virtual.
    // = 0;   : Creates a pure virtual function without an implementations
    virtual ~Item() = 0;

    int Id() const;

    std::string Owner() const;

    void Owner(std::string owner);

    virtual void Print() const;

protected:
    int id;
    std::string owner;

    // Static variables have one, common value for all instances of the class
    static int next_id;
};


#endif //ITEM_H
