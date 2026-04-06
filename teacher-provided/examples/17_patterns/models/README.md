The __models__ directory contains classes that describe the data in our application. Models should not contain any
logic, but they can have constructors or other member functions directly related to data.

__author.h__, __book.h__ and __user.h__ are unchanged from the ORM example. __library.h__ is a new __composite__ model
that combines the basic models into a more complex model. Only author functionality is implemented in this example.