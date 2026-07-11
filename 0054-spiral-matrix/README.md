# 0054-spiral-matrix

## 📋 Problem Description
Given an `m x n` matrix, the task is to return all its elements in a specific "spiral order". This means starting from the top-left corner, traverse right, then down, then left, then up, and continue this pattern inwards until all elements have been visited.

The function `spiralOrder` receives a `vector<vector<int>>` representing the `m x n` matrix. It must return a `vector<int>` containing all elements of the matrix arranged in the described spiral order.

## 🔍 Examples
```
Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
Output: [1,2,3,6,9,8,7,4,5]
Explanation:
1 -> 2 -> 3 (right)
         |
         v
4        6 (down)
^        |
|        v
7 <- 8 <- 9 (left)
|
v
4 (up)
  -> 5 (right, inner layer)
```

```
Input: matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
Output: [1,2,3,4,8,12,11,10,9,5,6,7]
Explanation:
1 ->  2 ->  3 ->  4 (right)
                   |
                   v
5                  8 (down)
^                  |
|                  v
9 <- 10 <- 11 <- 12 (left)
|
v
5 (up)
  -> 6 -> 7 (right, inner layer)
```

## 📌 Constraints
*   `m == matrix.length` (number of rows)
*   `n == matrix[i].length` (number of columns)
*   `1 <= m, n <= 10`
*   `-100 <= matrix[i][j] <= 100`

## 🤔 Understanding the Problem
The problem asks us to extract all elements from a 2D matrix by following a clockwise spiral path. This means we start at the top-left, move right across the top row, then down the rightmost column, then left across the bottom row, then up the leftmost column. After completing one full "layer" of the spiral, we repeat the process for the inner sub-matrix. The main challenge is to correctly manage the boundaries of the current layer being traversed and to ensure that each element is visited exactly once, even for edge cases like single-row or single-column matrices.

## 💡 Core Idea
The core idea is to simulate the spiral traversal by maintaining four boundary pointers (top, bottom, left, right) that define the current "active" sub-matrix. We iteratively "peel" off the outer layer of this sub-matrix in a clockwise direction, shrinking the boundaries after each segment of traversal.

## 🧠 Approach — Boundary Traversal / Simulation
This problem is a classic example of a **Boundary Traversal** or **Simulation** pattern. We simulate the process of moving along the edges of the current "active" sub-matrix. This pattern is suitable because the problem explicitly defines a path (spiral) that can be broken down into distinct segments (right, down, left, up) which are repeatedly applied to a shrinking boundary. By keeping track of the current boundaries, we can systematically visit each element without needing extra space for visited flags. The simulation continues until the boundaries cross each other, indicating that all elements have been processed.

## 📝 Step-by-Step Algorithm
1.  Initialize an empty list, `ans`, which will store the elements in spiral order.
2.  Determine the dimensions of the input matrix: `row` for the number of rows and `col` for the number of columns.
3.  Initialize four integer variables to represent the boundaries of the current sub-matrix:
    *   `str` (start row index): points to the top row. Initially `0`.
    *   `enr` (end row index): points to the bottom row. Initially `row - 1`.
    *   `stc` (start column index): points to the left column. Initially `0`.
    *   `enc` (end column index): points to the right column. Initially `col - 1`.
4.  Enter a `while` loop that continues as long as `str <= enr` AND `stc <= enc`. This condition ensures there is still a valid sub-matrix (at least one row and one column) to traverse.
5.  **Traverse Right (Top Row)**:
    *   Iterate a variable `i` from `stc` to `enc`.
    *   Add `mat[str][i]` to `ans`.
    *   After this loop, increment `str` (move the top boundary down) because the current top row has been processed.
6.  **Traverse Down (Rightmost Column)**:
    *   Iterate a variable `i` from the new `str` (after increment) to `enr`.
    *   Add `mat[i][enc]` to `ans`.
    *   After this loop, decrement `enc` (move the right boundary left) because the current rightmost column has been processed.
7.  **Traverse Left (Bottom Row)**:
    *   **Crucial Check**: Before traversing left, check if `str <= enr`. This handles cases where the matrix might have only one row (e.g., `[[1,2,3]]`) or when `str` has already crossed `enr` due to previous traversals (e.g., after processing a single-column matrix). If this condition is false, it means there are no more rows to traverse left on, so skip this step.
    *   If the condition is true, iterate a variable `i` from the new `enc` (after decrement) down to `stc`.
    *   Add `mat[enr][i]` to `ans`.
    *   After this loop, decrement `enr` (move the bottom boundary up) because the current bottom row has been processed.
