#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono> // Include the chrono header for timing

std::mutex mtx; // Mutex for protecting access to global variable

template<typename T>
void quicksort(std::vector<T>& a) {
    if (a.size() < 2) {
        return; // No need to sort if the array has fewer than 2 elements
    } else {
        T pivot = a[a.size() / 2]; // Choosing the middle element as the pivot
        std::vector<T> lesser, equal, greater;

        for (const T& e : a) {
            if (e < pivot) {
                lesser.push_back(e); // Elements less than pivot go to 'lesser'
            } else if (e == pivot) {
                equal.push_back(e);  // Elements equal to pivot go to 'equal'
            } else {
                greater.push_back(e); // Elements greater than pivot go to 'greater'
            }
        }

        // Create threads and recursively sort
        std::thread lesser_thread(quicksort<T>, std::ref(lesser));
        std::thread greater_thread(quicksort<T>, std::ref(greater));

        lesser_thread.join(); // Wait for the sorting of sub-arrays to complete
        greater_thread.join();

        // Merge the results after sorting
        mtx.lock();
        a.clear();
        a.insert(a.end(), lesser.begin(), lesser.end());
        a.insert(a.end(), equal.begin(), equal.end());
        a.insert(a.end(), greater.begin(), greater.end());
        mtx.unlock();
    }
}

int main() {
    std::vector<int> arr = {8, 14, -8, -9, 5, -9, -3, 0, 17, 19};

    // Start the timer
    auto start = std::chrono::high_resolution_clock::now();

    quicksort(arr);

    // Stop the timer
    auto stop = std::chrono::high_resolution_clock::now();

    // Calculate the duration
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "Sorted Array: ";
    for (int element : arr) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    // Output the duration
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;

    return 0;
}