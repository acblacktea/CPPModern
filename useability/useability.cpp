//
// Created by ByteDance on 12/10/23.
//

#include "useability.h"
#include<iostream>
#include<vector>
#include<algorithm>
#include<tuple>
#include<map>
#include<string>
#define LEN 10


/*-----------------------------------------------------------------------------------------------*/
int lenFoo() {
    int i = 2;
    return i;
}

constexpr int lenFooConstexpr() {
    return 5;
}

constexpr int fibonacci(const int n) {
    return n == 1 || n == 2 ? 1 : fibonacci(n - 1) + fibonacci(n - 2);

}

int fibonacci2(const int n) {
    if (n == 1) return 1;
    if (n == 2) return 1;
    return fibonacci(n - 1) + fibonacci2(n - 2);
}

void testChar(const char* s) {

}

void constExprTest() {
    char arr1[10];
    char arr2[LEN];
    int len = 10;
    char arr3[len];

    const int len2 = len + 1;
    constexpr int len2Constexpr = 1 + 2 + 3;

    char arr4[len2];
    char arr44[len2Constexpr];

    char arr5[lenFoo() + 5];
    char arr6[lenFooConstexpr() + 1];

    char arr7[fibonacci(10)];
    //std::cout << fibonacci(20) << std::endl;
    testChar("123");

}

/*-----------------------------------------------------------------------------------------------*/

void foo(char *) {
    std::cout << "foo(char *) is called" << std::endl;
}

void foo(int i) {
    std::cout << "foo(int) is called" << std::endl;
}

void nullPtrWithNull() {
    void *p = ((int*)0);
    if (std::is_same<decltype(NULL), decltype((long)0)>::value) {
        std::cout << "NULL == 0" << std::endl;
    }

    if (std::is_same<decltype(NULL), decltype((void *)0)>::value) {
        std::cout << "NULL == (void *)0" << std::endl;
    }

    if (std::is_same<decltype(NULL), std::nullptr_t>::value) {
        std::cout << "NULL == nullptr" << std::endl;
    }

    foo(0);
    foo(nullptr);
}

/*-----------------------------------------------------------------------------------------------*/

void declareInIfSwitch() {
    std::vector<int> vec = {1, 2, 3, 4};

    const std::vector<int>::iterator itr = std::find(vec.begin(), vec.end(), 2);
    if (itr != vec.end()) {
        *itr = 3;
    }

    if (const auto itr = std::find(vec.begin(), vec.end(), 3);itr != vec.end()) {
        itr != vec.end();
        *itr = 4;
    }

    for (auto element = vec.begin(); element != vec.end(); ++element) {
        std::cout << *element << std::endl;
    }

}

/*-----------------------------------------------------------------------------------------------*/
class Foo {
public:
    int valueA;
    int valueB;
    Foo(int a, int b) : valueA(a), valueB(b) {}
};

void traditionalCppWithConstruct() {
    int arr[3] = {1, 2, 3};
    Foo foo(1, 2);
    std::vector<int> vec = {1, 2, 3, 4, 5};

    std::cout << "arr[0]: " << arr[0] << std::endl;
    std::cout << "foo:" << foo.valueA << ", " << foo.valueB << std::endl;
}


/*-----------------------------------------------------------------------------------------------*/

class MagicFoo {
public:
    std::vector<int>vec;
    MagicFoo(std::initializer_list<int> list) {
        for (auto it = list.begin(); it != list.end(); ++it) {
            vec.push_back(*it);
        }
    }
};


/*-----------------------------------------------------------------------------------------------*/

void initializerList() {
    MagicFoo magicFoo {1, 2, 3, 4, 5};

    std::cout << "MagicFoo: ";
    for (auto it = magicFoo.vec.begin(); it != magicFoo.vec.end(); ++it) {
        std::cout << *it << std::endl;
    }
}

std::tuple<int, double, std::string> f() {
    return std::make_tuple(1, 2.3, "456");
}

/*-----------------------------------------------------------------------------------------------*/

void structedBinding() {
    auto [x, y, z] = f();
    std::cout << x << ", " << y << ", " << z << std::endl;
}

/*-----------------------------------------------------------------------------------------------*/

void testDecltype() {
    auto x = 1, y = 1;
    decltype(x + y) z;
    if (std::is_same<decltype(x), int>::value) {
        std::cout << "type x == int" << std::endl;
    }

    if (std::is_same<decltype(x), int>::value) {
        std::cout << "type x == float" << std::endl;
    }

    if (std::is_same<decltype(x), decltype((z))>::value) {
        std::cout << "type z == type x" << std::endl;
    }
}

/*-----------------------------------------------------------------------------------------------*/

