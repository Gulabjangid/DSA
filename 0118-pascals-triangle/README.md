# 0118-pascals-triangle

## 📋 Problem Description
Given an integer `numRows`, the task is to generate the first `numRows` rows of Pascal's Triangle.

In Pascal's Triangle, each number is the sum of the two numbers directly above it. The edges of the triangle (the first and last numbers in each row) are always 1.

The function should receive an integer `numRows` as input and return a `vector<vector<int>>` representing the generated Pascal's Triangle.

## 🔍 Examples
```
Input: numRows = 5
Output: [[1],[1,1],[1,2,1],[1,3,3,1],[1,4,6,4,1]]

Input: numRows = 1
Output: [[1]]
```

## 📌 Constraints
*   `1 <= numRows <= 30`

## 🤔 Understanding the Problem
The problem asks us to construct Pascal's Triangle up to a specified number of rows. The core rule is that any number inside the triangle is the sum of the two numbers directly above it. The numbers on the "edges" of the triangle (the very first and very last number in each row) are always 1. This means we need to iteratively build the triangle, where each new row depends on the values from the previous row. The first row is simply `[1]`.

## 💡 Core Idea
The key insight is that each row of Pascal's Triangle can be generated directly from the values of the immediately preceding row. We can build the triangle row by row, starting from the first row and using the rule that `current_element = element_above_left + element_above_right`.

## 🧠 Approach — Iterative Construction (Dynamic Programming)
This problem is a classic example of **Iterative Construction**, which is a form of **Dynamic Programming (Bottom-Up)**. We build the solution for `numRows` by first solving for `1` row, then `2` rows, and so on, up to `numRows`. Each step (generating a new row) leverages the results from the previous step (the previously generated row). This pattern fits perfectly because the value of an element in the current row is solely dependent on elements in the previous row, allowing us to build the triangle incrementally.

## 📝 Step-by-Step Algorithm
1.  Initialize an empty list of lists (or `vector<vector<int>>` in C++) to store the entire Pascal's Triangle. This will be our `result`.
2.  Iterate from `i = 0` up to `numRows - 1` (where `i` represents the current row index we are trying to build).
    a.  For each `i`, create a new list (or `vector<int>`) to represent the current row. This row will have `i + 1` elements.
    b.  Initialize all elements of this new row to `1`. This correctly sets the first and last elements of every row to `1`.
    c.  If `i` is greater than or equal to 2 (meaning we are building the third row or beyond), we need to calculate the inner elements:
        i.  Iterate from `j = 1` up to `i - 1` (these are the indices for the elements between the first and last `1`s).
        ii. For each `j`, calculate the value of `row[j]` using the rule: `row[j] = result[i - 1][j - 1] + result[i - 1][j]`. This means the current element is the sum of the element directly above it and to its left, and the element directly above it and to its right, from the *previous* row (`result[i - 1]`).
    d.  After constructing the current row, add it to our `result` list.
3.  After the loop finishes, `result` will contain all `numRows` of Pascal's Triangle. Return `result`.

## 💻 Solution
```cpp
class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        // This vector of vectors will store the entire Pascal's Triangle.
        // Each inner vector represents a row.
        vector<vector<int>> result;

        // Iterate 'numRows' times to generate each row of the triangle.
        // 'i' represents the current row index (0-indexed).
        for (int i = 0; i < numRows; i++) {
            // Create a new vector for the current row.
            // A row 'i' has 'i + 1' elements.
            // Initialize all elements to 1. This correctly sets the first and last elements
            // of every row to 1, as per Pascal's Triangle rules.
            vector<int> row(i + 1, 1);

            // Calculate the inner elements of the current row.
            // The first and last elements are already 1, so we iterate from j=1 up to i-1.
            // This loop only runs for rows with at least 3 elements (i.e., i >= 2).
            for (int j = 1; j < i; j++) {
                // The core rule of Pascal's Triangle:
                // An element is the sum of the two elements directly above it in the previous row.
                // 'result[i - 1]' refers to the previous row.
                // 'result[i - 1][j - 1]' is the element above and to the left.
                // 'result[i - 1][j]' is the element directly above and to the right.
                row[j] = result[i - 1][j - 1] + result[i - 1][j];
            }

            // Add the newly constructed row to our overall result.
            result.push_back(row);
        }

        // Return the complete Pascal's Triangle.
        return result;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(numRows^2) | The outer loop runs `numRows` times. The inner loop runs `i` times for each `i`. The total number of operations is proportional to the sum `1 + 2 + ... + numRows`, which is `numRows * (numRows + 1) / 2`, simplifying to O(numRows^2). |
| **Space** | O(numRows^2) | The `result` vector stores `numRows` rows. The `i`-th row contains `i+1` elements. The total number of elements stored is `1 + 2 + ... + numRows`, which is `numRows * (numRows + 1) / 2`, simplifying to O(numRows^2). |

## 🔗 Related Problems
- 119. Pascal's Triangle II
- 509. Fibonacci Number
- 70. Climbing Stairs