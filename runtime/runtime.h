//
// Created by ByteDance on 15/10/23.
//

#ifndef MODERNCPP_RUNTIME_H
#define MODERNCPP_RUNTIME_H
#include <iostream>

void lambdaExpressionCapture();
void lambdaGeneric();
void testRValueReference();
void testRValueReference2();
void testVectorRValueReference();
void testRVReference();

class A {
public:
    int *pointer;
    A():pointer(new int(1)) {
        std::cout << "construct " << pointer << std::endl;
    }
    A(A& a):pointer(new int(*a.pointer)) {
        std::cout << "copy " << pointer << std::endl;
    }
    A(A&& a):pointer(a.pointer) {
        a.pointer = nullptr;
        std::cout << "move " << pointer << std::endl;
    }
    ~A() {
        std::cout << "destruct " << pointer << std::endl;
        delete pointer;
    }
};
#endif //MODERNCPP_RUNTIME_H
