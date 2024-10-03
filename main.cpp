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

/* to do: make parameters for sorting into a class (? prob not worth it)
          comments and cleanup
          make variable names more reasonable
          clean up char declarations
*/

// Library includes
#include <iostream>                 // For console interaction
#include <fstream>                  // For file IO
#include <cstdint>                  // For unambiguous standard integer sizes
#include <iomanip>                  // For setprecision()
#include <chrono>                   // for high_resolution_clock
#include <string>                   // For stoi
#include <cstring>                  // For strlen

// Header includes
#include "sortingAlgorithms.hpp"    // Collection of sorting algorithms
#include "fileHandling.hpp"         // File I/O and dataset generation
#include "consoleInteraction.hpp"   // Console I/O
#include "utility.hpp"              // Helper functions
#include "Params.hpp"               // Custom class for user settings

#define QUIT_CHAR       'x'         // Quit/cancel/back character
#define SET_SIZE_DEFAULT 0          // First option in FILE_SIZES list
#define ALGO_DEFAULT     4          // Default to quicksort

// Defined in consoleInteraction.cpp
extern const uint32_t FILE_SIZES[];
extern const char * FILE_NAMES[];
extern const char * FILE_NAMES_SORTED[];
extern const char * FILE_NAMES_SORTED_REVERSE[];
extern const char * ALGO_NAMES[];

using namespace std;

