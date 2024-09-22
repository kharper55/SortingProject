#ifndef FILE_HANDLING_HPP
#define FILE_HANDLING_HPP

#include <iostream> // For console interaction
#include <cstdint>  // For unambiguous standard integer sizes
#include <random>   // For random device and mersenne twister implementation
#include <set>      // For checking uniqueness
#include <fstream>  // For file IO

using namespace std;

// File I/O
bool fileWriteRandInts(const char * fileName, ofstream &fileHandle, uint32_t numIterations);
bool fileReadRandInts(const char * fileName, ifstream &fileHandle, int buff[], int buffLen);
bool fileExists(const string& filename);
bool fileWrite(const char *fileName, ofstream &fileHandleWr, int * arr, int arrLen);

#endif // FILE_HANDLING_HPP