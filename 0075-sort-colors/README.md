# 0075-sort-colors

## 📋 Problem Description
You are given an array `nums` containing `n` objects. These objects are colored red, white, or blue. Your task is to sort them in-place such that objects of the same color are adjacent, and the colors appear in the order red, white, and blue.

The colors are represented by integers: `0` for red, `1` for white, and `2` for blue.

You must solve this problem without using any built-in sorting functions from the library.

The function `sortColors` receives a reference to an integer vector `nums` and modifies it in-place; it does not return any value.

## 🔍 Examples
```
Input: nums = [2,0,2,1,1,0]
Output: [0,0,1,1,2,2]

Input: nums = [2,0,1]
Output: [0,1,2]
```

## 📌 Constraints
*   `n == nums.length`
*   `1 <= n <= 300`
*   `nums[i]` is either `0`, `1`, or `2`.

## 🤔 Understanding the Problem
The problem asks us to sort an array containing only three distinct values (0, 1, 2) into ascending order. The key constraints are to perform this sorting "in-place" (without using significant extra memory) and "without using the library's sort function." The follow-up specifically asks for a "one-pass algorithm using only constant extra space," which is the most efficient way to solve this particular problem. This makes it non-trivial because a simple two-pass counting sort would work but isn't a single pass, and general comparison sorts are usually `O(N log N)`.

## 💡 Core Idea
The core idea is to use a three-pointer approach to partition the array into three sections: elements confirmed to be `0`s, elements confirmed to be `2`s, and elements yet to be processed (which will eventually become `1`s in the middle).

## 🧠 Approach — Three Pointers (Dutch National Flag Algorithm)
This problem is a classic application of the **Dutch National Flag Algorithm**. This pattern is ideal when you need to sort an array containing elements of three distinct types (like 0, 1, and 2) into their respective sections in a single pass. It works by maintaining three pointers that define the boundaries of the three sections: one for elements less than a pivot (here, `0`s), one for elements equal to the pivot (here, `1`s), and one for elements greater than the pivot (here, `2`s). This approach is highly efficient because it processes each element at most once and requires only a constant amount of extra space for the pointers.

## 📝 Step-by-Step Algorithm

1.  **Initialize Pointers**:
    *   `left`: Pointer to the beginning of the array, representing the boundary for `0`s. All elements to the left of `left` (exclusive) are `0`s. Initialize `left = 0`.
    *   `right`: Pointer to the end of the array, representing the boundary for `2`s. All elements to the right of `right` (exclusive) are `2`s. Initialize `right = nums.size() - 1`.
    *   `mid`: Pointer to the current element being examined. Initialize `mid = 0`.

2.  **Iterate Through the Array**: Continue iterating as long as `mid` is less than or equal to `right`.

3.  **Process `nums[mid]`**:
    *   **If `nums[mid]` is `0` (red)**:
        *   This `0` belongs to the left section. Swap `nums[mid]` with `nums[left]`.
        *   Increment both `left` and `mid` pointers. `left` moves past the newly placed `0`, and `mid` moves to the next element to examine.
    *   **If `nums[mid]` is `1` (white)**:
        *   This `1` is already in its correct relative position (between `0`s and `2`s). No swap is needed.
        *   Increment only the `mid` pointer to move to the next element.
    *   **If `nums[mid]` is `2` (blue)**:
        *   This `2` belongs to the right section. Swap `nums[mid]` with `nums[right]`.
        *   Decrement the `right` pointer.
        *   **Crucially, do NOT increment `mid` here.** The element that was just swapped into `nums[mid]` (from `nums[right]`) could be a `0`, `1`, or `2`. It needs to be re-evaluated in the next iteration.

4.  **Termination**: The loop terminates when `mid` crosses `right`. At this point, all `0`s will be at the beginning, all `2`s at the end, and all `1`s will naturally be in the middle, thus sorting the array.

## 💻 Solution

```cpp
class Solution {
public:
    void sortColors(vector<int>& nums) {
        // 'left' pointer tracks the boundary for 0s.
        // All elements to the left of 'left' (exclusive) are 0s.
        int left = 0;

        // 'right' pointer tracks the boundary for 2s.
        // All elements to the right of 'right' (exclusive) are 2s.
        int right = nums.size() - 1;

        // 'mid' pointer is the current element being examined.
        int mid = 0;

        // Iterate as long as the 'mid' pointer has not crossed the 'right' pointer.
        // This ensures all elements up to 'right' are processed.
        while (mid <= right) {
            if (nums[mid] == 0) {
                // If the current element is 0:
                // It belongs to the left section. Swap it with the element at 'left'.
                swap(nums[mid], nums[left]);
                // Move both 'mid' and 'left' pointers forward.
                // 'left' moves past the newly placed 0.
                // 'mid' moves to the next element, as the element swapped from 'left'
                // into 'mid' was either a 0 (already processed) or a 1/2 that
                // was correctly placed relative to 'left'.
                mid++;
                left++;
            } else if (nums[mid] == 1) {
                // If the current element is 1:
                // It is already in its correct relative position (in the middle).
                // Just move 'mid' pointer forward to examine the next element.
                mid++;
            } else { // nums[mid] == 2
                // If the current element is 2:
                // It belongs to the right section. Swap it with the element at 'right'.
                swap(nums[mid], nums[right]);
                // Only decrement the 'right' pointer.
                // The element swapped into 'nums[mid]' from 'nums[right]'
                // could be a 0, 1, or 2. It needs to be re-evaluated in the next iteration,
                // so 'mid' does not advance.
                right--;
            }
        }
    }
};
```

## ⏱️ Complexity Analysis

| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | Each element is visited by the `mid` pointer at most once. Swapping operations take constant time. |
| **Space** | O(1) | Only a constant number of extra variables (pointers `left`, `mid`, `right`) are used, regardless of input size. |

## 🔗 Related Problems
*   922. Sort Array By Parity II
*   283. Move Zeroes
*   75. Sort Colors (This problem itself is a classic partitioning problem)