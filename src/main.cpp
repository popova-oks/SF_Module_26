#include "../headers/array.h"
#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

std::atomic<int> sum(0);

void calc_summ_of_piece(const int* arr, const int size_of_arr, const int size_of_piece,
                        const int n) {
    int local_sum(0);
    int array_begin = n * size_of_piece;

    for(int i = array_begin; i < array_begin + size_of_piece; i++) {
        if (i == size_of_arr) {
            break; // если достигнут конец массива, то выходим из цикла и завершаем поток.
        }
        local_sum += arr[i];
    }
    sum += local_sum;
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

    std::vector<std::thread> threads;

    int counts_items = size / counts_threads;
    int remainder = size - (counts_items*counts_threads);
    while (remainder > 1) {
        counts_items++;
        remainder = size - (counts_items*counts_threads);
    }

    for(int i = 0; i < counts_threads; i++) {
        std::thread t(calc_summ_of_piece, array.get_array(), size, counts_items, i);
        threads.push_back(std::move(t));
    }

    for(auto& t : threads) {
        t.join();
    }

    std::cout << "Summ of array: " << sum << std::endl;

    return 0;
}