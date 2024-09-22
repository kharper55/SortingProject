#include "sortingAlgorithms.hpp"

/* ============================================================================
bubbleSort(array[0...n - 1])
  for i <- 0 to n - 2
    for j <- 0 to n - 2 - i
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
selectionSort(array[0...n - 1])
  for i from 0 to n - 1 do
    minIdx <- i
    for j from i + 1 to n - 1 do
        if array[j] < array[current minimum]
            minIdx <- j
    if minIdx != i
        swap array[i] with array[minIdx]
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
insertionSort(array[0...n - 1])
  for i from 1 to n - 1
    key <- array[i]
    j <- i - 1
    while j >= 0 and array[j] > key
        array[j + 1] <- array[j]
        j <- j - 1
    array[j + 1] <- key
end insertionSort
============================================================================ */
void insertionSort(int arr[], int arrLen) {
    int i, j, key;
    // Assume first index is sorted
    for (i = 1; i < arrLen; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
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
/* ============================================================================
mergeSort(array[0...n-1], leftIdx, rightIdx):
    if leftIdx > rightIdx 
        return
    midIdx = (leftIdx + rightIdx)/2
    mergeSort(array[0...n-1], leftIdx, midIdx)
    mergeSort(array[0...n-1], midIdx + 1, rightIdx)
    merge(array[0...n-1], leftIdx, midIdx, rightIdx)
end mergeSort
============================================================================ */
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

/* ============================================================================
quickSort(array[0...n-1], leftIdx, rightIdx)
    if (leftIdx < rightIdx)
        pivotIdx <- partition(array, leftIdx, rightIdx)
        quickSort(array, leftIdx, pivotIdx - 1)
        quickSort(array, pivotIdx + 1, rightIdx)
end quickSort
============================================================================ */

/* ============================================================================
partition(array, leftmostIndex, rightmostIndex)
        set rightmostIndex as pivotIndex
        storeIndex <- leftmostIndex - 1
        for i <- leftmostIndex + 1 to rightmostIndex
        if element[i] < pivotElement
            swap element[i] and element[storeIndex]
            storeIndex++
        swap pivotElement and element[storeIndex+1]
    return storeIndex + 1
end partition
============================================================================ */
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
shellSort(array[0...n-1]])
    for interval i <- (n - 1)/2m down to 1
        for each interval "i" in array
            sort all the elements at interval "i"
end shellSort
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