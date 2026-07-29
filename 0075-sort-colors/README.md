# 0075-sort-colors

## 📋 Problem Description
You are given an array `nums` containing `n` objects. These objects are colored red, white, or blue. The colors are represented by integers: `0` for red, `1` for white, and `2` for blue. Your task is to sort these objects *in-place* so that all objects of the same color are adjacent, and they appear in the order red, white, and blue. This means all `0`s should come first, followed by all `1`s, and then all `2`s.

You must solve this problem without using any built-in library sort functions.

The function receives a `vector<int>& nums` as input and modifies it directly (returns `void`).

## 🔍 Examples
```
Input: nums = [2,0,2,1,1,0]
Output: [0,0,1,1,2,2]
Explanation: The array is sorted such that all 0s come first, then 1s, then 2s.
```

```
Input: nums = [2,0,1]
Output: [0,1,2]
Explanation: The array is sorted in the required order.
```

## 📌 Constraints
*   `n == nums.length`
*   `1 <= n <= 300`
*   `nums[i]` is either `0`, `1`, or `2`.

## 🤔 Understanding the Problem
The problem asks us to perform a specific type of sorting on an array that contains only three distinct values (0, 1, and 2). The key challenges are the requirements for an *in-place* solution (modifying the original array without significant extra memory) and *without using standard library sort functions*. The "Follow up" explicitly guides us towards a one-pass algorithm using constant extra space, which is the most efficient way to solve this. This means we need a custom sorting logic tailored to these three specific values.

## 💡 Core Idea
The core idea is to partition the array into three distinct regions: elements known to be `0`s, elements known to be `1`s, and elements known to be `2`s. This can be achieved by maintaining three pointers that define the boundaries of these regions and iterating through the array once.

## 🧠 Approach — Dutch National Flag Algorithm (Three Pointers)
This problem is a classic application of the **Dutch National Flag Algorithm**, which is a specialized **Three Pointers** technique. This pattern is ideal for sorting an array containing a fixed, small number of distinct elements (like 0, 1, 2) into distinct partitions. It allows for a single pass through the array while maintaining the order of the partitions (0s, then 1s, then 2s) using only a constant amount of extra space for the pointers. By strategically swapping elements based on their value, we can move `0`s to the beginning, `2`s to the end, and leave `1`s in the middle, all within one traversal.

## 📝 Step-by-Step Algorithm
1.  Initialize three pointers:
    *   `left`: Points to the first element of the array. This pointer will track the boundary of the `0`s region. All elements to its left (exclusive) are `0`s.
    *   `mid`: Points to the current element being examined. This pointer iterates through the array.
    *   `right`: Points to the last element of the array. This pointer will track the boundary of the `2`s region. All elements to its right (exclusive) are `2`s.
2.  Start a loop that continues as long as the `mid` pointer is less than or equal to the `right` pointer. This ensures we process all elements between the `0`s and `2`s regions.
3.  Inside the loop, examine the value at `nums[mid]`:
    *   **If `nums[mid]` is `0` (red):**
        *   This `0` needs to be moved to the `left` side of the array.
        *   Swap `nums[mid]` with `nums[left]`.
        *   Increment both `left` and `mid` pointers. The element at `left` is now correctly a `0`, and the element that was swapped into `mid` (which came from `left`) needs to be re-evaluated in the next iteration (or it was already a `0` and is now correctly placed).
    *   **If `nums[mid]` is `1` (white):**
        *   This `1` is already in its correct "middle" position relative to the `0`s and `2`s.
        *   Simply increment the `mid` pointer to move to the next element.
    *   **If `nums[mid]` is `2` (blue):**
        *   This `2` needs to be moved to the `right` side of the array.
        *   Swap `nums[mid]` with `nums[right]`.
        *   Decrement the `right` pointer. The element at `right` is now correctly a `2`.
        *   **Crucially, do NOT increment `mid`** in this case. The element that was swapped into `nums[mid]` (which came from `right`) has not yet been examined. It could be a `0`, `1`, or `2`, and must be processed in the next iteration of the loop.

## 💻 Solution
```cpp
class Solution {
public:
    void sortColors(vector<int>& nums) {
        // Initialize three pointers:
        // 'left' pointer tracks the boundary for 0s (elements to its left are 0s).
        // 'right' pointer tracks the boundary for 2s (elements to its right are 2s).
        // 'mid' pointer iterates through the array, examining elements.
        int left = 0;
        int right = nums.size() - 1;
        int mid = 0;

        // Loop as long as the 'mid' pointer is within the unsorted region
        // (i.e., it hasn't crossed the 'right' pointer).
        while (mid <= right) {
            if (nums[mid] == 1) {
                // If the current element is 1, it's already in its correct relative position.
                // Just move to the next element.
                mid++;
            } else if (nums[mid] == 0) {
                // If the current element is 0, it belongs to the 'left' partition.
                // Swap it with the element at 'left'.
                std::swap(nums[left], nums[mid]);
                // Move both 'left' and 'mid' pointers forward.
                // The element at 'left' is now confirmed to be 0.
                // The element swapped into 'mid' needs to be checked, but since it came from 'left',
                // it would have been a 0 or 1, and 'mid' moving forward is safe.
                left++;
                mid++;
            } else { // nums[mid] == 2
                // If the current element is 2, it belongs to the 'right' partition.
                // Swap it with the element at 'right'.
                std::swap(nums[right], nums[mid]);
                // Move the 'right' pointer backward.
                // The element at 'right' is now confirmed to be 2.
                // IMPORTANT: Do NOT increment 'mid' here. The element that was swapped
                // into nums[mid] (which came from the 'right' side) has not yet been examined.
                // It could be a 0, 1, or 2, and must be processed in the next iteration.
                right--;
            }
        }
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | The `mid` pointer traverses the array from `0` to `N-1` at most once. Each element is visited and potentially swapped a constant number of times. |
| **Space** | O(1) | Only a constant amount of extra space is used for the three pointers (`left`, `mid`, `right`), regardless of the input array size. |

## 🔗 Related Problems
*   283. Move Zeroes
*   905. Sort Array By Parity
*   86. Partition List