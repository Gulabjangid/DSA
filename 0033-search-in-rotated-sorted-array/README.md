# 0033-search-in-rotated-sorted-array

## 📋 Problem Description
You are given an integer array `nums` that was initially sorted in ascending order and contains distinct values. This array was then possibly left rotated at an unknown pivot index `k`. This rotation means that the elements from index `k` to `n-1` come first, followed by elements from index `0` to `k-1`. For example, `[0,1,2,4,5,6,7]` rotated by `3` becomes `[4,5,6,7,0,1,2]`.

Given this rotated array `nums` and an integer `target`, your task is to find the index of the `target` in `nums`. If the `target` is not present in the array, return `-1`.

Your algorithm must achieve an `O(log n)` runtime complexity.

## 🔍 Examples
```
Input: nums = [4,5,6,7,0,1,2], target = 0
Output: 4
Explanation: The target 0 is found at index 4 in the array.
```
```
Input: nums = [4,5,6,7,0,1,2], target = 3
Output: -1
Explanation: The target 3 is not present in the array.
```
```
Input: nums = [1], target = 0
Output: -1
Explanation: The array contains only 1, and 0 is not present.
```

## 📌 Constraints
*   `1 <= nums.length <= 5000`
*   `-10^4 <= nums[i] <= 10^4`
*   All values of `nums` are **unique**.
*   `nums` is an ascending array that is possibly rotated.
*   `-10^4 <= target <= 10^4`

## 🤔 Understanding the Problem
The problem asks us to find a `target` value in an array that was originally sorted but has been rotated. The key challenge is that a standard binary search won't work directly because the array is no longer fully sorted. For instance, `nums[mid]` might be smaller than `nums[left]` if the rotation point is in the left half. We need to adapt the binary search logic to handle this "broken" sorted structure while still achieving the required `O(log n)` time complexity.

## 💡 Core Idea
Even though the entire array is rotated, when we split it into two halves using a `mid` point, at least one of these halves will always be sorted. We can leverage this property to intelligently decide which half to continue our search in.

## 🧠 Approach — Binary Search
The problem explicitly requires an `O(log n)` runtime complexity, which is a strong indicator that **Binary Search** is the intended algorithm. Although the array is rotated, it retains a crucial property: it's composed of two sorted subarrays. This partial sortedness allows us to adapt the binary search. In each step, we determine which half of the current search space (`left` to `mid` or `mid` to `right`) is sorted. Once we identify a sorted half, we can check if the `target` falls within that sorted range. If it does, we narrow our search to that sorted half; otherwise, the `target` must be in the *other* (potentially unsorted) half, and we search there. This process effectively halves the search space in each iteration, leading to `O(log n)` complexity.

## 📝 Step-by-Step Algorithm
1.  Initialize two pointers, `left` to `0` and `right` to `nums.size() - 1`, to define the current search space.
2.  Start a `while` loop that continues as long as `left` is less than or equal to `right`. This ensures our search space is valid.
3.  Inside the loop, calculate the `mid` index: `mid = left + (right - left) / 2`. This calculation prevents potential integer overflow that `(left + right) / 2` might cause with very large `left` and `right` values.
4.  Check if `nums[mid]` is equal to the `target`. If it is, we've found the target, so return `mid`.
5.  If `nums[mid]` is not the target, we need to determine which half of the array (from `left` to `mid` or `mid` to `right`) is sorted:
    *   **Case 1: The left half (`nums[left]` to `nums[mid]`) is sorted.** This condition is true if `nums[mid] >= nums[left]`.
        *   Now, check if the `target` falls within this sorted left half: `nums[left] <= target` AND `target < nums[mid]`.
            *   If true, the `target` must be in the left half, so update `right = mid - 1` to search in the left segment.
            *   If false, the `target` must be in the right (unsorted) half, so update `left = mid + 1` to search in the right segment.
    *   **Case 2: The right half (`nums[mid]` to `nums[right]`) is sorted.** This condition is true if `nums[mid] < nums[left]` (since the left half wasn't sorted, the right must be).
        *   Now, check if the `target` falls within this sorted right half: `nums[mid] < target` AND `target <= nums[right]`.
            *   If true, the `target` must be in the right half, so update `left = mid + 1` to search in the right segment.
            *   If false, the `target` must be in the left (unsorted) half, so update `right = mid - 1` to search in the left segment.
6.  If the `while` loop finishes without returning an index, it means the `target` was not found in the array. In this case, return `-1`.

## 💻 Solution

```cpp
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0; // Initialize the left pointer to the start of the array
        int right = nums.size() - 1; // Initialize the right pointer to the end of the array

        // Continue the binary search as long as the search space is valid
        while (left <= right) {
            // Calculate the middle index to prevent potential integer overflow
            int mid = left + (right - left) / 2;

            // If the middle element is the target, we found it
            if (nums[mid] == target) {
                return mid;
            }

            // Determine which half of the array is sorted
            // Case 1: The left half (from nums[left] to nums[mid]) is sorted
            if (nums[mid] >= nums[left]) {
                // Check if the target lies within this sorted left half
                if (nums[left] <= target && target < nums[mid]) {
                    // If target is in the left sorted half, search there
                    right = mid - 1;
                } else {
                    // Otherwise, target must be in the right (unsorted) half, search there
                    left = mid + 1;
                }
            }
            // Case 2: The right half (from nums[mid] to nums[right]) is sorted
            else { // nums[mid] < nums[left] implies the rotation point is in the left half, so right half is sorted
                // Check if the target lies within this sorted right half
                if (nums[mid] < target && target <= nums[right]) {
                    // If target is in the right sorted half, search there
                    left = mid + 1;
                } else {
                    // Otherwise, target must be in the left (unsorted) half, search there
                    right = mid - 1;
                }
            }
        }

        // If the loop finishes, the target was not found in the array
        return -1;
    }
};

```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(log n) | Each iteration of the binary search algorithm effectively halves the search space, leading to a logarithmic time complexity. |
| **Space** | O(1) | The algorithm uses a constant amount of extra space for pointers (`left`, `right`, `mid`), regardless of the input array size. |

## 🔗 Related Problems
- 153. Find Minimum in Rotated Sorted Array
- 154. Find Minimum in Rotated Sorted Array II
- 81. Search in Rotated Sorted Array II