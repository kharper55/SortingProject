/* ============================================================================
sortingAlgorithms.cpp

Desc:   Sorting Algorithms for Array Sorting Project 
Course: Datastructures and Algorithms (CSCI2226)
Author: Kevin Harper
Date:   09/22/2024
============================================================================ */

/* NOTE: 
    All sorting algorithm implementations and pseudocode representations 
    borrowed from www.programiz.com/dsa and adapted as necessary. */

#include "sortingAlgorithms.hpp"
//#include "utility.hpp"           // For swap()... Omitted due to possible overhead

/* ============================================================================
algorithm bubbleSortOptimized(array[0...n-1])

// Input: array[0...n-1] - an array of integers to be sorted, length n

    for i from 0 to n - 2
        swapped <- false
        for j from 0 to n - 2 - i
            if array[j] > array[j + 1]
                swap(array[j], array[j + 1])
        if swapped is still false, break from loop

end bubbleSortOptimized
============================================================================ */
void bubbleSortOptimized(uint32_t arr[], uint32_t arrLen) {
    const bool VERBOSE = false;
    uint32_t i, j, temp;

    // Outer loop
    for (i = 0; i < arrLen - 1; i++) {
        bool swapped = false;
        // Inner loop
        for (j = 0; j < arrLen - i - 1; j++) {
            // Lower index value is greater than upper index value
            if (arr[j] > arr[j + 1]) {
                // Perform the swap
                temp = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = temp;
                swapped = true;
            }
        }
        if (swapped == false) break;
    }
}

/* ============================================================================
algorithm bubbleSort(array[0...n-1])

// Input: array[0...n-1] - an array of integers to be sorted, length n

    for i from 0 to n - 2
        for j from 0 to n - 2 - i
            if array[j] > array[j + 1]
                swap(array[j], array[j + 1])

end bubbleSort
============================================================================ */
void bubbleSort(uint32_t arr[], uint32_t arrLen) {
    const bool VERBOSE = false;
    uint32_t i, j, temp;

    // Outer loop
    for (i = 0; i < arrLen - 1; i++) {
        bool swapped = false;
        // Inner loop
        for (j = 0; j < arrLen - i - 1; j++) {
            // Lower index value is greater than upper index value
            if (arr[j] > arr[j + 1]) {
                // Perform the swap
                //swap(arr[j + 1], arr[j]);
                temp = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = temp;
                swapped = true;
            }
        }
        if (swapped == false) break;
    }
}

/* ============================================================================
algorithm selectionSort(array[0...n-1])

// Input: array[0...n-1] - an array of integers to be sorted, length n

    for i from 0 to n - 1 do
        minIdx <- i
        for j from i + 1 to n - 1 do
            if array[j] < array[minIdx]
                minIdx <- j
        if minIdx != i
            swap(array[i], array[minIdx])

end selectionSort
============================================================================ */
void selectionSort(uint32_t arr[], uint32_t arrLen) {
    uint32_t i, j, minIdx, temp;
    for (i = 0; i < arrLen - 1; i++) {   // Outer loop
        minIdx = i;                      // Preset the minimum location
        for (j = i + 1; j < arrLen; j++) {
            if (arr[j] < arr[minIdx]) { // A smaller value is found
                minIdx = j;             // Update the minIdx
            }
        }
        if (minIdx != i) {              // minIdx was updated (smaller value found)
            // Perform the swap. minIdx > i
            temp = arr[i];
            arr[i] = arr[minIdx];
            arr[minIdx] = temp;
        }
    }
}

/* ============================================================================
algorithm insertionSort(array[0...n-1])

// Input: array[0...n-1] - an array of integers to be sorted, length n

    for i from 1 to n - 1
        key <- array[i]
        j <- i - 1
        while j >= 0 and array[j] > key
            array[j + 1] <- array[j]
            j <- j - 1
        array[j + 1] <- key

end insertionSort
============================================================================ */
void insertionSort(uint32_t arr[], uint32_t arrLen) {
    uint32_t i, key;
    int32_t j; // must be signed to allow termination of algorithm

    // Assume first index is sorted
    for (i = 1; i < arrLen; i++) {
        key = arr[i];
        j = i - 1;
        // Search for an element that is less than the predeclared key value
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j]; // Push back element, making room for key value
            j -= 1;
        }
        arr[j + 1] = key;   // Insert the key value at the found location
    }
}

