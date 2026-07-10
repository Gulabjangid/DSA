# 0074-search-a-2d-matrix

## 📋 Problem Description
You are given an `m x n` integer matrix with two special properties:
1. Each row is sorted in non-decreasing order from left to right.
2. The first integer of each row is greater than the last integer of the previous row.

Given an integer `target`, your task is to determine if `target` exists within the `matrix`. You must return `true` if it's found, and `false` otherwise.

The solution must have a time complexity of `O(log(m * n))`.

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

```
Input: matrix = [[1]], target = 1
Output: true
Explanation: The target '1' is present in the single-element matrix.
```

## 📌 Constraints
*   `m == matrix.length` (number of rows)
*   `n == matrix[i].length` (number of columns)
*   `1 <= m, n <= 100`
*   `-10^4 <= matrix[i][j], target <= 10^4`

## 🤔 Understanding the Problem
The problem asks us to efficiently find a `target` value in a 2D matrix. The key to solving this efficiently lies in the two given properties: rows are sorted, and the first element of a row is greater than the last element of the previous row. These properties imply that if we were to flatten the entire matrix into a single 1D array, that array would also be sorted. This strong ordering suggests that a linear scan (which would be `O(m*n)`) is not optimal, and we should aim for a logarithmic time complexity.

## 💡 Core Idea
The core idea is to leverage the fully sorted nature of the matrix (conceptually, if flattened) to apply binary search. Since the matrix is sorted both row-wise and across rows, we can use binary search to first pinpoint the correct row where the target *might* exist, and then use another binary search to find the target within that specific row.

## 🧠 Approach — Binary Search (Two-Phase)
This problem is a classic application of **Binary Search**. The reason this pattern fits perfectly is due to the highly sorted nature of the matrix. The two properties (rows sorted, and first element of a row greater than the last of the previous) essentially mean that the entire matrix, when viewed as a single sequence of numbers, is sorted. This allows us to eliminate large portions of the search space in logarithmic time. We can perform a binary search on the rows to find the correct row, and then a second binary search on the elements within that row.

## 📝 Step-by-Step Algorithm

1.  **Initialize Row Search Boundaries**: Set `str` (start row) to `0` and `enr` (end row) to `m-1` (where `m` is the number of rows).
2.  **Binary Search for the Correct Row**:
    *   While `str` is less than or equal to `enr`:
        *   Calculate `mid` row index: `mid = str + (enr - str) / 2`.
        *   **Check if target is in the current `mid` row's range**:
            *   If `target` is greater than or equal to the first element of `matrix[mid]` (`matrix[mid][0]`) AND `target` is less than or equal to the last element of `matrix[mid]` (`matrix[mid][n-1]`):
                *   This means the `target` *could* be in this row. Proceed to step 3 (binary search within this row).
        *   **Adjust row search boundaries**:
            *   If `target` is less than `matrix[mid][0]`:
                *   The target must be in an earlier row (if it exists). Update `enr = mid - 1`.
            *   Else (if `target` is greater than `matrix[mid][n-1]`):
                *   The target must be in a later row (if it exists). Update `str = mid + 1`.
3.  **Binary Search within the Identified Row**:
    *   If a potential row was found in step 2 (i.e., the `target` falls within its range), perform a standard binary search on that specific row (`matrix[mid]`).
    *   Initialize `st` (start column) to `0` and `end` (end column) to `n-1` (where `n` is the number of columns).
    *   While `st` is less than or equal to `end`:
        *   Calculate `midr` (middle column index): `midr = st + (end - st) / 2`.
        *   **Compare `matrix[mid][midr]` with `target`**:
            *   If `matrix[mid][midr]` equals `target`:
                *   The target is found. Return `true`.
            *   If `matrix[mid][midr]` is less than `target`:
                *   The target must be in the right half of the current search space. Update `st = midr + 1`.
            *   Else (`matrix[mid][midr]` is greater than `target`):
                *   The target must be in the left half of the current search space. Update `end = midr - 1`.
4.  **Target Not Found**: If the binary search for rows completes without finding a suitable row, or if the binary search within a row completes without finding the target, return `false`.

## 💻 Solution
```cpp
class Solution {
public:
    // Helper function to perform binary search within a specific row
    bool search(vector<vector<int>>& mat, int target, int mid_row_idx) {
        // 'mid_row_idx' is the index of the row we need to search in.
        // 'mat[mid_row_idx]' is the actual row (a 1D vector).

        int st = 0; // Start index for column search
        int end = mat[mid_row_idx].size() - 1; // End index for column search

        // Standard binary search loop
        while (st <= end) {
            int mid_col_idx = st + (end - st) / 2; // Calculate middle column index to prevent overflow

            // Check if the element at the middle column is our target
            if (mat[mid_row_idx][mid_col_idx] == target) {
                return true; // Target found in this row
            }
            // If the middle element is less than target, search in the right half
            else if (mat[mid_row_idx][mid_col_idx] < target) {
                st = mid_col_idx + 1;
            }
            // If the middle element is greater than target, search in the left half
            else {
                end = mid_col_idx - 1;
            }
        }
        return false; // Target not found in this row
    }

    // Main function to search for the target in the 2D matrix
    bool searchMatrix(vector<vector<int>>& mat, int target) {
        int m = mat.size(); // Number of rows
        if (m == 0) return false; // Handle empty matrix case
        int n = mat[0].size(); // Number of columns
        if (n == 0) return false; // Handle empty rows case

        int str = 0; // Start index for row search
        int enr = m - 1; // End index for row search

        // Binary search to find the correct row where the target might reside
        while (str <= enr) {
            int mid_row_idx = str + (enr - str) / 2; // Calculate middle row index

            // Check if the target falls within the range of values in the current middle row.
            // Due to the matrix properties, if target is in the matrix, it must be in this row
            // if it's between the first and last elements of this row.
            if (target >= mat[mid_row_idx][0] && target <= mat[mid_row_idx][n - 1]) {
                // Target is potentially in this row, so perform a binary search within this row
                return search(mat, target, mid_row_idx);
            }
            // If target is less than the first element of the current row,
            // it must be in an earlier row (if it exists).
            else if (target < mat[mid_row_idx][0]) {
                enr = mid_row_idx - 1;
            }
            // If target is greater than the last element of the current row,
            // it must be in a later row (if it exists).
            else {
                str = mid_row_idx + 1;
            }
        }

        // If the loop finishes, it means no suitable row was found where the target could exist.
        return false;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(log(m * n)) | The algorithm performs two binary searches: one on `m` rows (O(log m)) and another on `n` columns (O(log n)). The total time is O(log m + log n), which simplifies to O(log(m * n)). |
| **Space** | O(1) | The solution uses a constant amount of extra space for variables like `str`, `enr`, `mid`, etc., regardless of the input matrix size. |

## 🔗 Related Problems
- 240. Search a 2D Matrix II
- 162. Find Peak Element
- 33. Search in Rotated Sorted Array