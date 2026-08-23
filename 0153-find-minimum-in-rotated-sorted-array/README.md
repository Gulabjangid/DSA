# 0153-find-minimum-in-rotated-sorted-array

## 📋 Problem Description
You are given an array `nums` of length `n` that was originally sorted in ascending order. This array has been "rotated" between `1` and `n` times. A rotation operation moves the last element to the beginning of the array. For example, if `nums = [0,1,2,4,5,6,7]` and it's rotated 4 times, it becomes `[4,5,6,7,0,1,2]`. All elements in `nums` are unique.

Your task is to find and return the minimum element of this rotated sorted array.

You must implement an algorithm that runs in `O(log n)` time complexity.

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
Explanation: The original array was [11,13,15,17] and it was rotated 4 times (or 0 times, but problem states 1 to n times, so effectively 4 times means it's back to original).
```

## 📌 Constraints
*   `n == nums.length`
*   `1 <= n <= 5000`
*   `-5000 <= nums[i] <= 5000`
*   All the integers of `nums` are **unique**.
*   `nums` is sorted and rotated between `1` and `n` times.

## 🤔 Understanding the Problem
The problem asks us to find the smallest number in an array that was initially sorted but then "broken" into two sorted parts by a rotation. For example, `[4,5,6,7,0,1,2]` is essentially `[4,5,6,7]` followed by `[0,1,2]`. The minimum element (`0` in this case) is always the first element of the second sorted part. The challenge is to find this minimum efficiently, specifically in `O(log n)` time, which strongly suggests a binary search approach. The fact that elements are unique simplifies comparisons.

## 💡 Core Idea
Even though the array is rotated, it still maintains a crucial property: it's composed of two sorted subarrays. The minimum element is the "pivot" point where the second sorted subarray begins. We can leverage this piecewise sorted nature to apply binary search, repeatedly narrowing down the search space to the half that contains the minimum element.

## 🧠 Approach — Binary Search
Binary search is the ideal pattern for this problem due to the `O(log n)` time complexity requirement and the underlying sorted (albeit rotated) structure of the array. The array can be thought of as having a "left" sorted part (containing larger values) and a "right" sorted part (containing smaller values, including the minimum). By comparing the middle element with the rightmost element of our current search space, we can determine which half contains the minimum and discard the other half, effectively reducing the search space by half in each step.

## 📝 Step-by-Step Algorithm
1.  Initialize two pointers, `st` (start) to `0` and `end` to `nums.size() - 1`. These pointers define the current search range.
2.  Enter a `while` loop that continues as long as `st` is less than `end`. This condition ensures that our search space has at least two elements.
3.  Inside the loop, calculate the middle index `mid = st + (end - st) / 2`. This calculation method prevents potential integer overflow compared to `(st + end) / 2`.
4.  Compare the value at `nums[mid]` with the value at `nums[end]`:
    *   **If `nums[mid] > nums[end]`**: This indicates that the `mid` element is part of the "left" sorted portion (the larger values). The minimum element must therefore be in the right half of the current search space, specifically from `mid + 1` to `end`. Update `st = mid + 1`.
    *   **Else (`nums[mid] <= nums[end]`)**: This indicates that the `mid` element is part of the "right" sorted portion (the smaller values), or it *is* the minimum element itself, or the array is not truly rotated (e.g., `[1,2,3,4,5]`). In any of these scenarios, the minimum element must be in the range `[st, mid]`. We update `end = mid`. We do not set `end = mid - 1` because `nums[mid]` could potentially be the minimum.
5.  When the loop terminates, `st` will be equal to `end`. At this point, both pointers will be pointing to the index of the minimum element.
6.  Return `nums[st]` (or `nums[end]`, as they are the same).

## 💻 Solution

```cpp
class Solution {
public:
    int findMin(vector<int>& nums) {
        // Initialize two pointers, 'st' (start) and 'end'),
        // to define the current search space.
        // 'st' points to the first element, 'end' to the last.
        int st = 0;
        int end = nums.size() - 1;

        // The loop continues as long as 'st' is less than 'end'.
        // When 'st' equals 'end', we have narrowed down the search
        // to a single element, which must be the minimum.
        while (st < end) {
            // Calculate the middle index.
            // Using 'st + (end - st) / 2' prevents potential integer overflow
            // that ' (st + end) / 2' might cause if 'st' and 'end' are very large.
            int mid = st + (end - st) / 2;

            // Compare the element at 'mid' with the element at 'end'.
            // This comparison helps us determine which half of the array
            // contains the minimum element.

            // Case 1: nums[mid] > nums[end]
            // This implies that the 'mid' element is in the first, larger sorted part
            // of the rotated array. For example, in [4,5,6,7,0,1,2], if mid points to 7,
            // and end points to 2. Since 7 > 2, the minimum must be in the right half
            // (after mid), i.e., in [0,1,2].
            // So, we discard the left half including mid and update 'st'.
            if (nums[mid] > nums[end]) {
                st = mid + 1;
            }
            // Case 2: nums[mid] <= nums[end]
            // This implies that the 'mid' element is in the second, smaller sorted part
            // of the rotated array, or it is the minimum itself, or the array is not
            // rotated (or rotated n times) and mid is in the sorted portion.
            // For example, in [4,5,6,7,0,1,2], if mid points to 0, and end points to 2.
            // Since 0 <= 2, the minimum could be 0 or something to its left.
            // Or in [1,2,3,4,5], if mid points to 3, and end points to 5. Since 3 <= 5,
            // the minimum could be 3 or something to its left.
            // In either subcase, the minimum element must be in the range [st, mid].
            // We update 'end' to 'mid', keeping 'mid' as a potential candidate for the minimum.
            else {
                end = mid;
            }
        }

        // When the loop finishes, 'st' and 'end' will be equal,
        // pointing to the index of the minimum element.
        return nums[st];
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(log n) | Each iteration of the binary search loop effectively halves the search space, leading to logarithmic time complexity. |
| **Space** | O(1) | The algorithm uses a constant amount of extra space for pointers (`st`, `end`, `mid`), regardless of the input array size. |

## 🔗 Related Problems
*   33. Search in Rotated Sorted Array
*   154. Find Minimum in Rotated Sorted Array II
*   162. Find Peak Element