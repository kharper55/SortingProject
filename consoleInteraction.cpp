#include "consoleInteraction.hpp"

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

/* ============================================================================

============================================================================ */
void printCenteredTitle(const char * title, int col_width) {
    const int size = strlen(title);
    //int padding = (col_width - size) / 2;
    // Calculate padding on both sides
    int total_padding = col_width - size;
    int left_padding = total_padding / 2;
    int right_padding = total_padding - left_padding; // Make sure right padding balances any leftover

    cout << "\n";

    for (int i = 0; i < left_padding; i++) {
        cout << "=";
    }

    cout << title;

    for (int i = 0; i < right_padding; i++) {
        cout << "=";
    }

    cout << "\n\n";
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

    printCenteredTitle(TITLE, COL_WIDTH);

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

    printCenteredTitle(TITLE, COL_WIDTH);

    const char * fileName = (sorted) ? FILE_NAMES_SORTED[setSize] : FILE_NAMES[setSize];
    const char * fileName2 = (reverseSorted) ? FILE_NAMES_SORTED_REVERSE[setSize] : fileName;

    cout << "File              : " << fileName2 << ".txt";
    cout << "\nDataset size      : " << FILE_SIZES[setSize];
    cout << "\nSorting algorithm : " << sortingAlgo << "\n";
}

/* ============================================================================

============================================================================ */
char printConsoleSubMenu(char quitChar, char option) {

    const int ITOA_BUFF_SIZE = 10;
    const int COL_WIDTH = 60;
    char itoa_buff[ITOA_BUFF_SIZE];
    char choice;
    const int numFiles = sizeof(FILE_SIZES)/sizeof(FILE_SIZES[0]);
    const int numAlgos = sizeof(ALGO_NAMES)/sizeof(ALGO_NAMES[0]);

    //cout << "\n";
    
    switch(option) {

        case('a'):
            printCenteredTitle(" Dataset Generation Menu ", COL_WIDTH);
            for(int i = 0; i < numFiles; i++) {
                cout << static_cast<char>(0x61 + i) << ") " << FILE_SIZES[i] << "\n";
                if (i == numFiles - 1) {
                    cout << static_cast<char>(0x61 + i + 1) << ") All\n";
                }
            }

            cout << "\nChoose a dataset size for file generation (use '" << quitChar << "' to cancel): ";
            break;

        case('b'):
            printCenteredTitle(" Algorithm Selection Menu ", COL_WIDTH);
            for(int i = 0; i < numAlgos; i++) {
                cout << static_cast<char>(0x61 + i) << ") " << ALGO_NAMES[i] << "\n";
            }

            cout << "\nChoose a sorting algorithm (use '" << quitChar << "' to cancel): ";
            break;

        case('c'):
            printCenteredTitle(" Dataset Size Selection Menu ", COL_WIDTH);
            for(int i = 0; i < numFiles; i++) {
                if (i < numFiles) {
                    cout << static_cast<char>(0x61 + i) << ") " << FILE_SIZES[i] << "\n";
                }
            }

            cout << "\nChoose a dataset size for sorting (use '" << quitChar << "' to cancel): ";
            break;

        default:
            break;
    }

    cin >> choice;

    return choice;
}