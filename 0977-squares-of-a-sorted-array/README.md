# 0977-squares-of-a-sorted-array

## 📋 Problem Description
Given an integer array `nums` that is sorted in **non-decreasing** order, the task is to return a new array containing the squares of each number from `nums`, also sorted in **non-decreasing** order.

**Input:** An integer array `nums` sorted in non-decreasing order.
**Output:** An integer array where each element is the square of the corresponding element in `nums`, and the entire output array is sorted in non-decreasing order.

## 🔍 Examples
```
Input: nums = [-4,-1,0,3,10]
Output: [0,1,9,16,100]
Explanation: After squaring, the array becomes [16,1,0,9,100].
After sorting, it becomes [0,1,9,16,100].
```

```
Input: nums = [-7,-3,2,3,11]
Output: [4,9,9,49,121]
```

## 📌 Constraints
*   `1 <= nums.length <= 10^4`
*   `-10^4 <= nums[i] <= 10^4`
*   `nums` is sorted in **non-decreasing** order.

## 🤔 Understanding the Problem
The problem asks us to transform an array of integers by squaring each element, and then ensure the resulting array of squares is sorted in non-decreasing order. The initial array `nums` is already sorted. A key observation is that squaring negative numbers can change their relative order (e.g., -4 < -1, but (-4)^2 = 16 and (-1)^2 = 1, so 16 > 1). This means simply squaring each element in place will not necessarily result in a sorted array, thus requiring an additional sorting step. The problem statement also hints at a more optimal O(N) solution, implying that the direct approach of squaring and then sorting is considered "trivial" but valid.

## 💡 Core Idea
The most straightforward and direct way to solve this problem is a two-step process: first, iterate through the array and square every element, and then apply a standard sorting algorithm to arrange these squared values into non-decreasing order. This approach directly fulfills both requirements of the problem.

## 🧠 Approach — Direct Transformation and Sort
This approach involves two distinct phases: a transformation phase and a sorting phase. It's a common "brute force" or "naive" method when a more optimized approach isn't immediately obvious or necessary. It fits this problem because it directly addresses both requirements: squaring all numbers and then sorting them. While not the most optimal for this specific problem (as hinted by the follow-up), it correctly solves it.

## 📝 Step-by-Step Algorithm
1.  Initialize an array, which will be the result. For this solution, we will modify the input `nums` array directly.
2.  Iterate through each element of the `nums` array from the beginning to the end.
3.  For each element, calculate its square (multiply the element by itself).
4.  Replace the original element in the `nums` array with its squared value.
5.  After all elements have been squared, the array is no longer guaranteed to be sorted. Therefore, sort the entire `nums` array in non-decreasing order using a standard sorting algorithm.
6.  Return the modified and sorted `nums` array.

## 💻 Solution
```cpp
class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        // Step 1: Iterate through the input array and square each element in-place.
        // This modifies the original 'nums' array.
        // Example: If nums = [-4, -1, 0, 3, 10]
        // After this loop, nums becomes [16, 1, 0, 9, 100]
        for(int i = 0; i < nums.size(); ++i) {
            nums[i] = nums[i] * nums[i]; // Calculate the square and update the element
        }
        
        // Step 2: After all elements are squared, the array might no longer be sorted.
        // For example, [16, 1, 0, 9, 100] is not sorted.
        // We need to sort the entire array of squared values.
        // The `std::sort` function in C++ uses an efficient sorting algorithm
        // (typically IntroSort, which is a hybrid of QuickSort, HeapSort, and InsertionSort)
        // to sort the elements in non-decreasing order.
        sort(nums.begin(), nums.end());
        
        // Step 3: Return the array, which now contains squared elements sorted in non-decreasing order.
        // For the example, [16, 1, 0, 9, 100] becomes [0, 1, 9, 16, 100].
        return nums;
    }
};

```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N log N) | Squaring each of the N elements takes O(N). Sorting the N squared elements takes O(N log N) using a comparison-based sort. The dominant factor is sorting. |
| **Space** | O(1) | The solution modifies the input array in-place. No additional data structures are created that scale with the input size N. (Ignoring the auxiliary space used by the sorting algorithm itself, which is typically O(log N) for recursion stack or O(1) average for IntroSort). |

## 🔗 Related Problems
*   215. Kth Largest Element in an Array
*   88. Merge Sorted Array
*   167. Two Sum II - Input Array Is Sorted