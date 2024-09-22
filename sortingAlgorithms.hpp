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

// Sorting algorithm implementations
void bubbleSort(int arr[], int arrLen);                 // https://www.programiz.com/dsa/bubble-sort
void selectionSort(int arr[], int arrLen);              // https://www.programiz.com/dsa/selection-sort
void insertionSort(int arr[], int arrLen);              // https://www.programiz.com/dsa/insertion-sort
static void merge(int arr[], int p, int q, int r);
void mergeSort(int arr[], int l, int r);                // https://www.programiz.com/dsa/merge-sort
static int medianOfThree(int arr[], int low, int high); // partition pivot selection
static int partition(int arr[], int low, int high);
void quickSort(int array[], int low, int high);         // https://www.programiz.com/dsa/quick-sort
void shellSort(int arr[], int arrLen);                  // https://www.programiz.com/dsa/shell-sort

#endif  // SORTING_ALGORITHMS_HPP

/* ============================================================================
                                  END FILE
============================================================================ */