# 0073-set-matrix-zeroes

## 📋 Problem Description
Given an `m x n` integer matrix, the task is to modify it in place. If any element in the matrix is `0`, its entire corresponding row and entire corresponding column must be set to `0`. The modification must be performed directly on the input matrix without allocating significant extra space.

Input: An `m x n` integer matrix `matrix`.
Output: The function returns `void`, as it modifies the input `matrix` directly.

## 🔍 Examples
**Example 1:**
```
Input: matrix = [[1,1,1],[1,0,1],[1,1,1]]
Output: [[1,0,1],[0,0,0],[1,0,1]]
Explanation: The element at matrix[1][1] is 0. Therefore, row 1 and column 1 are set to 0.
```

**Example 2:**
```
Input: matrix = [[0,1,2,0],[3,4,5,2],[1,3,1,5]]
Output: [[0,0,0,0],[0,4,5,0],[0,3,1,0]]
Explanation: The elements at matrix[0][0] and matrix[0][3] are 0. This causes row 0 and columns 0 and 3 to be set to 0.
```

## 📌 Constraints
*   `m == matrix.length`
*   `n == matrix[0].length`
*   `1 <= m, n <= 200`
*   `-2^31 <= matrix[i][j] <= 2^31 - 1`

## 🤔 Understanding the Problem
The problem asks us to propagate zeros throughout a matrix: if a cell `(i, j)` is `0`, then all cells in row `i` and all cells in column `j` must become `0`. The critical constraint is that this must be done "in place," meaning we cannot create a new matrix to store the result. A naive approach of iterating and zeroing out immediately would be incorrect because changing a `0` to `0` might cause other non-zero cells to become `0` prematurely, which would then incorrectly trigger more zeroing. We need a way to remember which rows and columns should be zeroed based on the *original* state of the matrix before we start modifying it.

## 💡 Core Idea
The key insight for an O(1) auxiliary space solution is to repurpose the first row and first column of the matrix itself to store information about which rows and columns need to be zeroed. This acts as a set of "markers" without using additional memory proportional to `m` or `n`.

## 🧠 Approach — In-place Modification with O(1) Auxiliary Space
This problem is a classic example of an in-place modification problem where we need to process information without using significant extra memory. The pattern involves cleverly repurposing existing space within the input structure to store necessary state or markers. Specifically, we use the first row and first column of the matrix as "sentinels" or "flags" to indicate whether their corresponding rows or columns should be zeroed out. This avoids the `O(m+n)` space of separate boolean arrays and the `O(mn)` space of a copy, achieving constant auxiliary space.

## 📝 Step-by-Step Algorithm
1.  **Initialize Flags for First Row/Column**: Declare two boolean variables, `firstRowZero` and `firstColZero`. These will track whether the *original* first row or first column contained any zeros, respectively. This is crucial because we will use `matrix[0][j]` and `matrix[i][0]` as markers for other rows/columns, and we need to know if they themselves should be zeroed out independently at the very end.

2.  **Check First Row for Zeros**: Iterate through the first row (`matrix[0][j]`) from `j = 0` to `n-1`. If any element `matrix[0][j]` is `0`, set `firstRowZero` to `true` and break the loop, as we only need to know if *at least one* zero exists.

3.  **Check First Column for Zeros**: Iterate through the first column (`matrix[i][0]`) from `i = 0` to `m-1`. If any element `matrix[i][0]` is `0`, set `firstColZero` to `true` and break the loop.

4.  **Mark Rows and Columns (using first row/column as markers)**: Iterate through the "inner" part of the matrix, starting from `matrix[1][1]` up to `matrix[m-1][n-1]`. For each cell `matrix[i][j]`:
    *   If `matrix[i][j]` is `0`, it means its entire row `i` and entire column `j` need to be zeroed.
    *   Mark this by setting the corresponding first column element `matrix[i][0]` to `0` (indicating row `i` needs zeroing) and the corresponding first row element `matrix[0][j]` to `0` (indicating column `j` needs zeroing).

5.  **Zero Out Inner Matrix**: Iterate through the matrix again, but only for cells from `matrix[1][1]` to `matrix[m-1][n-1]`. For each cell `matrix[i][j]`:
    *   If its corresponding row marker (`matrix[i][0]`) is `0` OR its corresponding column marker (`matrix[0][j]`) is `0`, then set `matrix[i][j] = 0`.

