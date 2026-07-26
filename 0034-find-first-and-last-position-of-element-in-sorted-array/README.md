# 0034-find-first-and-last-position-of-element-in-sorted-array

## 📋 Problem Description
Given an array of integers `nums` that is sorted in non-decreasing order, and a target integer `target`, the task is to find the starting and ending position of the `target` value within the array.

If the `target` is not found anywhere in the array, the function should return `[-1, -1]`.

The algorithm must be designed to achieve an `O(log n)` runtime complexity, where `n` is the number of elements in `nums`.

**Input:**
*   `nums`: A vector (or array) of integers, sorted in non-decreasing order.
*   `target`: An integer value to search for.

**Output:**
*   A vector of two integers `[start_index, end_index]` representing the 0-based index of the first and last occurrences of the `target`.
*   If `target` is not found, return `[-1, -1]`.

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
This problem asks us to pinpoint the entire contiguous range where a specific `target` value appears within a sorted array. It's not enough to just find *an* instance of the target; we need its absolute first and last positions. The critical constraint is the `O(log n)` time complexity, which immediately rules out simple linear scans and points towards a more efficient search method. Edge cases include an empty array, a target that doesn't exist, or a target that appears only once (in which case the first and last positions would be the same).

## 💡 Core Idea
Given that the input array is sorted and the required time complexity is `O(log n)`, the core idea is to use **Binary Search**. We can adapt the standard binary search algorithm to find the first occurrence of the target and then reuse a similar adapted binary search to find the last occurrence.

## 🧠 Approach — Binary Search
The **Binary Search** pattern is perfectly suited for problems that involve searching for elements in sorted data structures with a logarithmic time complexity requirement. A standard binary search typically finds *any* instance of an element or determines its presence. For this problem, we need to modify the standard binary search logic slightly.

To find the *first* occurrence, when we encounter the `target` at `mid`, we record this `mid` as a potential answer and then continue searching in the *left half* of the array to see if an even earlier occurrence exists.
Similarly, to find the *last* occurrence, when we encounter the `target` at `mid`, we record this `mid` as a potential answer and then continue searching in the *right half* of the array to see if an even later occurrence exists. This dual application of modified binary search allows us to efficiently locate both boundaries.

## 📝 Step-by-Step Algorithm

1.  **Main Function (`searchRange`):**
    *   Initialize two integer variables, `firstIndex` and `lastIndex`, both to `-1`. These will store our final results.
    *   Call a helper function, let's call it `findFirstOccurrence(nums, target)`, which is designed to find the index of the first appearance of `target`. Store its return value in `firstIndex`.
    *   Call another helper function, `findLastOccurrence(nums, target)`, to find the index of the last appearance of `target`. Store its return value in `lastIndex`.
    *   Finally, return a vector containing `firstIndex` and `lastIndex`.

2.  **Helper Function (`findFirstOccurrence(nums, target)`):**
    *   Initialize `left = 0` and `right = nums.size() - 1` to define the search space.
    *   Initialize `ans = -1`. This variable will store the index of the first occurrence found so far.
    *   Enter a `while` loop that continues as long as `left <= right`.
        *   Calculate the middle index: `mid = left + (right - left) / 2`. This prevents potential integer overflow compared to `(left + right) / 2`.
        *   **If `nums[mid] == target`:**
            *   We've found an instance of the `target`. This `mid` is a potential candidate for the *first* occurrence.
            *   Store `mid` in `ans`.
            *   Crucially, to find an *even earlier* occurrence, we must continue searching in the left half of the current search space. So, update `right = mid - 1`.
        *   **If `nums[mid] > target`:**
            *   The `target` (if it exists) must be in the left half of the current search space because the array is sorted.
            *   Update `right = mid - 1`.
        *   **If `nums[mid] < target`:**
            *   The `target` must be in the right half of the current search space.
            *   Update `left = mid + 1`.
    *   After the loop finishes, return the value of `ans`. If `target` was never found, `ans` will remain `-1`.

