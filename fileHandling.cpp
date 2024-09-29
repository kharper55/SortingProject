/* ============================================================================
fileHandling.cpp

Desc:   File Operations for Array Sorting Project 
Course: Datastructures and Algorithms (CSCI2226)
Author: Kevin Harper
Date:   09/22/2024
============================================================================ */

#include "fileHandling.hpp"

/* Folder name for containing dataset files */
const char * datasetFolderPath = "Datasets";

/* Allow a range of 4000000 items for random integer generation */
const uint32_t MIN_RAND_VALUE = 1;       // Minimum value for random number
const uint32_t MAX_RAND_VALUE = 4000000; // Maximum value for random number

/* ============================================================================
Create a directory for storing files.
============================================================================ */
bool createDir(const char * dirName) {
    filesystem::path folderPath = dirName;

    // Create the folder if it doesn't exist
    if (!filesystem::exists(folderPath)) {
        if (filesystem::create_directory(folderPath)) {
            cout << "\nCreated folder: " << folderPath << ".\n";
            return true; // Folder created successfully
        } else {
            cout << "\nFailed to create folder: " << folderPath << ".\n";
            return false; // Folder creation failed
        }
    } 
    else {
        return true; // Folder already exists
    }
}

/* ============================================================================
Check if a file exists.
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
Function to populate an arbitrary file type with random uint32_t's, 
newline delimited.
============================================================================ */
bool fileWriteRandInts(const char *fileName, ofstream &fileHandle, uint32_t numIterations) {
    const bool VERBOSE = false;
    uint32_t randNum;                   // Random number
    set<uint32_t> uniqueNumbers;        // Container for unique numbers in the file
    bool ret = false;

    random_device rd;
    mt19937 gen(rd());

    // Produces random integer values i, uniformly distributed on the closed interval [a,b] (inclusive of endpoints)
    // https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
    uniform_int_distribution<uint32_t> dis(MIN_RAND_VALUE, MAX_RAND_VALUE);

    createDir(datasetFolderPath);
    filesystem::path filePath = datasetFolderPath / static_cast<filesystem::path>(fileName);

    // Check if the generation of numIterations randNums is possible
    if (((MAX_RAND_VALUE - MIN_RAND_VALUE) >= numIterations - 1) && (MAX_RAND_VALUE > MIN_RAND_VALUE)) {
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

                    // Write the number to the file
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
        cout << "Requested integer range ([" << MIN_RAND_VALUE << ":" << MAX_RAND_VALUE 
             << "]) is impossible to be satisfied\nwith " << numIterations 
             << " random integers.\n";
    }
    return ret;
}

/* ============================================================================
Read integers into an array buffer from a file.
============================================================================ */
bool fileRead(const char * fileName, ifstream &fileHandle, uint32_t buff[], uint32_t buffLen) {
    bool ret = false;
    uint32_t i = 0;
    string lineBuff;
    filesystem::path filePath = datasetFolderPath / static_cast<filesystem::path>(fileName);

    fileHandle.open(filePath);
    if (fileHandle.is_open()) {
        while(i < buffLen) {
            // Read in file entries to buffer
            getline(fileHandle, lineBuff);
            buff[i++] = stoi(lineBuff);
        }
        fileHandle.close();
        if (i == buffLen) {
            ret = true;
        }
        else {
            //ret = false;
            cout << "Did not find " << buffLen << " items in '" << fileName << "'.\n";
        }
    }
    else {
        cout << "File failed to open for reading.\n";
    }
    return ret;
}

/* ============================================================================
Write integer data contained in an array buffer to a file, retaining order of 
data in array buffer. Entries are newline delimited.
============================================================================ */
bool fileWrite(const char *fileName, ofstream &fileHandle, uint32_t arr[], uint32_t arrLen) {
    bool ret = true;
    filesystem::path filePath = datasetFolderPath / static_cast<filesystem::path>(fileName);

    fileHandle.open(filePath);

    if (fileHandle.is_open()) {
        for (int i = 0; i < arrLen; i++) {
            // Write array value to file, newline delimited
            fileHandle << arr[i];
            if (i != arrLen - 1) {
                fileHandle << '\n';
            }
        }
        fileHandle.close();
    }
    else {
        cout << "File failed to open for writing.\n";
        ret = false;
    }
    return ret;
}

/* ============================================================================
                                  END FILE
============================================================================ */