6.  **Zero Out First Row (if needed)**: After processing the inner matrix, check the `firstRowZero` flag. If it's `true`, iterate through the entire first row (`matrix[0][j]`) from `j = 0` to `n-1` and set all its elements to `0`. This step must be done after step 5 to ensure the markers in `matrix[0][j]` for other columns are used before `matrix[0][j]` itself is zeroed out.

7.  **Zero Out First Column (if needed)**: Similarly, check the `firstColZero` flag. If it's `true`, iterate through the entire first column (`matrix[i][0]`) from `i = 0` to `m-1` and set all its elements to `0`. This also must be done after step 5 for the same reason.

## 💻 Solution
```cpp
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();

        // These booleans will track if the *original* first row or first column
        // contained any zeros. We need to store this information separately
        // because we'll be using the first row and column themselves as markers
        // for other rows/columns. If we don't store this, we might lose
        // the original state of the first row/column.
        bool firstRowZero = false;
        bool firstColZero = false;

        // Step 1: Check if the first row needs to be zeroed out.
        // Iterate through the first row (matrix[0][j])
        for (int j = 0; j < n; j++) {
            if (matrix[0][j] == 0) {
                firstRowZero = true; // Mark that the first row should be zeroed.
                break; // No need to check further in this row once a zero is found.
            }
        }

        // Step 2: Check if the first column needs to be zeroed out.
        // Iterate through the first column (matrix[i][0])
        for (int i = 0; i < m; i++) {
            if (matrix[i][0] == 0) {
                firstColZero = true; // Mark that the first column should be zeroed.
                break; // No need to check further in this column once a zero is found.
            }
        }

        // Step 3: Use the first row and first column as markers.
        // Iterate through the rest of the matrix (from [1][1] to [m-1][n-1]).
        // If an element matrix[i][j] is 0, it means its entire row 'i' and
        // entire column 'j' need to be zeroed. We mark this by setting
        // matrix[i][0] to 0 (for row 'i') and matrix[0][j] to 0 (for column 'j').
        // This effectively uses the first row and column as auxiliary space.
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                if (matrix[i][j] == 0) {
                    matrix[i][0] = 0; // Mark row 'i' for zeroing by setting its first element to 0
                    matrix[0][j] = 0; // Mark column 'j' for zeroing by setting its first element to 0
                }
            }
        }

        // Step 4: Zero out cells based on the markers in the first row and column.
        // Iterate through the matrix again, but only for cells from [1][1] onwards.
        // If matrix[i][0] is 0 (meaning row 'i' needs to be zeroed, as marked in Step 3) OR
        // if matrix[0][j] is 0 (meaning column 'j' needs to be zeroed, as marked in Step 3),
        // then set the current cell matrix[i][j] to 0.
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                if (matrix[i][0] == 0 || matrix[0][j] == 0) {
                    matrix[i][j] = 0;
                }
            }
        }

        // Step 5: Finally, zero out the first row and first column if they
        // originally contained any zeros (as determined by our flags in Steps 1 & 2).
        // This step must be done last to avoid affecting the markers for
        // other rows/columns prematurely. For example, if firstRowZero was true,
        // zeroing matrix[0][j] before Step 4 would incorrectly zero out columns
        // that shouldn't be.

        // Zero out the first row if the 'firstRowZero' flag is true.
        if (firstRowZero) {
            for (int j = 0; j < n; j++) {
                matrix[0][j] = 0;
            }
        }

        // Zero out the first column if the 'firstColZero' flag is true.
        if (firstColZero) {
            for (int i = 0; i < m; i++) {
                matrix[i][0] = 0;
            }
        }
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(m * n) | The algorithm involves several distinct passes over the matrix. Each pass iterates through at most `m * n` elements (or a subset like `m` or `n` elements for the first row/column checks). Since the number of passes is constant (checking first row, checking first column, marking inner, zeroing inner, zeroing first row, zeroing first column), the total time complexity is proportional to the number of elements in the matrix. |
| **Space** | O(1) | The solution uses only a few boolean variables (`firstRowZero`, `firstColZero`) to store state, regardless of the matrix size. All modifications are done directly within the input matrix, satisfying the in-place requirement. |

## 🔗 Related Problems
- 48. Rotate Image
- 289. Game of Life
- 41. First Missing Positive