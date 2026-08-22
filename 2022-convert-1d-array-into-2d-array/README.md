# 2022-convert-1d-array-into-2d-array

## 📋 Problem Description
You are given a 0-indexed 1-dimensional (1D) integer array `original`, and two integers, `m` and `n`. Your task is to create a 2-dimensional (2D) array with `m` rows and `n` columns using *all* the elements from `original`.

The elements from `original` should populate the 2D array row by row. Specifically:
*   The first `n` elements of `original` (indices `0` to `n-1`) should form the first row of the constructed 2D array.
*   The next `n` elements of `original` (indices `n` to `2*n-1`) should form the second row.
*   This pattern continues until all elements from `original` are used.

You must return the `m x n` 2D array constructed according to this procedure. If it is impossible to construct such a 2D array (i.e., the number of elements in `original` does not exactly match `m * n`), you should return an empty 2D array.

## 🔍 Examples
```
Input: original = [1,2,3,4], m = 2, n = 2
Output: [[1,2],[3,4]]
Explanation: The constructed 2D array should contain 2 rows and 2 columns.
The first group of n=2 elements in original, [1,2], becomes the first row.
The second group of n=2 elements in original, [3,4], becomes the second row.
```

```
Input: original = [1,2,3], m = 1, n = 3
Output: [[1,2,3]]
Explanation: The constructed 2D array should contain 1 row and 3 columns.
All three elements in original are placed into the first row.
```

```
Input: original = [1,2], m = 1, n = 1
Output: []
Explanation: There are 2 elements in original.
It is impossible to fit 2 elements into a 1x1 2D array (which can only hold 1 element), so an empty 2D array is returned.
```

## 📌 Constraints
*   `1 <= original.length <= 5 * 10^4`
*   `1 <= original[i] <= 10^5`
*   `1 <= m, n <= 4 * 10^4`

## 🤔 Understanding the Problem
The problem asks us to reshape a 1D array into a 2D array of specific dimensions (`m` rows, `n` columns). The crucial condition is that *all* elements from the 1D array must be used, and they must perfectly fill the `m x n` grid. This means the total number of elements in the `original` array must be exactly equal to `m * n`. If this count doesn't match, it's an impossible conversion, and we must return an empty array. Otherwise, it's a straightforward mapping where elements fill the 2D array row by row.

## 💡 Core Idea
The core idea is to first validate if the conversion is possible by comparing the total number of elements in the `original` array with the product `m * n`. If valid, we can then iterate through the `original` array and sequentially place each element into the `m x n` 2D array, managing the current row and column indices.

## 🧠 Approach — Direct Construction / Array Traversal
This problem can be solved using a "Direct Construction" or "Array Traversal" approach. This pattern is suitable because the problem defines a very clear and deterministic mapping from the 1D array elements to their positions in the 2D array. We don't need complex data structures or advanced algorithms; a simple loop that iterates through the 1D array and places elements into the correct 2D array cells is sufficient. We just need to correctly manage the row and column indices as we populate the new 2D array.

## 📝 Step-by-Step Algorithm
1.  **Check for Impossibility**:
    *   Get the total number of elements in the `original` 1D array. Let this be `len`.
    *   Calculate the total number of elements required for the `m x n` 2D array, which is `m * n`.
    *   If `len` is not equal to `m * n`, it's impossible to form the desired 2D array. In this case, immediately return an empty 2D array (e.g., `{}`).

2.  **Initialize Result Array**:
    *   Create a new 2D integer array (or `vector<vector<int>>` in C++) named `ans` with `m` rows and `n` columns. This array will store our result.

3.  **Initialize Pointers for 2D Array**:
    *   Declare two integer variables, `currentRow` and `currentCol`, and initialize both to `0`. These will keep track of the current position (row and column index) where we need to place an element in the `ans` array.

4.  **Populate the 2D Array**:
    *   Iterate through the `original` 1D array from its first element (index `0`) up to its last element (index `len - 1`). Let the loop variable be `i`.
    *   In each iteration:
        *   Place the element `original[i]` into the `ans` array at the position `ans[currentRow][currentCol]`.
        *   Increment `currentCol` to move to the next column in the current row.
        *   **Check for Row Completion**: If `currentCol` becomes equal to `n` (meaning we have just filled the last column of the current row):
            *   Reset `currentCol` back to `0` to start from the first column of the next row.
            *   Increment `currentRow` to move to the next row.

5.  **Return Result**:
    *   After the loop finishes, all elements from `original` will have been placed into `ans`. Return the `ans` 2D array.

## 💻 Solution
```cpp
class Solution {
public:
    vector<vector<int>> construct2DArray(vector<int>& original, int m, int n) {
        // Step 1: Check for impossibility condition.
        // If the total number of elements in 'original' is not equal to the
        // required number of elements for an m x n 2D array (m * n),
        // then it's impossible to construct the 2D array.
        // In this case, return an empty 2D array.
        if (m * n != original.size()) {
            return {};
        }

        // Step 2: Initialize the result 2D array.
        // Create a 2D vector 'ans' with 'm' rows and 'n' columns.
        // All elements will be default-initialized (e.g., to 0 for int).
        vector<vector<int>> ans(m, vector<int>(n));

        // Step 3: Initialize row and column pointers for the 2D array.
        // 'row' tracks the current row index in 'ans'.
        // 'col' tracks the current column index in 'ans'.
        int row = 0;
        int col = 0;

        // Step 4: Iterate through the 1D 'original' array.
        // For each element in 'original', place it into the 'ans' array
        // at the current (row, col) position.
        for (int i = 0; i < original.size(); i++) {
            // Place the current element from 'original' into 'ans'.
            ans[row][col] = original[i];

            // Move to the next column in the current row.
            col++;

            // If 'col' reaches 'n', it means the current row is full.
            // Reset 'col' to 0 to start a new row, and increment 'row'.
            if (col == n) {
                col = 0;
                row++;
            }
        }

        // Step 5: Return the constructed 2D array.
        return ans;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(original.size()) or O(m * n) | We iterate through the `original` array exactly once. Each operation inside the loop (assignment, increment, comparison) takes constant time. |
| **Space** | O(m * n) | We create a new 2D array `ans` of size `m x n` to store the result. This space is proportional to the output size. |

## 🔗 Related Problems
- 59. Spiral Matrix II
- 48. Rotate Image
- 73. Set Matrix Zeroes