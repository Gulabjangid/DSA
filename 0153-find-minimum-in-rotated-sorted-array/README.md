# 0153-find-minimum-in-rotated-sorted-array

## 📋 Problem Description
You are given an array `nums` of length `n` that was originally sorted in ascending order. This array has been "rotated" between `1` and `n` times. Rotating an array `[a[0], a[1], ..., a[n-1]]` one time results in `[a[n-1], a[0], ..., a[n-2]]`. All elements in `nums` are unique.

Your task is to find and return the minimum element in this rotated sorted array.

The algorithm must run in `O(log n)` time complexity.

**Input:** A vector of integers `nums`.
**Output:** An integer representing the minimum element in `nums`.

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
Explanation: The original array was [11,13,15,17] and it was rotated 4 times (or 0 times, effectively).
```

## 📌 Constraints
*   `n == nums.length`
*   `1 <= n <= 5000`
*   `-5000 <= nums[i] <= 5000`
*   All the integers of `nums` are **unique**.
*   `nums` is sorted and rotated between `1` and `n` times.

## 🤔 Understanding the Problem
The problem asks us to find the smallest number in an array that was initially sorted but has been cyclically shifted. For example, `[1,2,3,4,5]` rotated 2 times becomes `[4,5,1,2,3]`. A straightforward linear scan to find the minimum would take `O(N)` time. However, the crucial constraint is to achieve `O(log N)` time complexity, which immediately suggests that a binary search approach is required. The challenge lies in adapting binary search to work on a "broken" sorted array where the usual monotonic property is disrupted by the rotation.

## 💡 Core Idea
The key insight is that a rotated sorted array always consists of two sorted segments. The minimum element is the "pivot" point where the second sorted segment begins, and it will be the only element that is smaller than its predecessor (unless the array is not rotated at all, in which case the first element is the minimum). We can leverage this property with binary search to efficiently locate this pivot point.

## 🧠 Approach — Binary Search
This problem is a classic application of **Binary Search**. The `O(log N)` time complexity requirement is a strong indicator for using binary search. While the entire array isn't sorted, we can always identify a sorted portion within our current search range. By comparing the middle element with the element at the end of our search range, we can determine which half of the array contains the minimum element and safely discard the other half. This repeated halving of the search space is what gives binary search its logarithmic time complexity.

## 📝 Step-by-Step Algorithm
1.  Initialize two pointers, `st` (start) to `0` and `end` to `nums.size() - 1`. These pointers define the current search space within the array.
2.  Enter a `while` loop that continues as long as `st < end`. This condition ensures that there is at least a two-element range to consider, allowing us to narrow down the search.
3.  Inside the loop, calculate the middle index `mid` using the formula `mid = st + (end - st) / 2`. This method helps prevent potential integer overflow that could occur with `(st + end) / 2` if `st` and `end` are very large.
4.  Compare the value at `nums[mid]` with the value at `nums[end]`:
    *   **If `nums[mid] > nums[end]`**: This condition implies that the `mid` element is part of the "left" sorted portion of the rotated array, and the rotation point (and thus the minimum element) must lie somewhere to the *right* of `mid`. For example, in `[4,5,6,7,0,1,2]`, if `mid` points to `7`, then `7 > 2`. The minimum `0` is in `[0,1,2]`. Therefore, we update `st = mid + 1` to search in the right half.
    *   **If `nums[mid] <= nums[end]`**: This condition implies that the `mid` element is part of the "right" sorted portion, or it *is* the minimum element itself, or the array is not rotated at all (fully sorted). For example, in `[4,5,6,7,0,1,2]`, if `mid` points to `0`, then `0 <= 2`. The minimum element could be `nums[mid]` or somewhere to its left. We can safely discard the elements from `mid+1` to `end`, but we must keep `mid` as a potential candidate for the minimum. Therefore, we update `end = mid`.
5.  The loop terminates when `st` becomes equal to `end`. At this point, both pointers converge on the index of the minimum element in the array.
6.  Return `nums[st]` (or `nums[end]`, as they are the same).

## 💻 Solution
```cpp
class Solution {
public:
    int findMin(vector<int>& nums) {
        // Initialize 'st' (start) pointer to the beginning of the array.
        int st = 0;
        
        // Initialize 'end' pointer to the end of the array.
        int end = nums.size() - 1;

        // The loop continues as long as 'st' is less than 'end'.
        // This ensures there's at least a two-element range to consider,
        // allowing us to narrow down the search space.
        // When st == end, we have converged on the minimum element.
        while (st < end) {
            // Calculate the middle index. Using st + (end - st) / 2 prevents
            // potential integer overflow that could occur with (st + end) / 2
            // if st and end are very large.
            int mid = st + (end - st) / 2;

            // Compare the middle element with the element at the 'end' pointer.
            // This comparison is key to determining which half contains the minimum.
            if (nums[mid] > nums[end]) {
                // If nums[mid] > nums[end], it means the 'mid' element
                // is in the left sorted portion of the rotated array.
                // For example, in [4,5,6,7,0,1,2], if mid points to 7, then 7 > 2.
                // The minimum element must therefore be in the right half (after mid).
                // We discard the left half and 'mid' itself, moving 'st' to mid + 1.
                st = mid + 1;
            } else {
                // If nums[mid] <= nums[end], it means the 'mid' element
                // is in the right sorted portion, or it is the minimum itself,
                // or the array is not rotated (fully sorted, e.g., [1,2,3,4]).
                // For example, in [4,5,6,7,0,1,2], if mid points to 0, then 0 <= 2.
                // The minimum element could be nums[mid] or somewhere to its left.
                // We can safely discard the right part (from mid+1 to end),
                // but we must keep 'mid' as a potential minimum.
                // So, we update 'end' to 'mid'.
                end = mid;
            }
        }
        
        // When the loop terminates, 'st' and 'end' will point to the same index.
        // This single index is the location of the minimum element in the array.
        return nums[st];       
    }
};

```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(log n) | Each iteration of the `while` loop effectively halves the search space, leading to logarithmic time complexity. |
| **Space** | O(1) | The algorithm uses a constant amount of extra space for pointers (`st`, `end`, `mid`), regardless of the input array's size. |

## 🔗 Related Problems
- 33. Search in Rotated Sorted Array
- 81. Search in Rotated Sorted Array II
- 162. Find Peak Element