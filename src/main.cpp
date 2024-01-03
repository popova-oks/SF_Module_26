#include "../headers/array.h"
#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

std::atomic<int> sum(0);

void calc_summ_of_piece(const int* arr, const int size_of_arr, const int size_of_piece,
                        const int n) {
    int local_sum(0);
    int array_begin = n * size_of_piece;
    if (array_begin >= size_of_arr) {
        return;
    }
    int array_end = array_begin + size_of_piece;
    if (array_end > size_of_arr) {
        array_end = size_of_arr;
    }
    for(int i = array_begin; i < array_end; i++) {
        local_sum += arr[i];
    }
    sum += local_sum;
}

int calculate_using_threads(int* array, const int size, const int counts_threads) {
    std::vector<std::thread> threads;

    int counts_items = size / counts_threads;
    int remainder = size - (counts_items*counts_threads);
    while (remainder > 1) {
        counts_items++;
        remainder = size - (counts_items * counts_threads);
    }

    for(int i = 0; i < counts_threads; i++) {
        std::thread t(calc_summ_of_piece, array, size, counts_items, i);
        threads.push_back(std::move(t));
    }

    for(auto& t : threads) {
        t.join();
    }
    return sum;
}

int calculate_without_threads(int* array, const int size) {
    int local_sum(0);
    for(int i = 0; i < size; i++) {
        local_sum += array[i];
    }
    return local_sum;
}

int main() {
    //создание массива и заполнение его случайными числами в диапазоне от 0 до
    std::cout << "Enter the size of your array: ";
    int size(0);
    std::cin >> size;
    Array array(size);
    array.fill_array(size);

    std::cout << "Enter the counts of threads: ";
    int counts_threads(0);
    std::cin >> counts_threads;

    // calculate sum using threads
    auto t_start = std::chrono::system_clock::now();
    int sum = calculate_using_threads(array.get_array(), size, counts_threads);
    auto t_end = std::chrono::system_clock::now();
    long diff = std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_start).count();
    std::cout << "Using threads: " << counts_threads << " is sum: " << sum
              << "  time (ms): " << diff << std::endl;

    // calculate sum in main thread
    t_start = std::chrono::system_clock::now();
    sum = calculate_without_threads(array.get_array(), size);
    t_end = std::chrono::system_clock::now();
    diff = std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_start).count();
    std::cout << "Without threads is summ: " << sum << "  time (ms): " << diff << std::endl;

    return 0;
}