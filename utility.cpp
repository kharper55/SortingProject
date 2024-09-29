/* ============================================================================
utility.cpp

Desc:   Miscellaneous Functions for Array Sorting Project 
Course: Datastructures and Algorithms (CSCI2226)
Author: Kevin Harper
Date:   09/22/2024
============================================================================ */

#include "utility.hpp"

/* ============================================================================
Find the minimum or maximum index in an array.
============================================================================ */
int findMinMax(uint32_t arr[], uint32_t arrLen, const bool minMax) {
    int selIndex = 0;
    int val = arr[0];
    int i = 0;

    if (arrLen <= 0) {
        return -1; // handle empty array case
    }

    // Search array for specified value (minimum or maximum)
    for (i = 1; i < arrLen; i++) {
        if (minMax == MIN) {
            if (arr[i] < val) {
                val = arr[i];
                selIndex = i;
            }
        } 
        else { // minMax == MAX
            if (arr[i] > val) {
                val = arr[i];
                selIndex = i;
            }
        }
    }
    return selIndex;
}

/* ============================================================================
Find first instance of a given unsigned integer value and return it's array 
index. Returns -1 if index not found.
============================================================================ */
int findValue(uint32_t arr[], uint32_t arrLen, uint32_t value) {
    if (arrLen <= 0) {
        return -1; // handle empty array case
    }

    // Search array for specified value
    for (int i = 0; i < arrLen; i++) {
        if (arr[i] == value) {
            return i; // Break early
        }
    }
    return -1;
}

/* ============================================================================
Reverse an assumed-to-be sorted integer array.
============================================================================ */
void reverseIntArray(uint32_t arr[], uint32_t arrLen) {
    int temp, upperIdx, lowerIdx = 0;

    // Starting from opposite ends of the array, swap values, then increment the
    // beginning pointer and decrement the end pointer until the middle of the 
    // array is reached
    for (upperIdx = arrLen - 1; upperIdx >= arrLen / 2; upperIdx--) {
        temp = arr[upperIdx];
        arr[upperIdx] = arr[lowerIdx];
        arr[lowerIdx] = temp;
        lowerIdx++;
    }
}

/* ============================================================================
Print an integer array to the console, with maxColWidth entries per line.
============================================================================ */
void printIntArray(const char * arrLabel, uint32_t arr[], uint32_t arrLen, uint32_t maxColWidth) {
    cout << "\nArray contents for " << arrLabel << ":\n{";
    for (int i = 0; i < arrLen; i++) {
        cout << arr[i];

        // Separate elements by a comma unless end of array is reached
        if (i != arrLen - 1) cout << ", ";
        else cout << "}";

        // Print a newline for every maxColWidth elements printed
        if (((i + 1) % maxColWidth == 0) && (i != 0) && (i != arrLen - 1)) cout << "\n ";
        else if (i == arrLen - 1) {
            cout << "\n";
        }
    }
}

/* ============================================================================
Swap value at idx1 with value at idx2. 
This function not used to limit overhead of function call with potentially 
large array arguments.
============================================================================ */
void swap(uint32_t arr[], uint32_t arrLen, uint32_t idx1, uint32_t idx2) {
    // Check for valid indices
    if (((idx1 < arrLen) && (idx2 < arrLen)) && idx1 != idx2) {
        // Swap the elements
        int temp = arr[idx1];
        arr[idx1] = arr[idx2];
        arr[idx2] = temp;
    }
}

/* ============================================================================
                                  END FILE
============================================================================ */