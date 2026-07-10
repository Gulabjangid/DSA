# 0088-merge-sorted-array

## 📋 Problem Description
You are given two integer arrays, `nums1` and `nums2`, which are sorted in non-decreasing order. You are also given two integers, `m` and `n`, representing the number of elements in `nums1` and `nums2` respectively that are actually part of the sorted sequences.

The task is to merge `nums2` into `nums1` so that `nums1` contains all elements from both arrays, sorted in non-decreasing order.

The final sorted array should not be returned by the function. Instead, it must be stored directly within `nums1`. To facilitate this, `nums1` has a total length of `m + n`. The first `m` elements of `nums1` are the ones to be merged, while the last `n` elements are initially set to `0` and should be ignored as they are placeholders for the elements from `nums2`. `nums2` has a length of `n`.

The function signature is `void merge(vector<int>& nums1, int m, vector<int>& nums2, int n)`. It modifies `nums1` in-place and returns nothing.

## 🔍 Examples
```
Input: nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3
Output: [1,2,2,3,5,6]
Explanation: The arrays we are merging are [1,2,3] and [2,5,6].
The result of the merge is [1,2,2,3,5,6] with the underlined elements coming from nums1.
```

```
Input: nums1 = [1], m = 1, nums2 = [], n = 0
Output: [1]
Explanation: The arrays we are merging are [1] and [].
The result of the merge is [1].
```

```
Input: nums1 = [0], m = 0, nums2 = [1], n = 1
Output: [1]
Explanation: The arrays we are merging are [] and [1].
The result of the merge is [1].
Note that because m = 0, there are no elements in nums1. The 0 is only there to ensure the merge result can fit in nums1.
```

## 📌 Constraints
*   `nums1.length == m + n`
*   `nums2.length == n`
*   `0 <= m, n <= 200`
*   `1 <= m + n <= 200`
*   `-10^9 <= nums1[i], nums2[j] <= 10^9`

## 🤔 Understanding the Problem
The problem asks us to combine two already sorted arrays, `nums1` (its first `m` elements) and `nums2` (all `n` elements), into a single sorted array. The crucial part is that this merge must happen *in-place* within `nums1`, meaning we cannot create a new array to store the result. `nums1` is conveniently pre-sized to `m + n` with its last `n` slots available (filled with zeros). The non-trivial aspect is how to merge without overwriting the valid elements of `nums1` before they've been processed, especially if we were to start merging from the beginning of the array.

## 💡 Core Idea
To perform the merge in-place without overwriting elements of `nums1` that are still needed, we should start placing the merged elements from the *end* of `nums1` and work our way backward. This way, the available `n` slots at the end of `nums1` are utilized first, and we only move elements from `nums1` to positions that are already "empty" or have been processed.

## 🧠 Approach — Two Pointers
This problem is a classic example of the **Two Pointers** pattern.
We use three pointers to efficiently manage the merging process: one for the end of the valid elements in `nums1`, one for the end of `nums2`, and one for the current position in `nums1` where the merged element should be placed. This pattern is ideal for problems involving sorted arrays where comparisons and element placements are needed. By starting from the largest elements (i.e., the end of the arrays) and moving backward, we can directly fill the available space in `nums1` without needing any temporary storage, thus achieving an in-place merge.

## 📝 Step-by-Step Algorithm
1.  **Initialize Pointers**:
    *   Create a pointer `i` and set it to `m - 1`. This pointer will track the last valid element in `nums1`.
    *   Create a pointer `j` and set it to `n - 1`. This pointer will track the last element in `nums2`.
    *   Create a pointer `idx` and set it to `m + n - 1`. This pointer will track the current position in `nums1` where the merged element should be placed (starting from the very end of the array).

