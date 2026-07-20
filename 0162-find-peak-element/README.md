# 0162-find-peak-element

## 📋 Problem Description
A peak element in an array is defined as an element that is strictly greater than both of its immediate neighbors.

Given a **0-indexed** integer array `nums`, your task is to find and return the index of any peak element. If there are multiple peak elements in the array, returning the index of any one of them is acceptable.

For elements at the boundaries of the array, you can imagine that `nums[-1]` and `nums[n]` (where `n` is the length of the array) are both equal to negative infinity (`-∞`). This means that an element at either end of the array is always considered strictly greater than a neighbor that is outside the array's bounds.

Your algorithm must achieve an `O(log n)` time complexity.

## 🔍 Examples
```
Input: nums = [1,2,3,1]
Output: 2
Explanation: 3 is a peak element, and its index is 2.
```

```
Input: nums = [1,2,1,3,5,6,4]
Output: 5
Explanation: The element 2 at index 1 is a peak, and the element 6 at index 5 is also a peak. Your function can return the index of either one.
```

## 📌 Constraints
*   `1 <= nums.length <= 1000`
*   `-2^31 <= nums[i] <= 2^31 - 1`
*   `nums[i] != nums[i + 1]` for all valid `i` (meaning no adjacent elements are equal, so no plateaus).

## 🤔 Understanding the Problem
The problem asks us to find the index of *any* element that is strictly larger than its immediate left and right neighbors. The crucial conditions are the `O(log n)` time complexity requirement and the imaginary `nums[-1] = nums[n] = -∞` neighbors. The `-∞` neighbors guarantee that a peak will always exist in any array, as the array must eventually "go down" towards these imaginary infinities. The `nums[i] != nums[i+1]` constraint simplifies things by preventing plateaus, ensuring clear ascents and descents.

## 💡 Core Idea
The `O(log n)` time complexity immediately suggests using a **Binary Search** approach. We can leverage the property that if an element is on an ascending slope, a peak *must* exist to its right, and if it's on a descending slope, a peak *must* exist to its left or at its current position.

## 🧠 Approach — Binary Search
This problem is a classic application of **Binary Search** on an array where we are not searching for a specific value, but rather for an element that satisfies a certain property (being a peak). The `O(log n)` time complexity constraint is the strongest hint for this pattern. Binary search works effectively here because the "imaginary -infinity neighbors" guarantee that at least one peak always exists. By comparing the middle element with its right neighbor, we can determine which half of the array *must* contain a peak, allowing us to discard half of the search space in each step.

## 📝 Step-by-Step Algorithm
1.  Initialize two pointers, `left` to `0` and `right` to `nums.size() - 1`. These pointers define the current search space.
2.  Enter a `while` loop that continues as long as `left < right`. This ensures there's at least a two-element range to consider.
3.  Inside the loop, calculate the middle index `mid` using the formula `left + (right - left) / 2` to prevent potential integer overflow.
4.  Compare the element at `nums[mid]` with its right neighbor `nums[mid + 1]`:
    *   **If `nums[mid] > nums[mid + 1]`**: This means we are either at a peak, or we are on a descending slope. In either case, a peak *must* exist within the range `[left, mid]`. The elements from `mid + 1` to `right` can be safely discarded because if there were a peak there, `nums[mid]` would have had to be smaller than `nums[mid+1]` at some point to reach it, which contradicts our current observation. So, we update `right = mid`.
    *   **If `nums[mid] < nums[mid + 1]`**: This means we are on an ascending slope. `nums[mid]` cannot be a peak because its right neighbor is greater. Due to the imaginary `nums[n] = -∞` at the end of the array, a peak *must* exist somewhere to the right of `mid`. Therefore, we update `left = mid + 1`, discarding `mid` and everything to its left.
5.  The loop terminates when `left` becomes equal to `right`. At this point, `left` (or `right`) will be the index of a peak element. Return `left`.

## 💻 Solution

```cpp
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        // Initialize two pointers, 'left' and 'right', to define the search space.
        // 'left' starts at the beginning of the array (index 0).
        // 'right' starts at the end of the array (last index).
        int left = 0;
        int right = nums.size() - 1;

        // The binary search loop continues as long as 'left' is less than 'right'.
        // When 'left' equals 'right', we have converged on a single element, which will be our peak.
        while (left < right) {
            // Calculate the middle index to avoid potential integer overflow.
            // This is equivalent to (left + right) / 2 but safer for large 'left' and 'right'.
            int mid = left + (right - left) / 2;
           
            // Compare the element at 'mid' with its right neighbor 'mid + 1'.
            // The problem guarantees nums[i] != nums[i+1], so no equality check is needed.
            if (nums[mid] > nums[mid + 1]) {
                // If nums[mid] is greater than nums[mid + 1], it means:
                // 1. 'mid' could be a peak itself (if nums[mid] > nums[mid-1]).
                // 2. We are on a descending slope, meaning a peak must exist to the left of or at 'mid'.
                //    (Because nums[-1] = -infinity, the array must eventually go up before coming down).
                // So, we can safely discard the right half (from mid + 1 to right) and search in [left, mid].
                // We set 'right = mid' because 'mid' itself could be the peak.
                right = mid;
            } else {
                // If nums[mid] < nums[mid + 1], it means we are on an ascending slope.
                // 'mid' cannot be a peak because its right neighbor is greater.
                // Since nums[n] = -infinity, a peak *must* exist somewhere to the right of 'mid'.
                // So, we discard 'mid' and everything to its left, and search in [mid + 1, right].
                // We set 'left = mid + 1' because 'mid' is definitely not the peak.
                left = mid + 1;
            }
        }
        
        // When the loop terminates, 'left' (which is now equal to 'right')
        // points to the index of a peak element.
        return left;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(log n) | Each iteration of the `while` loop reduces the search space by half, which is the characteristic behavior of binary search. |
| **Space** | O(1) | The algorithm uses a constant amount of extra space for a few variables (`left`, `right`, `mid`), regardless of the input array size. |

## 🔗 Related Problems
- 852. Peak Index in a Mountain Array
- 33. Search in Rotated Sorted Array
- 153. Find Minimum in Rotated Sorted Array