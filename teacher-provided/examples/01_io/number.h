/*

Any line starting with the # character is a pre-processor command that is
interpreted before the actual code is compiled.

The three pre-processor commands below ensure this header is only included
once during compilation to prevent "already defined" errors, usually the
result of circular inclusion.

This is called an "include guard" and should *always* be used.

*/

#ifndef NUMBER_H
#define NUMBER_H

/*

The function prototype below tells the compiler about the return type
and arguments of the function. It uses this to check for coding errors
while compiling.

Since each cpp file is built in a different compilation unit it is the
way you ensure errors calling a function is detected at compile time.

The name of the function and the type of its parameters is called the
function signature.

*/

// Returns a number read from keyboard
// Returns 0 in case of error
int getInt();

#endif
