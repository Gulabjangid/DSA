# 0215-kth-largest-element-in-an-array

## 📋 Problem Description
Given an integer array `nums` and an integer `k`, the task is to find and return the `k`-th largest element in the array.

It's important to note that this refers to the `k`-th largest element in the sorted order, not the `k`-th distinct element. For example, if the array is `[3,2,3,1,2,4,5,5,6]` and `k=4`, the sorted array is `[1,2,2,3,3,4,5,5,6]`. The 4th largest element is `4`.

The problem also poses a challenge: "Can you solve it without sorting?"

## 🔍 Examples
```
Input: nums = [3,2,1,5,6,4], k = 2
Output: 5
Explanation: If sorted, the array is [1,2,3,4,5,6]. The 2nd largest element is 5.
```
```
Input: nums = [3,2,3,1,2,4,5,5,6], k = 4
Output: 4
Explanation: If sorted, the array is [1,2,2,3,3,4,5,5,6]. The 4th largest element is 4.
```

## 📌 Constraints
*   `1 <= k <= nums.length <= 10^5`
*   `-10^4 <= nums[i] <= 10^4`

## 🤔 Understanding the Problem
The problem asks us to find an element based on its rank if the array were sorted. Specifically, we need the `k`-th largest. This means if we arrange all numbers from smallest to largest, we're looking for the element that would be at the `(total_elements - k)`-th position (0-indexed) or `k`-th position from the end. The distinction between "k-th largest" and "k-th distinct largest" is crucial; duplicates are counted towards the rank. While the problem hints at a solution without sorting, the provided solution leverages sorting directly.

## 💡 Core Idea
The most straightforward approach to finding the k-th largest element is to first sort the entire array. Once the array is sorted in ascending order, the k-th largest element can be directly accessed by its index from the end of the array.

## 🧠 Approach — Sorting
The pattern used here is **Sorting**.
This pattern fits the problem because sorting an array arranges all its elements in a specific order (either ascending or descending). Once sorted, finding the element at a particular rank (like the k-th largest) becomes a simple matter of indexing. For an array sorted in ascending order, the largest element is at the last index, the second largest at the second-to-last, and so on. This makes it a very intuitive and direct way to solve the problem, even if not the most optimal in terms of time complexity for larger datasets or when the "without sorting" hint is considered.

## 📝 Step-by-Step Algorithm
1.  **Sort the Array**: Take the input array `nums` and sort all its elements in ascending order. This means after sorting, `nums[0]` will be the smallest element, and `nums[nums.size() - 1]` will be the largest.
2.  **Identify Target Index**: Since the array is sorted in ascending order, the 1st largest element is at index `nums.size() - 1`. The 2nd largest is at `nums.size() - 2`. Following this pattern, the `k`-th largest element will be located at index `nums.size() - k`.
3.  **Retrieve Element**: Access the element at the calculated index `nums.size() - k` and return its value. The provided solution uses a loop to effectively reach this index and assign its value, which achieves the same result as direct indexing.

## 💻 Solution
```cpp
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        // Step 1: Sort the entire array in ascending order.
        // After this operation, the elements in 'nums' will be arranged
        // from smallest to largest. For example, if nums was [3,2,1,5,6,4],
        // it becomes [1,2,3,4,5,6].
        sort(nums.begin(), nums.end());

        // Step 2 & 3: Find the k-th largest element.
        // In an ascending sorted array:
        // The 1st largest element is at index `nums.size() - 1`.
        // The 2nd largest element is at index `nums.size() - 2`.
        // ...
        // The k-th largest element is at index `nums.size() - k`.

        // The following loop is a slightly indirect way to retrieve the element
        // at the target index `nums.size() - k`.
        // It iterates from the beginning of the array up to and including
        // the target index, continuously updating 'kth' with the element
        // at the current index 'i'.
        // By the time the loop finishes, 'kth' will hold the value of
        // `nums[nums.size() - k]`, which is the desired k-th largest element.
        int kth = 0; // Initialize a variable to store the k-th largest element
        for (int i = 0; i <= nums.size() - k; ++i) {
            kth = nums[i]; // Update 'kth' with the element at the current index 'i'
        }
        return kth; // Return the value stored in 'kth'
        
        // A more direct way to write the retrieval after sorting would be:
        // return nums[nums.size() - k];
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N log N) | The dominant operation is sorting the array, which typically takes O(N log N) time for N elements using `std::sort`. The subsequent loop runs at most N times, contributing O(N), which is less than O(N log N). |
| **Space** | O(log N) | `std::sort` in C++ is often implemented using IntroSort, which is an in-place algorithm. It uses O(log N) auxiliary space for the recursion stack during its QuickSort phase. |

## 🔗 Related Problems
- 347. Top K Frequent Elements
- 703. Kth Largest Element in a Stream
- 378. Kth Smallest Element in a Sorted Matrix