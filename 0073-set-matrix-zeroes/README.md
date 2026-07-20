# 0073-set-matrix-zeroes

## 📋 Problem Description
Given an `m x n` integer matrix, if any element within the matrix is `0`, its entire corresponding row and entire corresponding column must be set to `0`. This modification must be performed *in place*, meaning you cannot use additional memory proportional to the size of the input matrix.

The function `setZeroes` receives a `vector<vector<int>>& matrix` as input and modifies it directly. It does not return any value.

## 🔍 Examples
**Example 1:**
```
Input: matrix = [[1,1,1],[1,0,1],[1,1,1]]
Output: [[1,0,1],[0,0,0],[1,0,1]]
Explanation: The element at matrix[1][1] is 0. As a result, row 1 and column 1 are entirely set to 0.
```

**Example 2:**
```
Input: matrix = [[0,1,2,0],[3,4,5,2],[1,3,1,5]]
Output: [[0,0,0,0],[0,4,5,0],[0,3,1,0]]
Explanation: Elements at matrix[0][0] and matrix[0][3] are 0. This causes row 0, column 0, and column 3 to be set to 0.
```

## 📌 Constraints
*   `m == matrix.length`
*   `n == matrix[0].length`
*   `1 <= m, n <= 200`
*   `-2^31 <= matrix[i][j] <= 2^31 - 1`

## 🤔 Understanding the Problem
The core task is to propagate zeros throughout a matrix: if a cell is zero, its entire row and column become zero. The main challenge is the "in-place" requirement. A naive approach of iterating and immediately zeroing out rows/columns would be incorrect because a newly zeroed cell might then trigger further zeroing, which wasn't based on an *original* zero. We need a strategy to mark which rows and columns need to be zeroed without altering the original values needed for the marking process itself.

## 💡 Core Idea
The key insight for an O(1) space solution is to reuse the first row and first column of the matrix itself to store information about which rows and columns need to be zeroed. We use these as "marker" arrays, but we need separate boolean flags to handle the special case of `matrix[0][0]` since it serves as a marker for both the first row and the first column.

## 🧠 Approach — In-Place Modification / Constant Space Optimization
This problem is a classic example of an in-place modification problem where we need to process information without using significant auxiliary data structures. The pattern involves using the input matrix's own structure (specifically, its first row and first column) to store metadata. This allows us to achieve O(1) additional space complexity by cleverly repurposing existing memory, which is a common technique in competitive programming for space-constrained problems. By separating the marking phase from the zeroing phase, and handling the first row/column specially, we avoid conflicts.

## 📝 Step-by-Step Algorithm

1.  **Initialize Flags for First Row/Column**:
    *   Declare two boolean variables, `firstRowZero` and `firstColZero`, initialized to `false`. These flags will track if the *original* first row or first column contained any zeros.
    *   Iterate through the *first row* (`matrix[0][j]` for `j` from `0` to `n-1`). If any element is `0`, set `firstRowZero` to `true` and break the loop.
    *   Iterate through the *first column* (`matrix[i][0]` for `i` from `0` to `m-1`). If any element is `0`, set `firstColZero` to `true` and break the loop.
    *   These flags are essential because `matrix[0][0]` will be used as a marker for both its row and column, and we need to preserve the information about whether the first row/column *originally* had a zero.

2.  **Mark Rows and Columns (excluding the first row/column)**:
    *   Iterate through the matrix starting from `matrix[1][1]` (i.e., for `i` from `1` to `m-1` and `j` from `1` to `n-1`).
    *   If `matrix[i][j]` is `0`, it means its entire row `i` and entire column `j` must eventually be zeroed. Mark this by setting `matrix[i][0] = 0` (to indicate row `i` needs to be zeroed) and `matrix[0][j] = 0` (to indicate column `j` needs to be zeroed).

3.  **Zero Out Inner Matrix**:
    *   Now, iterate through the matrix again, starting from `matrix[1][1]` (i.e., for `i` from `1` to `m-1` and `j` from `1` to `n-1`).
    *   For each cell `matrix[i][j]`, check its corresponding markers: `matrix[i][0]` and `matrix[0][j]`.
    *   If `matrix[i][0]` is `0` (meaning row `i` should be zeroed based on our markers) OR `matrix[0][j]` is `0` (meaning column `j` should be zeroed), then set `matrix[i][j] = 0`.

