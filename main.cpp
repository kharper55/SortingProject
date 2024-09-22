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

/* to do: swap to uint32_ts for all sorting?
          make parameters for sorting into a class
          comment code

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
#include <iomanip>  // for setprecision()
#include <chrono>   // for high_resolution_clock
#include <string>   // For stoi
#include <cstring>  // For strlen

// Header includes
#include "sortingAlgorithms.hpp"
#include "fileHandling.hpp"
#include "consoleInteraction.hpp"
#include "utility.hpp"

#define QUIT_CHAR 'x'
#define SET_SIZE_DEFAULT 0 // First option in FILE_SIZES list
#define ALGO_DEFAULT 0     // First option in ALGO_NAMES list

extern const int FILE_SIZES[6];
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
    int sortFileSize = SET_SIZE_DEFAULT;
    int algo = ALGO_DEFAULT;
    bool useSortedFile = false;
    bool useDescendingOrderSortedFile = false;
    bool userQuit = false;

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
                            if ((static_cast<int>(choice) >= static_cast<int>('a')) && (static_cast<int>(choice) < static_cast<int>('a') + sizeof(FILE_SIZES)/sizeof(FILE_SIZES[0]) + 1)) {
                                
                                int loopSize = 0;

                                if (static_cast<int>(choice) == static_cast<int>('a') + sizeof(FILE_SIZES)/sizeof(FILE_SIZES[0])) {
                                    loopSize = sizeof(FILE_SIZES)/sizeof(FILE_SIZES[0]);
                                }

                                int i = 0;
                                do {
                                    char overwrite = 'y';
                                    cout << "\nGenerating file '" << FILE_NAMES[static_cast<int>(choice) - static_cast<int>('a') - loopSize + i] << ".txt' for dataset of size " << FILE_SIZES[static_cast<int>(choice) - static_cast<int>('a') - loopSize + i] << ".\n";
                                    
                                    if (fileExists(FILE_NAMES[static_cast<int>(choice) - static_cast<int>('a') - loopSize + i])) {
                                        cout << "\nFile exists. Operation will overwrite the file... Continue? (y/n): ";
                                        cin >> overwrite;
                                    }

                                    if (overwrite == 'y' || overwrite == 'Y') {
                                        if(!fileWriteRandInts(FILE_NAMES[static_cast<int>(choice) - static_cast<int>('a') - loopSize + i], fileHandleWr, FILE_SIZES[static_cast<int>(choice) - static_cast<int>('a') - loopSize + i])) {
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

                /* Option c - select sorting file size */
                case('c'):
                case('C'):
                    while (invalidOption == true) {
                        choice = printConsoleSubMenu(QUIT_CHAR, 'c');
                        if (choice != QUIT_CHAR && (choice != (QUIT_CHAR - 0x20))) {
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

                /* Option d - select file type (unsorted vs. sorted vs. reverse sorted) */
                /* Existence check performed elsewhere */
                case('d'):
                case('D'):  
                    {
                    char userIn = 'n';
                    printCenteredTitle(" File Type Selection Menu ", 60);
                    cout << "Use sorted version of file? (y/n): ";  
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

                /* Option e - show configuration (i.e. the sort to be performed and on which file) */
                case('e'):
                case('E'):
                    printConfiguration(sortFileSize, ALGO_NAMES[algo], useSortedFile, useDescendingOrderSortedFile);
                    cout << "\nPress enter to continue: ";
                    
                    cin.get();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard bytes if user entered any

                    break;

                /* Option f - perform sort */
                case('f'):
                case('F'):
                // needed to define scope explicitly with curly braces here
                // refactored to refetch the unsorted list every iteration
                {

                    char numIterations = 0;
                    bool invalidEntry = true;
                    
                    int * fileReadBuff = new int[FILE_SIZES[sortFileSize]];

                    const char * fileName = (useSortedFile) ? FILE_NAMES_SORTED[sortFileSize] : FILE_NAMES[sortFileSize];
                    const char * fileName2 = (useDescendingOrderSortedFile) ? FILE_NAMES_SORTED_REVERSE[sortFileSize] : fileName;

                    printCenteredTitle(" Sort Performance ", 60);

                    cout << "Reading input file '" << fileName2 << ".txt'...\n";
                    if (!fileExists(fileName2)) {
                        cout << "\nFile '" << fileName2 << ".txt' does not exist.\n";
                        cout << "\nPlease generate the appropriate file via the main menu.\n";
                    }
                    else if (fileReadRandInts(fileName2, fileHandleRd, fileReadBuff, FILE_SIZES[sortFileSize])) {

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
                                int * fileReadBuff = new int[FILE_SIZES[sortFileSize]];
                                fileReadRandInts(fileName2, fileHandleRd, fileReadBuff, FILE_SIZES[sortFileSize]);
                                cout << "\nIteration: " << i << "\n";

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

                                duration = chrono::duration_cast<chrono::duration<double>>(stop - start);
                                timeElapsed = duration.count();
                                cout << "Sorting took " << fixed << setprecision(10) << timeElapsed << " seconds.\n";
                                
                                //printIntArray(ALGO_NAMES[algo], fileReadBuff, FILE_SIZES[sortFileSize], 5);

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
                                        cout << "\n";
                                    }  
                                }
                            }
                        }
                    }
                    else {
                        cout << "\nFile failed to open for reading...\n";
                    }

                    delete[] fileReadBuff; // Free allocated space.

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