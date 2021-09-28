#include "call1.h"
#include "call2.h"

#include <iostream>

int main() {
    std::cout << "call1: " << CallFoobar1() << "\n";
    std::cout << "call2: " << CallFoobar2() << "\n";
}
