# 0027-remove-element

## 📋 Problem Description
Given an integer array `nums` and an integer `val`, the task is to remove all occurrences of `val` from `nums` **in-place**. This means modifying the original array directly without using extra space for a new array. The relative order of the remaining elements may be changed.

The function should return `k`, which is the number of elements in `nums` that are not equal to `val`. After the function executes, the first `k` elements of `nums` must contain these elements that are not equal to `val`. The content of `nums` beyond the `k`-th element does not matter.

## 🔍 Examples
```
Input:  nums = [3,2,2,3], val = 3
Output: 2, nums = [2,2,_,_]
Explanation: Your function should return k = 2, with the first two elements of nums being 2.
             The underscores indicate that elements beyond k are irrelevant.

Input:  nums = [0,1,2,2,3,0,4,2], val = 2
Output: 5, nums = [0,1,4,0,3,_,_,_]
Explanation: Your function should return k = 5, with the first five elements of nums containing 0, 0, 1, 3, and 4.
             Note that the five elements can be returned in any order.
             The underscores indicate that elements beyond k are irrelevant.
```

## 📌 Constraints
*   `0 <= nums.length <= 100`
*   `0 <= nums[i] <= 50`
*   `0 <= val <= 100`

## 🤔 Understanding the Problem
The core of this problem lies in the "in-place" modification requirement. We are not actually shrinking the array's size; instead, we are rearranging its elements such that all elements we want to keep are moved to the beginning of the array. The number of such elements (`k`) is what we need to return. The order of the elements that are kept does not matter, and the values in the array beyond the first `k` positions are irrelevant. This means we can overwrite elements we want to "remove" with elements we want to "keep".

## 💡 Core Idea
The key insight is to maintain a "write" pointer that tracks the next available position at the beginning of the array for an element that should be kept. As we iterate through the array with a "read" pointer, if an element is not `val`, we copy it to the position indicated by the "write" pointer and then advance the "write" pointer.

## 🧠 Approach — Two Pointers
This problem is a classic application of the **Two Pointers** pattern, specifically a variation often called "Fast and Slow Pointers" or "Read and Write Pointers".

This pattern fits perfectly because we need to iterate through the array (fast/read pointer) and selectively move elements to a different part of the same array (slow/write pointer). One pointer (`k` in the solution) keeps track of where the next "valid" element should be placed, effectively building the modified array from the beginning. The other pointer (the loop iterator) scans through all elements. By using two pointers, we can perform the in-place modification efficiently without needing extra space.

## 📝 Step-by-Step Algorithm
1.  Initialize a variable, let's call it `write_pointer` (or `k` as in the provided solution), to `0`. This pointer will keep track of the index where the next element to be kept should be placed. It will also ultimately represent the count of elements not equal to `val`.
2.  Iterate through each element in the `nums` array using a `read_pointer` (or a range-based for loop, which implicitly handles the read pointer).
3.  For each element `num` encountered by the `read_pointer`:
    a.  Check if `num` is **not** equal to `val` (the value we want to remove).
    b.  If `num` is not equal to `val`:
        i.  Assign `num` to `nums[write_pointer]`. This effectively moves the desired element to the front of the array.
        ii. Increment `write_pointer` by `1`. This prepares `write_pointer` for the next element that needs to be kept.
    c.  If `num` **is** equal to `val`:
        i.  Do nothing. This element is effectively "skipped" or "removed" as it will either be overwritten by a subsequent valid element or simply remain beyond the `k` valid elements.
4.  After the loop finishes iterating through all elements in `nums`, the `write_pointer` will hold the total count of elements that were not equal to `val`. Return `write_pointer`.

## 💻 Solution

```cpp
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        // Initialize a pointer 'k' to 0.
        // This 'k' serves two purposes:
        // 1. It acts as a 'write pointer', indicating the next available position
        //    in the array where an element NOT equal to 'val' should be placed.
        // 2. After the loop, 'k' will hold the count of elements that are not 'val'.
        int k = 0;
        
        // Iterate through each element 'num' in the 'nums' array.
        // This loop acts as our 'read pointer', scanning all elements.
        for (int num : nums) {
            // Check if the current element 'num' is NOT equal to the value 'val'
            // that we intend to remove.
            if (num != val) {
                // If 'num' is not 'val', it means we want to keep this element.
                // We place 'num' at the position indicated by 'k'.
                // Then, we increment 'k' to move the 'write pointer' to the
                // next available slot for the next element to keep.
                nums[k++] = num;
            }
            // If 'num' IS equal to 'val', we simply skip it.
            // This element is effectively "removed" because it won't be copied
            // to the front of the array, and its position will eventually be
            // overwritten by a subsequent desired element or left beyond the
            // first 'k' valid elements.
        }
        
        // After iterating through all elements, 'k' contains the total count
        // of elements that were not equal to 'val'. These 'k' elements are
        // now located at the beginning of the 'nums' array.
        return k;
    }
};

```

## ⏱️ Complexity Analysis

| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | We iterate through the `nums` array exactly once. Each element is visited and processed (at most one comparison and one assignment) in constant time. |
| **Space** | O(1) | We only use a single extra variable (`k`) to store the write pointer/count. No additional data structures are allocated that scale with the input size. |

## 🔗 Related Problems
- 26. Remove Duplicates from Sorted Array
- 283. Move Zeroes
- 80. Remove Duplicates from Sorted Array II