/* ============================================================================
algorithm merge(array[0...n-1], p, q, r)

// Inputs: array[0...n-1] - an array of integers to be sorted, length n
//         p - starting index of the first subarray
//         q - ending index of the first subarray
//         r - ending index of the second subarray

    // Determine the size of the two subarrays
    n1 = q - p + 1
    n2 = r - q

    // Create temporary arrays L and M
    create L[n1] containing elements array[p...n1 - 1]
    create M[n2] containing elements array[q + 1...n2 - 1]

    // Initialize pointers for L, M, and array[0...n - 1]
    i <- 0     // Pointer for L
    j <- 0     // Pointer for M
    k <- p     // Pointer for array

    // Merge the two subarrays back into array[0...n - 1]
    while i < n1 and j < n2 do
        if L[i] <= M[j] then
            array[k] = L[i]
            i = i + 1
        else
            array[k] = M[j]
            j = j + 1
        k = k + 1

    // Copy remaining elements from L[] into array[], if any
    while i < n1 do
        arr[k] = L[i]
        i = i + 1
        k = k + 1

    // Copy remaining elements from M[] into array[], if any
    while j < n2 do
        arr[k] = M[j]
        j = j + 1
        k = k + 1

end merge
============================================================================ */
static void merge(uint32_t arr[], uint32_t p, uint32_t q, uint32_t r) {

    // Create L ← A[p..q] and M ← A[q+1..r]
    uint32_t n1 = q - p + 1;
    uint32_t n2 = r - q;

    //int L[n1], M[n2];
    // Dynamic allocation to circumvent segfaults with recursive implementation
    uint32_t *L = new uint32_t[n1];
    uint32_t *M = new uint32_t[n2];

    for (int i = 0; i < n1; i++) {
        L[i] = arr[p + i];
    }
        
    for (int j = 0; j < n2; j++) {
        M[j] = arr[q + 1 + j];
    }
        
    // Maintain current index of sub-arrays and main array
    uint32_t i, j, k;
    i = 0;
    j = 0;
    k = p;

    // Until we reach either end of either L or M, pick larger among
    // elements L and M and place them in the correct position at A[p..r]
    while (i < n1 && j < n2) {
        if (L[i] <= M[j]) {
            arr[k] = L[i];
            i++;
        } 
        else {
            arr[k] = M[j];
            j++;
        }
        k++;
    }

    // When we run out of elements in either L or M,
    // pick up the remaining elements and put in A[p..r]
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = M[j];
        j++;
        k++;
    }

    // Free dynamically allocated memory
    delete[] L;
    delete[] M;
}

/* ============================================================================
algorithm mergeSort(array[0...n-1], leftIdx, rightIdx)

// Input: array[0...n-1] - an array of integers to be sorted, length n
//        leftIdx - the index of the first element in the current subarray
//        rightIdx - the index of the last element in the current subarray

    // Base case
    if leftIdx >= rightIdx 
        return
    
    // Recursive case
    midIdx = (leftIdx + (rightIdx - leftIdx)) / 2
    mergeSort(array, leftIdx, midIdx)
    mergeSort(array, midIdx + 1, rightIdx)
    merge(array, leftIdx, midIdx, rightIdx)

end mergeSort
============================================================================ */
void mergeSort(uint32_t arr[], uint32_t l, uint32_t r) {
    if (l < r) {

        // m is the point where the array is divided into two subarrays
        uint32_t m = l + (r - l) / 2;

        // Recursive call on left half of subarray
        mergeSort(arr, l, m);

        // Recursive call on right half of subarray
        mergeSort(arr, m + 1, r);

        // Merge the sorted subarrays
        merge(arr, l, m, r);
    }
}

