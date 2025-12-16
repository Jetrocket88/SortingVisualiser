#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <stddef.h>

void insertionSort(int *arr, size_t n);
int partition(int *arr, int low, int high);
void quickSort(int *arr, int low, int high);

#endif
