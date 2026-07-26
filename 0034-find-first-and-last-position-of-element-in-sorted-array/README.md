# 0034-find-first-and-last-position-of-element-in-sorted-array

## 📋 Problem Description
Given an array of integers `nums` that is sorted in non-decreasing order, the task is to find the starting and ending position of a given `target` value.

If the `target` is not found anywhere in the array, the function should return `[-1, -1]`.

The algorithm must be implemented with an `O(log n)` runtime complexity.

**Input:**
*   `nums`: A vector (or array) of integers, sorted in non-decreasing order.
*   `target`: An integer value to search for.

**Output:**
*   A vector of two integers `[start_index, end_index]` representing the first and last positions of the `target`. If `target` is not found, return `[-1, -1]`.

## 🔍 Examples
```
Input: nums = [5,7,7,8,8,10], target = 8
Output: [3,4]
Explanation: The first occurrence of 8 is at index 3, and the last occurrence is at index 4.

Input: nums = [5,7,7,8,8,10], target = 6
Output: [-1,-1]
Explanation: The target value 6 is not present in the array.

Input: nums = [], target = 0
Output: [-1,-1]
Explanation: The input array is empty, so the target cannot be found.
```

## 📌 Constraints
*   `0 <= nums.length <= 10^5`
*   `-10^9 <= nums[i] <= 10^9`
*   `nums` is a non-decreasing array.
*   `-10^9 <= target <= 10^9`

## 🤔 Understanding the Problem
This problem asks us to locate not just *an* instance of a `target` value, but specifically its first and last appearances within a sorted array. The key challenge is to achieve this in `O(log n)` time, which rules out a simple linear scan. We need to be careful about edge cases like an empty array, a target that doesn't exist, or a target that appears only once.

## 💡 Core Idea
Since the input array is sorted and the required time complexity is `O(log n)`, the core idea is to leverage Binary Search. A standard binary search finds *any* occurrence. To find the first and last occurrences, we will need two modified binary searches: one tailored to find the leftmost boundary and another for the rightmost boundary.

## 🧠 Approach — Binary Search
This problem is a classic application of the **Binary Search** algorithm. Binary search is perfectly suited here because the input array `nums` is sorted, allowing us to efficiently narrow down the search space by half in each step. This property is what enables the required `O(log n)` time complexity. Instead of a single binary search, we'll implement two specialized binary search functions: one to pinpoint the very first index where `target` appears, and another to find the very last index.

## 📝 Step-by-Step Algorithm

1.  **Main Function `searchRange(nums, target)`:**
    *   This function will serve as the entry point.
    *   It will call two helper functions: `firstoccurence(nums, target)` to find the starting index and `lastoccurence(nums, target)` to find the ending index.
    *   Finally, it will return a vector containing the results from these two helper calls.

2.  **Helper Function `firstoccurence(nums, target)` (Finding the Leftmost Index):**
    *   Initialize `left = 0`, `right = nums.size() - 1`.
    *   Initialize `ans = -1` to store the potential first index (default to -1 if not found).
    *   Enter a `while` loop that continues as long as `left <= right`:
        *   Calculate the middle index: `mid = left + (right - left) / 2`. This prevents potential integer overflow compared to `(left + right) / 2`.
        *   **If `nums[mid] == target`:**
            *   We've found an occurrence of the target. Store `mid` in `ans`.
            *   To ensure we find the *first* occurrence, we must continue searching in the left half of the current search space. So, update `right = mid - 1`.
        *   **If `nums[mid] > target`:**
            *   The target, if it exists, must be in the left half of the current search space. Update `right = mid - 1`.
        *   **If `nums[mid] < target`:**
            *   The target, if it exists, must be in the right half of the current search space. Update `left = mid + 1`.
    *   After the loop finishes, return the value of `ans`.

3.  **Helper Function `lastoccurence(nums, target)` (Finding the Rightmost Index):**
    *   Initialize `left = 0`, `right = nums.size() - 1`.
    *   Initialize `ans = -1` to store the potential last index (default to -1 if not found).
    *   Enter a `while` loop that continues as long as `left <= right`:
        *   Calculate the middle index: `mid = left + (right - left) / 2`.
        *   **If `nums[mid] == target`:**
            *   We've found an occurrence of the target. Store `mid` in `ans`.
            *   To ensure we find the *last* occurrence, we must continue searching in the right half of the current search space. So, update `left = mid + 1`.
        *   **If `nums[mid] > target`:**
            *   The target, if it exists, must be in the left half of the current search space. Update `right = mid - 1`.
        *   **If `nums[mid] < target`:**
            *   The target, if it exists, must be in the right half of the current search space. Update `left = mid + 1`.
    *   After the loop finishes, return the value of `ans`.

## 💻 Solution
```cpp
class Solution {
public:
    // Helper function to find the first (leftmost) occurrence of the target
    int firstoccurence(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;
        int ans = -1; // Initialize answer to -1 (target not found by default)

        // Standard binary search loop condition
        while (left <= right) {
            // Calculate mid to prevent potential integer overflow for large left/right values
            int mid = left + (right - left) / 2; 

            if (nums[mid] == target) {
                // If target is found, store its index as a potential first occurrence.
                // We then try to find an even earlier occurrence by searching in the left half.
                ans = mid;
                right = mid - 1; 
            } else if (nums[mid] > target) {
                // If the middle element is greater than the target,
                // the target (if it exists) must be in the left half.
                right = mid - 1;
            } else { // nums[mid] < target
                // If the middle element is less than the target,
                // the target (if it exists) must be in the right half.
                left = mid + 1;
            }
        }
        return ans; // Return the first occurrence index, or -1 if not found
    }

    // Helper function to find the last (rightmost) occurrence of the target
    int lastoccurence(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;
        int ans = -1; // Initialize answer to -1 (target not found by default)

        // Standard binary search loop condition
        while (left <= right) {
            // Calculate mid to prevent potential integer overflow
            int mid = left + (right - left) / 2; 

            if (nums[mid] == target) {
                // If target is found, store its index as a potential last occurrence.
                // We then try to find an even later occurrence by searching in the right half.
                ans = mid;
                left = mid + 1; 
            } else if (nums[mid] > target) {
                // If the middle element is greater than the target,
                // the target (if it exists) must be in the left half.
                right = mid - 1;
            } else { // nums[mid] < target
                // If the middle element is less than the target,
                // the target (if it exists) must be in the right half.
                left = mid + 1;
            }
        }
        return ans; // Return the last occurrence index, or -1 if not found
    }

    // Main function to find both first and last positions of the target
    vector<int> searchRange(vector<int>& nums, int target) {
        // Call the helper functions to find the first and last occurrences
        // and return their results as a vector of two integers.
        return { firstoccurence(nums,target), lastoccurence(nums,target) };
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(log n) | The solution performs two independent binary search operations. Each binary search takes `O(log n)` time on an array of size `n`. Therefore, the total time complexity remains `O(log n)`. |
| **Space** | O(1) | The algorithm uses a constant amount of extra space for variables like `left`, `right`, `mid`, and `ans`, regardless of the input array's size. |

## 🔗 Related Problems
- 35. Search Insert Position
- 278. First Bad Version
- 162. Find Peak Element