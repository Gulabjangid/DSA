# 0240-search-a-2d-matrix-ii

## 📋 Problem Description
You are given an `m x n` integer matrix. Your task is to write an efficient algorithm to determine if a given `target` integer exists within this matrix.

The matrix has two special properties:
1.  Integers in each row are sorted in ascending order from left to right.
2.  Integers in each column are sorted in ascending order from top to bottom.

The function should receive the `matrix` (a `vector` of `vector`s of integers) and the `target` integer, and it must return `true` if the `target` is found in the matrix, otherwise `false`.

## 🔍 Examples
```
Input: matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 5
Output: true
Explanation: The number 5 is present in the matrix at matrix[1][1].
```

```
Input: matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 20
Output: false
Explanation: The number 20 is not present in the matrix.
```

```
Input: matrix = [[-5]], target = -5
Output: true
```

## 📌 Constraints
*   `m == matrix.length` (number of rows)
*   `n == matrix[i].length` (number of columns)
*   `1 <= n, m <= 300`
*   `-10^9 <= matrix[i][j] <= 10^9`
*   All integers in each row are sorted in ascending order.
*   All integers in each column are sorted in ascending order.
*   `-10^9 <= target <= 10^9`

## 🤔 Understanding the Problem
The problem asks us to find a `target` value in a 2D matrix that has a unique sorting property: both its rows and columns are sorted. This is not a standard sorted matrix where the first element of each row is greater than the last element of the previous row (like in problem 74). Here, an element might be smaller than elements above it in a different column, but larger than elements to its left in the same row. A naive approach of iterating through all elements would be O(m*n), and performing binary search on each row would be O(m log n). The challenge is to leverage the combined row and column sorting for a more efficient solution.

## 💡 Core Idea
The key insight is to start the search from a corner where we can consistently eliminate either a row or a column based on the comparison with the `target`. The top-right or bottom-left corners are ideal for this "elimination" strategy.

## 🧠 Approach — Staircase Search (or Zig-zag Search)
This problem can be efficiently solved using a "Staircase Search" or "Zig-zag Search" pattern. This pattern is suitable because the sorted nature of both rows and columns allows us to make informed decisions about where to move next in the matrix. By starting at a specific corner (e.g., top-right or bottom-left), comparing the current element with the `target` allows us to eliminate an entire row or an entire column from the search space in each step, significantly reducing the search area.

## 📝 Step-by-Step Algorithm
1.  **Handle Edge Cases**: First, check if the matrix is empty or if its first row is empty. If so, the `target` cannot be found, so return `false`.
2.  **Initialize Pointers**: Get the number of rows (`m`) and columns (`n`). Initialize two pointers: `row` to `0` (start at the first row) and `col` to `n - 1` (start at the last column). This places our starting point at the top-right corner of the matrix.
3.  **Iterate and Search**: Enter a `while` loop that continues as long as `row` is within the matrix bounds (`row < m`) and `col` is within the matrix bounds (`col >= 0`).
    *   **Found Target**: Inside the loop, compare the element at `matrix[row][col]` with the `target`. If `matrix[row][col]` is equal to `target`, we have found it, so return `true`.
    *   **Current Element Too Large**: If `matrix[row][col]` is greater than `target`: Since the current row is sorted in ascending order, all elements to the right of `matrix[row][col]` would also be greater than `target`. Therefore, we must move left to find a smaller value. Decrement `col` by 1.
    *   **Current Element Too Small**: If `matrix[row][col]` is less than `target`: Since the current column is sorted in ascending order, all elements above `matrix[row][col]` would also be smaller than `target`. Therefore, we must move down to find a larger value. Increment `row` by 1.
4.  **Target Not Found**: If the loop finishes without returning `true`, it means the `target` was not found in the matrix. Return `false`.

## 💻 Solution
```cpp
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& mat, int tar) {
        // Handle edge case: if the matrix is empty or has empty rows, target cannot be found.
        if (mat.empty() || mat[0].empty())
            return false; 

        // Get the dimensions of the matrix.
        int row_count = mat.size();    // Number of rows
        int col_count = mat[0].size(); // Number of columns

        // Initialize pointers for our search.
        // We start from the top-right corner of the matrix.
        // 'r' for current row index, 'c' for current column index.
        int r = 0;             // Start at the first row (index 0)
        int c = col_count - 1; // Start at the last column (index col_count - 1)

        // Continue searching as long as our pointers are within the matrix boundaries.
        // 'r' must be less than total rows, 'c' must be non-negative.
        while (r < row_count && c >= 0) {
            // Get the current element being examined.
            int current_val = mat[r][c];

            // Case 1: Target found!
            if (current_val == tar) {
                return true;
            } 
            // Case 2: Current element is greater than the target.
            // Since the row is sorted ascendingly from left to right,
            // all elements to the right of 'current_val' in this row are even larger.
            // Also, since the column is sorted ascendingly from top to bottom,
            // all elements below 'current_val' in this column are larger.
            // To find a smaller value (our target), we must move left in the current row.
            else if (current_val > tar) {
                c--; // Move to the previous column
            } 
            // Case 3: Current element is less than the target.
            // Since the column is sorted ascendingly from top to bottom,
            // all elements above 'current_val' in this column are smaller.
            // Also, since the row is sorted ascendingly from left to right,
            // all elements to the left of 'current_val' in this row are smaller.
            // To find a larger value (our target), we must move down in the current column.
            else { // current_val < tar
                r++; // Move to the next row
            }
        }

        // If the loop finishes, it means the target was not found in the matrix.
        return false;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(m + n) | In the worst case, the search path starts at one corner and moves diagonally across the matrix, eliminating one row or one column in each step. The total number of steps is at most `m + n`. |
| **Space** | O(1) | The algorithm uses only a few constant extra variables for pointers and dimensions, regardless of the matrix size. |

## 🔗 Related Problems
- 74. Search a 2D Matrix
- 378. Kth Smallest Element in a Sorted Matrix
- 1351. Count Negative Numbers in a Sorted Matrix