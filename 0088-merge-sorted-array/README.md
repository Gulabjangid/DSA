# 0088-merge-sorted-array

## 📋 Problem Description
You are given two integer arrays, `nums1` and `nums2`, both of which are sorted in non-decreasing order. You are also provided with two integers, `m` and `n`, representing the number of elements initially present in `nums1` and `nums2` respectively.

The goal is to merge `nums2` into `nums1` such that the resulting `nums1` array is sorted in non-decreasing order. The final sorted array must be stored directly within `nums1` (an in-place modification).

To accommodate the merged elements, `nums1` has a total length of `m + n`. The first `m` elements of `nums1` are the ones that should be merged, while the last `n` elements are initially set to `0` and should be treated as empty space. `nums2` has a length of `n`.

The function `merge` receives `nums1`, `m`, `nums2`, and `n` as input. It does not return any value; instead, it modifies `nums1` directly.

## 🔍 Examples
```
Input: nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3
Output: [1,2,2,3,5,6]
Explanation: The arrays to be merged are [1,2,3] and [2,5,6].
The result of the merge is [1,2,2,3,5,6], where the underlined elements originally came from nums1.
```

```
Input: nums1 = [1], m = 1, nums2 = [], n = 0
Output: [1]
Explanation: The arrays to be merged are [1] and [].
The result of the merge is [1].
```

```
Input: nums1 = [0], m = 0, nums2 = [1], n = 1
Output: [1]
Explanation: The arrays to be merged are [] and [1].
The result of the merge is [1].
Since m = 0, there are no initial elements in nums1 to consider. The '0' in nums1 is just a placeholder to ensure enough space.
```

## 📌 Constraints
*   `nums1.length == m + n`
*   `nums2.length == n`
*   `0 <= m, n <= 200`
*   `1 <= m + n <= 200`
*   `-10^9 <= nums1[i], nums2[j] <= 10^9`

## 🤔 Understanding the Problem
The problem asks us to combine two already sorted arrays, `nums1` (containing `m` meaningful elements) and `nums2` (containing `n` elements), into a single sorted array. The critical requirement is that the final sorted array must be stored directly within `nums1`, utilizing the empty space at its end. This "in-place" modification means we cannot simply create a new array. A naive approach of merging from the beginning would overwrite elements of `nums1` that haven't been processed yet, making the problem non-trivial.

## 💡 Core Idea
The key insight is to perform the merge operation from the *end* of `nums1` backwards. By placing the largest elements first into the largest available indices, we ensure that we never overwrite an element in `nums1` that still needs to be compared or moved.

## 🧠 Approach — Two Pointers
This problem is perfectly suited for the **Two Pointers** pattern. We can maintain three pointers: one for the current position in the valid part of `nums1` (starting from its effective end), one for the current position in `nums2` (starting from its end), and one for the current write position in the merged `nums1` (starting from its total end). This allows us to compare the largest remaining elements from both arrays and place them directly into their final sorted positions in `nums1` without needing any extra space. Merging from the end is crucial for in-place modification because it leverages the empty space at the end of `nums1` without destroying elements needed for comparison.

## 📝 Step-by-Step Algorithm
1.  **Initialize Pointers**:
    *   Create a pointer `idx` that points to the last available position in `nums1` where a merged element will be placed. This starts at `m + n - 1` (the very end of the `nums1` array).
    *   Create a pointer `i` that points to the last valid element in the initial `nums1` array. This starts at `m - 1`.
    *   Create a pointer `j` that points to the last element in `nums2`. This starts at `n - 1`.

2.  **Merge from End**:
    *   Start a `while` loop that continues as long as both `i` (pointer for `nums1`) and `j` (pointer for `nums2`) are non-negative, meaning there are still elements to compare in both arrays.
    *   Inside the loop, compare `nums1[i]` and `nums2[j]`:
        *   If `nums1[i]` is greater than or equal to `nums2[j]`, it means `nums1[i]` is the larger (or equal) element and should be placed at the current `idx` position in `nums1`. So, set `nums1[idx] = nums1[i]`, then decrement `i` to move to the next smaller element in `nums1`.
        *   Otherwise (if `nums2[j]` is larger), set `nums1[idx] = nums2[j]`, then decrement `j` to move to the next smaller element in `nums2`.
    *   In either case, after placing an element, decrement `idx` to move to the next available position in `nums1` (moving leftwards).

3.  **Handle Remaining `nums2` Elements**:
    *   After the first `while` loop finishes, one of the arrays (or both) might have been exhausted.
    *   If there are still elements remaining in `nums2` (i.e., `j >= 0`), it means all elements from the initial `nums1` have been placed, and the remaining elements in `nums2` are smaller than all elements already placed. Copy these remaining elements from `nums2` directly into `nums1` from `idx` downwards. Continue this until `j` becomes negative.
    *   Note: If there are still elements remaining in the initial `nums1` (i.e., `i >= 0`), no action is needed. These elements are already in their correct sorted positions relative to each other, and any `nums2` elements that were smaller than them would have already been placed.

## 💻 Solution
```cpp
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        // Initialize a pointer 'idx' for the current position in nums1 where we will place the merged element.
        // It starts at the very end of the nums1 array (m + n - 1), as we are merging backwards.
        int idx = m + n - 1;

        // Initialize a pointer 'i' for the last valid element in the initial part of nums1.
        // This is m - 1, as nums1 contains 'm' elements from index 0 to m-1.
        int i = m - 1;

        // Initialize a pointer 'j' for the last element in nums2.
        // This is n - 1, as nums2 contains 'n' elements from index 0 to n-1.
        int j = n - 1;

        // Loop while there are still elements to compare in both nums1 (initial part) and nums2.
        // We compare from the largest elements downwards.
        while (i >= 0 && j >= 0) {
            // If the current element in nums1 is greater than or equal to the current element in nums2,
            // it means nums1[i] is the larger (or equal) element and should be placed at the current 'idx' in nums1.
            if (nums1[i] >= nums2[j]) {
                nums1[idx] = nums1[i]; // Place nums1[i] into its sorted position.
                i--;                   // Move to the next smaller element in nums1.
            } else {
                // Otherwise, nums2[j] is the larger element.
                nums1[idx] = nums2[j]; // Place nums2[j] into its sorted position.
                j--;                   // Move to the next smaller element in nums2.
            }
            idx--; // Move the write pointer 'idx' one step to the left (towards the beginning of the array).
        }

        // After the main loop, one of the arrays (or both) might have been exhausted.
        // If there are still elements remaining in nums2 (i.e., j >= 0),
        // it means all elements from the initial nums1 have been placed, and the remaining nums2 elements
        // are smaller than all elements already placed.
        // We simply copy these remaining elements from nums2 into the beginning of nums1.
        while (j >= 0) {
            nums1[idx] = nums2[j]; // Copy the remaining element from nums2.
            idx--;                 // Move write pointer.
            j--;                   // Move nums2 pointer.
        }
        // Note: If there are remaining elements in nums1 (i.e., i >= 0),
        // they are already in their correct sorted positions and don't need to be moved.
        // This is because we merged from the end, and any elements from nums2 that were smaller
        // than these remaining nums1 elements would have already been placed.
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(m + n) | Each element from `nums1` (m elements) and `nums2` (n elements) is visited and placed into its final position exactly once. |
| **Space** | O(1) | The algorithm modifies `nums1` in-place and only uses a constant amount of extra space for pointers (`idx`, `i`, `j`). |

## 🔗 Related Problems
- 21. Merge Two Sorted Lists
- 977. Squares of a Sorted Array
- 75. Sort Colors