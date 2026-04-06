#include <iostream>
#include <vector>

#include "item.h"
#include "album.h"
#include "book.h"

/*
 * Class overview:
 * - Base class: Item
 * - Derived classes: Album and Book
 *
 *
 * New inheritance concepts:
 * - Using ':' to specify base class(es), see album.h
 * - Using ':' to call base class constructors, see album.cpp
 * - Using 'const' to define read only member functions
 * - Using 'virtual' to mark functions as replaceable
 * - Using 'override' to mark functions as replaced
 * - Using '= 0;' to mark functions as pure virtual
 *
 * New general concepts:
 * - Using 'explicit' to prevent functions from being used for implicit conversion
 * - Using '= default;' to use default function implementations
 * - Using static class members
 * - Using std::move() to prevent unnecessary variable copies
 * Note: Album and Book are very similar. Album is commented, Book is not.
 */

int main()
{
    // Create objects on the heap
    auto *album1 = new Album("Owner 1", "Artist 1");
    auto *book1 = new Book("Owner 1", "Author 1");

    // Create a list that can contain any object of a class derived from Item
    std::vector<Item*> items;

    // Push two objects (of different classes!) to the same list.
    // This implicitly converts the pointers from Album* and Book* to Item*.
    // Conversion *up* the hierarchy is called *boxing*
    items.push_back(album1);
    items.push_back(book1);

    // Access all items as if they are the same type (they are: Item)
    for (auto item: items)
    {
        // Access the Print() function through the pointer.
        // This will call the overridden version of Print() from the derived classes.
        item->Print();
        std::cout << std::endl;
    }

    // Get the Item with index 0 from the vector.
    // This will be an Item* because the values in the vector are of type Item*.
    Item *item1 = items[0];

    // You can only access Item members from an object of type Item*
    int id = item1->Id();
    std::string owner = item1->Owner();

    // To access members exclusive to derived classes you must first cast the object to the right type.
    // Conversion *down* the hierarchy is called *unboxing*
    for (auto item: items)
    {
        // typeid() can be used to check the derived type from a base pointer.
        // Note: You must dereference the pointer here.
        if (typeid(*item) == typeid(Album))
        {
            // You can use static_cast<> to unbox the pointer.
            // Static cast will always succeed even if the base pointer is not of the correct derived class.
            // Due to this static_cast<> can be dangerous, and must only be used if you know the type is correct.
            auto *album = static_cast<Album*>(item);

            // Access Album member
            std::string artist = album->Artist();

            std::cout << "Album found: ";
            album->Print();
            std::cout << std::endl;

        }

        // You can also cast and check at the same time with dynamic_cast.
        // This is recommended if you're not sure if the wanted type is correct.
        auto *book = dynamic_cast<Book*>(item);

        // dynamic_cast<> returns a nullptr if the object is not of the wanted type
        if (book)
        {
            // Access Book member
            std::string author = book->Author();

            std::cout << "Book  found: ";
            book->Print();
            std::cout << std::endl;
        }
    }

    return 0;
}