template<typename R,typename  T, typename U>
R add(T x, U y) {
    return x + y;
}

template<typename T, typename U>
auto add2(T x, U y) -> decltype(x + y) {
    return x + y;
}

template<typename  T, typename U>
auto add3(T x, U y) {
    return x + y;
}

/*-----------------------------------------------------------------------------------------------*/

void testTailTypeInference() {
    // c++ 11
    auto w = add2<int, double>(1, 2.0);
    if (std::is_same<decltype(w), double>::value) {
        std::cout << "w is double: ";
    }

    std::cout << w << std::endl;

    // after c++14
    auto q = add3<double, int>(1.0, 2);
    std::cout << "q: " << q << std::endl;
}

/*-----------------------------------------------------------------------------------------------*/

template<typename T>
auto print_type_info(const T& t) {
    if constexpr (std::is_integral<T>::value) {
        return t + 1;
    } else {
        return t + 0.001;
    }
}

/*-----------------------------------------------------------------------------------------------*/

void testIfConstExpr() {
    std::cout << print_type_info(5) << std::endl;
    std::cout << print_type_info(3.14) << std::endl;
}

/*-----------------------------------------------------------------------------------------------*/

void testRangeBaseLoop() {
    std::vector<int> vec = {1, 2, 3, 4};
    if (auto itr = std::find(vec.begin(), vec.end(), 3); itr != vec.end()) {
        *itr = 4;
    }

    for (auto element : vec) {
        std:: cout << element << std::endl;
    }

    for (auto &element : vec) {
        element += 1;
    }

    for (auto element : vec) {
        std::cout << element << std::endl;
    }
}

/*-----------------------------------------------------------------------------------------------*/
template<typename T, typename U>
class MagicType {
public:
    T dark;
    U magic;
};

//template<typename T>
//typedef MagicType<std::vector<T>, std::string> FakeDarkMagic;

typedef int (*process)(void *);
using NewProcess = int(*)(void *);
template<typename T>
using TrueDarkMagic = MagicType<std::vector<T>, std::string>;

/*-----------------------------------------------------------------------------------------------*/
template<typename... Ts> class Magic;
//class Magic<int, std::vector<int>, std::map<std::string, std::vector<int>>> darkMargic;
//template<typename  Require, typename... Args> class Magic;
template<typename... Args> void printf(const std::string &str, Args... args);


template<typename... Ts>
void magic(Ts... args) {
    std::cout << sizeof...(args) << std::endl;
}

template<typename T0>
void printf1(T0 value) {
    std::cout << value << std::endl;
}

template<typename T, typename... Ts>
void printf1(T value, Ts... args) {
    std::cout << value << std::endl;
    printf1(args...);
}

template<typename T0, typename... T>
void printf2(T0 t0, T... t) {
    std::cout << t0 << std::endl;
    if constexpr(sizeof...(t) > 0) printf2(t...);
}

void testVariableLengthParameter() {
    printf1(1, 2, "123", 1.1);
}

template<typename T, typename... Ts>
auto printf3(T value, Ts... args) {
    std::cout << value << " ";
    (void)std::initializer_list<T>{([&args]{
        std::cout << args << " ";
    }(), value)...};

    std::cout << std::endl;
}

void testVariableLengthParameter2() {
    printf3(1, 2, 2.1, "123");
    printf3(1, 2, 2.5, "1234");
}

template<typename... T>
auto sum(T... t) {
    return (t + ...);
}

void testFoldExpression() {
    std::cout << sum(1, 2, 3, 4, 5) << std::endl;
}

void testDelegateConstructor() {
    Base b(2);
    std::cout << b.value1 << std::endl;
    std::cout << b.value2 << std::endl;
}


void testInheritanceConstructor() {
    Subclass s(3);
    std::cout << s.value1 << std::endl;
    std::cout << s.value2 << std::endl;
}

void Subclass2::foo(int) {
    std::cout << "123" << std::endl;
}

void Subclass3::foo(int) {
    std::cout << "456" << std::endl;
}

void testOverride() {
    Base2 *test1 = new Subclass2();
    test1->foo(1);
    Base2 *test2 = new Subclass3();
    test2->foo(2);
}

void compareEnum(new_enum en1, new_enum en2) {
    if (en1 == en2) {
        std::cout << "equal" << std::endl;
    }
}

void testStructuredBinding() {
    std::map<std::string, long long int> m {
            {"a", 1},
            {"b", 2},
            {"c", 3}
    };

    update(m, [](std::string key) {
        return std::hash<std::string>{}(key);
    });
    for (auto&& [key, value] : m)
        std::cout << key << ":" << value << std::endl;
}