/* ============================================================================

============================================================================ */
int main() {
    
    ofstream fileHandleWr;
    ifstream fileHandleRd;

    auto start = chrono::high_resolution_clock::now();
    auto stop = start;
    auto duration = chrono::duration_cast<chrono::duration<double>>(stop - start);
    double timeElapsed = duration.count();

    char option;
    char choice;
    uint32_t sortFileSize = SET_SIZE_DEFAULT;
    int algo = ALGO_DEFAULT;
    bool useSortedFile = false;
    bool useDescendingOrderSortedFile = false;
    bool userQuit = false;

    Params userParams;

    while(!userQuit) {

        bool invalidOption = true;
        printConsoleMenu(QUIT_CHAR);
        cin >> option;

        /* Handle upper and lower case versions of quitChar if its an ASCII letter */
        if(option != QUIT_CHAR && (option != (QUIT_CHAR - 0x20))) {
            switch(option) {

                /* Option a - generate datasets */
                case('a'):
                case('A'):
                    while (invalidOption == true) {
                        choice = printConsoleSubMenu(QUIT_CHAR, 'a');
                        if (choice != QUIT_CHAR && (choice != (QUIT_CHAR - 0x20))) {
                            // + 1 handles option 'g' - generate all
                            if ((choice >= 'a') && (choice < 'a' + sizeof(FILE_SIZES)/sizeof(FILE_SIZES[0]) + 1)) {
                                
                                int loopSize = 0; // Set loopSize according to how many different datasets we'd like 
                                                  // to generate at once. Should be either 0 or 6, used in a do-while
                                                  // loop to ensure at least one file generation

                                // User chose option 'g' - generate all datasets
                                if (choice == 'a' + sizeof(FILE_SIZES)/sizeof(FILE_SIZES[0])) {
                                    loopSize = sizeof(FILE_SIZES)/sizeof(FILE_SIZES[0]);
                                }

                                int i = 0;
                                do {
                                    char overwrite = 'y';
                                    cout << "\nGenerating file '" << FILE_NAMES[choice - 'a' - loopSize + i] 
                                         << "' for dataset of size " << FILE_SIZES[choice - 'a' - loopSize + i] 
                                         << ".\n";
                                    
                                    if (fileExists(FILE_NAMES[choice - 'a' - loopSize + i])) {
                                        cout << "\nFile exists. Operation will overwrite the file... Continue? (y/n): ";
                                        cin >> overwrite;
                                    }

                                    if (overwrite == 'y' || overwrite == 'Y') {
                                        if(!fileWriteRandInts(FILE_NAMES[choice - 'a' - loopSize + i], fileHandleWr, FILE_SIZES[choice - 'a' - loopSize + i])) {
                                            cout << "\nFile write failed!\n";
                                        }
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
                        // Break from outer while loop in case 'a'
                        else {
                            invalidOption = false;
                        }
                    }
                    break;

                /* Option b - select sorting algorithm */
                case('b'):
                case('B'):
                    while (invalidOption == true) {
                        choice = printConsoleSubMenu(QUIT_CHAR, 'b');
                        if (choice != QUIT_CHAR && (choice != (QUIT_CHAR - 0x20))) {
                            if ((choice >= 'a') && (choice < 'a' + sizeof(ALGO_NAMES)/sizeof(ALGO_NAMES[0]))) {
                                cout << "\nSelecting " << ALGO_NAMES[choice - 'a'] << " algorithm.\n";
                                // Update the selected algorithm
                                algo = choice - 'a';
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

                /* Option c - select sorting file size */
                case('c'):
                case('C'):
                    while (invalidOption == true) {
                        choice = printConsoleSubMenu(QUIT_CHAR, 'c');
                        if (choice != QUIT_CHAR && (choice != (QUIT_CHAR - 0x20))) {
                            if ((choice >= 'a') && (choice < 'a' + sizeof(FILE_SIZES)/sizeof(FILE_SIZES[0]))) {
                                cout << "\nSelecting datset of size " << FILE_SIZES[choice - 'a'] << " for sorting.\n";
                                // Update file size (to be used as a pointer to FILE_SIZE[])
                                sortFileSize = choice - 'a';
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

                /* Option d - select file type (unsorted vs. sorted vs. reverse sorted) */
                /* Existence check performed elsewhere */
                case('d'):
                case('D'):  
                {
                    char useSorted = 'n';
                    printCenteredTitle(" File Type Selection Menu ", 60);
                    cout << "Use sorted version of file? (y/n): ";  
                    cin >> useSorted;
                    useSortedFile = (useSorted == 'y' || useSorted == 'Y') ? true : false;
                    if (useSorted == 'y' || useSorted == 'Y') {
                        cout << "\nUse reverse sorted version of file? (y/n): ";  
                        cin >> useSorted;
                        useDescendingOrderSortedFile = (useSorted == 'y' || useSorted == 'Y') ? true : false;
                    }
                    else {
                        useDescendingOrderSortedFile = false;
                    }
                    break;
                }

                /* Option e - show configuration (i.e. the sort to be performed and on which file) */
                case('e'):
                case('E'):
                    printConfiguration(sortFileSize, ALGO_NAMES[algo], useSortedFile, useDescendingOrderSortedFile);
                    cout << "\nPress enter to continue: ";
                    
                    cin.get();

                    // Discard bytes if user entered any
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

                    break;

                /* Option f - perform sort */
                case('f'):
                case('F'):
                // needed to define scope explicitly with curly braces here
                // refactored to refetch the unsorted list every iteration
                {
                    char numIterations = 0;
                    bool invalidEntry = true;
                    
                    //uint32_t * fileReadBuff = new uint32_t[FILE_SIZES[sortFileSize]];
                    //uint32_t fileReadBuffDummy[FILE_SIZES[5]];
                    uint32_t * fileReadBuffDummy = new uint32_t[FILE_SIZES[sortFileSize]];

                    const char * fileName = (useSortedFile) ? FILE_NAMES_SORTED[sortFileSize] : FILE_NAMES[sortFileSize];
                    const char * fileName2 = (useDescendingOrderSortedFile) ? FILE_NAMES_SORTED_REVERSE[sortFileSize] : fileName;

                    printCenteredTitle(" Sort Performance ", 60);

                    // Check whether the selected file actually exists
                    cout << "Reading input file '" << fileName2 << "'...\n";
                    if (!fileExists(fileName2)) {
                        cout << "\nFile '" << fileName2 << "' does not exist.\n";
                        cout << "\nPlease generate the appropriate file via the main menu.\n";
                    }
                    else if (fileRead(fileName2, fileHandleRd, fileReadBuffDummy, FILE_SIZES[sortFileSize])) {
                    //else {
                        // Get a number of iterations to perform from the user
                        while (invalidEntry) {
                            cout << "\nEnter the desired number of iterations as an integer in the\nrange [1, 5] (use '" << QUIT_CHAR << "' to cancel): ";
                            cin >> numIterations;
                            if (!(static_cast<int>(numIterations) >= static_cast<int>('1') && static_cast<int>(numIterations) <= static_cast<int>('5'))) {
                                if (numIterations == QUIT_CHAR || numIterations == QUIT_CHAR - 0x20) break;
                                cout << "Invalid entry";
                            }
                            else invalidEntry = false;
                        }

                        if (!invalidEntry) {
                            const char * dynamicPluralize = (static_cast<int>(numIterations) > static_cast<int>('1')) ? "s " : " ";
                            cout << "\nCommencing " << numIterations << " sort" << dynamicPluralize;
                            cout << "using " << ALGO_NAMES[algo] << ". This may take a while...\n";
                            
                            for (int i = 1; i <= static_cast<int>(numIterations - 48); i++) {
                                uint32_t * fileReadBuff = new uint32_t[FILE_SIZES[sortFileSize]];
                                fileRead(fileName2, fileHandleRd, fileReadBuff, FILE_SIZES[sortFileSize]);
                                cout << "\nIteration: " << i << "\n";

                                // Perform an iteration of the chosen sorting algorithm on the selected dataset
                                // Decided to place time captures inside individual switch case blocks to avoid including asm jump overhead
                                switch(algo) {
                                    case(BUBBLE):
                                        start = chrono::high_resolution_clock::now();
                                        bubbleSort(fileReadBuff, FILE_SIZES[sortFileSize]);
                                        stop = chrono::high_resolution_clock::now();
                                        break;
                                    case(SELECTION):
                                        start = chrono::high_resolution_clock::now();
                                        selectionSort(fileReadBuff, FILE_SIZES[sortFileSize]);
                                        stop = chrono::high_resolution_clock::now();
                                        break;
                                    case(INSERTION):
                                        start = chrono::high_resolution_clock::now();
                                        insertionSort(fileReadBuff, FILE_SIZES[sortFileSize]);
                                        stop = chrono::high_resolution_clock::now();
                                        break;
                                    case(MERGE):
                                        start = chrono::high_resolution_clock::now();
                                        mergeSort(fileReadBuff, 0, FILE_SIZES[sortFileSize] - 1);
                                        stop = chrono::high_resolution_clock::now();
                                        break;
                                    case(QUICK):
                                        start = chrono::high_resolution_clock::now();
                                        quickSort(fileReadBuff, 0, FILE_SIZES[sortFileSize] - 1);
                                        stop = chrono::high_resolution_clock::now();
                                        break;
                                    case(SHELL):
                                        start = chrono::high_resolution_clock::now();
                                        shellSort(fileReadBuff, FILE_SIZES[sortFileSize]);
                                        stop = chrono::high_resolution_clock::now();
                                        break;
                                    default:
                                        // This should never execute... Validation performed elsewhere
                                        break;
                                }

                                // Calculate and display time duration
                                duration = chrono::duration_cast<chrono::duration<double>>(stop - start);
                                timeElapsed = duration.count();
                                cout << "Sorting took " << fixed << setprecision(10) << timeElapsed << " seconds.\n";
                                
                                /* Optionally write sorted array to a new file if file DNE */
                                if (!fileExists(FILE_NAMES_SORTED[sortFileSize])) {
                                    char yn = 'y';
                                    cout << "\nWrite sorted array to file? (y/n): ";
                                    cin >> yn;
                                    if (yn == 'y' || yn == 'Y') {
                                        fileWrite(FILE_NAMES_SORTED[sortFileSize], fileHandleWr, fileReadBuff, FILE_SIZES[sortFileSize]);
                                    }
                                }

                                /* Optionally write reverse sorted array to a new file if file DNE */
                                if (!fileExists(FILE_NAMES_SORTED_REVERSE[sortFileSize])) {
                                    char yn = 'y';
                                    cout << "\nWrite reverse sorted array to file? (y/n): ";
                                    cin >> yn;
                                    if (yn == 'y' || yn == 'Y') {
                                        reverseIntArray(fileReadBuff, FILE_SIZES[sortFileSize]);
                                        fileWrite(FILE_NAMES_SORTED_REVERSE[sortFileSize], fileHandleWr, fileReadBuff, FILE_SIZES[sortFileSize]);
                                        reverseIntArray(fileReadBuff, FILE_SIZES[sortFileSize]); // reverse again incase verification is desired
                                    }
                                }

                                /* Optionally verify array sorting by printing contents to console */
                                if (i == static_cast<int>(numIterations - 48)) {
                                    char verify = 'y';
                                    cout << "\nVerify sort? (y/n): ";
                                    cin >> verify;

                                    if (verify == 'y' || verify == 'Y') {
                                        printIntArray(ALGO_NAMES[algo], fileReadBuff, FILE_SIZES[sortFileSize], 5);
                                        int minIdx = findMinMax(fileReadBuff, FILE_SIZES[sortFileSize], MIN);
                                        int maxIdx = findMinMax(fileReadBuff, FILE_SIZES[sortFileSize], MAX);
                                        cout << "\nMinimum value (" << fileReadBuff[minIdx] << ") found at array index " << minIdx << ".\n";
                                        cout << "Maximum value (" << fileReadBuff[maxIdx] << ") found at array index " << maxIdx << ".\n";
                                        if (minIdx == 0 && maxIdx == FILE_SIZES[sortFileSize] - 1) {
                                            cout << "\nArray appears to be properly sorted.\n";
                                        }
                                        else {
                                            cout << "\nMinimum and/or maximum value are out of place.\n";
                                            cout << "Sorting appears to have failed.\n";
                                        }
                                    }  
                                }

                                delete[] fileReadBuff; // Free allocated space for array buffer
                                                       // in preparation for subsequent iterations.
                            }
                        }
                    }
                    else {
                        cout << "\nFile read failed...\n";
                    }

                    delete[] fileReadBuffDummy; // Free allocated space for file integrity check.

                    break;
                }
                
                /* Invalid option from user (i.e. not 'a' : 'f' || 'x') */
                default:
                    cout << "\n'" << option << "'" << " is not a valid option.\n";
                    break;
            }
        }

        /* User entered quitChar ('x' by default) */
        else {
            userQuit = true;
        }
    }

	return 0;
}

/* ============================================================================
                                  END FILE
============================================================================ */