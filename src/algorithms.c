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

int parition(int* arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j <= high; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}

void quickSort(int* arr, int low, int high) {
    if (low < high) {
        int pi = parition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

