# 0867-transpose-matrix

## 📋 Problem Description
Given a 2D integer array `matrix`, the task is to return its **transpose**.

The **transpose** of a matrix is defined as the matrix flipped over its main diagonal. This operation effectively switches the row and column indices of each element. Specifically, if an element is at `matrix[i][j]` in the original matrix, it will be located at `result[j][i]` in the transposed matrix.

The function `transpose` receives a `vector<vector<int>>` representing the 2D integer array `matrix` and must return a new `vector<vector<int>>` which is the transpose of the input matrix.

## 🔍 Examples
```
Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
Output: [[1,4,7],[2,5,8],[3,6,9]]
Explanation: The element at (0,0) is 1, remains at (0,0).
The element at (0,1) is 2, moves to (1,0).
The element at (1,0) is 4, moves to (0,1).
And so on.
```

```
Input: matrix = [[1,2,3],[4,5,6]]
Output: [[1,4],[2,5],[3,6]]
Explanation: The original matrix is 2 rows x 3 columns. The transposed matrix will be 3 rows x 2 columns.
```

## 📌 Constraints
*   `m == matrix.length` (number of rows)
*   `n == matrix[i].length` (number of columns)
*   `1 <= m, n <= 1000`
*   `1 <= m * n <= 10^5` (total number of elements)
*   `-10^9 <= matrix[i][j] <= 10^9` (value range of elements)

## 🤔 Understanding the Problem
The problem asks us to perform a fundamental matrix operation: transposition. The key insight is understanding how the dimensions change and how individual elements map from the original matrix to the transposed one. If the original matrix has `m` rows and `n` columns, its transpose will have `n` rows and `m` columns. Each element `matrix[i][j]` (at row `i`, column `j`) simply moves to `result[j][i]` (row `j`, column `i`) in the new matrix. There are no complex conditions or optimizations; it's a direct transformation.

## 💡 Core Idea
The core idea is to create a new matrix with dimensions swapped (if original is `m x n`, new is `n x m`) and then iterate through every element of the original matrix, placing `matrix[i][j]` into `result[j][i]`.

## 🧠 Approach — Direct Matrix Manipulation
This problem is a straightforward application of **Direct Matrix Manipulation** or **Array Traversal**. This pattern is suitable because the problem defines a direct, element-wise transformation from an input matrix to an output matrix. There's no need for complex algorithms like searching, sorting, or dynamic programming; we simply need to correctly map each element according to the definition of a transpose. We iterate through all elements of the original matrix once and place them into their new positions in a newly constructed matrix.

## 📝 Step-by-Step Algorithm
1.  **Determine Dimensions**: First, get the number of rows (`m`) and columns (`n`) from the input `matrix`. `m` will be `matrix.size()` and `n` will be `matrix[0].size()`.
2.  **Create Result Matrix**: Initialize a new 2D integer array, let's call it `result`, with `n` rows and `m` columns. This is because the transpose of an `m x n` matrix is an `n x m` matrix.
3.  **Iterate and Assign**:
    *   Use a nested loop structure to iterate through each element of the original `matrix`.
    *   The outer loop will iterate `i` from `0` to `m-1` (representing rows of the original matrix).
    *   The inner loop will iterate `j` from `0` to `n-1` (representing columns of the original matrix).
    *   Inside the inner loop, for each element `matrix[i][j]`, assign its value to `result[j][i]`. This correctly swaps the row and column indices.
4.  **Return Result**: After the loops complete, the `result` matrix will contain the transpose of the original matrix. Return `result`.

## 💻 Solution
```cpp
class Solution {
public:
    vector<vector<int>> transpose(vector<vector<int>>& matrix) {
        // Get the number of rows (m) from the original matrix.
        int m = matrix.size();
        // Get the number of columns (n) from the first row of the original matrix.
        // We assume matrix is non-empty based on constraints (m, n >= 1).
        int n = matrix[0].size();

        // Create a new result matrix.
        // The transposed matrix will have 'n' rows and 'm' columns.
        // Initialize all elements to default values (0 for int), though they will be overwritten.
        vector<vector<int>> result(n, vector<int>(m));

        // Iterate through each element of the original matrix.
        // 'i' represents the row index in the original matrix (0 to m-1).
        for (int i = 0; i < m; ++i) {
            // 'j' represents the column index in the original matrix (0 to n-1).
            for (int j = 0; j < n; ++j) {
                // The core operation of transposition:
                // An element at (i, j) in the original matrix
                // moves to (j, i) in the transposed matrix.
                result[j][i] = matrix[i][j];
            }
        }
        
        // Return the newly formed transposed matrix.
        return result;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(m * n) | We iterate through each of the `m * n` elements of the input matrix exactly once to copy them to the result matrix. |
| **Space** | O(m * n) | We create a new `n x m` matrix to store the transposed result. This new matrix has `n * m` elements. |

## 🔗 Related Problems
- 48. Rotate Image
- 73. Set Matrix Zeroes
- 54. Spiral Matrix