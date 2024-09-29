/* ============================================================================
utility.hpp

Desc:   Miscellaneous Functions for Array Sorting Project 
Course: Datastructures and Algorithms (CSCI2226)
Author: Kevin Harper
Date:   09/22/2024
============================================================================ */

#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <iostream> // For console interaction
#include <cstdint>  // For unsigned integer types

// Preprocessor stuff
enum MIN_MAX { MIN = 0, MAX }; // Sensible typedefs for findIndex() minMax param

using namespace std;

// Array helper functions
void reverseIntArray(uint32_t arr[], uint32_t arrLen);
int findMinMax(uint32_t arr[], uint32_t arrLen, const bool minMax);
int findValue(uint32_t arr[], uint32_t arrLen, uint32_t value);
void printIntArray(const char * arrLabel, uint32_t arr[], uint32_t arrLen, uint32_t maxColWidth);
void swap(uint32_t arr[], uint32_t arrLen, uint32_t idx1, uint32_t idx2);

#endif // UTILITY_HPP

/* ============================================================================
                                  END FILE
============================================================================ */