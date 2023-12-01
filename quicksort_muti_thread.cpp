#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

std::mutex mtx; // 互斥锁，用于保护对全局变量的访问

template<typename T>
void quicksort(std::vector<T>& a) {
    if (a.size() < 2) {
        return;
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

        // 创建线程并进行递归排序
        std::thread lesser_thread(quicksort<T>, std::ref(lesser));
        std::thread greater_thread(quicksort<T>, std::ref(greater));

        lesser_thread.join(); // 等待子数组的排序完成
        greater_thread.join();

        // 合并排序后的结果
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

    quicksort(arr);

    std::cout << "Sorted Array: ";
    for (int element : arr) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    return 0;
}
