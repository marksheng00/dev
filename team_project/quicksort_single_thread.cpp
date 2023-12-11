#include <iostream>
#include <vector>

template<typename T>
std::vector<T> quicksort(std::vector<T>& a) {
    if (a.size() < 2) {
        return a; // Return array as is if the size is less than 2
    } else {
        T pivot = a[a.size() / 2]; // Choose the middle element as the pivot
        std::vector<T> lesser, equal, greater;

        for (const T& e : a) {
            if (e < pivot) {
                lesser.push_back(e); // Elements less than the pivot go into 'lesser'
            } else if (e == pivot) {
                equal.push_back(e);  // Elements equal to the pivot go into 'equal'
            } else {
                greater.push_back(e); // Elements greater than the pivot go into 'greater'
            }
        }

        std::vector<T> result;
        result = quicksort(lesser);  // Recursively sort the sub-array less than the pivot
        result.insert(result.end(), equal.begin(), equal.end());
        std::vector<T> temp = quicksort(greater);  // Recursively sort the sub-array greater than the pivot
        result.insert(result.end(), temp.begin(), temp.end());

        return result;
    }
}

int main() {
    std::vector<int> arr = {8, 14, -8, -9, 5, -9, -3, 0, 17, 19};
    std::vector<int> sorted_arr = quicksort(arr);

    std::cout << "Sorted Array: ";
    for (int element : sorted_arr) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    return 0;
}

