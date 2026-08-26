# 2965-find-missing-and-repeated-values

## 📋 Problem Description
You are given a 0-indexed 2D integer matrix `grid` of size `n * n`. The values within the grid are in the range `[1, n^2]`.
In a perfectly formed grid, each integer from `1` to `n^2` would appear exactly once. However, in the given `grid`, one number, let's call it `a`, appears twice, and another number, `b`, is completely missing.

Your task is to find these two numbers, `a` (the repeated number) and `b` (the missing number).

You must return a 0-indexed integer array `ans` of size 2, where `ans[0]` equals `a` (the repeated number) and `ans[1]` equals `b` (the missing number).

## 🔍 Examples
```
Input: grid = [[1,3],[2,2]]
Output: [2,4]
Explanation: The grid is 2x2, so expected numbers are 1, 2, 3, 4.
Number 2 appears twice, so 'a' is 2.
Number 4 is missing, so 'b' is 4.
```

```
Input: grid = [[9,1,7],[8,9,2],[3,4,6]]
Output: [9,5]
Explanation: The grid is 3x3, so expected numbers are 1 through 9.
Number 9 appears twice, so 'a' is 9.
Number 5 is missing, so 'b' is 5.
```

## 📌 Constraints
*   `2 <= n == grid.length == grid[i].length <= 50`
*   `1 <= grid[i][j] <= n * n`
*   For all `x` that `1 <= x <= n * n`, there is exactly one `x` that is not equal to any of the grid members (this is `b`).
*   For all `x` that `1 <= x <= n * n`, there is exactly one `x` that is equal to exactly two of the grid members (this is `a`).
*   For all `x` that `1 <= x <= n * n` except two of them, there is exactly one pair of `i, j` that `0 <= i, j <= n - 1` and `grid[i][j] == x`.

## 🤔 Understanding the Problem
The problem essentially asks us to identify two specific numbers in a sequence that should ideally contain all integers from `1` to `N` (where `N = n*n`). One number (`a`) has taken the place of another (`b`), meaning `a` appears twice and `b` is entirely absent. The core challenge is to efficiently find these two values given the constraints and the structure of the input. Since `n` is small (`<= 50`), `N` can be up to `50*50 = 2500`.

## 💡 Core Idea
The key insight is to leverage mathematical properties of sums and sums of squares. By comparing the actual sum and sum of squares of elements in the grid with the expected sum and sum of squares for a complete sequence from `1` to `N`, we can form a system of equations to solve for the repeated number `a` and the missing number `b`.

## 🧠 Approach — Mathematical Properties of Sums
This problem can be solved using a **Mathematical Approach** that utilizes the properties of arithmetic series. This pattern is particularly useful when dealing with arrays or sequences where elements are expected to be within a certain range, and there are missing or duplicate values. It fits this problem perfectly because we know the exact range of numbers (`1` to `n*n`) that *should* be present, allowing us to calculate expected sums and compare them with the actual sums from the given `grid`. This method avoids the need for extra data structures like hash sets or frequency arrays, making it space-efficient.

## 📝 Step-by-Step Algorithm

1.  **Determine `N`**: Calculate the total number of elements expected in a complete sequence, which is `N = n * n`.

2.  **Calculate Expected Sums**:
    *   Calculate the expected sum of all numbers from `1` to `N`. The formula for the sum of an arithmetic series is `S = N * (N + 1) / 2`.
    *   Calculate the expected sum of squares of all numbers from `1` to `N`. The formula for the sum of squares is `S2 = N * (N + 1) * (2 * N + 1) / 6`.

3.  **Calculate Actual Sums**:
    *   Initialize `actual_sum = 0` and `actual_sum_squares = 0`.
    *   Iterate through each element `val` in the `n x n` `grid`.
    *   Add `val` to `actual_sum`.
    *   Add `val * val` to `actual_sum_squares`.

