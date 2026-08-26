# 2965-find-missing-and-repeated-values

## 📋 Problem Description
You are given an `n x n` 2D integer matrix `grid`. The `grid` contains `n*n` integers, all of which are within the range `[1, n*n]`. In this grid, exactly one number, let's call it `a`, appears twice, and exactly one number, let's call it `b`, is missing from the range `[1, n*n]`. All other numbers in the range `[1, n*n]` appear exactly once. Your task is to find these two numbers, `a` (the repeated one) and `b` (the missing one).

Return a 0-indexed integer array `ans` of size 2, where `ans[0]` is `a` and `ans[1]` is `b`.

## 🔍 Examples
```
Input: grid = [[1,3],[2,2]]
Output: [2,4]
Explanation: Number 2 is repeated and number 4 is missing so the answer is [2,4].
```

```
Input: grid = [[9,1,7],[8,9,2],[3,4,6]]
Output: [9,5]
Explanation: Number 9 is repeated and number 5 is missing so the answer is [9,5].
```

## 📌 Constraints
*   `2 <= n == grid.length == grid[i].length <= 50`
*   `1 <= grid[i][j] <= n * n`

## 🤔 Understanding the Problem
The problem asks us to identify two specific numbers within an `n x n` grid. The grid should ideally contain all numbers from `1` to `n*n` exactly once. However, it deviates from this ideal state in two ways: one number (`a`) is duplicated, and consequently, one number (`b`) from the expected range `[1, n*n]` is entirely absent. The challenge is to find these `a` and `b` efficiently. The fact that numbers are from a specific consecutive range `[1, n*n]` is a crucial hint.

## 💡 Core Idea
The core idea is to leverage mathematical properties of sums and sums of squares. By comparing the actual sum and sum of squares of all numbers in the grid with the expected sum and sum of squares for a complete sequence from `1` to `N` (where `N = n*n`), we can form a system of two linear equations that allows us to solve for the repeated number (`a`) and the missing number (`b`).

## 🧠 Approach — Mathematical Properties / Summation Formulas
This problem can be solved very efficiently by utilizing mathematical properties, specifically the sum of an arithmetic series and the sum of squares of an arithmetic series. This approach is powerful because it allows us to deduce the missing and repeated numbers without needing extra space for frequency counts or modifying the input array. Since we know the exact range of numbers `[1, N]` that *should* be present, any deviation in the total sum or sum of squares must be directly attributable to the repeated and missing elements.

## 📝 Step-by-Step Algorithm
1.  Determine the size of the grid, `n`.
2.  Calculate `N = n * n`, which represents the total count of elements in the grid and also the upper bound of the expected number range `[1, N]`.
3.  Initialize two `long long` variables: `actual_sum` and `actual_sum_squares` to 0. These will accumulate the sum and sum of squares of all numbers found in the `grid`.
4.  Iterate through each element `val` in the `n x n` grid:
    *   Add `val` to `actual_sum`.
    *   Add `val * val` to `actual_sum_squares`.
5.  Calculate the `expected_sum` for a complete sequence of numbers from 1 to `N` using the formula for the sum of the first `N` natural numbers: `S = N * (N + 1) / 2`.
6.  Calculate the `expected_sum_squares` for a complete sequence of numbers from 1 to `N` using the formula for the sum of squares of the first `N` natural numbers: `S2 = N * (N + 1) * (2 * N + 1) / 6`.
7.  Let `a` be the repeated number and `b` be the missing number.
    *   The difference in sums: `diff_sum = actual_sum - expected_sum`. This difference is equivalent to `(a - b)`, because the `expected_sum` has `b` but not `a`, while `actual_sum` has `a` but not `b` (it has `a` twice and `b` is missing). So, `actual_sum = expected_sum - b + a`.
    *   The difference in sums of squares: `diff_sum_squares = actual_sum_squares - expected_sum_squares`. Similarly, this difference is equivalent to `(a^2 - b^2)`. So, `actual_sum_squares = expected_sum_squares - b^2 + a^2`.
8.  We now have two equations:
    *   `a - b = diff_sum`
    *   `a^2 - b^2 = diff_sum_squares`
