# 0074-search-a-2d-matrix

## 📋 Problem Description
You are given an `m x n` integer matrix with two special properties:
1.  Each row is sorted in non-decreasing order (elements are arranged from smallest to largest).
2.  The first integer of each row is strictly greater than the last integer of the previous row.

Given this matrix and an integer `target`, your task is to determine if the `target` value exists within the matrix. You must return `true` if the `target` is found, and `false` otherwise.

The solution must achieve an `O(log(m * n))` time complexity.

## 🔍 Examples
```
Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 3
Output: true
Explanation: The target '3' is present in the first row of the matrix.
```

```
Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 13
Output: false
Explanation: The target '13' is not present in the matrix.
```

## 📌 Constraints
*   `m == matrix.length` (number of rows)
*   `n == matrix[i].length` (number of columns)
*   `1 <= m, n <= 100`
*   `-10^4 <= matrix[i][j], target <= 10^4`

## 🤔 Understanding the Problem
The problem asks us to find a specific `target` value in a 2D matrix that has a very specific sorted structure. Not only are individual rows sorted, but the rows themselves are "sorted" relative to each other. This means that if you were to flatten the entire matrix into a single 1D array, it would be completely sorted. This crucial property is what makes the problem non-trivial and hints at a highly efficient search algorithm, specifically one that can leverage sorted data. The `O(log(m * n))` time complexity requirement further reinforces this idea.

## 💡 Core Idea
The key insight is that due to the two sorted properties (rows sorted, and first element of a row > last element of previous row), the entire `m x n` matrix can be conceptually treated as a single, flattened 1D sorted array of `m * n` elements. This allows us to apply binary search, which is ideal for searching in sorted data structures, to achieve the required logarithmic time complexity.

## 🧠 Approach — Binary Search
This problem is a classic application of **Binary Search**.
The reason this pattern fits perfectly is because of the two strong sorted properties of the matrix. Each row is sorted, and critically, the first element of any row is greater than the last element of the preceding row. This implies that if you were to concatenate all rows, you would get a single, perfectly sorted 1D array. Binary search is the most efficient algorithm for searching in sorted data, providing a logarithmic time complexity, which directly matches the `O(log(m * n))` requirement. We can perform two binary searches: one to find the correct row, and another to find the element within that row.

## 📝 Step-by-Step Algorithm

1.  **First Binary Search (Row Search):**
    *   Initialize `str` (start row index) to `0` and `enr` (end row index) to `m - 1` (where `m` is the number of rows).
    *   Enter a `while` loop that continues as long as `str <= enr`.
    *   Inside the loop, calculate the `mid` row index: `mid = str + (enr - str) / 2`. This prevents potential integer overflow compared to `(str + enr) / 2`.
    *   Compare the `target` with the first and last elements of the `mid`-th row:
        *   If `target` is greater than or equal to `mat[mid][0]` (the first element of the `mid` row) AND `target` is less than or equal to `mat[mid][n-1]` (the last element of the `mid` row), it means the `target` *could* be in this `mid` row. At this point, we've narrowed down the search to a single row. Proceed to step 2 (Second Binary Search) on this specific row.
        *   If `target` is less than `mat[mid][0]`, it means the `target` must be in a row *before* the `mid` row (if it exists). So, update `enr = mid - 1`.
        *   If `target` is greater than `mat[mid][n-1]`, it means the `target` must be in a row *after* the `mid` row (if it exists). So, update `str = mid + 1`.
    *   If the `while` loop finishes without finding a suitable row (i.e., the target was not within the range of any row), it means the `target` is not in the matrix. Return `false`.

2.  **Second Binary Search (Column Search within the identified Row):**
    *   This step is called if the first binary search successfully identifies a potential row. Let's say this row is `mat[row_index]`.
    *   Initialize `st` (start column index) to `0` and `end` (end column index) to `n - 1` (where `n` is the number of columns).
    *   Enter a `while` loop that continues as long as `st <= end`.
    *   Inside the loop, calculate the `midr` (mid column index): `midr = st + (end - st) / 2`.
    *   Compare `mat[row_index][midr]` with the `target`:
        *   If `mat[row_index][midr] == target`, we found the `target`. Return `true`.
        *   If `mat[row_index][midr] < target`, the `target` must be in the right half of the current search space within this row. Update `st = midr + 1`.
        *   If `mat[row_index][midr] > target`, the `target` must be in the left half of the current search space within this row. Update `end = midr - 1`.
    *   If this `while` loop finishes without finding the `target` in the specified row, it means the `target` is not in that row. Return `false`.

## 💻 Solution

```cpp
class Solution {
public:
    // Helper function to perform binary search on a single row
    // 'mat' is the entire matrix, 'target' is the value to find,
    // 'mid' is the index of the row to search within.
    bool search(vector<vector<int>>& mat, int target, int mid) {
        // Initialize start and end pointers for binary search within the row
        int st = 0;
        int end = mat[mid].size() - 1; // 'mat[mid].size()' gives the number of columns in this row

        // Perform standard binary search
        while (st <= end) {
            // Calculate the middle index to avoid potential integer overflow
            int midr = st + (end - st) / 2;

            // Check if the element at midr is the target
            if (mat[mid][midr] == target) {
                return true; // Target found
            }
            // If target is greater, search in the right half
            else if (mat[mid][midr] < target) {
                st = midr + 1;
            }
            // If target is smaller, search in the left half
            else {
                end = midr - 1;
            }
        }
        return false; // Target not found in this row
    }

    // Main function to search for target in the 2D matrix
    bool searchMatrix(vector<vector<int>>& mat, int target) {
        // Get the dimensions of the matrix
        int m = mat.size();    // Number of rows
        int n = mat[0].size(); // Number of columns (assuming matrix is not empty and rows have same length)

        // Initialize start and end pointers for binary search on rows
        int str = 0; // Start row index
        int enr = m - 1; // End row index

        // Perform binary search to find the correct row
        while (str <= enr) {
            // Calculate the middle row index
            int mid = str + (enr - str) / 2;

            // Check if the target falls within the range of the current 'mid' row
            // This means target >= first element of mid row AND target <= last element of mid row
            if (target >= mat[mid][0] && target <= mat[mid][n - 1]) {
                // If it does, perform a binary search within this specific row
                return search(mat, target, mid);
            }
            // If target is smaller than the first element of the 'mid' row,
            // it must be in an earlier row (if it exists).
            else if (target < mat[mid][0]) {
                enr = mid - 1;
            }
            // If target is larger than the last element of the 'mid' row,
            // it must be in a later row (if it exists).
            else {
                str = mid + 1;
            }
        }

        // If the loop finishes, it means no suitable row was found,
        // so the target is not in the matrix.
        return false;
    }
};

```

## ⏱️ Complexity Analysis

| | Complexity | Reason |
|---|---|---|
| **Time** | O(log(m * n)) | The first binary search takes O(log m) time to find the correct row. The second binary search takes O(log n) time to find the element within that row. The total time is O(log m + log n), which simplifies to O(log(m * n)). |
| **Space** | O(1) | The solution uses a constant amount of extra space for variables (pointers, mid indices) regardless of the input matrix size. |

## 🔗 Related Problems
- 704. Binary Search
- 33. Search in Rotated Sorted Array
- 162. Find Peak Element