3.  **Helper Function (`findLastOccurrence(nums, target)`):**
    *   Initialize `left = 0` and `right = nums.size() - 1`.
    *   Initialize `ans = -1`. This variable will store the index of the last occurrence found so far.
    *   Enter a `while` loop that continues as long as `left <= right`.
        *   Calculate the middle index: `mid = left + (right - left) / 2`.
        *   **If `nums[mid] == target`:**
            *   We've found an instance of the `target`. This `mid` is a potential candidate for the *last* occurrence.
            *   Store `mid` in `ans`.
            *   Crucially, to find an *even later* occurrence, we must continue searching in the right half of the current search space. So, update `left = mid + 1`.
        *   **If `nums[mid] > target`:**
            *   The `target` must be in the left half.
            *   Update `right = mid - 1`.
        *   **If `nums[mid] < target`:**
            *   The `target` must be in the right half.
            *   Update `left = mid + 1`.
    *   After the loop finishes, return the value of `ans`. If `target` was never found, `ans` will remain `-1`.

## 💻 Solution
```cpp
class Solution {
public:
    /**
     * @brief Helper function to find the first occurrence of the target in a sorted array.
     * @param nums The sorted array of integers.
     * @param target The value to search for.
     * @return The index of the first occurrence of target, or -1 if not found.
     */
    int firstoccurence(vector<int>& nums, int target) {
        int left = 0; // Initialize the left pointer for the binary search range
        int right = nums.size() - 1; // Initialize the right pointer for the binary search range
        int ans = -1; // Variable to store the potential first occurrence index, initialized to -1 (not found)

        // Standard binary search loop: continues as long as the search space is valid
        while (left <= right) {
            // Calculate the middle index to prevent potential integer overflow
            // (left + right) / 2 could overflow if left and right are very large
            int mid = left + (right - left) / 2;

            if (nums[mid] == target) {
                // If the target is found at mid, this is a potential first occurrence.
                // We store this index and then try to find an even earlier occurrence
                // by narrowing our search to the left half of the current sub-array.
                ans = mid;
                right = mid - 1; // Move right pointer to search in the left sub-array
            } else if (nums[mid] > target) {
                // If the middle element is greater than the target,
                // the target (if it exists) must be in the left half.
                right = mid - 1;
            } else { // nums[mid] < target
                // If the middle element is less than the target,
                // the target must be in the right half.
                left = mid + 1;
            }
        }
        return ans; // Return the first occurrence index, or -1 if target was not found
    }

    /**
     * @brief Helper function to find the last occurrence of the target in a sorted array.
     * @param nums The sorted array of integers.
     * @param target The value to search for.
     * @return The index of the last occurrence of target, or -1 if not found.
     */
    int lastoccurence(vector<int>& nums, int target) {
        int left = 0; // Initialize the left pointer for the binary search range
        int right = nums.size() - 1; // Initialize the right pointer for the binary search range
        int ans = -1; // Variable to store the potential last occurrence index, initialized to -1 (not found)

        // Standard binary search loop: continues as long as the search space is valid
        while (left <= right) {
            // Calculate the middle index to prevent potential integer overflow
            int mid = left + (right - left) / 2;

            if (nums[mid] == target) {
                // If the target is found at mid, this is a potential last occurrence.
                // We store this index and then try to find an even later occurrence
                // by narrowing our search to the right half of the current sub-array.
                ans = mid;
                left = mid + 1; // Move left pointer to search in the right sub-array
            } else if (nums[mid] > target) {
                // If the middle element is greater than the target,
                // the target must be in the left half.
                right = mid - 1;
            } else { // nums[mid] < target
                // If the middle element is less than the target,
                // the target must be in the right half.
                left = mid + 1;
            }
        }
        return ans; // Return the last occurrence index, or -1 if target was not found
    }

    /**
     * @brief Main function to find both the first and last positions of a target element.
     * @param nums The sorted array of integers.
     * @param target The value to search for.
     * @return A vector containing the first and last indices of target, or [-1, -1] if not found.
     */
    vector<int> searchRange(vector<int>& nums, int target) {
        // Call the helper functions to find the first and last occurrences
        // and return their results as a vector of two integers.
        return { firstoccurence(nums, target), lastoccurence(nums, target) };
    }
};

```

## ⏱️ Complexity Analysis

| | Complexity | Reason |
|---|---|---|
| **Time** | O(log n) | The solution performs two independent binary searches: one for the first occurrence and one for the last occurrence. Each binary search takes O(log n) time. Therefore, the total time complexity is O(log n) + O(log n) = O(log n). |
| **Space** | O(1) | The algorithm uses a constant amount of extra space for variables like `left`, `right`, `mid`, and `ans` within the helper functions, regardless of the input array size. No additional data structures that scale with `n` are used. |

## 🔗 Related Problems
- 35. Search Insert Position
- 69. Sqrt(x)
- 162. Find Peak Element