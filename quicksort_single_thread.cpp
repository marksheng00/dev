#include <iostream>
#include <vector>

template<typename T>
std::vector<T> quicksort(std::vector<T>& a) {
    if (a.size() < 2) {
        return a;
    } else {
        T pivot = a[a.size() / 2]; // 选择中间位置的元素作为基准值
        std::vector<T> lesser, equal, greater;

        for (const T& e : a) {
            if (e < pivot) {
                lesser.push_back(e); // 小于基准值的元素放入 lesser
            } else if (e == pivot) {
                equal.push_back(e);  // 等于基准值的元素放入 equal
            } else {
                greater.push_back(e); // 大于基准值的元素放入 greater
            }
        }

        std::vector<T> result;
        result = quicksort(lesser);  // 对小于基准值的子数组进行递归排序
        result.insert(result.end(), equal.begin(), equal.end());
        std::vector<T> temp = quicksort(greater);  // 对大于基准值的子数组进行递归排序
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
