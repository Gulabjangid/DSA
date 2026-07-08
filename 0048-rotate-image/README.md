# 0048-rotate-image

## 📋 Problem Description
You are given an `n x n` 2D integer `matrix` representing an image. Your task is to rotate the image by 90 degrees in a clockwise direction.

The rotation must be performed **in-place**, meaning you must modify the input 2D matrix directly. You are explicitly forbidden from allocating another 2D matrix to solve this problem.

The function `rotate` receives a `vector<vector<int>>& matrix` as input and modifies it directly, returning nothing.

## 🔍 Examples
```
Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
Output: [[7,4,1],[8,5,2],[9,6,3]]
Explanation:
The original matrix:
1 2 3
4 5 6
7 8 9

After 90-degree clockwise rotation:
7 4 1
8 5 2
9 6 3
```

```
Input: matrix = [[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]]
Output: [[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]]
Explanation:
The original matrix:
 5  1  9 11
 2  4  8 10
13  3  6  7
15 14 12 16

After 90-degree clockwise rotation:
15 13  2  5
14  3  4  1
12  6  8  9
16  7 10 11
```

## 📌 Constraints
*   `n == matrix.length == matrix[i].length`
*   `1 <= n <= 20`
*   `-1000 <= matrix[i][j] <= 1000`

## 🤔 Understanding the Problem
The problem asks us to perform a 90-degree clockwise rotation on a square matrix. The critical constraint is that this operation must be done "in-place," meaning we cannot create a new matrix to store the result. We must modify the original matrix directly using only a constant amount of extra space. This makes the problem non-trivial, as simply moving an element to its final rotated position might overwrite another element that hasn't been moved yet.

## 💡 Core Idea
A 90-degree clockwise rotation can be achieved by a sequence of two simpler, in-place transformations: first, transposing the matrix (swapping elements across its main diagonal), and then reversing each row of the transposed matrix.

## 🧠 Approach — Matrix Transformation
This problem is best solved using a **Matrix Transformation** approach. This pattern involves applying a series of geometric or algebraic operations directly to the elements of a matrix to achieve a desired state. It fits this problem perfectly because we are performing a geometric rotation on a 2D grid of data. The "in-place" constraint guides us to break down the complex rotation into simpler, in-place operations like transposing and row reversal, which can be done without allocating significant additional memory.

## 📝 Step-by-Step Algorithm

1.  **Get Matrix Dimension**: First, determine the size `n` of the square matrix (since `n x n`).

2.  **Step 1: Transpose the Matrix**:
    *   Iterate through the matrix using nested loops. The outer loop `i` will go from `0` to `n-1` (representing rows).
    *   The inner loop `j` will go from `i` to `n-1` (representing columns). Starting `j` from `i` ensures that we only process the upper triangle of the matrix (including the main diagonal) and avoid swapping elements twice (e.g., swapping `(0,1)` with `(1,0)` and then `(1,0)` with `(0,1)` again).
    *   Inside the inner loop, swap the element at `matrix[i][j]` with the element at `matrix[j][i]`. This effectively flips the matrix over its main diagonal.

3.  **Step 2: Reverse Each Row**:
    *   After transposing, iterate through each row of the matrix. The outer loop `i` will go from `0` to `n-1`.
    *   For each row `i`, use two pointers: `left` initialized to `0` (start of the row) and `right` initialized to `n-1` (end of the row).
    *   While `left` is less than `right`:
        *   Swap the element at `matrix[i][left]` with the element at `matrix[i][right]`.
        *   Increment `left` by 1 and decrement `right` by 1 to move the pointers towards the center of the row.
    *   This process reverses the order of elements in the current row.

4.  After these two steps, the matrix will be rotated 90 degrees clockwise in-place.

## 💻 Solution
```cpp
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {

        int n = matrix.size(); // Get the dimension of the square matrix.

        // Step 1: Transpose the matrix.
        // Transposing means swapping elements across the main diagonal (top-left to bottom-right).
        // For an element originally at (row, col), it moves to (col, row).
        // We iterate through the upper triangle (including the diagonal) to ensure
        // each pair of elements (matrix[i][j] and matrix[j][i]) is swapped only once.
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) { // Start j from i to process only the upper triangle.
                // Swap matrix[i][j] with matrix[j][i]
                swap(matrix[i][j], matrix[j][i]);
            }
        }
        
        // Step 2: Reverse each row of the transposed matrix.
        // After transposing, a 90-degree clockwise rotation is completed by reversing each row.
        // For example, if a row was [A, B, C], it becomes [C, B, A].
        for (int i = 0; i < n; i++) { // Iterate through each row of the matrix.
            int left = 0;           // Pointer for the start of the current row.
            int right = n - 1;      // Pointer for the end of the current row.
            
            // Use two pointers to swap elements from the ends towards the center of the row.
            while (left < right) {  
                // Swap the element at the left pointer with the element at the right pointer.
                swap(matrix[i][left], matrix[i][right]);
                left++;             // Move the left pointer one step to the right.
                right--;            // Move the right pointer one step to the left.
            }
        }
    }
};

```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(n^2) | The algorithm involves two main passes over the matrix. Transposing iterates through roughly half of the `n*n` elements, and reversing rows iterates through all `n` rows, each taking `n/2` swaps. Both operations are proportional to `n*n`. |
| **Space** | O(1) | The rotation is performed in-place. Only a few auxiliary variables (like `n`, `i`, `j`, `left`, `right`) are used, which consume a constant amount of extra space regardless of the input matrix size. |

## 🔗 Related Problems
- 54. Spiral Matrix
- 73. Set Matrix Zeroes
- 289. Game of Life
- 1886. Determine Whether Matrix Can Be Rotated