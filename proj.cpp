/* ============================================================================
Proj.cpp

Desc:   Project for Datastructures and algorithms (CSCI2226)
Author: Kevin Harper
Date:   08/27/2024

NOTE: IN VSCODE, IF GDB IS THROWING ERROR 0xC0000139 DESPITE THE PROGRAM 
      SUCCESSFULLY BUILDING, YOU MUST GO TO SETTINGS AND CHANGE THE TERMINAL. 
      IN THE TERMINAL WINDOW, NAVIGATE TO THE "+" ICON WITH THE DROPDOWN ARROW,
      THEN SELECT CONFIGURE TERMINAL SETTINGS, NAVIGATE TO C:\msys64\ucrt64.exe 
      (FOR DEFAULT MSYS2 INSTALL SETTINGS) AND USE THIS EXECUTABLE PATH IN THE 
      SETTINGS WINDOW. THEN USE THE BUTTON ON THE BOTTOM OF THE VSCODE SCREEN
      "C/C++: g++.exe build and debug active file (PROJ_NAME)" TO BUILD AND
      DEBUG THE FILE IN THE NATIVE VSCODE TERMINAL.

============================================================================ */


/* to do: fix inconsistent header widths; make into a function
          separate functionality into multiple .cpp and .h files 
          expand sorting switch case to accept an argument for numerous consecutive sorts
          swap to uint32_ts for all sorting?
          handle x and 'X' for quitting
          clean up UI by reprinting instructions
            quickSort segfaults on sorted array
*/

/*
https://www.programiz.com/dsa/bubble-sort
https://www.programiz.com/dsa/selection-sort
https://www.programiz.com/dsa/insertion-sort
https://www.programiz.com/dsa/merge-sort
https://www.programiz.com/dsa/quick-sort
https://www.programiz.com/dsa/shell-sort
*/

// Library includes
#include <iostream> // For console interaction
#include <fstream>  // For file IO
#include <cstdint>  // For unambiguous standard integer sizes
#include <random>   // For random device and mersenne twister implementation
#include <iomanip>  // for setprecision()
#include <chrono>   // for high_resolution_clock
#include <string>   // For stoi
#include <set>      // For checking uniqueness

// Preprocessor stuff
#define NUM_ITERATIONS (uint32_t)25000
enum MIN_MAX { MIN = 0, MAX };

#define QUIT_CHAR 'x'
#define SET_SIZE_DEFAULT 0
#define ALGO_DEFAULT 0

const int FILE_SIZES[] = {
    50000,
    100000,
    175000,
    300000,
    425000,
    550000
};

const char * FILE_NAMES[] = {
    "set50k",
    "set100k",
    "set175k",
    "set300k",
    "set425k",
    "set550k"
};

const char * FILE_NAMES_SORTED[] = {
    "set50kSorted",
    "set100kSorted",
    "set175kSorted",
    "set300kSorted",
    "set425kSorted",
    "set550kSorted"
};

const char * FILE_NAMES_SORTED_REVERSE[] = {
    "set50kSortedReverse",
    "set100kSortedReverse",
    "set175kSortedReverse",
    "set300kSortedReverse",
    "set425kSortedReverse",
    "set550kSortedReverse"
};

const char * ALGO_NAMES[] = {
    "Bubble Sort",
    "Selection Sort",
    "Insertion Sort",
    "Merge Sort",
    "Quick Sort",
    "Shell Sort"
};

enum ALGOS {
    BUBBLE,
    SELECTION,
    INSERTION,
    MERGE,
    QUICK,
    SHELL
};

using namespace std;

// Sorting algorithm implementations
void bubbleSort(int arr[], int arrLen);         // x
void selectionSort(int arr[], int arrLen);      // revise
void insertionSort(int arr[], int arrLen);      // revise
void mergeSort(int arr[], int l, int r);        // from programiz.com... revise to remove function call overhead?
void quickSort(int array[], int low, int high); // from programiz.com... revise to remove function call overhead?
void shellSort(int arr[], int arrLen);          // from programiz.com

