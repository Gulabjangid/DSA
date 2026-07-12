# 0026-remove-duplicates-from-sorted-array

## 📋 Problem Description
Given an integer array `nums` that is sorted in non-decreasing order, the task is to remove duplicate elements **in-place** such that each unique element appears only once. The relative order of the elements must be preserved.

The function should return `k`, which represents the number of unique elements in the modified array. After the function executes, the first `k` elements of `nums` should contain the unique numbers in sorted order. Any elements beyond index `k-1` can be ignored.

**Input:** An integer array `nums` sorted in non-decreasing order.
**Output:** An integer `k`, representing the count of unique elements. The input array `nums` will be modified in-place such that its first `k` elements contain the unique numbers.

## 🔍 Examples
```
Input: nums = [1,1,2]
Output: 2, nums = [1,2,_]
Explanation: Your function should return k = 2, with the first two elements of nums being 1 and 2 respectively. The elements beyond the returned k are irrelevant.
```

```
Input: nums = [0,0,1,1,1,2,2,3,3,4]
Output: 5, nums = [0,1,2,3,4,_,_,_,_,_]
Explanation: Your function should return k = 5, with the first five elements of nums being 0, 1, 2, 3, and 4 respectively. The elements beyond the returned k are irrelevant.
```

## 📌 Constraints
*   `1 <= nums.length <= 3 * 10^4`
*   `-100 <= nums[i] <= 100`
*   `nums` is sorted in **non-decreasing** order.

## 🤔 Understanding the Problem
The problem asks us to modify a given sorted array by removing all duplicate elements, ensuring that each unique number appears exactly once. This modification must be done "in-place," meaning we cannot use a new array to store the result; we must alter the original `nums` array directly. The relative order of the unique elements must also be maintained. Finally, we need to return the count of these unique elements, `k`. The fact that the array is sorted is a crucial hint, as it implies all duplicate elements will be adjacent.

## 💡 Core Idea
Since the array is sorted, all identical elements are grouped together. We can use two pointers: one to iterate through the entire array (the "fast" pointer) and another to mark the position where the next unique element should be placed (the "slow" pointer).

## 🧠 Approach — Two Pointers
This problem is a classic application of the **Two Pointers** pattern. This pattern is highly effective when dealing with sorted arrays or linked lists, especially when modifications need to be done in-place or when searching for pairs/subsequences. In this scenario, one pointer (`k` in the solution, often called `slow`) tracks the boundary of the unique elements found so far, indicating where the next unique element should be written. The other pointer (`i` in the solution, often called `fast`) iterates through the entire array to discover new unique elements. The sorted nature of the array allows us to easily identify duplicates by simply comparing `nums[i]` with the last unique element `nums[k-1]`.

## 📝 Step-by-Step Algorithm
1.  Initialize a pointer `k` (which will also represent the count of unique elements) to `1`. This is because the first element `nums[0]` is always considered unique and is already in its correct place. `k` will point to the next available position for a unique element.
2.  Initialize another pointer `i` to `1`. This pointer will iterate through the array from the second element to the end.
3.  Start a loop that continues as long as `i` is less than the total size of the array (`nums.size()`).
4.  Inside the loop, compare the element at `nums[i]` (the element currently being examined by the fast pointer) with the element at `nums[k-1]` (the last unique element recorded by the slow pointer).
    *   If `nums[i]` is **not equal** to `nums[k-1]`, it means we have found a new unique element.
        *   Place this unique element `nums[i]` into the position `nums[k]`.
        *   Increment `k` by `1` to move the slow pointer to the next available slot for a unique element.
    *   If `nums[i]` is **equal** to `nums[k-1]`, it means `nums[i]` is a duplicate.
        *   In this case, we simply ignore `nums[i]`. The `k` pointer remains unchanged, effectively "skipping" this duplicate. The element at `nums[i]` will eventually be overwritten by a subsequent unique element or will fall outside the `k` boundary.
5.  After the loop finishes, the pointer `k` will hold the total count of unique elements. Return `k`. The `nums` array will have its first `k` elements containing the unique numbers in sorted order.

## 💻 Solution
```cpp
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        // 'k' acts as a "slow" pointer, indicating the next position
        // where a unique element should be placed.
        // It also represents the count of unique elements found so far.
        // We initialize it to 1 because the first element (nums[0])
        // is always considered unique and is already in its correct place.
        // (Constraints guarantee nums.length >= 1, so nums[0] always exists).
        int k = 1;

        // 'i' acts as a "fast" pointer, iterating through the array
        // starting from the second element (index 1).
        for (int i = 1; i < nums.size(); ++i) {
            // Compare the element at the fast pointer 'i' with the
            // last recorded unique element, which is at nums[k-1].
            // Since the array is sorted, if nums[i] is different from nums[k-1],
            // it means we have found a new unique element.
            if (nums[i] != nums[k - 1]) {
                // Place this new unique element at the position indicated by 'k'.
                // This effectively moves the unique element to the front of the array.
                nums[k] = nums[i];
                // Increment 'k' to point to the next available position
                // for a unique element, and to update the count of unique elements.
                k++;
            }
            // If nums[i] == nums[k-1], it's a duplicate.
            // We simply ignore it and let 'i' advance, while 'k' remains
            // unchanged. The duplicate element at nums[i] will eventually
            // be overwritten by a new unique element if found later,
            // or it will be beyond the 'k' boundary and thus ignored.
        }

        // 'k' now holds the total number of unique elements.
        // The first 'k' elements of 'nums' contain these unique elements.
        return k;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | The algorithm iterates through the array once with the `fast` pointer `i`. Each element is visited and processed a constant number of times. |
| **Space** | O(1) | No additional data structures are used. All modifications are performed in-place within the input array. |

## 🔗 Related Problems
- 27. Remove Element
- 80. Remove Duplicates from Sorted Array II
- 283. Move Zeroes