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
#include <set>        // For checking uniqueness of random integers
#include <fstream>    // For file IO
#include <filesystem> // For folder creation

using namespace std;

// File I/O
bool fileWriteRandInts(const char * fileName, ofstream &fileHandle, uint32_t numIterations);
bool fileRead(const char * fileName, ifstream &fileHandle, uint32_t buff[], uint32_t buffLen);
bool fileExists(const char * fileName);
bool fileWrite(const char * fileName, ofstream &fileHandleWr, uint32_t arr[], uint32_t arrLen);
bool createDir(const char * dirName);

#endif // FILE_HANDLING_HPP

/* ============================================================================
                                  END FILE
============================================================================ */