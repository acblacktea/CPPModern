//
// Created by ByteDance on 15/10/23.
//

#include <iostream>
#include <memory>
#include <utility>
#include <functional>
#include <vector>
#include "runtime.h"

auto lamadaValueCapture() {
    int value = 1;
    auto copyValue = [value]{
        return value;
    };

    auto copyValue2 = [&value] {
        return value;
    };

    auto copyValue3 = [&] {
        return value;
    };

    auto copyValue4 = [=] {
        return value;
    };

    value = 100;
    auto storedValue = copyValue();
    std::cout << "storedValue = " << storedValue << std::endl;
}

void lambdaExpressionCapture(){
    auto important = std::make_unique<int>(1);
    auto add = [v1 = 1, v2 = std::move(important)](int x, int y) -> int {
        return x + y + v1 + (*v2);
    };

    std::cout << add(3, 4) << std::endl;
}

void lambdaGeneric() {
    auto generic = [](auto x, auto y) {
        return x + y;
    };

    std::cout << generic(1, 2) << std::endl;
    std::cout << generic(1.1, 2.2) << std::endl;
}

using foo = void(int);
void functional(foo f) {
    f(1);
}

void testFunction() {
    auto f = [](int value) {
        std::cout << value << std::endl;
    };

    functional(f);
    f(1);
}

int foo2(int para) {
    return para;
}

void testFunctional() {
    std::function<int(int)> func = foo2;

    int important = 10;
    std::function<int(int)> func2 = [&](int value) -> int {
        return 1 + value + important;
    };

    std::cout << func(10) << std::endl;
    std::cout << func2(10) << std::endl;
}

int foo3(int a, int b, int c) { return 1;}
int testBind() {
    auto bindFoo = std::bind(foo3, std::placeholders::_1, 1, 2);
    bindFoo(1);
}

void testStrlingLiteral() {
    const char s[] = "01234";
    const char (&left)[6] = "01234";
    int a = 5;
    if (std::is_same<decltype(a), int&>::value) {}

    static_assert(std::is_same<decltype("01234"), const char(&)[6]>::value, "");
}

std::vector<int> createTestVector() {
    std::vector<int> temp = {1, 2, 3, 4};
    return temp;
}

void reference(std::string& str) {
    std::cout << "lvalue" << std::endl;
}

void reference(std::string&& str) {
    std::cout << "rvalue" << std::endl;
}

void testRValueReference() {
    std::string lv1 = "string,";

    std::string&& rv1 = std::move(lv1);
    std::cout << rv1 << std::endl;

    const std::string& lv2 = lv1 + lv1;

    std::cout << lv2 << std::endl;

    std::string&& rv2 = lv1 + lv2;
    rv2 += "string";
    std::cout << rv2 << std::endl;

    reference(rv2);
}

void testImplictConvertRValueReference() {
    std::vector<int>ve2{1,2,3};
    std::vector<int>&& ve = createTestVector();
}

A returnRvalue(bool test) {
    A a,b;
    if (test) return a;
    else return b;
}

void testRValueReference2() {
    A obj = returnRvalue(false);
    std::cout << "obj:" << std::endl;
    std::cout << obj.pointer << std::endl;
    std::cout << *obj.pointer << std::endl;
}

void testVectorRValueReference() {
    std::string str = "Hello world.";
    std::vector<std::string> v;

    v.push_back(str);
    std::cout << "str: " << str << std::endl;

    v.push_back(std::move(str));
    std::cout << "str: " << str << std::endl;
}

void reference(int& v) {
    std::cout << "lvalue reference" << std::endl;
}

void reference(int&& v) {
    std::cout << "rvalue reference" << std::endl;
}

template<typename  T>
void pass(T&& v) {
    std::cout << "normal param passing:";
    reference(v);
}

template<typename  T>
void pass2(T&& v) {
    std::cout << "normal param passing: ";
    reference(v);
    std::cout << "std::move param passing:";
    reference(std::move(v));
    std::cout << "std::forward param passing:";
    reference(std::forward<T>(v));
    std::cout << "static_cast<T&&> param passing:";
    reference(static_cast<T&&>(v));
}

void testRVReference () {
    std::cout << "rvalue pass:" << std::endl;
    pass2(1);

    std::cout << "lvalue pass:" << std::endl;
    int l = 1;
    pass2(l);
}