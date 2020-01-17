#include <iostream>
#include "../version.h"

int main()
{
    std::cout << "build = " << PROJECT_VERSION_PATCH << std::endl;
    std::cout << "Hello world!";
    return 0;
}