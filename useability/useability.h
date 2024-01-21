//
// Created by ByteDance on 12/10/23.
//

#ifndef MODERNCPP_USEABILITY_H
#define MODERNCPP_USEABILITY_H
#include <iostream>
#include <map>
void constExprTest();
void NullPtrWithNull();
void declareInIfSwitch();
void initializerList();
void structedBinding();
void testDecltype();
void testTailTypeInference();
void testIfConstExpr();
void testRangeBaseLoop();
void testVariableLengthParameter();
void testVariableLengthParameter2();
void testFoldExpression();
void testDelegateConstructor();
void testInheritanceConstructor();
void testOverride();
void testStructuredBinding();

template<typename T, int BufSize>
class bufferT {
public:
    T& alloc();
    void free(T& item);
private:
    T data[BufSize];
};


class Base {
public:
    int value1, value2;
    Base() {
        value1 = 1;
    }
    Base(int value) : Base() {
        value2 = value;
    }
};

class Subclass : public Base {
public:
    using Base::Base;
};


struct Base2 {
    virtual void foo(int) = 0;
};

struct Subclass2: Base2 {
    void foo(int) override;
    //virtual void foo(float) override;
};

struct Subclass3: Subclass2 {
    void foo(int) override;
};

struct Base3 {
    virtual void foo() final;
};

struct SubClass31 final: Base {};

struct SubClass1 final: Base {};
// struct Subclass2 : SubClass1 {}; // error

//struct Subclass3: Base { void foo();};

class Magic2 {
public:
    Magic2() = default;
    Magic2& operator=(const Magic2&) = delete;
    Magic2(int magicNumber);
};

enum class new_enum : unsigned int {
    value1,
    value2,
    value3 = 100,
    value4 = 100,
    value5,
};

template<typename T>
std::ostream& operator<<(typename std::enable_if<std::is_enum<T>::value, std::ostream>::type& stream, const T& e) {
    return stream << static_cast<typename std::underlying_type<T>::type>(e);
}

// test1
template <typename Key, typename Value, typename F>
void update(std::map<Key, Value>& m, F foo) {
    for (auto&& [key, value] : m ) value = foo(key);
}


// test2
template<typename... T> auto mean(T... t) { return (t + ...) / sizeof...(t);}

#endif //MODERNCPP_USEABILITY_H
