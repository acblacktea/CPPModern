//
// Created by ByteDance on 19/10/23.
//

#include <memory>
#include <iostream>
#include <string>
#include "pointer.h"
void foo(std::shared_ptr<int>i) {
    (*i)++;
}

void testSharedPtr() {
    auto pointer = std::make_shared<int>(10);
    foo(pointer);
    std::cout << *pointer << std::endl;
}

void testSharedPtrCount() {
    auto pointer = std::make_shared<int>(10);
    auto pointer2 = pointer;
    auto pointer3 = pointer;

    std::cout << "pointer.use_count() = " << pointer.use_count() << std::endl;
    std::cout << "pointer2.use_count() = " << pointer2.use_count() << std::endl;
    std::cout << "pointer3.use_count() = " << pointer3.use_count() << std::endl;

    pointer2.reset();
    std::cout << "reset pointer2:" << std::endl;
    std::cout << pointer.get() << std::endl;
    std::cout << pointer2.get() << std::endl;
    std::cout << pointer3.get() << std::endl;

    std::cout << "pointer.use_count() = " << pointer.use_count() << std::endl;
    std::cout << "pointer2.use_count() = " << pointer2.use_count() << std::endl;
    std::cout << "pointer3.use_count() = " << pointer3.use_count() << std::endl;

    pointer3.reset();
    std::cout << "reset pointer3:" << std::endl;

    std::cout << "pointer.use_count() = " << pointer.use_count() << std::endl;
    std::cout << "pointer2.use_count() = " << pointer2.use_count() << std::endl;
    std::cout << "pointer3.use_count() = " << pointer3.use_count() << std::endl;
}

void testUniquePtr() {
    std::unique_ptr<int> pointer = std::make_unique<int>(10);
    //std::unique_ptr<int> pointer2 = pointer;
}

// todo
template<typename  T, typename ...Args>
std::unique_ptr<T> make_unique2(Args&& ...args) {
    return std::unique_ptr<T>(new T(args)...);
}

struct Foo {
    int q;
    Foo() { q = 5; std::cout << "Foo:Foo" << std::endl; }
    ~Foo() { std::cout << "Foo::~Foo" << std::endl; }
    void foo() {std::cout << "function Foo::foo" << std::endl; }
};

void f(const Foo & a) {
    std::cout << "f(const Foo&)" << std::endl;
}

void testUniquePtr2() {
    std::unique_ptr<Foo> p1(std::make_unique<Foo>());

    // p1 is not empty, prints
    if (p1) p1->foo();
    std::unique_ptr<Foo> p2(std::move(p1));

    f(*p2);

    if(p2) p2->foo();
    if(p1) p1->foo();

    p1 = std::move(p2);

    if (p2) p2->foo();
    std::cout << "p2 was destroyed" << std::endl;

    if (p1) p1->foo();
}


void testMove() {
    std::string s = "abcd";
    std::string &&q = std::move(s);
    //s = "1234";
    std::cout << s << std::endl;
    std::cout << q << std::endl;
}

void testCircleReference() {
    std::shared_ptr<classA> a = std::make_shared<classA>();
    std::shared_ptr<classB> b = std::make_shared<classB>();
    a->pointer = b;
    b->pointer = a;
}