4.  **Formulate Equations**:
    *   Let `a` be the repeated number and `b` be the missing number.
    *   The difference in sums: `actual_sum - S = (S - b + a) - S = a - b`. Let's call this `diff_ab`.
    *   The difference in sums of squares: `actual_sum_squares - S2 = (S2 - b^2 + a^2) - S2 = a^2 - b^2`.
    *   We know that `a^2 - b^2 = (a - b) * (a + b)`.
    *   Therefore, `actual_sum_squares - S2 = (a - b) * (a + b)`.
    *   If `a - b` is not zero (which it won't be, as `a` is repeated and `b` is missing, so `a != b`), we can find `a + b`: `a + b = (actual_sum_squares - S2) / (a - b)`. Let's call this `sum_ab`.

5.  **Solve for `a` and `b`**:
    *   We now have a system of two linear equations:
        1.  `a - b = diff_ab`
        2.  `a + b = sum_ab`
    *   Add the two equations: `(a - b) + (a + b) = diff_ab + sum_ab` => `2a = diff_ab + sum_ab` => `a = (diff_ab + sum_ab) / 2`.
    *   Subtract the first equation from the second: `(a + b) - (a - b) = sum_ab - diff_ab` => `2b = sum_ab - diff_ab` => `b = (sum_ab - diff_ab) / 2`.
    *   Alternatively, once `a` is found, `b = a - diff_ab`.

6.  **Return Result**: Return `a` and `b` in an array `[a, b]`. Ensure to use `long long` for sums to prevent overflow, as `N` can be up to 2500, and `N^2` can be `6.25 * 10^6`, so `sum_squares` can be very large.

## 💻 Solution
```cpp
class Solution {
public:
    vector<int> findMissingAndRepeatedValues(vector<vector<int>>& grid) {
        // Get the dimension of the grid (n x n)
        long long n = grid.size();
        // Calculate the total number of elements if the sequence were complete (1 to N)
        long long N = n * n;

        // Initialize variables to store the actual sum and sum of squares of elements in the grid
        long long actual_sum = 0;
        long long actual_sum_squares = 0;

        // Iterate through each element in the 2D grid
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                long long val = grid[i][j]; // Get the current value
                actual_sum += val;          // Add value to actual sum
                actual_sum_squares += val * val; // Add square of value to actual sum of squares
            }
        }

        // Calculate the expected sum of numbers from 1 to N
        // Formula: S = N * (N + 1) / 2
        long long expected_sum = (N * (N + 1)) / 2;
        // Calculate the expected sum of squares of numbers from 1 to N
        // Formula: S2 = N * (N + 1) * (2 * N + 1) / 6
        long long expected_sum_squares = (N * (N + 1) * (2 * N + 1)) / 6;

        // Let 'a' be the repeated number and 'b' be the missing number.
        // The actual sum is (expected_sum - b + a).
        // So, actual_sum - expected_sum = a - b.
        long long diff_ab = actual_sum - expected_sum; // This is (a - b)

        // The actual sum of squares is (expected_sum_squares - b^2 + a^2).
        // So, actual_sum_squares - expected_sum_squares = a^2 - b^2.
        // We know a^2 - b^2 = (a - b) * (a + b).
        // Therefore, (actual_sum_squares - expected_sum_squares) / (a - b) = a + b.
        long long sum_ab = (actual_sum_squares - expected_sum_squares) / diff_ab; // This is (a + b)

        // Now we have a system of two linear equations:
        // 1) a - b = diff_ab
        // 2) a + b = sum_ab

        // Add (1) and (2): (a - b) + (a + b) = diff_ab + sum_ab => 2a = diff_ab + sum_ab
        // So, a = (diff_ab + sum_ab) / 2
        long long repeated_num = (diff_ab + sum_ab) / 2; // This is 'a'

        // From equation (1): b = a - diff_ab
        long long missing_num = repeated_num - diff_ab; // This is 'b'

        // Return the repeated number 'a' and the missing number 'b' as integers.
        return {(int)repeated_num, (int)missing_num};
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(n^2) | We iterate through all `n*n` elements of the grid exactly once to calculate sums. All other operations are constant time. |
| **Space** | O(1) | We only use a few `long long` variables to store sums and intermediate results, regardless of the input size. |

## 🔗 Related Problems
*   645. Set Mismatch
*   268. Missing Number
*   287. Find the Duplicate Number