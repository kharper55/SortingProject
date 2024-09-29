/* ============================================================================
sortingAlgorithms.hpp

Desc:   Sorting Algorithms for Array Sorting Project 
Course: Datastructures and Algorithms (CSCI2226)
Author: Kevin Harper
Date:   09/22/2024
============================================================================ */

#ifndef SORTING_ALGORITHMS_HPP
#define SORTING_ALGORITHMS_HPP

using namespace std;

#include <cstdint> // For standard unsigned integer sizes

// Sorting algorithm implementations
void bubbleSort(uint32_t arr[], uint32_t arrLen);                         // https://www.programiz.com/dsa/bubble-sort
void bubbleSortOptimized(uint32_t arr[], uint32_t arrLen);
void selectionSort(uint32_t arr[], uint32_t arrLen);                      // https://www.programiz.com/dsa/selection-sort
void insertionSort(uint32_t arr[], uint32_t arrLen);                      // https://www.programiz.com/dsa/insertion-sort
static void merge(uint32_t arr[], uint32_t p, uint32_t q, uint32_t r);
void mergeSort(uint32_t arr[], uint32_t l, uint32_t r);                   // https://www.programiz.com/dsa/merge-sort
static uint32_t medianOfThree(uint32_t arr[], int32_t low, int32_t high); // partition pivot selection
static uint32_t partition(uint32_t arr[], int32_t low, int32_t high);
void quickSort(uint32_t array[], int32_t low, int32_t high);              // https://www.programiz.com/dsa/quick-sort
void shellSort(uint32_t arr[], uint32_t arrLen);                          // https://www.programiz.com/dsa/shell-sort

#endif  // SORTING_ALGORITHMS_HPP

/* ============================================================================
                                  END FILE
============================================================================ */