8.  **Traverse Up (Leftmost Column)**:
    *   **Crucial Check**: Before traversing up, check if `stc <= enc`. This handles cases where the matrix might have only one column (e.g., `[[1],[2],[3]]`) or when `stc` has already crossed `enc`. If this condition is false, it means there are no more columns to traverse up on, so skip this step.
    *   If the condition is true, iterate a variable `i` from the new `enr` (after decrement) down to the new `str` (after increment).
    *   Add `mat[i][stc]` to `ans`.
    *   After this loop, increment `stc` (move the left boundary right) because the current leftmost column has been processed.
9.  The `while` loop continues, processing the next inner layer of the matrix.
10. Once the `while` loop terminates (when `str > enr` or `stc > enc`), return the `ans` vector.

## 💻 Solution
```cpp
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& mat) {
        // Get the dimensions of the matrix.
        int row = mat.size();
        int col = mat[0].size();

        // Initialize an empty vector to store the elements in spiral order.
        vector<int> ans;

        // Initialize boundary pointers for the current sub-matrix.
        // `str`: start row index (top boundary)
        // `enr`: end row index (bottom boundary)
        // `stc`: start column index (left boundary)
        // `enc`: end column index (right boundary)
        int str = 0;
        int enr = row - 1;
        int stc = 0;
        int enc = col - 1;

        // Loop as long as there's a valid sub-matrix to traverse.
        // The condition `str <= enr` ensures there are rows remaining.
        // The condition `stc <= enc` ensures there are columns remaining.
        while (str <= enr && stc <= enc) {
            // 1. Traverse Right: From left to right along the current top row.
            // We iterate from `stc` to `enc` using the `str` row index.
            for (int i = stc; i <= enc; i++) {
                ans.push_back(mat[str][i]);
            }
            // After traversing the top row, move the top boundary down.
            str++;

            // 2. Traverse Down: From top to bottom along the current rightmost column.
            // We iterate from the new `str` (after increment) to `enr` using the `enc` column index.
            for (int i = str; i <= enr; i++) {
                ans.push_back(mat[i][enc]);
            }
            // After traversing the rightmost column, move the right boundary left.
            enc--;

            // 3. Traverse Left: From right to left along the current bottom row.
            // This step is only performed if there's still a valid row to traverse (i.e., `str` hasn't crossed `enr`).
            // This check is crucial for matrices like [[1,2,3]] (single row) where `str` would become > `enr` after step 1.
            if (str <= enr) {
                // We iterate from the new `enc` (after decrement) down to `stc` using the `enr` row index.
                for (int i = enc; i >= stc; i--) {
                    ans.push_back(mat[enr][i]);
                }
            }
            // After traversing the bottom row, move the bottom boundary up.
            // This decrement happens regardless of the if condition, as 'enr' is always processed if the condition is met.
            enr--; 

            // 4. Traverse Up: From bottom to top along the current leftmost column.
            // This step is only performed if there's still a valid column to traverse (i.e., `stc` hasn't crossed `enc`).
            // This check is crucial for matrices like [[1],[2],[3]] (single column) or when `stc` would become > `enc` after step 2.
            if (stc <= enc) {
                // We iterate from the new `enr` (after its decrement) down to the new `str` (after its increment).
                // Note: `mat[enr][stc]` (bottom-left) was added in step 3. `mat[str][stc]` (top-left) was added in step 1.
                // So we traverse the elements *between* these two.
                for (int i = enr; i >= str; i--) { 
                    ans.push_back(mat[i][stc]);
                }
            }
            // After traversing the leftmost column, move the left boundary right.
            stc++;
        }
        return ans;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(m * n) | Each element in the `m x n` matrix is visited and added to the result vector exactly once. |
| **Space** | O(m * n) | We store all `m * n` elements of the matrix in the `ans` vector. If output space is not counted, auxiliary space is O(1) for the boundary pointers. |

## 🔗 Related Problems
- 59. Spiral Matrix II
- 48. Rotate Image