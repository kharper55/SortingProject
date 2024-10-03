#include "Params.hpp"
#include <stdexcept> // For std::out_of_range

// Default values
#define SET_SIZE_DEFAULT 1024
#define ALGO_DEFAULT 0

// Default constructor
Params::Params()
    : option('\0'),
      choice('\0'),
      sortFileSize(SET_SIZE_DEFAULT),
      algo(ALGO_DEFAULT),
      useSortedFile(false),
      useDescendingOrderSortedFile(false),
      userQuit(false) {}

// Constructor with option and choice
Params::Params(char opt, char cho)
    : option(opt),
      choice(cho),
      sortFileSize(SET_SIZE_DEFAULT),
      algo(ALGO_DEFAULT),
      useSortedFile(false),
      useDescendingOrderSortedFile(false),
      userQuit(false) {}

// Constructor with all parameters
Params::Params(char opt, char cho, uint32_t size, int algorithm, 
               bool useSorted, bool useDescending, bool quit)
    : option(opt),
      choice(cho),
      sortFileSize(size),
      algo(algorithm),
      useSortedFile(useSorted),
      useDescendingOrderSortedFile(useDescending),
      userQuit(quit) {}

void Params::addDuration(double duration) {
    durationValues.push_back(duration);
}

bool Params::removeDurationAtIndex(size_t index) {
    if (index < durationValues.size()) {
        durationValues.erase(durationValues.begin() + index);
        return true; // Successfully removed
    }
    return false; // Index out of range
}

bool Params::removeLastDuration() {
    if (!durationValues.empty()) {
        durationValues.pop_back();
        return true; // Successfully removed
    }
    return false; // No durations to remove
}

void Params::clearDurations() {
    durationValues.clear(); // Clear all durations
}

double Params::computeAverageDuration() const {
    if (durationValues.empty()) {
        return 0.0; // Return 0 if there are no durations
    }

    double sum = 0.0;
    for (double duration : durationValues) {
        sum += duration;
    }
    return sum / durationValues.size(); // Calculate the average
}
