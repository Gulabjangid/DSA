# 0240-search-a-2d-matrix-ii

## 📋 Problem Description
You are given an `m x n` integer matrix. Your task is to write an efficient algorithm that determines if a given `target` value exists within this matrix.

The matrix has two important properties:
1.  Integers in each row are sorted in ascending order from left to right.
2.  Integers in each column are sorted in ascending order from top to bottom.

The function should receive the `matrix` (a 2D vector of integers) and the `target` integer. It must return `true` if the `target` is found in the matrix, and `false` otherwise.

## 🔍 Examples
```
Input: matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 5
Output: true
Explanation: The value 5 is present in the matrix at matrix[1][1].
```

```
Input: matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 20
Output: false
Explanation: The value 20 is not present in the matrix.
```

```
Input: matrix = [[-5]], target = -5
Output: true
Explanation: The value -5 is present in the matrix at matrix[0][0].
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
The problem asks us to find a `target` value in a 2D matrix with a specific sorting property: both rows and columns are sorted. This is not a standard sorted matrix where the first element of each row is greater than the last element of the previous row (like in LeetCode 74). Here, the sorting is independent for rows and columns, which means a simple binary search on the flattened matrix or a binary search on rows followed by binary search on columns won't work directly. The challenge is to leverage *both* sorting properties simultaneously to find the target efficiently, avoiding a brute-force O(m*n) scan.

## 💡 Core Idea
The key insight is to start the search from a corner where we can make a definitive decision about eliminating a row or a column based on comparing the current element with the target. The top-right or bottom-left corners are ideal for this.

## 🧠 Approach — Staircase Search (or Zigzag Search)
This problem can be efficiently solved using a "Staircase Search" or "Zigzag Search" pattern. This pattern is particularly well-suited for matrices where both rows and columns are sorted. The reason it fits is that by starting at a specific corner (e.g., top-right), comparing the current element with the target allows us to eliminate an entire row or an entire column from the search space in each step, significantly reducing the search area.

## 📝 Step-by-Step Algorithm
1.  **Handle Edge Cases**: First, check if the matrix is empty or if its first row is empty. If so, the target cannot be found, so return `false`.
2.  **Initialize Pointers**: Get the number of rows (`m`) and columns (`n`). Initialize two pointers:
    *   `row_idx` to `0` (start at the first row).
    *   `col_idx` to `n - 1` (start at the last column).
    This places our starting point at the top-right corner of the matrix.
3.  **Iterate and Search**: Enter a `while` loop that continues as long as `row_idx` is within the matrix bounds (`row_idx < m`) and `col_idx` is within the matrix bounds (`col_idx >= 0`).
4.  **Compare Current Element**: Inside the loop, compare the value at `matrix[row_idx][col_idx]` with the `target`:
    *   **If `matrix[row_idx][col_idx] == target`**: The target is found. Return `true`.
    *   **If `matrix[row_idx][col_idx] > target`**: The current element is greater than the target. Since elements in the current column are sorted in ascending order from top to bottom, all elements below `matrix[row_idx][col_idx]` in this column will also be greater than the target. Also, elements to the right in the current row are greater. Therefore, we must move to a smaller value. The only way to find a potentially smaller value is to move left in the current row. So, decrement `col_idx` by 1.
    *   **If `matrix[row_idx][col_idx] < target`**: The current element is smaller than the target. Since elements in the current row are sorted in ascending order from left to right, all elements to the left of `matrix[row_idx][col_idx]` in this row will also be smaller than the target. Also, elements above in the current column are smaller. Therefore, we must move to a larger value. The only way to find a potentially larger value is to move down in the current column. So, increment `row_idx` by 1.
5.  **Target Not Found**: If the loop finishes (meaning `row_idx` went out of bounds or `col_idx` went out of bounds), it means the target was not found in the matrix. Return `false`.

## 💻 Solution
```cpp
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& mat, int tar) {
        // Handle edge cases: If the matrix is empty or has empty rows,
        // the target cannot be found.
        if (mat.empty() || mat[0].empty())
            return false;

        // Get the dimensions of the matrix.
        int numRows = mat.size();
        int numCols = mat[0].size();

        // Initialize pointers for our search.
        // We start from the top-right corner of the matrix.
        // 'r' represents the current row index, starting at 0 (first row).
        // 'c' represents the current column index, starting at numCols - 1 (last column).
        int r = 0;
        int c = numCols - 1;

        // Continue the search as long as our pointers are within the matrix bounds.
        // 'r' must be less than numRows (not gone past the last row).
        // 'c' must be greater than or equal to 0 (not gone past the first column).
        while (r < numRows && c >= 0) {
            // Get the value at the current position.
            int currentValue = mat[r][c];

            // Case 1: Current value matches the target.
            // We found the target, so return true.
            if (currentValue == tar) {
                return true;
            }
            // Case 2: Current value is greater than the target.
            // Since rows are sorted left-to-right, all elements to the right of 'currentValue'
            // in the current row would also be greater.
            // Since columns are sorted top-to-bottom, all elements below 'currentValue'
            // in the current column would also be greater.
            // To find a smaller value (closer to target), we must move left.
            else if (currentValue > tar) {
                c--; // Move to the previous column.
            }
            // Case 3: Current value is less than the target.
            // Since rows are sorted left-to-right, all elements to the left of 'currentValue'
            // in the current row would also be smaller.
            // Since columns are sorted top-to-bottom, all elements above 'currentValue'
            // in the current column would also be smaller.
            // To find a larger value (closer to target), we must move down.
            else { // currentValue < tar
                r++; // Move to the next row.
            }
        }

        // If the loop finishes, it means the pointers have gone out of bounds
        // without finding the target.
        return false;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(m + n) | In the worst case, the `row` pointer traverses `m` rows and the `col` pointer traverses `n` columns. Each step eliminates either a row or a column from the search space. Thus, the total number of steps is at most `m + n`. |
| **Space** | O(1) | The algorithm uses a constant amount of extra space for pointers (`r`, `c`) and variables, regardless of the input matrix size. |

## 🔗 Related Problems
*   74. Search a 2D Matrix
*   1351. Count Negative Numbers in a Sorted Matrix
*   378. Kth Smallest Element in a Sorted Matrix