// Array helper functions
void reverseIntArray(int arr[], int arrLen);
int findIndex(int arr[], int arrLen, const bool minMax);
void printIntArray(const char * arrLabel, int arr[], int arrLen, int maxColWidth);

// File I/O
bool fileWriteRandInts(const char * fileName, ofstream &fileHandle, uint32_t numIterations);
bool fileReadRandInts(const char * fileName, ifstream &fileHandle, int buff[], int buffLen);
bool fileExists(const string& filename);
bool fileWrite(const char *fileName, ofstream &fileHandle, int * arr, int arrLen);

// Console interaction
void printConsoleMenu(char quitChar);
char printConsoleSubMenu(char quitChar, char option);
//void printConfiguration(int setSize, const char * sortingAlgo, bool sorted);
void printConfiguration(int setSize, const char * sortingAlgo, bool sorted, bool reverseSorted);

/* ============================================================================

============================================================================ */
int main() {
    
    ofstream fileHandle;
    const char * fileName = "file1.txt";
    int testArr[] = {699, 728, 999, 500, 400, 120, 123, 463, 691, 501, 802};
    int testArrSize = sizeof(testArr) / sizeof(testArr[0]);

    ifstream fileHandleRd;
    int fileReadBuff[NUM_ITERATIONS];
    
    // factor this to not overwrite files. we want to use the same file of integers for each and every trial
    if(!fileWriteRandInts(fileName, fileHandle, NUM_ITERATIONS)) {
        cout << "File write failed!\n";
        return -1;
    }
    //bubbleSort(testArr, testArrSize);
    //selectionSort(testArr, testArrSize);
    //insertionSort(testArr, testArrSize);
    //mergeSort(testArr, 0, testArrSize - 1);
    //quickSort(testArr, 0, testArrSize - 1);
    //shellSort(testArr, testArrSize);
    //printIntArray("shell sort", testArr, testArrSize, 8);

    fileReadRandInts(fileName, fileHandleRd, fileReadBuff, NUM_ITERATIONS);
    //printIntArray("random integers", fileReadBuff, NUM_ITERATIONS, 5);

    cout << "\nArray max is " << fileReadBuff[findIndex(fileReadBuff, NUM_ITERATIONS, MAX)] << ".\n";
    cout << "Array min is " << fileReadBuff[findIndex(fileReadBuff, NUM_ITERATIONS, MIN)] << ".\n";

    auto start = chrono::high_resolution_clock::now();
    //shellSort(fileReadBuff, NUM_ITERATIONS);
    quickSort(fileReadBuff, 0, NUM_ITERATIONS - 1);
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::duration<double>>(stop - start);
    double timeElapsed = duration.count();
    //printIntArray("sorted random integers", fileReadBuff, NUM_ITERATIONS, 5);
    cout << "\nArray max is " << fileReadBuff[findIndex(fileReadBuff, NUM_ITERATIONS, MAX)] << ".\n";
    cout << "Array min is " << fileReadBuff[findIndex(fileReadBuff, NUM_ITERATIONS, MIN)] << ".\n";
    cout << "Sorting took " << fixed << setprecision(10) << timeElapsed << " seconds.\n"; // fixed, setprecision()?

    char option;
    char choice;
    int sortFileSize = SET_SIZE_DEFAULT;
    int algo = ALGO_DEFAULT;
    bool useSortedFile = false;
    bool useDescendingOrderSortedFile = false;
    bool userQuit = false;
    //bool invalidOption = true;
    while(!userQuit) {
        bool invalidOption = true;
        //char overwrite = 'y';
        printConsoleMenu('x');

        cin >> option;
        if(option != QUIT_CHAR) {
            switch(option) {
                case('a'):
                case('A'):
                    while (invalidOption == true) {
                        choice = printConsoleSubMenu('x', option);
                        if (choice != QUIT_CHAR) {
                            // + 1 handles option 'g' - generate all
                            if ((static_cast<int>(choice) >= static_cast<int>('a')) && (static_cast<int>(choice) < static_cast<int>('a') + sizeof(FILE_SIZES)/sizeof(FILE_SIZES[0]) + 1)) {
                                
                                int loopSize = 0;

                                if (static_cast<int>(choice) == static_cast<int>('a') + sizeof(FILE_SIZES)/sizeof(FILE_SIZES[0])) {
                                    loopSize = sizeof(FILE_SIZES)/sizeof(FILE_SIZES[0]);
                                }

                                //for (int i = 0; i < loopSize; i++) {
                                int i = 0;
                                do {
                                    char overwrite = 'y';
                                    cout << "\nGenerating file '" << FILE_NAMES[static_cast<int>(choice) - static_cast<int>('a') - loopSize + i] << ".txt' for dataset of size " << FILE_SIZES[static_cast<int>(choice) - static_cast<int>('a') - loopSize + i] << ".\n";
                                    
                                    if (fileExists(FILE_NAMES[static_cast<int>(choice) - static_cast<int>('a') - loopSize + i])) {
                                        cout << "\nFile exists. Operation will overwrite the file... Continue? (y/n): ";
                                        cin >> overwrite;
                                    }

                                    if (overwrite == 'y' || overwrite == 'Y') {
                                        //cout << "\nGenerating file " << FILE_NAMES[static_cast<int>(choice) - static_cast<int>('a') - loopSize + i] << "...\n";
                                        if(!fileWriteRandInts(FILE_NAMES[static_cast<int>(choice) - static_cast<int>('a') - loopSize + i], fileHandle, FILE_SIZES[static_cast<int>(choice) - static_cast<int>('a') - loopSize + i])) {
                                            cout << "\nFile write failed!\n";
                                            //return -1;
                                        }
                                        //else {}
                                        cout << "\nDone.\n";
                                        invalidOption = false;
                                    }
                                    else {
                                        cout << "\nAborting...\n";
                                    }
                                    i++;
                                }
                                while(i < loopSize);
                            }
                            else {
                                cout << "\nUnrecognized option...\n";
                            }
                        }
                        else {
                            invalidOption = false;
                        }
                    }
                    break;

                case('b'):
                case('B'):
                    //cout << "b selected";
                    while (invalidOption == true) {
                        choice = printConsoleSubMenu('x', option);
                        if (choice != QUIT_CHAR) {
                            if ((static_cast<int>(choice) >= static_cast<int>('a')) && (static_cast<int>(choice) < static_cast<int>('a') + sizeof(ALGO_NAMES)/sizeof(ALGO_NAMES[0]))) {
                                cout << "\nSelecting " << ALGO_NAMES[static_cast<int>(choice) - static_cast<int>('a')] << " algorithm.\n";
                                algo = static_cast<int>(choice) - static_cast<int>('a');
                                invalidOption = false;
                            }
                            else {
                                cout << "\nUnrecognized option...\n";
                            }
                        }
                        else {
                            invalidOption = false;
                        }
                    }
                    break;

                case('c'):
                case('C'):
                    while (invalidOption == true) {
                        choice = printConsoleSubMenu('x', option);
                        if (choice != QUIT_CHAR) {
                            if ((static_cast<int>(choice) >= static_cast<int>('a')) && (static_cast<int>(choice) < static_cast<int>('a') + sizeof(FILE_SIZES)/sizeof(FILE_SIZES[0]))) {
                                cout << "\nSelecting datset of size " << FILE_SIZES[static_cast<int>(choice) - static_cast<int>('a')] << " for sorting.\n";
                                sortFileSize = static_cast<int>(choice) - static_cast<int>('a');
                                invalidOption = false;
                            }
                            else {
                                cout << "\nUnrecognized option...\n";
                            }
                        }
                        else {
                            invalidOption = false;
                        }
                    }
                    break;

                case('d'):
                case('D'):  
                    {
                    char userIn = 'n';
                    cout << "\nUse sorted version of file? (y/n): ";  
                    cin >> userIn;
                    useSortedFile = (userIn == 'y' || userIn == 'Y') ? true : false;
                    if (userIn == 'y' || userIn == 'Y') {
                        cout << "\nUse reverse sorted version of file? (y/n): ";  
                        cin >> userIn;
                        useDescendingOrderSortedFile = (userIn == 'y' || userIn == 'Y') ? true : false;
                    }
                    else {
                        useDescendingOrderSortedFile = false;
                    }
                    break;
                    }

                case('e'):
                case('E'):
                    printConfiguration(sortFileSize, ALGO_NAMES[algo], useSortedFile, useDescendingOrderSortedFile);
                    cout << "\nPress enter to continue: ";
                    
                    cin.get();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard bytes if user entered any

                    break;

                case('f'):
                case('F'):
                // needed to define scope explicitly with curly braces here
                // this needs to be refactored to get the unsorted list every iteration
                {

                    char numIterations = 0;
                    bool invalidEntry = true;
                    
                    int * fileReadBuff2 = new int[FILE_SIZES[sortFileSize]];

                    const char * fileName2 = (useSortedFile) ? FILE_NAMES_SORTED[sortFileSize] : FILE_NAMES[sortFileSize];
                    const char * fileName3 = (useDescendingOrderSortedFile) ? FILE_NAMES_SORTED_REVERSE[sortFileSize] : fileName2;

                    cout << "\nReading input file '" << fileName3 << ".txt'...\n";
                    if (!fileExists(fileName3)) {
                        cout << "\nFile '" << fileName3 << ".txt' does not exist.\n";
                        cout << "\nPlease generate the appropriate file via the main menu.\n";
                    }
                    else if (fileReadRandInts(fileName3, fileHandleRd, fileReadBuff2, FILE_SIZES[sortFileSize])) {

                        while (invalidEntry/*static_cast<int>(numIterations) < 1 && static_cast<int>(numIterations) > 5*/) {
                            cout << "\nEnter the desired number of iterations as an integer in the range [1, 5] (use '" << QUIT_CHAR << "' to cancel): ";
                            cin >> numIterations;
                            if (!(static_cast<int>(numIterations) >= static_cast<int>('1') && static_cast<int>(numIterations) <= static_cast<int>('5'))) {
                                if (numIterations == QUIT_CHAR) break;
                                cout << "Invalid entry";
                            }
                            else invalidEntry = false;
                        }

                        if (!invalidEntry) {
                            const char * f = (static_cast<int>(numIterations) > static_cast<int>('1')) ? "s " : " ";
                            cout << "\nCommencing " << numIterations << " sort" << f << "using " << ALGO_NAMES[algo] << ". This may take some time...\n";
                            
                            for (int i = 1; i <= static_cast<int>(numIterations - 48); i++) {
                                int * fileReadBuff2 = new int[FILE_SIZES[sortFileSize]];
                                fileReadRandInts(fileName3, fileHandleRd, fileReadBuff2, FILE_SIZES[sortFileSize]);
                                cout << "\nIteration: " << i << "\n";

                                // Decided to place time captures inside individual switch case blocks to avoid including asm jump overhead
                                switch(algo) {
                                    case(BUBBLE):
                                        start = chrono::high_resolution_clock::now();
                                        bubbleSort(fileReadBuff2, FILE_SIZES[sortFileSize]);
                                        stop = chrono::high_resolution_clock::now();
                                        break;
                                    case(SELECTION):
                                        start = chrono::high_resolution_clock::now();
                                        selectionSort(fileReadBuff2, FILE_SIZES[sortFileSize]);
                                        stop = chrono::high_resolution_clock::now();
                                        break;
                                    case(INSERTION):
                                        start = chrono::high_resolution_clock::now();
                                        insertionSort(fileReadBuff2, FILE_SIZES[sortFileSize]);
                                        stop = chrono::high_resolution_clock::now();
                                        break;
                                    case(MERGE):
                                        start = chrono::high_resolution_clock::now();
                                        mergeSort(fileReadBuff2, 0, FILE_SIZES[sortFileSize] - 1);
                                        stop = chrono::high_resolution_clock::now();
                                        break;
                                    case(QUICK):
                                        start = chrono::high_resolution_clock::now();
                                        quickSort(fileReadBuff2, 0, FILE_SIZES[sortFileSize] - 1);
                                        stop = chrono::high_resolution_clock::now();
                                        break;
                                    case(SHELL):
                                        start = chrono::high_resolution_clock::now();
                                        shellSort(fileReadBuff2, FILE_SIZES[sortFileSize]);
                                        stop = chrono::high_resolution_clock::now();
                                        break;
                                    default:
                                        // This should never execute... Validation performed elsewhere
                                        break;
                                }

                                duration = chrono::duration_cast<chrono::duration<double>>(stop - start);
                                timeElapsed = duration.count();
                                cout << "Sorting took " << fixed << setprecision(10) << timeElapsed << " seconds.\n";
                                //printIntArray("sorted array", fileReadBuff2, FILE_SIZES[sortFileSize], 5);
                                //numIterations--;
                                //fileWrite(FILE_NAMES_SORTED[sortFileSize], fileHandle, fileReadBuff2, FILE_SIZES[sortFileSize]);
                                if (!fileExists(FILE_NAMES_SORTED[sortFileSize])) {
                                    char yn = 'y';
                                    cout << "\nWrite sorted array to file? (y/n): ";
                                    cin >> yn;
                                    if (yn == 'y' || yn == 'Y') {
                                        fileWrite(FILE_NAMES_SORTED[sortFileSize], fileHandle, fileReadBuff2, FILE_SIZES[sortFileSize]);
                                    }
                                }
                                if (!fileExists(FILE_NAMES_SORTED_REVERSE[sortFileSize])) {
                                    char yn = 'y';
                                    cout << "\nWrite reverse sorted array to file? (y/n): ";
                                    cin >> yn;
                                    if (yn == 'y' || yn == 'Y') {
                                        //printIntArray("not reverse", fileReadBuff2, sortFileSize, 5);
                                        reverseIntArray(fileReadBuff2, FILE_SIZES[sortFileSize]);
                                        //printIntArray("reverse", fileReadBuff2, sortFileSize, 5);

                                        fileWrite(FILE_NAMES_SORTED_REVERSE[sortFileSize], fileHandle, fileReadBuff2, FILE_SIZES[sortFileSize]);
                                    }
                                }
                            }     
                        }
                    }
                    else {
                        cout << "\nFile failed to open for reading...\n";
                    }

                    delete[] fileReadBuff2; // Free allocated space.

                    break;
                }

                default:
                    cout << "\n'" << option << "'" << " is not a valid option.\n";
                    break;
            }
        }
        else {
            userQuit = true;
        }
    }

	return 0;
}

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

