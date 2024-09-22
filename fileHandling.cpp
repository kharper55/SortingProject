/* ============================================================================
fileHandling.cpp

Desc:   File Operations for Array Sorting Project 
Course: Datastructures and Algorithms (CSCI2226)
Author: Kevin Harper
Date:   09/22/2024
============================================================================ */

#include "fileHandling.hpp"

const char * datasetFolderPath = "Datasets";

/* ============================================================================

============================================================================ */
bool createDir(const char * dirName) {
    filesystem::path folderPath = dirName;

    // Create the folder if it doesn't exist
    if (!filesystem::exists(folderPath)) {
        if (filesystem::create_directory(folderPath)) {
            cout << "\nCreated folder: " << folderPath << ".\n";
            return true; // Folder created successfully
        } else {
            cerr << "\nFailed to create folder: " << folderPath << ".\n";
            return false; // Folder creation failed
        }
    } 
    else {
        return true; // Folder already exists
    }
}

/* ============================================================================

============================================================================ */
bool fileExists(const char * fileName) {
    bool ret;
    filesystem::path filePath = datasetFolderPath / static_cast<filesystem::path>(fileName);
    ifstream file(filePath);

    ret = file.good();
    file.close();
    
    return ret;
}

/* ============================================================================
Function to populate a .txt file with random uint32_t's, newline delimited.
============================================================================ */
bool fileWriteRandInts(const char *fileName, ofstream &fileHandle, uint32_t numIterations) {
    const bool VERBOSE = false;
    const uint32_t MIN_VALUE = 0;       // Minimum value for random number
    const uint32_t MAX_VALUE = 4000000  /*numIterations - 2*/; // Maximum value for random number
    uint32_t randNum;                   // Random number
    set<uint32_t> uniqueNumbers;        // Container for unique numbers in the file
    bool ret = false;

    random_device rd;
    mt19937 gen(rd());

    // Produces random integer values i, uniformly distributed on the closed interval [a,b] (inclusive of endpoints)
    // https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
    uniform_int_distribution<uint32_t> dis(MIN_VALUE, MAX_VALUE);

    createDir(datasetFolderPath);
    filesystem::path filePath = datasetFolderPath / static_cast<filesystem::path>(fileName);

    // Check if the generation of numIterations randNums is possible
    if (((MAX_VALUE - MIN_VALUE) >= numIterations - 1) && (MAX_VALUE > MIN_VALUE)) {
        // Open the specified file for writing (overwrite mode)
        fileHandle.open(filePath);

        if (fileHandle.is_open()) {
            // Generate and write numIterations distinct random numbers
            while (uniqueNumbers.size() < numIterations) {
                // Generate a random number in the range [MIN_VALUE, MAX_VALUE]
                randNum = dis(gen);

                // Check if the number is unique
                if (uniqueNumbers.find(randNum) == uniqueNumbers.end()) {
                    uniqueNumbers.insert(randNum);  // implicitly updates set.size()

                    fileHandle << randNum;
                    if (uniqueNumbers.size() < numIterations) {
                        fileHandle << '\n';
                    }

                    if (VERBOSE) {
                        cout << "Wrote distinct random integer " << uniqueNumbers.size() 
                            << " with value " << randNum << "\n";
                    }
                }

                else { 
                    if (VERBOSE) {
                        cout << "Integer " << randNum << " already exists in the file.\n";
                    }
                }
            }

            // Close the file
            fileHandle.close();
            ret = true;
        }
        else {
            cout << "File failed to open for writing.\n";
        }
    }
    else {
        cout << "Requested integer range ([" << MIN_VALUE << ":" << MAX_VALUE 
             << "]) is impossible to be satisfied\nwith " << numIterations 
             << " random integers.\n";
    }
    return ret;
}

/* ============================================================================

============================================================================ */
bool fileReadRandInts(const char * fileName, ifstream &fileHandle, int buff[], int buffLen) {
    bool ret = false;
    uint32_t i = 0;
    string lineBuff;
    filesystem::path filePath = datasetFolderPath / static_cast<filesystem::path>(fileName);

    fileHandle.open(filePath);
    if (fileHandle.is_open()) {
        while(i < buffLen) {
            getline(fileHandle, lineBuff);
            buff[i++] = stoi(lineBuff);
        }
        fileHandle.close();
        ret = true;
    }
    else {
        cout << "File failed to open for reading.\n";
    }
    return ret;
}

/* ============================================================================

============================================================================ */
bool fileWrite(const char *fileName, ofstream &fileHandle, int * arr, int arrLen) {
    bool ret = 1;
    filesystem::path filePath = datasetFolderPath / static_cast<filesystem::path>(fileName);

    fileHandle.open(filePath);

    if (fileHandle.is_open()) {
        for (int i = 0; i < arrLen; i++) {
            fileHandle << arr[i];
            if (i != arrLen - 1) {
                fileHandle << '\n';
            }
        }
        fileHandle.close();
    }
    else {
        cout << "File failed to open for writing.\n";
        ret = 0;
    }
    return ret;
}

/* ============================================================================
                                  END FILE
============================================================================ */