2.  **Main Merging Loop**:
    *   Start a `while` loop that continues as long as both `i` (pointer for `nums1`) and `j` (pointer for `nums2`) are valid (i.e., `i >= 0` and `j >= 0`).
    *   Inside the loop, compare `nums1[i]` and `nums2[j]`:
        *   If `nums1[i]` is greater than or equal to `nums2[j]`: This means `nums1[i]` is the larger element. Place `nums1[i]` into `nums1[idx]`. Then, decrement `i` to move to the next smaller element in `nums1`.
        *   Else (if `nums2[j]` is greater): This means `nums2[j]` is the larger element. Place `nums2[j]` into `nums1[idx]`. Then, decrement `j` to move to the next smaller element in `nums2`.
    *   After placing an element, decrement `idx` in either case to move to the next available position in `nums1` (one step to the left).

3.  **Handle Remaining Elements from `nums2`**:
    *   After the main loop finishes, it's possible that `nums2` still has elements remaining (if `j >= 0`). This happens if all elements from `nums1` were smaller than some elements in `nums2`, or `nums1` was exhausted first.
    *   Start another `while` loop that continues as long as `j >= 0`.
    *   Place `nums2[j]` into `nums1[idx]`.
    *   Decrement both `j` and `idx`.
    *   (Note: If `nums1` has remaining elements (`i >= 0`), they are already in their correct sorted positions at the beginning of `nums1` and do not need to be moved. So, no explicit loop is needed for `nums1`'s remaining elements.)

4.  **Completion**: Once both loops are finished, `nums1` will contain the merged and sorted elements.

## 💻 Solution
```cpp
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        // Initialize a pointer 'idx' to the last position of the merged array in nums1.
        // This is where the largest element will be placed first.
        int idx = m + n - 1;

        // Initialize pointer 'i' to the last valid element in nums1.
        // (The elements from index 0 to m-1 are the actual elements to merge from nums1).
        int i = m - 1;

        // Initialize pointer 'j' to the last element in nums2.
        int j = n - 1;

        // Loop while there are elements to compare in both nums1 (valid part) and nums2.
        // We compare from the end because we are filling nums1 from the end,
        // which prevents overwriting elements of nums1 that haven't been processed yet.
        while (i >= 0 && j >= 0) {
            // If the current element in nums1 is greater than or equal to the current element in nums2,
            // it means nums1[i] is the larger element and should go into the current 'idx' position.
            if (nums1[i] >= nums2[j]) {
                nums1[idx] = nums1[i]; // Place nums1[i] at the end of the merged section
                i--;                   // Move to the next smaller element in nums1
            } else {
                // Otherwise, nums2[j] is larger, so it goes into the current 'idx' position.
                nums1[idx] = nums2[j]; // Place nums2[j] at the end of the merged section
                j--;                   // Move to the next smaller element in nums2
            }
            idx--; // Move the write pointer to the next available position (one step left)
        }

        // After the main loop, one of the arrays might still have elements.
        // If there are remaining elements in nums2 (j >= 0), it means they are all smaller
        // than any elements already placed from nums1 (or nums1 was exhausted).
        // These remaining elements from nums2 must be placed at the beginning of nums1.
        while (j >= 0) {
            nums1[idx] = nums2[j]; // Place the remaining nums2 element
            idx--;                 // Move write pointer
            j--;                   // Move nums2 pointer
        }

        // If there are remaining elements in nums1 (i >= 0), they are already in their correct
        // sorted positions at the beginning of nums1 and do not need to be moved.
        // For example, if nums1 = [1,2,3,0,0,0], m=3, nums2 = [], n=0.
        // The main loop won't run. The second loop won't run. nums1 remains [1,2,3,0,0,0] (effectively [1,2,3]).
        // This is correct.
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(m + n) | We iterate through `nums1` (m elements) and `nums2` (n elements) at most once. Each element is compared and placed exactly once. |
| **Space** | O(1) | The merge is performed in-place within `nums1`, using only a constant number of extra pointers. |

## 🔗 Related Problems
*   21. Merge Two Sorted Lists
*   148. Sort List
*   977. Squares of a Sorted Array