/* ============================================================================
bubbleSort(array)
  for i <- 1 to sizeOfArray - 1
    for j <- 1 to sizeOfArray - 1 - i
      if leftElement > rightElement
        swap leftElement and rightElement
end bubbleSort
============================================================================ */
void bubbleSort(int arr[], int arrLen) {
    const bool VERBOSE = false;
    int i, j, temp;
    // Outer loop
    for (i = 0; i < arrLen - 1; i++) {
        // Inner loop
        for (j = 0; j < arrLen - i - 1; j++) {
            // Lower index value is greater than upper index value
            if (arr[j] > arr[j + 1]) {
                if (VERBOSE) {
                    cout << "Array index " << j << " value (" << 
                        arr[j] << ")" << " is greater than value at index " <<
                        j + 1 << " (" << arr[j + 1] << ")." << "\n";
                }
                // Perform the swap
                temp = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

/* ============================================================================
selectionSort(array, size)
  for i from 0 to size - 1 do
    set i as the index of the current minimum
    for j from i + 1 to size - 1 do
      if array[j] < array[current minimum]
        set j as the new current minimum index
    if current minimum is not i
      swap array[i] with array[current minimum]
end selectionSort
============================================================================ */
void selectionSort(int arr[], int arrLen) {
    int i, j, minIdx, temp;
    for (i = 0; i < arrLen - 1; i++) {   // Outer loop
        minIdx = i;                      // Preset the minimum location
        for (j = i + 1; j < arrLen; j++) {
            if (arr[j] < arr[minIdx]) { // A smaller value is found
                minIdx = j;             // Update the minIdx
            }
        }
        if (minIdx != i) {              // minIdx was updated (smaller value found)
            // Perform the swap. minIdx > i
            temp = arr[i];
            arr[i] = arr[minIdx];
            arr[minIdx] = temp;
        }
    }
}

/* ============================================================================
insertionSort(array)
  mark first element as sorted
  for each unsorted element X
    'extract' the element X
    for j <- lastSortedIndex down to 0
      if current element j > X
        move sorted element to the right by 1
    break loop and insert X here
end insertionSort
============================================================================ */
void insertionSort(int arr[], int arrLen) {
    int i, j, key;
    // Assume first index is sorted
    for (i = 1; i < arrLen; i++) {
    // while (arr[i + 1] < arr[i]) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            // temp = arr[i + 1];
            // arr[i + 1] = arr[i];
            // arr[i] = temp;
            arr[j + 1] = arr[j];
            j -= 1;
        }
        arr[j + 1] = key;
    }
}

/* ============================================================================

============================================================================ */
// https://www.programiz.com/dsa/merge-sort
// Merge two subarrays L and M into arr
void merge(int arr[], int p, int q, int r) {

    // Create L ← A[p..q] and M ← A[q+1..r]
    int n1 = q - p + 1;
    int n2 = r - q;

    //int L[n1], M[n2];
    // Dynamic allocation to circumvent segfaults with recursive implementation
    int *L = new int[n1];
    int *M = new int[n2];

    for (int i = 0; i < n1; i++) {
        L[i] = arr[p + i];
    }
        
    for (int j = 0; j < n2; j++) {
        M[j] = arr[q + 1 + j];
    }
        
    // Maintain current index of sub-arrays and main array
    int i, j, k;
    i = 0;
    j = 0;
    k = p;

    // Until we reach either end of either L or M, pick larger among
    // elements L and M and place them in the correct position at A[p..r]
    while (i < n1 && j < n2) {
        if (L[i] <= M[j]) {
            arr[k] = L[i];
            i++;
        } 
        else {
            arr[k] = M[j];
            j++;
        }
        k++;
    }

    // When we run out of elements in either L or M,
    // pick up the remaining elements and put in A[p..r]
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = M[j];
        j++;
        k++;
    }

    // Free dynamically allocated memory
    delete[] L;
    delete[] M;
}

// https://www.programiz.com/dsa/merge-sort
// Divide the array into two subarrays, sort them and merge them
void mergeSort(int arr[], int l, int r) {
    if (l < r) {

        // m is the point where the array is divided into two subarrays
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        // Merge the sorted subarrays
        merge(arr, l, m, r);
    }
}

/* ============================================================================

============================================================================ */
int medianOfThree(int arr[], int low, int high) {
    int mid = low + (high - low) / 2;
    
    if (arr[low] > arr[mid]) {
        // swap arr[low] and arr[mid]
        int temp = arr[low];
        arr[low] = arr[mid];
        arr[mid] = temp;
    }
    if (arr[low] > arr[high]) {
        // swap arr[low] and arr[high]
        int temp = arr[low];
        arr[low] = arr[high];
        arr[high] = temp;
    }
    if (arr[mid] > arr[high]) {
        // swap arr[mid] and arr[high]
        int temp = arr[mid];
        arr[mid] = arr[high];
        arr[high] = temp;
    }
    
    // Use the middle element as the pivot by swapping it to the end
    int temp = arr[mid];
    arr[mid] = arr[high];
    arr[high] = temp;
    
    return arr[high];  // pivot is now at arr[high]
}

/* ============================================================================

============================================================================ */
// https://www.programiz.com/dsa/quick-sort
// function to find the partition position
int partition(int arr[], int low, int high) {

    // select the rightmost element as pivot
    //int pivot = arr[high];
    int pivot = medianOfThree(arr, low, high); // segfault possibly from deep recursion 
                                               // necessitated a better pivot selection
    int temp = 0;

    // pointer for greater element
    int i = (low - 1);

    // traverse each element of the array
    // compare them with the pivot
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            
            // if element smaller than pivot is found
            // swap it with the greater element pointed by i
            i++;
            
            // swap element at i with element at j
            //swap(&array[i], &array[j]);
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    // swap the pivot element with the greater element at i
    temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    // return the partition point
    return (i + 1);
}

// https://www.programiz.com/dsa/quick-sort
void quickSort(int array[], int low, int high) {
    if (low < high) {

        // find the pivot element such that
        // elements smaller than pivot are on left of pivot
        // elements greater than pivot are on right of pivot
        int pi = partition(array, low, high);

        // recursive call on the left of pivot
        quickSort(array, low, pi - 1);

        // recursive call on the right of pivot
        quickSort(array, pi + 1, high);
    }
}


/* ============================================================================

============================================================================ */
void shellSort(int arr[], int arrLen) {
    // Rearrange elements at each arrLen/2, arrLen/4, arrLen/8, ... intervals
    // ie Shell's original sequence. see below link for other possible sequences
    // https://www.programiz.com/dsa/shell-sort
    for (int interval = arrLen / 2; interval > 0; interval /= 2) {
        for (int i = interval; i < arrLen; i += 1) {
            int temp = arr[i];
            int j;
            for (j = i; j >= interval && arr[j - interval] > temp; j -= interval) {
                arr[j] = arr[j - interval];
            }
            arr[j] = temp;
        }
    }
}

/* ============================================================================

============================================================================ */
int findIndex(int arr[], int arrLen, const bool minMax) {
    int selIndex = 0;
    int val = arr[0];
    int i = 0;

    if (arrLen <= 0) {
        return -1; // or handle empty array case
    }

    for (i = 1; i < arrLen; i++) {
        if (minMax == MIN) {
            if (arr[i] < val) {
                val = arr[i];
                selIndex = i;
            }
        } 
        else { // minMax == MAX
            if (arr[i] > val) {
                val = arr[i];
                selIndex = i;
            }
        }
    }
    return selIndex;
}

/* ============================================================================
This function reverses a sorted integer array.
============================================================================ */
void reverseIntArray(int arr[], int arrLen) {
    
    int temp, upperIdx, lowerIdx = 0;
    for (upperIdx = arrLen - 1; upperIdx >= arrLen / 2; upperIdx--) {
        temp = arr[upperIdx];
        arr[upperIdx] = arr[lowerIdx];
        arr[lowerIdx] = temp;
        lowerIdx++;
    }
    /*
    int temp;
    int lowerIdx = 0;
    int upperIdx = arrLen - 1;
    
    while (lowerIdx < upperIdx) {
        // Swap elements
        temp = arr[lowerIdx];
        arr[lowerIdx] = arr[upperIdx];
        arr[upperIdx] = temp;
        
        // Move indices towards the center
        lowerIdx++;
        upperIdx--;
    }*/
}

/* ============================================================================

============================================================================ */
void printIntArray(const char * arrLabel, int arr[], int arrLen, int maxColWidth) {
    cout << "\nArray contents for " << arrLabel << ":\n{";
    for (int i = 0; i < arrLen; i++) {
        cout << arr[i];

        if (i != arrLen - 1) cout << ", ";
        else cout << "}";

        if (((i + 1) % maxColWidth == 0) && (i != 0) && (i != arrLen - 1)) cout << "\n ";
        else if (i == arrLen - 1) {
            cout << "\n";
        }
    }
}


/* ============================================================================

============================================================================ */
void printConsoleMenu(char quitChar) {
    const int COL_WIDTH = 60;
    const char * OPTIONS_LIST[] = {
        "Generate file",
        "Select sorting algorithm",
        "Select file size",
        "Select file type",
        "Show configuration",
        "Perform sort"
    };
    const char * TITLE = " Main Menu ";

    char * itoa_buff;

    cout << "\n";

    for (int i = 0; i < COL_WIDTH/2 - sizeof(TITLE)/sizeof(TITLE[0])/2; i++) {
        cout << "=";
    }

    cout << TITLE;

    for (int i = 0; i < COL_WIDTH/2 - sizeof(TITLE)/sizeof(TITLE[0])/2; i++) {
        cout << "=";
    }

    cout << "\n\n";

    for (int i = 0; i < sizeof(OPTIONS_LIST)/sizeof(OPTIONS_LIST[0]); i++) { 
        cout << static_cast<char>(0x61 + i) << ") " << OPTIONS_LIST[i] << "\n";
    }

    cout << "\nSelect an option from the list (use '" << quitChar << "' to quit): ";
} 

/* ============================================================================

============================================================================ */
void printConfiguration(int setSize, const char * sortingAlgo, bool sorted, bool reverseSorted) {
    const int COL_WIDTH = 60;
    const char * TITLE = " Settings ";

    cout << "\n";

    for (int i = 0; i < COL_WIDTH/2 - sizeof(TITLE)/sizeof(TITLE[0])/2; i++) {
        cout << "=";
    }

    cout << TITLE;

    for (int i = 0; i < COL_WIDTH/2 - sizeof(TITLE)/sizeof(TITLE[0])/2; i++) {
        cout << "=";
    }

    const char * fileName = (sorted) ? FILE_NAMES_SORTED[setSize] : FILE_NAMES[setSize];
    const char * fileName2 = (reverseSorted) ? FILE_NAMES_SORTED_REVERSE[setSize] : fileName;
    /*
    if (sorted && reverseSorted) {
        const char * fileName = FILE_NAMES_SORTED_REVERSE[setSize];
    }*/
    cout << "\n\nFile              : " << fileName2 << ".txt";
    cout << "\nDataset size      : " << FILE_SIZES[setSize];
    cout << "\nSorting algorithm : " << sortingAlgo << "\n";
}

/* ============================================================================

============================================================================ */
char printConsoleSubMenu(char quitChar, char option) {

    const int ITOA_BUFF_SIZE = 10;
    char itoa_buff[ITOA_BUFF_SIZE];
    char choice;
    const int numFiles = sizeof(FILE_SIZES)/sizeof(FILE_SIZES[0]);
    const int numAlgos = sizeof(ALGO_NAMES)/sizeof(ALGO_NAMES[0]);

    cout << "\n";
    
    switch(option) {

        case('a'):
            for(int i = 0; i < numFiles; i++) {
                cout << static_cast<char>(0x61 + i) << ") " << FILE_SIZES[i] << "\n";
                if (i == numFiles - 1) {
                    cout << static_cast<char>(0x61 + i + 1) << ") All\n";
                }
            }

            cout << "\nChoose a dataset size for file generation (use '" << quitChar << "' to cancel): ";
            break;

        case('b'):
            for(int i = 0; i < numAlgos; i++) {
                cout << static_cast<char>(0x61 + i) << ") " << ALGO_NAMES[i] << "\n";
            }

            cout << "\nChoose a sorting algorithm (use '" << quitChar << "' to cancel): ";
            break;

        case('c'):
            for(int i = 0; i < numFiles; i++) {
                if (i < numFiles) {
                    cout << static_cast<char>(0x61 + i) << ") " << FILE_SIZES[i] << "\n";
                }
                /*
                if (i == numFiles - 1) {
                    cout << static_cast<char>(0x61 + i + 1) << ") All\n";
                }*/
            }

            cout << "\nChoose a dataset size for sorting (use '" << quitChar << "' to cancel): ";
            break;

        default:
            break;
    }

    cin >> choice;

    return choice;
}

/* ============================================================================
                                  END FILE
============================================================================ */