9.  Factor the second equation: `(a - b)(a + b) = diff_sum_squares`.
10. Substitute `(a - b)` from the first equation into the factored second equation: `(diff_sum)(a + b) = diff_sum_squares`.
11. Solve for `a + b`: `sum_ab = diff_sum_squares / diff_sum`. (Note: `diff_sum` will not be zero because `a` and `b` are distinct).
12. Now we have a simple system of two linear equations:
    *   `a - b = diff_sum`
    *   `a + b = sum_ab`
13. Add these two equations together: `(a - b) + (a + b) = diff_sum + sum_ab`, which simplifies to `2a = diff_sum + sum_ab`.
14. Solve for `a`: `a = (diff_sum + sum_ab) / 2`. This is the repeated number.
15. Solve for `b` using the first equation: `b = a - diff_sum`. This is the missing number.
16. Return `[a, b]` as the result.

## 💻 Solution
```cpp
class Solution {
public:
    vector<int> findMissingAndRepeatedValues(vector<vector<int>>& grid) {
        // Get the dimension of the grid (n x n).
        long long n = grid.size();
        // Calculate N, the total number of elements in the grid,
        // which is also the upper bound of the expected range [1, N].
        long long N = n * n;

        // Initialize variables to store the sum and sum of squares
        // of the numbers actually present in the grid.
        long long actual_sum = 0;
        long long actual_sum_squares = 0;

        // Iterate through each element in the 2D grid.
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                long long val = grid[i][j];
                // Add the current value to the actual_sum.
                actual_sum += val;
                // Add the square of the current value to the actual_sum_squares.
                actual_sum_squares += val * val;
            }
        }

        // Calculate the expected sum of numbers from 1 to N.
        // Formula: S = N * (N + 1) / 2
        long long expected_sum = (N * (N + 1)) / 2;
        // Calculate the expected sum of squares of numbers from 1 to N.
        // Formula: S2 = N * (N + 1) * (2 * N + 1) / 6
        long long expected_sum_squares = (N * (N + 1) * (2 * N + 1)) / 6;

        // Let 'a' be the repeated number and 'b' be the missing number.
        // The actual_sum contains 'a' twice and is missing 'b'.
        // So, actual_sum = (expected_sum - b + a).
        // Rearranging, actual_sum - expected_sum = a - b.
        long long diff_a_minus_b = actual_sum - expected_sum; // This is (a - b)

        // Similarly, for sums of squares:
        // actual_sum_squares = (expected_sum_squares - b^2 + a^2).
        // Rearranging, actual_sum_squares - expected_sum_squares = a^2 - b^2.
        long long diff_a2_minus_b2 = actual_sum_squares - expected_sum_squares; // This is (a^2 - b^2)

        // We know a^2 - b^2 = (a - b) * (a + b).
        // So, diff_a2_minus_b2 = diff_a_minus_b * (a + b).
        // Therefore, (a + b) = diff_a2_minus_b2 / diff_a_minus_b.
        long long sum_a_plus_b = diff_a2_minus_b2 / diff_a_minus_b; // This is (a + b)

        // Now we have a system of two linear equations:
        // 1) a - b = diff_a_minus_b
        // 2) a + b = sum_a_plus_b

        // Add the two equations:
        // (a - b) + (a + b) = diff_a_minus_b + sum_a_plus_b
        // 2a = diff_a_minus_b + sum_a_plus_b
        // a = (diff_a_minus_b + sum_a_plus_b) / 2
        long long repeated_val = (diff_a_minus_b + sum_a_plus_b) / 2; // This is 'a'

        // Substitute 'a' back into the first equation (a - b = diff_a_minus_b):
        // b = a - diff_a_minus_b
        long long missing_val = repeated_val - diff_a_minus_b; // This is 'b'

        // Return the repeated and missing values as an integer vector.
        return {(int)repeated_val, (int)missing_val};
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N^2) | We iterate through all `n*n` elements of the grid exactly once to calculate sums. The subsequent mathematical calculations are constant time operations. |
| **Space** | O(1) | We only use a fixed number of variables to store sums and intermediate results, regardless of the input grid size. No auxiliary data structures are allocated. |

## 🔗 Related Problems
- 268. Missing Number
- 645. Set Mismatch
- 448. Find All Numbers Disappeared in an Array