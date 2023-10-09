#include <iostream>
#include "ExternC/foo.h"
namespace A
{
    extern "C" int h();
}

extern "C" int h() { return 97; } // definition for the C linkage function h
// A::h and ::h refer to the same function

int main() {
    [out = std::ref(std::cout << "result from c code: " << add(1, 2))]() {
        out.get() << ".\n";
    }();
    return 0;
}
