//
// Created by ByteDance on 19/10/23.
//

#ifndef MODERNCPP_POINTER_H
#define MODERNCPP_POINTER_H
#include <memory>

void testSharedPtr();
void testSharedPtrCount();
void testUniquePtr2();
void testMove();
void testCircleReference();

class classB;
class classA {
public:
    std::weak_ptr<classB> pointer;
    ~classA() {
        std::cout << "A was destroyed" << std::endl;
    }
};

class classB {
public:
    std::weak_ptr<classA> pointer;
    ~classB() {
        std::cout << "B was destoryed" << std::endl;
    }

};
#endif //MODERNCPP_POINTER_H
