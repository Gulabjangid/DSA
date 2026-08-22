# 2022-convert-1d-array-into-2d-array

## 📋 Problem Description
You are given a 0-indexed 1-dimensional (1D) integer array `original`, and two integers, `m` and `n`. Your task is to create a 2-dimensional (2D) array with `m` rows and `n` columns using **all** the elements from `original`.

The elements from indices `0` to `n - 1` (inclusive) of `original` should form the first row of the constructed 2D array. The elements from indices `n` to `2 * n - 1` (inclusive) should form the second row, and so on. This means elements are taken sequentially from the 1D array to fill the 2D array row by row.

Return an `m x n` 2D array constructed according to the above procedure. If it is impossible to construct such a 2D array (i.e., the number of elements in `original` does not match `m * n`), return an empty 2D array.

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
It is impossible to fit 2 elements into a 1x1 2D array, which only holds 1 element. Thus, an empty 2D array is returned.
```

## 📌 Constraints
*   `1 <= original.length <= 5 * 10^4`
*   `1 <= original[i] <= 10^5`
*   `1 <= m, n <= 4 * 10^4`

## 🤔 Understanding the Problem
The problem asks us to reshape a 1D array into a 2D array of specified dimensions `m` rows and `n` columns. The crucial part is that the elements must be placed in a specific, sequential order: the first `n` elements from the 1D array form the first row of the 2D array, the next `n` elements form the second row, and so on. A key edge case to handle is when the total number of elements in the `original` array (`original.size()`) does not exactly match the total capacity of the target 2D array (`m * n`). In such a scenario, it's impossible to use all elements or fill the array completely, so an empty 2D array must be returned.

## 💡 Core Idea
The core idea is to directly simulate the process of filling the 2D array. We iterate through the 1D `original` array and place each element into the correct `(row, col)` position in the new 2D array, incrementing the column and then the row as needed. A preliminary check for array size compatibility is essential to handle impossible cases.

## 🧠 Approach — Direct Simulation / Array Manipulation
This problem can be solved using a **Direct Simulation / Array Manipulation** approach. This pattern is suitable because the problem explicitly defines a straightforward, deterministic mapping from the 1D array elements to specific positions in the 2D array. There's no complex logic, searching, or optimization required beyond simply following the given rules for populating the matrix. We iterate through the input array once and populate the output array according to the specified row-major order.

## 📝 Step-by-Step Algorithm
1.  Get the total number of elements in the `original` 1D array. Let's call this `len`.
2.  Perform an initial check: If `m * n` (the total number of elements required for the 2D array) is not equal to `len`, it means it's impossible to construct the 2D array using all elements from `original`. In this case, immediately return an empty 2D array.
3.  If the sizes match (`m * n == len`), proceed to construct the 2D array.
4.  Initialize an `m x n` 2D integer array, let's call it `ans`, which will store our result.
5.  Initialize two integer variables: `currentRow` to `0` and `currentCol` to `0`. These will keep track of the current position where an element should be placed in the `ans` array.
6.  Iterate through the `original` array using a loop from index `i = 0` up to `len - 1`.
7.  Inside the loop, for each element `original[i]`:
    a.  Place `original[i]` into the `ans` array at the position `ans[currentRow][currentCol]`.
    b.  Increment `currentCol` to move to the next column in the current row.
    c.  After incrementing `currentCol`, check if `currentCol` has become equal to `n`. If it has, it means the current row (`currentRow`) is now full.
        i.  If `currentCol == n`, reset `currentCol` back to `0` to start from the beginning of the next row.
        ii. Increment `currentRow` to move to the next row.
8.  After the loop finishes, all elements from `original` will have been placed into `ans`. Return the constructed `ans` 2D array.

## 💻 Solution
```cpp
class Solution {
public:
    vector<vector<int>> construct2DArray(vector<int>& original, int m, int n) {
        // Step 1 & 2: Initial check for feasibility.
        // The total number of elements in 'original' must exactly match
        // the total capacity of the target 2D array (m * n).
        if (m * n != original.size()) {
            // If they don't match, it's impossible to construct the array
            // as specified, so return an empty 2D array.
            return {};
        }

        // Step 3 & 4: Initialize the 2D array.
        // Create a 2D vector 'ans' with 'm' rows and 'n' columns.
        // All elements will be default-initialized (e.g., to 0 for integers).
        vector<vector<int>> ans(m, vector<int>(n));

        // Step 5: Initialize row and column pointers for the 'ans' 2D array.
        // These pointers will track where the next element from 'original' should go.
        int currentRow = 0;
        int currentCol = 0;

        // Step 6: Iterate through each element of the 'original' 1D array.
        for (int i = 0; i < original.size(); i++) {
            // Step 7a: Place the current element from 'original' into 'ans'
            // at the position indicated by 'currentRow' and 'currentCol'.
            ans[currentRow][currentCol] = original[i];

            // Step 7b: Move to the next column in the current row.
            currentCol++;

            // Step 7c: Check if the current row is full.
            // If 'currentCol' has reached 'n', it means we've filled all 'n' columns
            // for the 'currentRow'.
            if (currentCol == n) {
                // Step 7ci: Reset 'currentCol' to 0 to start from the beginning of the next row.
                currentCol = 0;
                // Step 7cii: Move to the next row.
                currentRow++;
            }
        }
        // Step 8: After iterating through all elements, the 'ans' 2D array is fully constructed.
        // Return the constructed 2D array.
        return ans;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(m * n) | We iterate through each of the `original.size()` elements exactly once. Since `original.size()` must equal `m * n` for a valid construction, the time complexity is linear with respect to the total number of elements in the resulting 2D array. |
| **Space** | O(m * n) | We create a new 2D array `ans` of size `m x n` to store the result. This space is directly proportional to the size of the output. |

## 🔗 Related Problems
- 59. Spiral Matrix II
- 867. Transpose Matrix
- 1252. Cells with Odd Values in a Matrix