/* ============================================================================
algorithm medianOfThree(array[0...n-1], leftIdx, rightIdx)

// Inputs: array[0...n-1] - an array of integers to be sorted, length n
//         leftIdx - the index of the first element in the current subarray
//         rightIdx - the index of the last element in the current subarray

    midIdx = leftIdx + (rightIdx - leftIdx) / 2
    
    // Ensure array[leftIdx] <= array[midIdx] <= array[rightIdx]
    if array[leftIdx] > array[midIdx]:
        swap(array[leftIdx], array[mid])
    if array[leftIdx] > array[rightIdx]:
        swap(array[leftIdx], array[rightIdx])
    if array[midIdx] > array[rightIdx]:
        swap(array[midIdx], array[rightIdx])
    
    // Move the median (arr[mid]) to the end for use as the pivot
    swap(array[midIdx], array[rightIdx])
    
    // Return value of the pivot
    return array[rightIdx]

end medianOfThree
============================================================================ */
static uint32_t medianOfThree(uint32_t arr[], int32_t low, int32_t high) {
    uint32_t mid = low + (high - low) / 2;
    
    if (arr[low] > arr[mid]) {
        // swap arr[low] and arr[mid]
        uint32_t temp = arr[low];
        arr[low] = arr[mid];
        arr[mid] = temp;
    }
    if (arr[low] > arr[high]) {
        // swap arr[low] and arr[high]
        uint32_t temp = arr[low];
        arr[low] = arr[high];
        arr[high] = temp;
    }
    if (arr[mid] > arr[high]) {
        // swap arr[mid] and arr[high]
        uint32_t temp = arr[mid];
        arr[mid] = arr[high];
        arr[high] = temp;
    }
    
    // Use the middle element as the pivot by swapping it to the end
    uint32_t temp = arr[mid];
    arr[mid] = arr[high];
    arr[high] = temp;
    
    return arr[high];  // pivot is now at arr[high]
}

/* ============================================================================
algorithm partition(array[0...n-1], leftIdx, rightIdx)

// Inputs: array[0...n-1] - an array of integers to be sorted, length n
//         leftIdx - the index of the first element in the current subarray
//         rightIdx - the index of the last element in the current subarray

    pivotVal <- medianOfThree(array, leftIdx, rightIdx)
    storeIdx <- leftIdx - 1
    for i <- leftIdx + 1 to rightIdx
        if array[i] <= pivotVal
            storeIdx <- storeIdx + 1
            swap(array[i], array[storeIdx])
    swap(array[rightIdx], array[storeIdx + 1])
    return storeIdx + 1

end partition
============================================================================ */
static uint32_t partition(uint32_t arr[], int32_t low, int32_t high) {

    // select the rightmost element as pivot
    // int pivot = arr[high]; // old pivot selection caused segfaults
    uint32_t pivot = medianOfThree(arr, low, high); // better pivot selection
    uint32_t temp = 0;

    // pointer for greater element
    int32_t i = low - 1;

    // traverse each element of the array
    // compare them with the pivot
    for (uint32_t j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            
            // if element smaller than pivot is found
            // swap it with the greater element pointed by i
            i++;
            
            // swap element at i with element at j
            //swap(&array[i], &array[j]);
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    // swap the pivot element with the greater element at i
    temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    // return the partition point
    return (i + 1);
}

/* ============================================================================
algorithm quickSort(array[0...n-1], leftIdx, rightIdx)

// Inputs: array[0...n-1] - an array of integers to be sorted, length n
//         leftIdx - the index of the first element in the current subarray
//         rightIdx - the index of the last element in the current subarray

    // Base case
    if (leftIdx >= rightIdx)
        return

    // Recursive case
    pivotIdx <- partition(array, leftIdx, rightIdx)
    quickSort(array, leftIdx, pivotIdx - 1)
    quickSort(array, pivotIdx + 1, rightIdx)

end quickSort
============================================================================ */
void quickSort(uint32_t array[], int32_t low, int32_t high) {
    if (low < high) {

        // find the pivot element such that
        // elements smaller than pivot are on left of pivot
        // elements greater than pivot are on right of pivot
        uint32_t pi = partition(array, low, high);

        // recursive call on the left of pivot
        quickSort(array, low, pi - 1);

        // recursive call on the right of pivot
        quickSort(array, pi + 1, high);
    }
}

/* ============================================================================
algorithm shellSort(array[0...n-1])

// Input: array[0...n-1] - an array of integers to be sorted, length n

    m <- 1
    for interval i <- floor(n / 2^m) 
        for each interval "i" in array
            sort all the elements at interval "i"
        m <- m + 1
            
end shellSort
============================================================================ */
void shellSort(uint32_t arr[], uint32_t arrLen) {
    // Rearrange elements at each arrLen/2, arrLen/4, arrLen/8, ... intervals
    // ie Shell's original sequence.
    for (uint32_t interval = arrLen / 2; interval > 0; interval /= 2) {
        for (uint32_t i = interval; i < arrLen; i += 1) {
            int temp = arr[i];
            int j;
            for (j = i; j >= interval && arr[j - interval] > temp; j -= interval) {
                arr[j] = arr[j - interval];
            }
            arr[j] = temp;
        }
    }
}

/* ============================================================================
                                  END FILE
============================================================================ */