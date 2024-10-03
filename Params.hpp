#ifndef PARAMS_HPP
#define PARAMS_HPP

#include <cstdint>
#include <vector>

class Params {
    // API
    public:
        // Default constructor
        Params();

        // Constructor with some parameters
        Params(char opt, char cho);

        // Constructor with all parameters
        Params(char opt, char cho, uint32_t size, int algorithm, 
            bool useSorted, bool useDescending, bool quit);

        // Public methods
        void addDuration(double duration);
        bool removeDurationAtIndex(size_t index);  // Remove duration at a specific index
        bool removeLastDuration();                 // Remove the last added duration
        void clearDurations();                     // Clear all durations
        size_t getDurationCount() const;           // Get the number of durations
        double computeAverageDuration() const;

        // Getters/setters for private parameters
        char getOption() const { return option; }
        void setOption(char opt) { option = opt; }
        char getChoice() const { return choice; }
        void setChoice(char cho) { choice = cho; }
        uint32_t getSortFileSize() const { return sortFileSize; }
        void setSortFileSize(uint32_t size) { sortFileSize = size; }
        int getAlgo() const { return algo; }
        void setAlgo(int a) { algo = a; }
        bool isUseSortedFile() const { return useSortedFile; }
        void setUseSortedFile(bool use) { useSortedFile = use; }
        bool isUseDescendingOrderSortedFile() const { return useDescendingOrderSortedFile; }
        void setUseDescendingOrderSortedFile(bool use) { useDescendingOrderSortedFile = use; }
        bool isUserQuit() const { return userQuit; }
        void setUserQuit(bool quit) { userQuit = quit; }

    // Private members
    private:
        char option;                        // Not sure if i want this to be a param
        char choice;
        uint32_t sortFileSize;
        int algo;
        bool useSortedFile;
        bool useDescendingOrderSortedFile;
        bool userQuit;
        std::vector<double> durationValues; // Stores time duration values
};

#endif // PARAMS_HPP
