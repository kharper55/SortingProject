#ifndef CONSOLE_INTERACTION_HPP
#define CONSOLE_INTERACTION_HPP

#include <iostream> // For console interaction
#include <cstring>  // For strlen

using namespace std;

extern const int FILE_SIZES[6];
extern const char * FILE_NAMES[6];
extern const char * FILE_NAMES_SORTED[6];
extern const char * FILE_NAMES_SORTED_REVERSE[6];
extern const char * ALGO_NAMES[6];

// Console interaction
void printCenteredTitle(const char * title, int col_width);
void printConsoleMenu(char quitChar);
char printConsoleSubMenu(char quitChar, char option);
void printConfiguration(int setSize, const char * sortingAlgo, bool sorted, bool reverseSorted);

#endif // CONSOLE_INTERACTION_HPP