# 0532-k-diff-pairs-in-an-array

## 📋 Problem Description
Given an array of integers `nums` and an integer `k`, the task is to find the number of **unique** k-diff pairs in the array.

A **k-diff pair** is defined as an integer pair `(nums[i], nums[j])` that satisfies the following conditions:
1. `0 <= i, j < nums.length` (both indices are within the array bounds)
2. `i != j` (the two numbers must come from different positions in the array)
3. `|nums[i] - nums[j]| == k` (the absolute difference between the two numbers is exactly `k`)

The function should return the total count of such unique pairs. Note that `|val|` denotes the absolute value of `val`.

## 🔍 Examples
```
Input: nums = [3,1,4,1,5], k = 2
Output: 2
Explanation: The unique 2-diff pairs are (1, 3) and (3, 5).
             Even though there are two '1's in the input, we only count the pair (1, 3) once.

Input: nums = [1,2,3,4,5], k = 1
Output: 4
Explanation: The unique 1-diff pairs are (1, 2), (2, 3), (3, 4), and (4, 5).

Input: nums = [1,3,1,5,4], k = 0
Output: 1
Explanation: The unique 0-diff pair is (1, 1). This means we are looking for two identical numbers at different indices.
```

## 📌 Constraints
*   `1 <= nums.length <= 10^4`
*   `-10^7 <= nums[i] <= 10^7`
*   `0 <= k <= 10^7`

## 🤔 Understanding the Problem
The problem asks us to count pairs of numbers `(a, b)` from the input array `nums` such that their absolute difference `|a - b|` equals `k`. The crucial part is that we need to count **unique** pairs. This means if `(1, 3)` is a 2-diff pair, and the array contains multiple `1`s and `3`s, we still only count `(1, 3)` once. An important edge case is when `k = 0`, which implies we are looking for pairs of identical numbers `(x, x)` where `x` appears at least twice in the array. The condition `i != j` ensures we can't form a pair with a number and itself at the same index.

## 💡 Core Idea
The core idea is to first sort the array. Once sorted, we can efficiently find pairs using a two-pointer approach, as the relative order of numbers is preserved, making it easier to adjust our search based on the current difference. Sorting also simplifies handling duplicate numbers to ensure we count only unique pairs.

## 🧠 Approach — Two Pointers
This problem can be efficiently solved using the **Two Pointers** pattern after sorting the input array.
The Two Pointers pattern is suitable here because once the array is sorted, if `nums[j] - nums[i]` is too small, we know we need a larger `nums[j]`, so we can increment `j`. If the difference is too large, we need a larger `nums[i]` (or a smaller `nums[j]`, but `j` can only increase to maintain `j > i`), so we can increment `i`. This systematic movement allows us to check all potential pairs in a single pass after sorting, ensuring `O(N)` traversal time.

## 📝 Step-by-Step Algorithm
1.  **Handle Edge Case for `k`**: If `k` is negative, no absolute difference can be negative, so return `0`.
2.  **Sort the Array**: Sort the input array `nums` in non-decreasing order. This is crucial for the two-pointer approach to work correctly and to easily handle duplicates.
3.  **Initialize Pointers and Counter**:
    *   Initialize `ans = 0` to store the count of unique k-diff pairs.
    *   Initialize `i = 0` (left pointer) and `j = 1` (right pointer). `j` starts at `1` to ensure `i != j` initially.
4.  **Two-Pointer Traversal**: Iterate while both `i` and `j` are within the array bounds (`i < n` and `j < n`, where `n` is the array size).
    *   **Handle `i == j`**: If `i` and `j` point to the same index (this can happen if `i` advances past `j`), increment `j` to ensure `i != j` and continue to the next iteration.
    *   **Calculate Difference**: Calculate `diff = nums[j] - nums[i]`. Since the array is sorted and `j > i` (or `j` will be incremented until `j > i`), `diff` will always be non-negative, effectively handling `|nums[i] - nums[j]|`.
    *   **Compare `diff` with `k`**:
        *   If `diff < k`: The difference is too small. We need a larger second number. Increment `j` to move to the next potential `nums[j]`.
        *   If `diff > k`: The difference is too large. We need a larger first number. Increment `i` to move to the next potential `nums[i]`.
        *   If `diff == k`: A valid k-diff pair `(nums[i], nums[j])` is found.
            *   Increment `ans`.
            *   **Skip Duplicates**: To ensure we count only *unique* pairs, advance `i` past all occurrences of `nums[i]` (the current `a` value) and `j` past all occurrences of `nums[j]` (the current `b` value). This prevents counting `(1,3)` multiple times if the array contains `[1,1,3,3]`.
5.  **Return Result**: After the loop finishes, `ans` will hold the total count of unique k-diff pairs. Return `ans`.

## 💻 Solution
```cpp
class Solution {
public:
    int findPairs(vector<int>& nums, int k) {
        // If k is negative, it's impossible to have an absolute difference equal to k.
        // Absolute differences are always non-negative.
        if (k < 0) return 0;

        // Sort the array. This is crucial for the two-pointer approach
        // and simplifies handling unique pairs.
        sort(nums.begin(), nums.end());

        int n = nums.size();
        // Initialize two pointers: 'i' for the first element of the pair,
        // 'j' for the second element.
        // 'j' starts at 1 to ensure i != j initially.
        int i = 0, j = 1;
        int ans = 0; // Counter for unique k-diff pairs

        // Iterate while both pointers are within the array bounds.
        while (i < n && j < n) {
            // Ensure i and j point to different indices.
            // If i catches up to j (e.g., if i was incremented past j),
            // increment j to maintain j > i.
            if (i == j) {
                j++;
                continue; // Skip to the next iteration
            }

            // Calculate the difference between the elements pointed by j and i.
            // Since the array is sorted, nums[j] >= nums[i] (assuming j > i),
            // so nums[j] - nums[i] directly gives the absolute difference.
            int diff = nums[j] - nums[i];

            // Case 1: Difference is less than k.
            // We need a larger difference. Since nums is sorted,
            // incrementing j will potentially increase nums[j] and thus the difference.
            if (diff < k) {
                j++;
            }
            // Case 2: Difference is greater than k.
            // We need a smaller difference. Incrementing i will potentially
            // increase nums[i], thus reducing the difference (nums[j] - nums[i]).
            else if (diff > k) {
                i++;
            }
            // Case 3: Difference is exactly k. A valid pair is found.
            else {
                ans++; // Increment the count of unique pairs.

                // Store the current values to skip duplicates.
                // We need to advance both pointers past any duplicate values
                // to ensure that each unique pair (a, b) is counted only once,
                // regardless of how many times 'a' or 'b' appear in the input array.
                int a = nums[i];
                int b = nums[j];

                // Advance pointer i past all occurrences of 'a'.
                while (i < n && nums[i] == a) i++;
                // Advance pointer j past all occurrences of 'b'.
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
| **Time** | O(N log N) | Dominated by sorting the array (O(N log N)). The two-pointer traversal takes O(N) time as each pointer traverses the array at most once. |
| **Space** | O(1) | If the sorting algorithm used is in-place (like `std::sort` for `std::vector`), the auxiliary space complexity is O(1). Some sorting algorithms might use O(log N) space for recursion stack. |

## 🔗 Related Problems
- 167. Two Sum II - Input Array Is Sorted
- 15. 3Sum
- 26. Remove Duplicates from Sorted Array