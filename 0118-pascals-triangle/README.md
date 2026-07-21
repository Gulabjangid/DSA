# 0118-pascals-triangle

## 📋 Problem Description
Given an integer `numRows`, the task is to generate the first `numRows` of Pascal's triangle. In Pascal's triangle, each number is the sum of the two numbers directly above it. The triangle starts with a single '1' at the top, and each subsequent row begins and ends with '1'.

The function `generate` receives one integer, `numRows`, as input. It must return a `vector<vector<int>>` representing the first `numRows` of Pascal's triangle.

## 🔍 Examples
```
Input: numRows = 5
Output: [[1],[1,1],[1,2,1],[1,3,3,1],[1,4,6,4,1]]
Explanation:
Row 0: [1]
Row 1: [1,1]
Row 2: [1, (1+1), 1] = [1,2,1]
Row 3: [1, (1+2), (2+1), 1] = [1,3,3,1]
Row 4: [1, (1+3), (3+3), (3+1), 1] = [1,4,6,4,1]
```

```
Input: numRows = 1
Output: [[1]]
Explanation: Only the first row is requested.
```

## 📌 Constraints
*   `1 <= numRows <= 30`

## 🤔 Understanding the Problem
The problem asks us to construct Pascal's triangle up to a specified number of rows. The key characteristic of Pascal's triangle is its additive property: every number (except the ones at the edges) is the sum of the two numbers directly above it in the previous row. The edges of every row are always 1. This means to build any given row, we need access to the elements of the row immediately preceding it. The problem is non-trivial because it requires careful iteration and management of previous results to construct the current result.

## 💡 Core Idea
The fundamental insight is the recursive relationship within Pascal's triangle: `triangle[row][col] = triangle[row-1][col-1] + triangle[row-1][col]`. We can build the triangle row by row, using the previously computed row to generate the current one.

## 🧠 Approach — Iterative Construction with Dynamic Programming Principles
This problem is best solved using an **Iterative Construction** approach, which aligns with **Dynamic Programming** principles. We build the solution from the bottom up. Each row of Pascal's triangle can be computed directly from the values in the previous row. This exhibits the "optimal substructure" property (the solution to the larger problem depends on solutions to smaller subproblems) and "overlapping subproblems" (though here it's more direct dependency on the immediate prior subproblem), making DP a natural fit. We simply iterate `numRows` times, generating one row at a time and storing it, then using it for the next iteration.

## 📝 Step-by-Step Algorithm
1.  Initialize an empty list of lists (or `vector<vector<int>>` in C++) called `result` to store the entire Pascal's triangle.
2.  Start a loop that iterates `i` from `0` up to `numRows - 1`. This loop represents the current row number we are trying to construct.
3.  Inside this loop, for each `i`:
    a.  Create a new list (or `vector<int>`) called `currentRow`. This row will have `i + 1` elements.
    b.  Initialize all elements of `currentRow` to `1`. This handles the fact that the first and last elements of every row in Pascal's triangle are always `1`.
    c.  Now, iterate `j` from `1` up to `i - 1`. This inner loop calculates the values for the elements *between* the first and last `1`s.
        *   For `i = 0` (first row) and `i = 1` (second row), this inner loop will not execute, which is correct as these rows only contain `1`s.
    d.  Inside the inner loop (for `j`):
        *   Set `currentRow[j]` to the sum of the element directly above it and the element to its left in the previous row. Specifically, `currentRow[j] = result[i - 1][j - 1] + result[i - 1][j]`. `result[i - 1]` refers to the previously computed row.
    e.  After the inner loop completes (or if it didn't run), `currentRow` is fully constructed. Add `currentRow` to our `result` list.
4.  After the outer loop finishes, `result` will contain all `numRows` of Pascal's triangle. Return `result`.

## 💻 Solution
```cpp
class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        // This vector of vectors will store the entire Pascal's triangle.
        // Each inner vector represents a row.
        vector<vector<int>> result;

        // Iterate 'numRows' times to generate each row of the triangle.
        // 'i' represents the current row index (0-indexed).
        for (int i = 0; i < numRows; i++) {
            // Create a new vector for the current row.
            // A row 'i' has 'i + 1' elements.
            // Initialize all elements to 1. This correctly sets the first and last elements
            // of every row to 1, and also handles the first two rows (i=0, i=1) entirely.
            vector<int> row(i + 1, 1);

            // Calculate the inner elements of the current row.
            // This loop runs from the second element (index 1) up to the second-to-last element (index i-1).
            // It will not run for i=0 (row 0: [1]) or i=1 (row 1: [1,1]) as they have no inner elements.
            for (int j = 1; j < i; j++) {
                // The core rule of Pascal's triangle:
                // An element is the sum of the two elements directly above it in the previous row.
                // result[i - 1] gives us the previous row.
                // result[i - 1][j - 1] is the element directly above and to the left.
                // result[i - 1][j] is the element directly above and to the right.
                row[j] = result[i - 1][j - 1] + result[i - 1][j];
            }

            // Add the newly constructed row to our result triangle.
            result.push_back(row);
        }

        // Return the complete Pascal's triangle.
        return result;
    }
};

```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(numRows^2) | The outer loop runs `numRows` times. The inner loop runs `i` times for each row `i`. The total number of operations is proportional to the sum `1 + 2 + ... + numRows`, which is `numRows * (numRows + 1) / 2`, simplifying to O(numRows^2). |
| **Space** | O(numRows^2) | We store all elements of the Pascal's triangle. The `k`-th row has `k+1` elements. The total number of elements stored is `1 + 2 + ... + numRows`, which is `numRows * (numRows + 1) / 2`, simplifying to O(numRows^2). |

## 🔗 Related Problems
- 119. Pascal's Triangle II
- 62. Unique Paths
- 70. Climbing Stairs