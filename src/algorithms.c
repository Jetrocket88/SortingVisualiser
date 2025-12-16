#include "../headers/algorithms.h"

void insertionSort(int *arr, size_t n) {

    for(size_t i = 1; i < n; i++) {
        int value = arr[i];
        size_t position = i;
        while(position > 0 && arr[position - 1] > value) {
            arr[position] = arr[position - 1];
            position--;
        }
        arr[position] = value;
    }
}
