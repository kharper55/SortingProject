#include "fileHandling.hpp"

/* ============================================================================

============================================================================ */
bool fileExists(const string& filename) {
    bool ret;
    ifstream file(filename);
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

    // Check if the generation of numIterations randNums is possible
    if (((MAX_VALUE - MIN_VALUE) >= numIterations - 1) && (MAX_VALUE > MIN_VALUE)) {
        // Open the specified file for writing (overwrite mode)
        fileHandle.open(fileName/*, ofstream::out*/);

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

                    //fileHandle << randNum << '\n';
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

    fileHandle.open(fileName/*, ifstream::in*/);
    if (fileHandle.is_open()) {
        while(i < buffLen) {
            //cout << "Reading line " << i + 1;
            getline(fileHandle, lineBuff);
            //cout << ". Value is " << stoi(lineBuff) << ".\n";
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
    
    fileHandle.open(fileName/*, ofstream::out*/);

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