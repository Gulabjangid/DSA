# 0118-pascals-triangle

## 📋 Problem Description
Given an integer `numRows`, the task is to generate the first `numRows` rows of Pascal's triangle. In Pascal's triangle, each number is the sum of the two numbers directly above it. The function should return a `vector<vector<int>>` representing the generated triangle.

## 🔍 Examples
```
Input: numRows = 5
Output: [[1],[1,1],[1,2,1],[1,3,3,1],[1,4,6,4,1]]
Explanation:
Row 0: [1]
Row 1: [1,1]
Row 2: [1,2,1] (1+1=2)
Row 3: [1,3,3,1] (1+2=3, 2+1=3)
Row 4: [1,4,6,4,1] (1+3=4, 3+3=6, 3+1=4)
```

```
Input: numRows = 1
Output: [[1]]
Explanation: Only the first row is requested.
```

## 📌 Constraints
*   `1 <= numRows <= 30`

## 🤔 Understanding the Problem
The problem asks us to construct Pascal's triangle up to a specified number of rows. The fundamental rule is that any number within the triangle (not on the edges) is the sum of the two numbers directly above it. The numbers on the edges of each row are always 1. We need to generate all these rows and store them in a 2D data structure. The main challenge is correctly applying the sum rule while also handling the boundary conditions (the '1's at the start and end of each row) for every row.

## 💡 Core Idea
The core idea is to build the triangle row by row, leveraging the inherent property that each element (except the ones at the edges) is the sum of the two elements directly above it from the *previous* row. This allows us to construct the current row efficiently once the previous row is known.

## 🧠 Approach — Iterative Construction / Dynamic Programming (Bottom-Up)
This problem is best solved using an iterative construction approach, which can also be viewed as a form of dynamic programming (bottom-up). We build the solution for `numRows` by first generating the first row, then the second, and so on, up to the desired `numRows`. Each new row is computed directly from the previously generated row. This pattern is efficient because we avoid redundant calculations; once a row is computed, it's stored and used as a building block for the next row. This approach naturally handles the dependencies between rows.

## 📝 Step-by-Step Algorithm
1.  Initialize an empty 2D vector (e.g., `vector<vector<int>> result`) which will store all the rows of Pascal's triangle.
2.  Start a loop that iterates `numRows` times. Let `i` be the current row index, starting from 0.
3.  Inside the loop, for each `i`:
    a.  Create a new 1D vector (e.g., `vector<int> currentRow`) of size `i + 1`. This is because the `i`-th row (0-indexed) has `i + 1` elements.
    b.  Initialize all elements of `currentRow` to 1. This conveniently sets the first element (`currentRow[0]`) and the last element (`currentRow[i]`) to 1, as they are always 1 in Pascal's triangle.
    c.  If `i` is greater than 1 (meaning we are not on the first or second row, which are `[1]` and `[1,1]` respectively, and are already correctly initialized), iterate from `j = 1` up to `i - 1`. This loop covers the elements *between* the first and last '1's.
    d.  For each `j`, calculate `currentRow[j]` by summing the element directly above it and the element to its left in the *previous* row. Specifically, `currentRow[j]` will be `result[i - 1][j - 1] + result[i - 1][j]`.
    e.  After filling all elements of `currentRow`, add `currentRow` to the `result` 2D vector.
4.  After the loop finishes, return the `result` 2D vector containing the complete Pascal's triangle.

## 💻 Solution
```cpp
class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        // Initialize a 2D vector to store all rows of Pascal's triangle.
        // This will be our final result.
        vector<vector<int>> result;

        // Iterate 'numRows' times to generate each row of the triangle.
        // 'i' represents the current row index (0-indexed).
        for (int i = 0; i < numRows; i++) {
            // Create a new vector for the current row.
            // A row 'i' has 'i + 1' elements.
            // Initialize all elements to 1. This correctly sets the first and last elements
            // of every row to 1, as they are always 1 in Pascal's triangle.
            vector<int> row(i + 1, 1);

            // Calculate the inner elements of the current row.
            // We only need to do this if the row has more than 2 elements (i.e., i > 1).
            // For i=0 (row [1]) and i=1 (row [1,1]), all elements are already 1.
            // 'j' iterates from the second element (index 1) up to the second-to-last element (index i-1).
            for (int j = 1; j < i; j++) {
                // The value of an element in Pascal's triangle is the sum of the two elements
                // directly above it in the previous row.
                // 'result[i - 1]' refers to the previous row.
                // 'result[i - 1][j - 1]' is the element directly above and to the left.
                // 'result[i - 1][j]' is the element directly above.
                row[j] = result[i - 1][j - 1] + result[i - 1][j];
            }

            // Add the newly generated row to our result.
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
| **Time** | O(numRows^2) | We iterate `numRows` times. In each iteration `i`, we create a row of size `i+1` and then iterate `i-1` times to fill its inner elements. The total number of operations is proportional to the sum `1 + 2 + ... + numRows`, which is `numRows * (numRows + 1) / 2`, simplifying to O(numRows^2). |
| **Space** | O(numRows^2) | We store all `numRows` rows. The `i`-th row contains `i+1` integers. The total number of integers stored is `1 + 2 + ... + numRows`, which is `numRows * (numRows + 1) / 2`, simplifying to O(numRows^2). |

## 🔗 Related Problems
- 119. Pascal's Triangle II
- 70. Climbing Stairs
- 509. Fibonacci Number