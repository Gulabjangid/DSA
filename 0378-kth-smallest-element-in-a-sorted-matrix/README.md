# 0378-kth-smallest-element-in-a-sorted-matrix

## 📋 Problem Description
Given an `n x n` integer matrix, where every row and every column is sorted in ascending order, the task is to find and return the `k`-th smallest element in the entire matrix.

It's important to note that we are looking for the `k`-th smallest element in the sorted order of all elements, not the `k`-th distinct element.

The solution must have a memory complexity better than `O(n^2)`.

## 🔍 Examples
```
Input: matrix = [[1,5,9],[10,11,13],[12,13,15]], k = 8
Output: 13
Explanation: The elements in the matrix, when sorted, are [1, 5, 9, 10, 11, 12, 13, 13, 15]. The 8th smallest number is 13.

Input: matrix = [[-5]], k = 1
Output: -5
Explanation: The only element is -5, which is the 1st smallest.
```

## 📌 Constraints
*   `n == matrix.length == matrix[i].length`
*   `1 <= n <= 300`
*   `-10^9 <= matrix[i][j] <= 10^9`
*   All rows and columns of `matrix` are guaranteed to be sorted in non-decreasing order.
*   `1 <= k <= n^2`

## 🤔 Understanding the Problem
The problem asks us to find an element by its rank (the `k`-th smallest) within a special kind of 2D array. The key property is that both rows and columns are individually sorted. This means the smallest element is always `matrix[0][0]` and the largest is `matrix[n-1][n-1]`. The challenge is that simply merging rows or columns isn't straightforward due to the 2D nature. We need a way to efficiently find the `k`-th element without explicitly sorting all `n^2` elements if possible, especially considering the memory constraint.

## 💡 Core Idea
The most straightforward way to find the `k`-th smallest element from a collection of numbers is to gather all numbers and then use a data structure that can efficiently maintain order or extract ranked elements. A priority queue (heap) is a natural fit for this task.

## 🧠 Approach — Priority Queue (Max-Heap)
This solution utilizes a **Priority Queue**, specifically a **Max-Heap**.
A max-heap is a data structure that always keeps the largest element at its root (top). This property makes it suitable for finding the `k`-th smallest element. The approach is to insert all elements from the matrix into the max-heap. Once all elements are in the heap, we can repeatedly extract the largest element until only `k` elements remain. The element at the top of the heap will then be the `k`-th smallest element from the original set. This works because by removing the largest elements, we are effectively "counting down" from the largest to the `k`-th smallest.

## 📝 Step-by-Step Algorithm
1.  **Initialize a Max-Priority Queue**: Create an empty `std::priority_queue` (which is a max-heap by default in C++).
2.  **Populate the Priority Queue**: Iterate through each row of the `matrix` from `i = 0` to `n-1`. For each row, iterate through each element `matrix[i][j]` from `j = 0` to `n-1`. Push every element encountered into the priority queue.
3.  **Extract `k`-th Smallest**: After all `n*n` elements have been inserted, the priority queue will contain all elements from the matrix. To find the `k`-th smallest, we need to remove the `n*n - k` largest elements.
    *   While the size of the priority queue is greater than `k`, repeatedly remove the top element (which is the largest element currently in the heap) using `pq.pop()`.
4.  **Return Result**: Once the loop finishes, the priority queue will contain exactly `k` elements, and the element at its top (`pq.top()`) will be the `k`-th smallest element from the original matrix. Return this value.

## 💻 Solution
```cpp
class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        // A max-priority queue is used. By default, std::priority_queue in C++
        // is a max-heap, meaning the largest element is always at the top.
        priority_queue<int> pq;

        int n = matrix.size(); // Get the dimension of the square matrix

        // Iterate through all elements in the matrix
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                // Push each element into the max-priority queue.
                // This operation takes O(log P) time, where P is the current size of the PQ.
                pq.push(matrix[i][j]);
            }
        }

        // After the loops, the priority queue contains all n*n elements.
        // To find the k-th smallest, we need to remove the (n*n - k) largest elements.
        // The loop continues as long as the priority queue has more than 'k' elements.
        while (k < pq.size()) {
            // Remove the largest element (top of the max-heap).
            // This operation also takes O(log P) time.
            pq.pop();
        }

        // After removing (n*n - k) elements, the priority queue will have exactly 'k' elements.
        // The element at the top of the max-heap will be the k-th smallest element overall.
        return pq.top();
    }
};

```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N^2 log N) | Each of the `N^2` elements is pushed into the priority queue. Each push operation takes `O(log P)` time, where `P` is the current size of the priority queue (up to `N^2`). Summing these up gives `O(N^2 log(N^2)) = O(N^2 log N)`. Subsequently, `N^2 - k` elements are popped, each taking `O(log N)` time. |
| **Space** | O(N^2) | The priority queue stores all `N^2` elements from the matrix in the worst case. This solution **does not** meet the problem's explicit memory constraint of "better than `O(n^2)`". An optimized approach using a min-heap of size `k` or binary search on the answer could achieve `O(k)` or `O(1)` space respectively. |

## 🔗 Related Problems
- 215. Kth Largest Element in an Array
- 703. Kth Largest Element in a Stream
- 373. Find K Pairs with Smallest Sums