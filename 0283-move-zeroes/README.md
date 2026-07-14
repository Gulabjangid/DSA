# 0283-move-zeroes

## 📋 Problem Description
Given an integer array `nums`, the task is to rearrange its elements such that all `0`'s are moved to the end of the array. Crucially, the relative order of the non-zero elements must be preserved. This operation must be performed in-place, meaning you cannot create a new copy of the array; modifications must happen directly within the original `nums` array. The function `moveZeroes` receives a reference to the integer array `nums` and modifies it directly, returning `void`.

## 🔍 Examples
```
Input: nums = [0,1,0,3,12]
Output: [1,3,12,0,0]
Explanation: The non-zero elements (1, 3, 12) maintain their relative order. All zeroes are moved to the end.

Input: nums = [0]
Output: [0]
Explanation: The array contains only a zero, which remains in place.

Input: nums = [1,2,3]
Output: [1,2,3]
Explanation: No zeroes are present, so the array remains unchanged.
```

## 📌 Constraints
*   `1 <= nums.length <= 10^4`
*   `-2^31 <= nums[i] <= 2^31 - 1`

## 🤔 Understanding the Problem
The problem asks us to partition an array into two sections: non-zero elements first, followed by zero elements. The main challenge is not just moving zeroes, but doing so *in-place* and *preserving the relative order* of the non-zero elements. This means if `1` appeared before `3` in the original array, it must still appear before `3` in the modified array, even if there were zeroes between them. The "in-place" constraint often hints at solutions that modify the array directly using pointers or swaps, avoiding extra memory.

## 💡 Core Idea
The core idea is to maintain a pointer that tracks the position where the next non-zero element should be placed. As we iterate through the array, whenever we encounter a non-zero element, we place it at this tracked position and advance the pointer. All elements after this pointer will eventually become zeroes.

## 🧠 Approach — Two Pointers
This problem is a classic application of the **Two Pointers** pattern. This pattern is suitable here because we need to iterate through an array and make decisions or perform operations based on the values at different positions, often involving partitioning or reordering elements in-place. One pointer (`i`) can be used to scan the entire array, while another pointer (`j`) can be used to mark the boundary or the "write" position for elements that satisfy a certain condition (in this case, non-zero elements). This allows us to effectively separate elements into two logical groups within the same array without using extra space.

## 📝 Step-by-Step Algorithm
1.  Initialize a pointer, let's call it `j`, to `0`. This pointer `j` will keep track of the position where the next non-zero element should be placed. Essentially, `nums[0...j-1]` will contain all non-zero elements found so far, in their correct relative order.
2.  Iterate through the array `nums` using another pointer, `i`, starting from `0` up to `n-1` (where `n` is the size of the array).
3.  Inside the loop, for each element `nums[i]`:
    a.  If `nums[i]` is **not equal to `0`**:
        i.  This means we have found a non-zero element that needs to be moved to the front part of the array.
        ii. Swap `nums[i]` with `nums[j]`. This moves the non-zero element to its correct position.
        iii. Increment `j` by `1`. This advances the "write" pointer to the next available slot for a non-zero element.
    b.  If `nums[i]` **is equal to `0`**:
        i.  Do nothing. We simply skip this element. The `j` pointer remains unchanged, effectively "leaving" the zero behind to be eventually overwritten by a non-zero element from `nums[i]` or to remain at the end of the array.
4.  After the loop finishes, all non-zero elements will have been moved to the beginning of the array (positions `0` to `j-1`), maintaining their original relative order. The remaining elements from `j` to `n-1` will all be `0`s.

## 💻 Solution
```cpp
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int n = nums.size(); // Get the total number of elements in the array.

        // 'j' is the "slow" pointer. It tracks the position where the next non-zero element should be placed.
        // All elements to the left of 'j' (i.e., nums[0...j-1]) are guaranteed to be non-zero.
        int j = 0; 
        
        // 'i' is the "fast" pointer. It iterates through all elements of the array.
        for (int i = 0; i < n; i++) {
            // If the current element nums[i] is a non-zero number:
            if (nums[i] != 0) {
                // We've found a non-zero element that needs to be moved to the front.
                // Swap nums[i] with nums[j].
                // This moves the non-zero element to its correct position at 'j'.
                // If i == j, it's a swap with itself (no-op), which is fine.
                // If i > j, it means nums[j] must be a zero (or a non-zero that was already processed
                // and 'j' moved past it), so we are effectively moving a non-zero forward and a zero backward.
                std::swap(nums[j], nums[i]);
                
                // Increment 'j' to point to the next available slot for a non-zero element.
                j++;
            }
            // If nums[i] is 0, we simply continue.
            // The 'j' pointer does not advance, effectively leaving the zero at nums[i] (or a zero that was
            // previously at nums[j]) to be overwritten later by a non-zero, or to remain at the end.
        }
        // After the loop, all non-zero elements are in nums[0...j-1] in their original relative order.
        // All elements from nums[j...n-1] will naturally be zeroes.
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | The single loop iterates through the array once. Each operation inside the loop (comparison, swap, increment) takes constant time. |
| **Space** | O(1) | The algorithm modifies the array in-place and uses only a few constant-space variables (`n`, `i`, `j`). No additional data structures are allocated. |

## 🔗 Related Problems
*   26. Remove Duplicates from Sorted Array
*   27. Remove Element