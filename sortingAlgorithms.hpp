#ifndef SORTING_ALGORITHMS_HPP
#define SORTING_ALGORITHMS_HPP

#include <iostream> // For console interaction

using namespace std;

// Sorting algorithm implementations
void bubbleSort(int arr[], int arrLen);         // x
void selectionSort(int arr[], int arrLen);      // revise
void insertionSort(int arr[], int arrLen);      // revise
void mergeSort(int arr[], int l, int r);        // from programiz.com... revise to remove function call overhead?
void quickSort(int array[], int low, int high); // from programiz.com... revise to remove function call overhead?
void shellSort(int arr[], int arrLen);          // from programiz.com

#endif  // SORTING_ALGORITHMS_HPP