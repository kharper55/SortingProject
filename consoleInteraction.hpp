/* ============================================================================
consoleInteraction.hpp

Desc:   Console Operations for Array Sorting Project 
Course: Datastructures and Algorithms (CSCI2226)
Author: Kevin Harper
Date:   09/22/2024
============================================================================ */

#ifndef CONSOLE_INTERACTION_HPP
#define CONSOLE_INTERACTION_HPP

#include <iostream> // For console interaction
#include <cstring>  // For strlen
#include <cstdint>   // For uint_xxt types

using namespace std;

/* Defined in consoleInteraction.cpp, used in main.cpp */
extern const uint32_t FILE_SIZES[6];
extern const char * FILE_NAMES[6];
extern const char * FILE_NAMES_SORTED[6];
extern const char * FILE_NAMES_SORTED_REVERSE[6];
extern const char * ALGO_NAMES[6];

enum ALGOS {    /* enum value corresponds to array index in ALGO_NAMES */
    BUBBLE,
    SELECTION,
    INSERTION,
    MERGE,
    QUICK,
    SHELL
};

// Console interaction
void printCenteredTitle(const char * title, int col_width);
void printConsoleMenu(char quitChar);
char printConsoleSubMenu(char quitChar, char option);
void printConfiguration(uint32_t setSize, const char * sortingAlgo, bool sorted, bool reverseSorted);

#endif // CONSOLE_INTERACTION_HPP

/* ============================================================================
                                  END FILE
============================================================================ */