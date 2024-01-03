#pragma once
#include <iostream>

class Array
{
public:
    Array();
    Array(int n);
    ~Array();
    void set_size_arr(int n);
    void fill_array(int n);
    int* get_array() {return arr;}
private:
    int size_arr;
    int *arr;
};