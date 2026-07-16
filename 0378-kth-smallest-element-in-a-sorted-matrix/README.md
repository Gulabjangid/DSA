# 0378-kth-smallest-element-in-a-sorted-matrix

## 📋 Problem Description
Given an `n x n` matrix where each row and each column is sorted in ascending order, the task is to find and return the `k`-th smallest element in the entire matrix. It's important to note that we are looking for the `k`-th smallest element in the sorted order of all elements, not the `k`-th distinct element.

The function receives a `vector<vector<int>> matrix` (the `n x n` matrix) and an integer `k`. It must return an integer, which is the `k`-th smallest element.

A crucial requirement is to find a solution with a memory complexity better than `O(n^2)`.

## 🔍 Examples
```
Input: matrix = [[1,5,9],[10,11,13],[12,13,15]], k = 8
Output: 13
Explanation: The elements in the matrix, when sorted, are [1,5,9,10,11,12,13,13,15]. The 8th smallest number is 13.

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
The problem asks us to find the `k`-th smallest element in a special kind of matrix: one where both its rows and columns are sorted. This property is key, as it suggests we don't necessarily need to flatten and sort the entire matrix. The challenge lies in efficiently finding this `k`-th element without using excessive memory, specifically better than `O(n^2)`. Simply extracting all elements into a list and sorting it would work, but might not meet the memory or time constraints for larger `n`.

## 💡 Core Idea
The provided solution's core idea is to collect all elements from the matrix into a data structure that can efficiently keep track of the largest elements seen so far, and then extract the `k`-th smallest element from this collection. A max-priority queue (max-heap) is used for this purpose.

## 🧠 Approach — Heap / Priority Queue
This approach utilizes a **Max-Priority Queue (Max-Heap)**. A priority queue is a data structure that allows efficient retrieval of the maximum (or minimum) element. In C++, `std::priority_queue` by default implements a max-heap.

The reason this pattern fits is that we need to find the `k`-th smallest element. A common strategy for finding the `k`-th smallest/largest element in a collection is to use a heap. If we want the `k`-th smallest, we can use a max-heap. If we want the `k`-th largest, we can use a min-heap. The provided solution, however, uses a max-heap to store *all* elements, then repeatedly pops the largest until `k` elements remain, at which point the top of the heap is the `k`-th smallest.

## 📝 Step-by-Step Algorithm
1.  **Initialize a Max-Priority Queue**: Create an empty max-priority queue (a max-heap). This priority queue will store integers.
2.  **Iterate and Populate**: Traverse through each element of the `n x n` matrix. For every element `matrix[i][j]`, push it into the max-priority queue.
3.  **Reduce to K Elements**: After all `n*n` elements have been pushed into the priority queue, it now contains all elements from the matrix. The priority queue is ordered such that the largest element is always at the top. To find the `k`-th smallest element, we need to remove the largest elements until only `k` elements remain.
    *   Repeatedly pop (remove the top element from) the priority queue as long as its size is greater than `k`.
4.  **Retrieve Result**: Once the priority queue contains exactly `k` elements, the element at the top of the priority queue (which is the largest among the remaining `k` elements) will be the `k`-th smallest element from the original matrix. Return this element.

## 💻 Solution
```cpp
class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {

        // Initialize a max-priority queue. By default, std::priority_queue is a max-heap.
        // It will store integers.
        priority_queue<int> pq;

        // Get the size of the matrix (n x n).
        int n = matrix.size();

        // Iterate through each row of the matrix.
        for (int i = 0; i < n; i++) {
            // Iterate through each column in the current row.
            for (int j = 0; j < n; j++) {
                // Push the current matrix element into the priority queue.
                // This will add all n*n elements to the priority queue.
                pq.push(matrix[i][j]);
            }
        }

        // After pushing all elements, the priority queue contains all n*n elements.
        // To find the k-th smallest, we need to remove the largest elements
        // until only k elements remain. The top of the max-heap will then be
        // the largest among the k smallest, which is the k-th smallest element.
        // We keep popping as long as the priority queue size is greater than k.
        while (k < pq.size()) {
            pq.pop(); // Remove the largest element (top of the max-heap).
        }

        // The priority queue now contains exactly k elements.
        // The top element is the largest among these k elements,
        // which corresponds to the k-th smallest element in the original matrix.
        return pq.top();
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N^2 log(N^2)) | The algorithm iterates through all `N^2` elements of the matrix. Each element is pushed into a priority queue. In the worst case, the priority queue can grow to `N^2` elements. A push operation on a priority queue of size `P` takes `O(log P)` time. Thus, `N^2` pushes take `O(N^2 log(N^2))` time. After populating, `N^2 - k` elements are popped, each taking `O(log(N^2))` time. The dominant factor is `N^2 log(N^2)`. |
| **Space** | O(N^2) | The priority queue stores all `N^2` elements from the matrix. In the worst case, `k` could be `N^2`, requiring all elements to be stored. |

**Important Note on Constraints:** The problem statement explicitly requires a solution with "memory complexity better than `O(n^2)`". The provided solution uses `O(n^2)` space, which does not meet this specific requirement. A more optimal heap-based solution would maintain a max-heap of size `k` throughout the iteration, leading to `O(N^2 log k)` time and `O(k)` space, which would satisfy the memory constraint. Other approaches like binary search on the answer space can achieve `O(N log(max_val - min_val))` time and `O(1)` space.

## 🔗 Related Problems
- 215. Kth Largest Element in an Array
- 703. Kth Largest Element in a Stream
- 373. Find K Pairs with Smallest Sums