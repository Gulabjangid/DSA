# 0532-k-diff-pairs-in-an-array

## 📋 Problem Description
Given an array of integers `nums` and an integer `k`, the task is to return the number of **unique** k-diff pairs in the array.

A **k-diff** pair is defined as an integer pair `(nums[i], nums[j])` that satisfies the following conditions:
1. `0 <= i, j < nums.length` (both indices are valid within the array)
2. `i != j` (the two elements must come from different positions in the array)
3. `|nums[i] - nums[j]| == k` (the absolute difference between the two elements is exactly `k`)

The problem emphasizes finding the count of **unique** pairs. This means if, for example, `(1, 3)` is a 2-diff pair, and the array contains multiple `1`s or `3`s that could form the same pair, it should only be counted once.

The function receives a `vector<int> nums` and an `int k` and must return an `int` representing the count of unique k-diff pairs.

## 🔍 Examples
```
Input: nums = [3,1,4,1,5], k = 2
Output: 2
Explanation: There are two 2-diff pairs: (1, 3) and (3, 5).
             Even though '1' appears twice, the pair (1, 3) is counted only once.

Input: nums = [1,2,3,4,5], k = 1
Output: 4
Explanation: There are four 1-diff pairs: (1, 2), (2, 3), (3, 4), and (4, 5).

Input: nums = [1,3,1,5,4], k = 0
Output: 1
Explanation: There is one 0-diff pair: (1, 1). This occurs because there are two '1's in the array at different indices.
```

## 📌 Constraints
*   `1 <= nums.length <= 10^4`
*   `-10^7 <= nums[i] <= 10^7`
*   `0 <= k <= 10^7`

