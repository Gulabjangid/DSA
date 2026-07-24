# 0532-k-diff-pairs-in-an-array

## 📋 Problem Description
Given an array of integers `nums` and an integer `k`, the task is to find the number of **unique** k-diff pairs in the array.

A **k-diff pair** is defined as an integer pair `(nums[i], nums[j])` that satisfies the following conditions:
1. `0 <= i, j < nums.length` (both indices are valid within the array)
2. `i != j` (the two elements must come from different positions in the array)
3. `|nums[i] - nums[j]| == k` (the absolute difference between the two elements is exactly `k`)

The function should return the count of such unique pairs. Note that `|val|` denotes the absolute value of `val`.

## 🔍 Examples
```
Input: nums = [3,1,4,1,5], k = 2
Output: 2
Explanation: There are two 2-diff pairs: (1, 3) and (3, 5).
             Even though '1' appears twice, we only count unique pairs of values.

Input: nums = [1,2,3,4,5], k = 1
Output: 4
Explanation: There are four 1-diff pairs: (1, 2), (2, 3), (3, 4), and (4, 5).

Input: nums = [1,3,1,5,4], k = 0
Output: 1
Explanation: There is one 0-diff pair: (1, 1). This means we need two instances of the same number in the array.
```

## 📌 Constraints
*   `1 <= nums.length <= 10^4`
*   `-10^7 <= nums[i] <= 10^7`
*   `0 <= k <= 10^7`

## 🤔 Understanding the Problem
The problem asks us to count pairs of numbers `(a, b)` from the input array `nums` such that `|a - b| = k`. A crucial detail is that we need to count **unique** pairs. This means if `(1, 3)` is a valid pair, and `1` appears multiple times, we still only count `(1, 3)` once. Also, `i != j` implies that if `k=0`, we need to find pairs of identical numbers that appear at *different indices*. This means for `k=0`, a number must appear at least twice in the array to form a `0-diff` pair with itself.

## 💡 Core Idea
The core idea is to first sort the array. Once sorted, we can efficiently find pairs with a specific difference using a two-pointer approach, while also easily handling the uniqueness requirement by skipping duplicate elements.

## 🧠 Approach — Two Pointers
This problem can be efficiently solved using the **Two Pointers** pattern. This pattern is particularly well-suited when dealing with sorted arrays where we need to find pairs or triplets that satisfy a certain condition (like a specific sum or difference). By sorting the array, we establish an order that allows us to move two pointers (one from the beginning, one from further ahead) in a controlled manner. If the difference between the elements pointed to is too small, we increment the right pointer to increase the difference. If it's too large, we increment the left pointer to decrease the difference. When a valid pair is found, we increment our count and then advance both pointers, carefully skipping any duplicate values to ensure we only count unique pairs.

## 📝 Step-by-Step Algorithm
1.  **Handle Edge Case for `k`**: If `k` is negative, no absolute difference can be negative, so return `0`.
2.  **Sort the Array**: Sort the input array `nums` in non-decreasing order. This is essential for the two-pointer approach to work correctly.
3.  **Initialize Pointers and Counter**:
    *   Initialize `i` (left pointer) to `0`.
    *   Initialize `j` (right pointer) to `1`.
    *   Initialize `ans` (count of unique k-diff pairs) to `0`.
4.  **Iterate with Two Pointers**: Use a `while` loop that continues as long as both `i` and `j` are within the array bounds (`i < n` and `j < n`, where `n` is the array size).
5.  **Handle `i == j`**: If `i` and `j` point to the same index, increment `j` to ensure `i != j` and continue to the next iteration. This prevents considering an element paired with itself unless `k=0` and there are duplicates.
6.  **Calculate Difference**: Calculate `diff = nums[j] - nums[i]`.
7.  **Adjust Pointers Based on Difference**:
    *   If `diff < k`: The difference is too small. To increase the difference, increment `j` (move the right pointer to a larger number).
    *   If `diff > k`: The difference is too large. To decrease the difference, increment `i` (move the left pointer to a larger number).
    *   If `diff == k`: A valid k-diff pair `(nums[i], nums[j])` has been found.
        *   Increment `ans`.
        *   **Skip Duplicates**: To ensure unique pairs, advance `i` past all occurrences of `nums[i]` and advance `j` past all occurrences of `nums[j]`. This prevents counting `(1, 3)` multiple times if `1` or `3` appear more than once.
8.  **Return Result**: After the loop finishes, `ans` will hold the total count of unique k-diff pairs. Return `ans`.

## 💻 Solution
```cpp
class Solution {
public:
    int findPairs(vector<int>& nums, int k) {
        // If k is negative, an absolute difference cannot be negative.
        // So, no pairs can satisfy the condition.
        if (k < 0) return 0;

        // Sort the array. This is crucial for the two-pointer approach
        // and for efficiently handling duplicates.
        sort(nums.begin(), nums.end());

        int n = nums.size();
        // Initialize two pointers: 'i' for the left element, 'j' for the right element.
        // 'j' starts at 1 to ensure i != j initially.
        int i = 0, j = 1;
        int ans = 0; // Counter for unique k-diff pairs

        // Iterate while both pointers are within the array bounds.
        while (i < n && j < n) {
            // Ensure i and j always point to different elements.
            // If j catches up to i (e.g., after i increments), move j forward.
            if (i == j) {
                j++;
                continue;
            }

            // Calculate the difference between the elements pointed by j and i.
            // Since the array is sorted, nums[j] >= nums[i], so nums[j] - nums[i]
            // is equivalent to |nums[j] - nums[i]|.
            int diff = nums[j] - nums[i];

            // If the difference is less than k, we need a larger difference.
            // Move the right pointer 'j' forward to potentially find a larger number.
            if (diff < k) {
                j++;
            }
            // If the difference is greater than k, we need a smaller difference.
            // Move the left pointer 'i' forward to potentially find a larger number,
            // which would reduce the difference with nums[j].
            else if (diff > k) {
                i++;
            }
            // If the difference is exactly k, we found a valid pair.
            else {
                ans++; // Increment the count of unique pairs.

                // Store the current values to skip duplicates.
                // We need to advance 'i' past all occurrences of nums[i]
                // and 'j' past all occurrences of nums[j] to ensure
                // we only count this unique pair (nums[i], nums[j]) once.
                int a = nums[i];
                int b = nums[j];

                // Skip all elements equal to 'a' from the left pointer.
                while (i < n && nums[i] == a) i++;
                // Skip all elements equal to 'b' from the right pointer.
                while (j < n && nums[j] == b) j++;
            }
        }

        return ans; // Return the total count of unique k-diff pairs.
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N log N) | Dominated by the initial sorting of the `nums` array. The two-pointer traversal takes O(N) time as each pointer moves linearly through the array at most once. |
| **Space** | O(1) | The space complexity is O(1) if the sorting algorithm used is in-place (like `std::sort` for `std::vector` in C++). No additional data structures are used that grow with input size. |

## 🔗 Related Problems
-   15. 3Sum
-   167. Two Sum II - Input Array Is Sorted
-   26. Remove Duplicates from Sorted Array