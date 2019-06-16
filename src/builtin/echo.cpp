#include <builtin/echo.hpp>
#include <iostream>

/**
 * Implementation of the echo builtin command
 */
using namespace vsh::builtin;
using std::cout; 
using std::string;

void Echo::execute(int argc, char** argv) {
    for (char** arg = argv++; *arg; arg++) {
        cout << *arg;
    }
}