## 🤔 Understanding the Problem
The problem asks us to find pairs of numbers `(a, b)` from the input array `nums` such that their absolute difference `|a - b|` equals `k`. The key challenge is ensuring that we count only **unique** pairs. This means if `(1, 3)` is a valid pair, and the array contains multiple `1`s and `3`s, we still count `(1, 3)` just once. Also, the two numbers forming a pair must come from different indices (`i != j`), which is particularly relevant when `k = 0` (we're looking for `(x, x)` pairs, meaning there must be at least two occurrences of `x` in the array). An edge case is `k < 0`, which by definition cannot form a valid absolute difference.

## 💡 Core Idea
The core idea is to first sort the array. Once sorted, we can efficiently find pairs using a two-pointer approach, which allows us to control the difference `nums[j] - nums[i]` and easily skip duplicate elements to ensure unique pairs are counted.

## 🧠 Approach — Two Pointers
This problem can be efficiently solved using the **Two Pointers** pattern after sorting the input array. This pattern is suitable because once the array is sorted, we can maintain two pointers, `i` and `j`, and move them in a coordinated fashion to find elements that satisfy a certain condition (in this case, `nums[j] - nums[i] == k`). Sorting allows us to monotonically increase or decrease the difference by moving `i` or `j`, and also simplifies the process of skipping duplicate elements to count only unique pairs.

## 📝 Step-by-Step Algorithm

1.  **Handle Edge Case for `k`**: If `k` is negative, it's impossible to have an absolute difference equal to `k`. In this case, return `0`.
2.  **Sort the Array**: Sort the input array `nums` in non-decreasing order. This is crucial for the two-pointer approach to work efficiently and to handle duplicates easily.
3.  **Initialize Pointers and Counter**:
    *   Initialize a counter `ans = 0` to store the number of unique k-diff pairs.
    *   Initialize two pointers, `i = 0` and `j = 1`. Pointer `i` will represent the first element of a potential pair, and `j` will represent the second. `j` starts at `1` to ensure `i != j` initially.
4.  **Iterate with Two Pointers**: Use a `while` loop that continues as long as both `i` and `j` are within the array bounds (`i < n` and `j < n`, where `n` is the array size).
5.  **Handle `i == j`**: If `i` and `j` ever point to the same index (this can happen if `i` advances past `j` while skipping duplicates), increment `j` to ensure `i != j` and continue to the next iteration.
6.  **Calculate Difference**: Calculate the difference `diff = nums[j] - nums[i]`.
7.  **Compare Difference with `k`**:
    *   **If `diff < k`**: The difference is too small. To increase the difference, we need a larger `nums[j]`. So, increment `j`.
    *   **If `diff > k`**: The difference is too large. To decrease the difference, we need a larger `nums[i]` (which makes `nums[j] - nums[i]` smaller) or a smaller `nums[j]` (which is not possible since `j` only moves forward). So, increment `i`.
    *   **If `diff == k`**: A k-diff pair `(nums[i], nums[j])` is found.
        *   Increment `ans`.
        *   **Skip Duplicates**: To ensure we count only unique pairs, we must advance both `i` and `j` past any duplicate values.
            *   Store `nums[i]` in a temporary variable (e.g., `a`). Then, increment `i` as long as `i` is within bounds and `nums[i]` is equal to `a`.
            *   Store `nums[j]` in a temporary variable (e.g., `b`). Then, increment `j` as long as `j` is within bounds and `nums[j]` is equal to `b`.
8.  **Return Result**: After the loop finishes, `ans` will hold the total count of unique k-diff pairs. Return `ans`.

## 💻 Solution
```cpp
class Solution {
public:
    int findPairs(vector<int>& nums, int k) {
        // Edge case: If k is negative, it's impossible to have an absolute difference equal to k.
        // Return 0 unique pairs.
        if (k < 0) return 0;

        // Step 1: Sort the array. This is crucial for the two-pointer approach
        // and for efficiently handling duplicates.
        sort(nums.begin(), nums.end());

        int n = nums.size();
        // Initialize two pointers: 'i' for the first element of a potential pair,
        // and 'j' for the second. 'j' starts ahead of 'i' to ensure i != j initially.
        int i = 0, j = 1;
        // Initialize the counter for unique k-diff pairs.
        int ans = 0;

        // Step 2: Iterate using the two-pointer approach.
        // Continue as long as both pointers are within array bounds.
        while (i < n && j < n) {
            // Ensure i and j point to different elements.
            // If j catches up to i (e.g., after i increments past a duplicate),
            // advance j to maintain i < j.
            if (i == j) {
                j++;
                continue; // Restart loop iteration with updated j
            }

            // Calculate the difference between the elements pointed by j and i.
            // Since the array is sorted, nums[j] >= nums[i].
            int diff = nums[j] - nums[i];

            // Case 1: Difference is less than k.
            // To increase the difference, we need a larger second element.
            // So, move pointer j forward.
            if (diff < k) {
                j++;
            }
            // Case 2: Difference is greater than k.
            // To decrease the difference, we need a larger first element (or smaller second,
            // but j only moves forward). So, move pointer i forward.
            else if (diff > k) {
                i++;
            }
            // Case 3: Difference is exactly k. We found a k-diff pair!
            else {
                ans++; // Increment the count of unique pairs.

                // To ensure we count only unique pairs (e.g., (1,3) once even if multiple 1s or 3s exist),
                // we must skip all duplicate values for both nums[i] and nums[j].
                int a = nums[i]; // Store current nums[i]
                int b = nums[j]; // Store current nums[j]

                // Advance i past all occurrences of 'a' (nums[i]).
                while (i < n && nums[i] == a) {
                    i++;
                }
                // Advance j past all occurrences of 'b' (nums[j]).
                while (j < n && nums[j] == b) {
                    j++;
                }
            }
        }

        // Return the total count of unique k-diff pairs.
        return ans;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N log N) | Dominated by sorting the array. The two-pointer traversal takes O(N) time as each pointer moves forward at most N times. |
| **Space** | O(1) | Uses constant extra space for pointers and variables. (Note: `std::sort` might use O(log N) or O(N) space depending on implementation, but typically O(1) auxiliary space is considered for in-place sorts). |

## 🔗 Related Problems
-   167. Two Sum II - Input Array Is Sorted
-   15. 3Sum
-   26. Remove Duplicates from Sorted Array