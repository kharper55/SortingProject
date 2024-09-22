#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <iostream> // For console interaction

// Preprocessor stuff
enum MIN_MAX { MIN = 0, MAX };

using namespace std;

// Array helper functions
void reverseIntArray(int arr[], int arrLen);
int findIndex(int arr[], int arrLen, const bool minMax);
void printIntArray(const char * arrLabel, int arr[], int arrLen, int maxColWidth);

#endif // UTILITY_HPP