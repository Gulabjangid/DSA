# 0153-find-minimum-in-rotated-sorted-array

## 📋 Problem Description
You are given an array `nums` of length `n` that was originally sorted in ascending order and contains unique elements. This array has been **rotated** between `1` and `n` times. A rotation operation moves the last element to the front, shifting all other elements one position to the right. For instance, if `nums = [0,1,2,4,5,6,7]` is rotated 4 times, it becomes `[4,5,6,7,0,1,2]`. If it's rotated 7 times, it becomes `[0,1,2,4,5,6,7]` (the original array).

Your task is to find and return the minimum element of this rotated sorted array.

You must implement an algorithm that runs in `O(log n)` time.

## 🔍 Examples
```
Input: nums = [3,4,5,1,2]
Output: 1
Explanation: The original array was [1,2,3,4,5] rotated 3 times.

Input: nums = [4,5,6,7,0,1,2]
Output: 0
Explanation: The original array was [0,1,2,4,5,6,7] and it was rotated 4 times.

Input: nums = [11,13,15,17]
Output: 11
Explanation: The original array was [11,13,15,17] and it was rotated 4 times (effectively 0 rotations, but problem states 1 to n rotations).
```

## 📌 Constraints
*   `n == nums.length`
*   `1 <= n <= 5000`
*   `-5000 <= nums[i] <= 5000`
*   All integers of `nums` are **unique**.
*   `nums` is sorted and rotated between `1` and `n` times.

## 🤔 Understanding the Problem
The problem asks us to locate the smallest element in an array that was initially sorted but has been shifted cyclically. While a linear scan would easily find the minimum in O(N) time, the crucial requirement is to achieve this in O(log N) time. This immediately signals that a simple iteration is not sufficient and we need a more efficient search strategy, likely leveraging the partially sorted nature of the array. The minimum element will always be the "pivot" point where the ascending order breaks and restarts.

## 💡 Core Idea
The core idea is to exploit the property that a rotated sorted array consists of two sorted subarrays. By comparing the middle element with the elements at the boundaries of our search space, we can determine which half contains the minimum element and effectively discard the other half, thus narrowing down the search space logarithmically.

## 🧠 Approach — Binary Search
This problem is a classic application of **Binary Search**. The `O(log n)` time complexity requirement is the strongest hint for this pattern. Even though the entire array isn't sorted, its structure (two sorted subarrays) allows us to make informed decisions about which half to continue searching in. Binary search is ideal for efficiently searching in sorted or partially sorted data structures by repeatedly dividing the search interval in half until the target is found or the interval becomes empty. Here, our "target" is the minimum element, which is the unique point where the ascending order "resets."

## 📝 Step-by-Step Algorithm
1.  Initialize two pointers, `st` (start) to `0` and `end` to `nums.size() - 1`. These pointers define the current search space within the array.
2.  Enter a `while` loop that continues as long as `st < end`. This condition ensures that our search space contains at least two elements, allowing us to effectively narrow it down. When `st == end`, we have converged on the minimum element.
3.  Calculate the `mid` index using the formula `mid = st + (end - st) / 2`. This method is preferred over `(st + end) / 2` to prevent potential integer overflow when `st` and `end` are very large.
4.  Compare the value at `nums[mid]` with the value at `nums[end]`:
    *   **If `nums[mid] > nums[end]`**: This scenario indicates that the `mid` element belongs to the "left" sorted portion of the array, and the `end` element belongs to the "right" sorted portion. Since `nums[mid]` is greater than `nums[end]`, it means the rotation point (and thus the minimum element) must lie *after* `mid`. Therefore, we update our start pointer: `st = mid + 1`. The search space becomes `[mid+1, end]`.
    *   **Else (`nums[mid] < nums[end]`)**: This implies that `nums[mid]` is either the minimum element itself or it is located in the same sorted segment as the minimum element. The `end` element is greater than `mid`, meaning the subarray from `mid` to `end` is sorted in ascending order. The minimum cannot be to the right of `mid`. Therefore, the minimum must be in the range `st` to `mid` (inclusive). We update our end pointer: `end = mid`. The search space becomes `[st, mid]`.
5.  Once the `while` loop terminates (when `st == end`), both pointers will be pointing to the index of the minimum element in the array.
6.  Return `nums[st]` (or `nums[end]`, as they are now the same).

## 💻 Solution
```cpp
class Solution {
public:
    int findMin(vector<int>& nums) {
        int st = 0; // Initialize the start pointer to the beginning of the array (index 0).
        int end = nums.size() - 1; // Initialize the end pointer to the last element's index.

        // The binary search loop continues as long as the search space contains more than one element.
        // When st == end, we have successfully narrowed down the search to a single element, which is the minimum.
        while (st < end) {
            // Calculate the middle index. This method prevents potential integer overflow
            // that could occur with (st + end) / 2 if st and end are very large.
            int mid = st + (end - st) / 2;

            // Compare the middle element with the element at the 'end' of the current search space.
            // This comparison is key to determining which half contains the minimum.

            // Case 1: If nums[mid] > nums[end]
            // This condition implies that the elements from 'mid' to 'end' are not sorted in ascending order
            // (e.g., [..., 7, 0, 1, 2]). The 'mid' element (7) is greater than the 'end' element (2).
            // This means the minimum element must be in the right half of the current search space,
            // specifically in the range from 'mid + 1' to 'end'.
            // Example: nums = [4,5,6,7,0,1,2], st=0, end=6, mid=3 (nums[mid]=7). nums[end]=2.
            // Since 7 > 2, the minimum (0) must be in [0,1,2]. So, we shift 'st' to 'mid + 1'.
            if (nums[mid] > nums[end]) {
                st = mid + 1;
            }
            // Case 2: If nums[mid] < nums[end]
            // This condition implies that the elements from 'mid' to 'end' are sorted in ascending order
            // (e.g., [..., 0, 1, 2]). The 'mid' element (0) is less than the 'end' element (2).
            // In this situation, 'nums[mid]' could be the minimum element itself, or the minimum
            // could be to its left (in the range 'st' to 'mid'). The minimum cannot be to the right of 'mid'.
            // Therefore, we update 'end' to 'mid', effectively narrowing the search to the left half.
            // Example: nums = [4,5,6,7,0,1,2], after first iteration st=4, end=6. mid=5 (nums[mid]=1). nums[end]=2.
            // Since 1 < 2, the minimum (1) is either at 'mid' or to its left. So, we shift 'end' to 'mid'.
            else { // nums[mid] < nums[end]
                end = mid;
            }
        }

        // When the loop terminates, 'st' and 'end' pointers will be equal,
        // and both will point to the index of the minimum element in the array.
        return nums[st];
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(log n) | In each iteration of the `while` loop, the search space (defined by `st` and `end`) is approximately halved. This logarithmic reduction in search space is the defining characteristic of binary search. |
| **Space** | O(1) | The algorithm uses a constant amount of extra space for a few variables (`st`, `end`, `mid`), regardless of the input array size `n`. |

## 🔗 Related Problems
- 33. Search in Rotated Sorted Array
- 81. Search in Rotated Sorted Array II
- 162. Find Peak Element