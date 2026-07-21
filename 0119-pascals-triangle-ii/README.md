# 0119-pascals-triangle-ii

## 📋 Problem Description
Given an integer `rowIndex`, the task is to return the `rowIndex`-th (0-indexed) row of Pascal's Triangle. In Pascal's Triangle, each number is the sum of the two numbers directly above it. The triangle starts with a single '1' at the top (row 0), and each subsequent row begins and ends with '1'.

The function should accept an integer `rowIndex` as input and return a `std::vector<int>` representing the elements of the specified row.

## 🔍 Examples
```
Input: rowIndex = 3
Output: [1,3,3,1]
Explanation:
Row 0: [1]
Row 1: [1,1]
Row 2: [1,2,1]
Row 3: [1,3,3,1]

Input: rowIndex = 0
Output: [1]
Explanation: This is the first row (0-indexed) of Pascal's Triangle.

Input: rowIndex = 1
Output: [1,1]
Explanation: This is the second row (0-indexed) of Pascal's Triangle.
```

## 📌 Constraints
*   `0 <= rowIndex <= 33`

## 🤔 Understanding the Problem
The problem asks us to generate a specific row of Pascal's Triangle. Pascal's Triangle is a triangular array of binomial coefficients where each number is the sum of the two numbers directly above it. The edges of the triangle are always 1s. The main challenge is to efficiently compute the elements of the target row, as each element depends on elements from the previous row. We need to handle base cases like `rowIndex = 0` and `rowIndex = 1` correctly.

## 💡 Core Idea
The fundamental property of Pascal's Triangle is that each element (except the ones at the edges) is the sum of the two elements directly above it. This allows us to construct each row iteratively, building upon the values calculated in the previous row.

## 🧠 Approach — Dynamic Programming
This problem is a classic application of Dynamic Programming. We can observe that the calculation of the current row `i` depends entirely on the values of the previous row `i-1`. This exhibits the characteristics of overlapping subproblems and optimal substructure, making Dynamic Programming a suitable approach. We store all previously computed rows, and when calculating a new row, we simply look up the necessary values from the last stored row.

## 📝 Step-by-Step Algorithm
1.  Initialize an empty `vector<vector<int>>` called `result` to store all generated rows of Pascal's Triangle.
2.  Iterate with a loop variable `i` from `0` up to `rowIndex` (inclusive). This loop will generate each row of the triangle.
    a.  Inside the loop, create a new `vector<int>` named `row` for the current `i`-th row. This row will have `i + 1` elements.
    b.  Initialize all elements of this `row` to `1`. This correctly sets the first and last elements of every row, as they are always `1` in Pascal's Triangle.
    c.  If `i` is greater than `1` (meaning we are not on the 0th or 1st row, which are trivial), iterate with a nested loop variable `j` from `1` up to `i - 1`.
        i.  For each `j`, calculate `row[j]` by summing the two elements directly above it in the *previous* row. These elements are `result[i-1][j-1]` and `result[i-1][j]`.
    d.  After constructing the `row`, add it to the `result` vector.
3.  Once the outer loop completes, the `result` vector will contain all rows of Pascal's Triangle from row 0 up to `rowIndex`.
4.  Finally, extract the `rowIndex`-th row from `result` (i.e., `result[rowIndex]`) and return it. The provided solution creates a new `ans` vector and copies elements into it before returning.

## 💻 Solution
```cpp
class Solution {
public:
    vector<int> getRow(int rowIndex) {
   
        // 'result' will store all generated rows of Pascal's Triangle up to 'rowIndex'.
        // This is a vector of vectors, where each inner vector represents a row.
        vector<vector<int>> result;

        // Iterate from row 0 up to 'rowIndex' (inclusive) to generate each row.
        for (int i = 0; i <= rowIndex; i++) {
            // Create a new 'row' vector for the current 'i'-th row.
            // It will have 'i + 1' elements.
            // Initialize all elements to 1. This handles the edges of Pascal's Triangle
            // (the first and last elements of every row are always 1).
            vector<int> row(i + 1, 1); 
            
            // For rows greater than 1 (i.e., i > 1), calculate the inner elements.
            // The first element (row[0]) and last element (row[i]) are already correctly set to 1.
            // We iterate from the second element (index 1) up to the second-to-last element (index i-1).
            for(int j = 1; j < i; j++){
                // Each element in the current row is the sum of the two elements directly above it
                // in the previous row (which is stored at result[i-1]).
                // Specifically, row[j] = element at (previous row, current column - 1) + element at (previous row, current column).
                row[j] = result[i-1][j-1] + result[i-1][j];
            }
            // Add the newly constructed 'row' to our 'result' collection.
            result.push_back(row);
        }
        
        // After the loop, 'result' contains all rows from 0 to 'rowIndex'.
        // We need to return the 'rowIndex'-th row.
        // The problem asks for a vector<int> as output, so we create one to hold the final answer.
        vector<int> ans;

        // Copy elements from result[rowIndex] into the 'ans' vector.
        // The size of result[rowIndex] is rowIndex + 1.
        for(int i = 0; i < rowIndex + 1; i++){
            ans.push_back(result[rowIndex][i]);
        }
        
        // Note: A more concise way to return the row would be 'return result[rowIndex];'
        // as result[rowIndex] is already a vector<int>. The explicit copy loop is functional but redundant.

        // Return the final 'rowIndex'-th row.
        return ans;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(rowIndex^2) | The outer loop runs `rowIndex + 1` times. The inner loop runs `i` times for each `i`. The total number of operations is proportional to the sum `0 + 1 + ... + rowIndex`, which simplifies to `O(rowIndex^2)`. |
| **Space** | O(rowIndex^2) | We store all rows from 0 to `rowIndex` in the `result` vector. The `i`-th row has `i + 1` elements. The total number of elements stored is `1 + 2 + ... + (rowIndex + 1)`, which is `O(rowIndex^2)`. |

## 🔗 Related Problems
- 118. Pascal's Triangle
- 70. Climbing Stairs
- 509. Fibonacci Number