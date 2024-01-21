//
// Created by ByteDance on 18/10/23.
//

#include <vector>
#include <iostream>
#include <algorithm>
#include <array>
#include <unordered_map>
#include <map>
#include <string>
#include "container.h"

void testContainer() {
    std::vector<int>v;
    std::cout << "size:" << v.size() << std::endl;
    std::cout << "capacity:" << v.capacity() << std::endl;

    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    std::cout << "size:" << v.size() << std::endl;
    std::cout << "capacity:" << v.capacity() << std::endl;


    v.push_back(4);
    v.push_back(5);
    v.push_back(-20);
    std::sort(v.begin(), v.end(), [&](int &a, int &b) {
        return a > b;
    });

    std::cout << "size:" << v.size() << std::endl;
    std::cout << "capacityL" << v.capacity() << std::endl;

    v.clear();
    std::cout << "size:" << v.size() << std::endl;
    std::cout << "capacity:" << v.capacity() << std::endl;

    v.shrink_to_fit();
    std::cout << "size:" << v.size() << std::endl;
    std::cout << "capacity:" << v.capacity() << std::endl;
}

void testList() {
    std::array<int, 4> arr = {1, 2, 3, 4};
    arr.empty();
    arr.size();

    for (auto &i : arr) {
        //...
    }

    std::sort(arr.begin(), arr.end(), [](int a, int b) {
        return b > a;
    });

    constexpr int len = 4;
    std::array<int, len> arr2 = {1, 2, 3, 4};
}

void foo(int *p, int len) {
    return;
}

void testArrayCCompatible() {
    std::array<int, 4> arr = {1, 2, 3, 4};
    foo(&arr[0], arr.size());
    foo(arr.data(), arr.size());

    std::sort(arr.begin(), arr.end());
}

void testUnorderedMap() {
    std::unordered_map<int, std::string> unMap = {
            {2, "2"},
            {1, "1"},
            {3, "3"},
    };

    std::map<int, std::string> mp = {
            {2, "2"},
            {1, "1"},
            {3, "3"},
    };

    for (auto &it : unMap) {
        std::cout << it.first << " " << it.second << std::endl;
    }

    for (auto &it : mp) {
        std::cout << it.first << "*" << it.second << std::endl;
    }
}

auto getStudent(int id) {
    if (id == 0) {
        return std::make_tuple(3.8, 'A', "John");
    }

    if (id == 1) {
        return std::make_tuple(2.9, 'C', "Jack");
    }

    if (id == 2) {
        return std::make_tuple(1.7, 'D', "Ive");
    }

    return std::make_tuple(0.0, 'D', "null");
}

void testTuple() {
    auto student = getStudent(0);
    std::cout << "ID: 0, "
              << "GPA: " << std::get<0>(student) << ", "
              << "Grade: " << std::get<1>(student) << ", "
              << "Name: " << std::get<2>(student) << '\n';

    double gpa;
    char grade;
    std::string name;

    std::tie(gpa, grade, name) = getStudent(1);
    std::cout << "ID: 1, "
              << "GPA: " << gpa << ", "
              << "Grade: " << grade << ", "
              << "Name: " << name << '\n';
}

void testVariant() {
    std::tuple<std::string, double, double, int> t("123", 4.5, 6.7, 8);
    int i = 2;
    std::cout << tuple_index(t, i) << std::endl;

    auto new_tuple = std::tuple_cat(getStudent(1), std::move(t));

}

template<typename  T>
auto tupleLen(T &tpl) {
    return std::tuple_size<T>::value;
}
