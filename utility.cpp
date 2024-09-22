/* ============================================================================
utility.cpp

Desc:   Miscellaneous Functions for Array Sorting Project 
Course: Datastructures and Algorithms (CSCI2226)
Author: Kevin Harper
Date:   09/22/2024
============================================================================ */

#include "utility.hpp"

/* ============================================================================

============================================================================ */
int findIndex(int arr[], int arrLen, const bool minMax) {
    int selIndex = 0;
    int val = arr[0];
    int i = 0;

    if (arrLen <= 0) {
        return -1; // or handle empty array case
    }

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
This function reverses a sorted integer array.
============================================================================ */
void reverseIntArray(int arr[], int arrLen) {
    
    int temp, upperIdx, lowerIdx = 0;
    for (upperIdx = arrLen - 1; upperIdx >= arrLen / 2; upperIdx--) {
        temp = arr[upperIdx];
        arr[upperIdx] = arr[lowerIdx];
        arr[lowerIdx] = temp;
        lowerIdx++;
    }
}

/* ============================================================================

============================================================================ */
void printIntArray(const char * arrLabel, int arr[], int arrLen, int maxColWidth) {
    cout << "\nArray contents for " << arrLabel << ":\n{";
    for (int i = 0; i < arrLen; i++) {
        cout << arr[i];

        if (i != arrLen - 1) cout << ", ";
        else cout << "}";

        if (((i + 1) % maxColWidth == 0) && (i != 0) && (i != arrLen - 1)) cout << "\n ";
        else if (i == arrLen - 1) {
            cout << "\n";
        }
    }
}

/* ============================================================================
                                  END FILE
============================================================================ */