/* ============================================================================
fileHandling.hpp

Desc:   File Operations for Array Sorting Project 
Course: Datastructures and Algorithms (CSCI2226)
Author: Kevin Harper
Date:   09/22/2024
============================================================================ */

#ifndef FILE_HANDLING_HPP
#define FILE_HANDLING_HPP

#include <iostream>   // For console interaction
#include <cstdint>    // For unambiguous standard integer sizes
#include <random>     // For random device and mersenne twister implementation
#include <set>        // For checking uniqueness
#include <fstream>    // For file IO
#include <filesystem> // For folder creation

using namespace std;

// File I/O
bool fileWriteRandInts(const char * fileName, ofstream &fileHandle, uint32_t numIterations);
bool fileReadRandInts(const char * fileName, ifstream &fileHandle, int buff[], int buffLen);
bool fileExists(const char * fileName);
bool fileWrite(const char * fileName, ofstream &fileHandleWr, int * arr, int arrLen);
bool createDir(const char * dirName);

#endif // FILE_HANDLING_HPP

/* ============================================================================
                                  END FILE
============================================================================ */