#include "../headers/array.h"
#include <iostream>

Array::Array() : size_arr(0), arr(nullptr) {}
Array::Array(int n) : size_arr(n), arr(new int[n]) {}
Array::~Array() {
    if(arr != nullptr) {
        delete[] arr;
    }
}

void Array::set_size_arr(int n) { size_arr = n; }

void Array::fill_array(int n) {
    if(arr == nullptr) {
        arr = new int[n];
    }
    for(int i = 0; i < n; i++) {
        arr[i] = rand() % n; //генерация случайного числа от 0 до n
    }
}

// void Array::operator()(const std::string msg) { std::cout << msg << std::endl; }