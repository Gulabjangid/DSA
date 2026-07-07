# 0867-transpose-matrix

## 📋 Problem Description
Given a 2D integer array `matrix`, the task is to return its transpose. The transpose of a matrix is formed by "flipping" the matrix over its main diagonal. This means that the row and column indices of each element are switched. Specifically, an element at `matrix[i][j]` in the original matrix will be located at `result[j][i]` in the transposed matrix. If the original matrix has `m` rows and `n` columns, the transposed matrix will have `n` rows and `m` columns.

## 🔍 Examples
```
Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
Output: [[1,4,7],[2,5,8],[3,6,9]]
Explanation: The element at (0,0) is 1, (0,1) is 2, (0,2) is 3. In the transpose, (0,0) is 1, (1,0) is 2, (2,0) is 3.
Similarly, (1,0) is 4, (1,1) is 5, (1,2) is 6. In the transpose, (0,1) is 4, (1,1) is 5, (2,1) is 6.
```

```
Input: matrix = [[1,2,3],[4,5,6]]
Output: [[1,4],[2,5],[3,6]]
Explanation: The original matrix is 2x3. The transposed matrix will be 3x2.
matrix[0][0]=1 -> result[0][0]=1
matrix[0][1]=2 -> result[1][0]=2
matrix[0][2]=3 -> result[2][0]=3
matrix[1][0]=4 -> result[0][1]=4
matrix[1][1]=5 -> result[1][1]=5
matrix[1][2]=6 -> result[2][1]=6
```

## 📌 Constraints
*   `m == matrix.length` (number of rows)
*   `n == matrix[i].length` (number of columns)
*   `1 <= m, n <= 1000`
*   `1 <= m * n <= 10^5` (total number of elements in the matrix)
*   `-10^9 <= matrix[i][j] <= 10^9` (value range for elements)

## 🤔 Understanding the Problem
The problem asks us to create a new matrix that is the transpose of a given input matrix. The core concept of transposition is to swap the row and column indices for every element. This means if an element is at `(row, col)` in the original matrix, it will be at `(col, row)` in the transposed matrix. A key implication is that the dimensions of the resulting matrix will be swapped compared to the original: an `m x n` matrix becomes an `n x m` matrix after transposition.

## 💡 Core Idea
The most direct way to transpose a matrix is to apply its mathematical definition: for every element `matrix[i][j]`, its new position in the transposed matrix will be `result[j][i]`.

## 🧠 Approach — Direct Construction / Matrix Traversal
This problem is solved using a "Direct Construction" approach combined with "Matrix Traversal". We iterate through every element of the original matrix. For each element `matrix[i][j]`, we directly calculate its new position `result[j][i]` in the transposed matrix and assign the value. This pattern is suitable because the transformation rule for each element is simple, independent of other elements, and allows us to build the result matrix element by element in a single pass.

## 📝 Step-by-Step Algorithm
1.  First, determine the dimensions of the input `matrix`. Let `m` be the number of rows and `n` be the number of columns.
2.  Create a new 2D integer array, let's call it `result`, which will store the transposed matrix. The dimensions of `result` must be `n` rows and `m` columns (the original dimensions swapped).
3.  Initialize an outer loop that iterates through each row of the original `matrix`. Let the row index be `i`, ranging from `0` to `m - 1`.
4.  Inside the outer loop, initialize an inner loop that iterates through each column of the original `matrix`. Let the column index be `j`, ranging from `0` to `n - 1`.
5.  For each element `matrix[i][j]` encountered during the nested loops, assign its value to the corresponding position in the `result` matrix. Specifically, set `result[j][i] = matrix[i][j]`. This step effectively swaps the row and column indices.
6.  After the nested loops complete, all elements from the original matrix will have been placed into their correct transposed positions in the `result` matrix.
7.  Return the `result` matrix.

## 💻 Solution
```cpp
class Solution {
public:
    vector<vector<int>> transpose(vector<vector<int>>& matrix) {
        // Get the dimensions of the original matrix.
        // 'm' represents the number of rows in the original matrix.
        int m = matrix.size();
        // 'n' represents the number of columns in the original matrix.
        // We assume the matrix is not empty, so matrix[0] exists.
        int n = matrix[0].size();

        // Create a new matrix 'result' to store the transpose.
        // The dimensions of the transposed matrix are swapped:
        // it will have 'n' rows and 'm' columns.
        vector<vector<int>> result(n, vector<int>(m));

        // Iterate through each element of the original matrix.
        // The outer loop iterates through rows of the original matrix (0 to m-1).
        for (int i = 0; i < m; ++i) {
            // The inner loop iterates through columns of the original matrix (0 to n-1).
            for (int j = 0; j < n; ++j) {
                // According to the definition of transpose,
                // the element at matrix[i][j] in the original matrix
                // moves to result[j][i] in the transposed matrix.
                result[j][i] = matrix[i][j];
            }
        }
        
        // Return the newly constructed transposed matrix.
        return result;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(m * n) | We iterate through each of the `m * n` elements in the original matrix exactly once to copy them to the new matrix. |
| **Space** | O(m * n) | We create a new matrix of size `n * m` (which is equivalent to `m * n`) to store the result. |

## 🔗 Related Problems
- 48. Rotate Image
- 73. Set Matrix Zeroes
- 54. Spiral Matrix