4.  **Zero Out First Row/Column (if needed)**:
    *   Finally, use the flags set in step 1 to handle the first row and first column:
        *   If `firstRowZero` is `true`, iterate through the entire first row (`matrix[0][j]` for `j` from `0` to `n-1`) and set all its elements to `0`.
        *   If `firstColZero` is `true`, iterate through the entire first column (`matrix[i][0]` for `i` from `0` to `m-1`) and set all its elements to `0`.
    *   It's critical to perform these steps *last* to ensure that the first row and column markers are not prematurely overwritten before they are used to zero out the inner matrix.

## 💻 Solution
```cpp
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int m = matrix.size();    // Get the number of rows in the matrix
        int n = matrix[0].size(); // Get the number of columns in the matrix

        // These boolean flags will track if the first row or first column
        // originally contained a zero. This is crucial because matrix[0][0]
        // will be used as a marker for both its row and column, so we need
        // separate information to correctly handle the first row and first column
        // at the very end.
        bool firstRowZero = false;
        bool firstColZero = false;

        // Step 1: Check if the first row needs to be zeroed out
        // Iterate through the first row (matrix[0][j]) to see if any element is 0.
        for (int j = 0; j < n; j++) {
            if (matrix[0][j] == 0) {
                firstRowZero = true; // Set the flag if a zero is found
                break;               // No need to check further in this row
            }
        }

        // Step 2: Check if the first column needs to be zeroed out
        // Iterate through the first column (matrix[i][0]) to see if any element is 0.
        for (int i = 0; i < m; i++) {
            if (matrix[i][0] == 0) {
                firstColZero = true; // Set the flag if a zero is found
                break;               // No need to check further in this column
            }
        }

        // Step 3: Use the first row and first column as markers for the rest of the matrix.
        // Iterate through the matrix starting from (1,1) (i.e., excluding the first row and first column).
        // If an element matrix[i][j] is 0, it means its entire row 'i' and column 'j'
        // should eventually be zeroed. We mark this by setting matrix[i][0] to 0
        // (to indicate that row 'i' needs to be zeroed) and matrix[0][j] to 0
        // (to indicate that column 'j' needs to be zeroed).
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                if (matrix[i][j] == 0) {
                    matrix[i][0] = 0; // Mark row 'i' by setting its first element to 0
                    matrix[0][j] = 0; // Mark column 'j' by setting its first element to 0
                }
            }
        }

        // Step 4: Zero out cells based on the markers in the first row and first column.
        // Iterate through the matrix again, starting from (1,1).
        // For each cell matrix[i][j], check its corresponding markers:
        // if the marker in its first column cell (matrix[i][0]) is 0,
        // OR the marker in its first row cell (matrix[0][j]) is 0,
        // then this cell matrix[i][j] should be set to 0.
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                if (matrix[i][0] == 0 || matrix[0][j] == 0) {
                    matrix[i][j] = 0;
                }
            }
        }

        // Step 5: Zero out the first row if the 'firstRowZero' flag was set.
        // This step must be performed AFTER processing the inner matrix (Step 4)
        // to ensure that the markers in the first row were used correctly
        // before potentially overwriting them.
        if (firstRowZero) {
            for (int j = 0; j < n; j++) {
                matrix[0][j] = 0;
            }
        }

        // Step 6: Zero out the first column if the 'firstColZero' flag was set.
        // Similar to the first row, this is done last for the same reason.
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
| **Time** | O(m*n) | The algorithm involves several distinct passes over the matrix. Each pass iterates through at most `m*n` elements (or a subset like `(m-1)*(n-1)`). Since the number of passes is constant (specifically, 4-5 passes), the total time complexity remains directly proportional to the total number of elements in the matrix. |
| **Space** | O(1) | The solution uses only a fixed number of boolean variables (`firstRowZero`, `firstColZero`) to store state, regardless of the input matrix size. All modifications are performed directly within the given input matrix, making it an in-place solution. |

## 🔗 Related Problems
- 289. Game of Life
- 48. Rotate Image
- 41. First Missing Positive