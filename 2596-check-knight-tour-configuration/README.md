# 2596-check-knight-tour-configuration

## 📋 Problem Description
This problem, LeetCode 2662, asks us to verify if a given `n x n` integer matrix `grid` represents a valid knight's tour configuration on a chessboard.

A valid knight's tour must adhere to the following rules:
1.  The knight starts at the top-left cell of the board, which is `(0, 0)`.
2.  The knight visits every cell on the board exactly once.
3.  The `grid[row][col]` value indicates the `grid[row][col]`-th cell that the knight visited. Moves are 0-indexed, meaning the starting cell `(0,0)` must contain the value `0`.
4.  Each subsequent move (e.g., from cell `k` to cell `k+1`) must be a valid knight's move. A knight's move consists of moving two squares vertically and one square horizontally, or two squares horizontally and one square vertically (an "L" shape). There are 8 possible moves from any given cell.

The function `checkValidGrid` receives an `n x n` integer matrix `grid` as input. It must return `true` if `grid` represents a valid knight's tour configuration, and `false` otherwise.

## 🔍 Examples
```
Input: grid = [[0,11,16,5,20],[17,4,19,10,15],[12,1,8,21,6],[3,18,23,14,9],[24,13,2,7,22]]
Output: true
Explanation: The diagram shows that the knight starts at (0,0) with 0, then moves to (2,1) with 1, then (4,2) with 2, and so on, following valid knight moves until all cells are visited.
```

```
Input: grid = [[0,3,6],[5,8,1],[2,7,4]]
Output: false
Explanation: The knight starts at (0,0) with 0. It moves to (2,1) with 1. Then to (0,2) with 2. Then to (0,1) with 3. Then to (2,2) with 4. Then to (0,0) with 5. Then to (2,0) with 6. Then to (1,2) with 7. The 8th move should be to the cell containing 8, which is (1,1). However, (1,1) is not a valid knight's move from (1,2). Thus, the configuration is invalid.
```

## 📌 Constraints
*   `n == grid.length == grid[i].length`
*   `3 <= n <= 7`
*   `0 <= grid[row][col] < n * n`
*   All integers in `grid` are **unique**.

## 🤔 Understanding the Problem
The problem is not asking us to *find* a knight's tour, but rather to *verify* if a given `grid` represents a pre-defined valid tour. This means the `grid` itself dictates the sequence of moves: `grid[r1][c1] = k` and `grid[r2][c2] = k+1` implies the knight moved from `(r1, c1)` to `(r2, c2)` as its `(k+1)`-th move. The core challenge is to systematically check if each step in this sequence is a valid knight's move and if the tour starts correctly and visits all cells. The constraints on `n` are small (`n` up to 7), meaning the total number of cells (`n*n`) is at most 49, which suggests that solutions with complexity related to `N*N` (where `N` is `n*n`) would be efficient enough.

## 💡 Core Idea
The key insight is that since the `grid` explicitly tells us the order of moves (from `0` to `n*n-1`), we can simulate the knight's tour step by step. We start at the cell containing `0` (which must be `(0,0)`) and then for each subsequent move `k+1`, we find the cell containing `k+1` and verify that it is a valid knight's move away from the cell that contained `k`.

## 🧠 Approach — Depth-First Search (DFS)
This problem can be elegantly solved using a Depth-First Search (DFS) approach. DFS is suitable here because we are essentially traversing a path (the knight's tour) and at each step, we need to verify if the next expected move is valid.

The DFS function will recursively check if the current cell `(row, col)` holds the `currentMoveValue` and, if so, if it's possible to make a valid knight's move to a cell that holds `currentMoveValue + 1`. This recursive structure naturally explores the path defined by the grid values. The small constraints on `n` ensure that the maximum recursion depth (`n*n`) is manageable.

## 📝 Step-by-Step Algorithm
1.  **Define Knight's Moves**: Create two arrays, `dr` and `dc`, to represent the 8 possible changes in row and column for a knight's move. For example:
    *   `dr = {-2, -2, -1, -1, 1, 1, 2, 2}`
    *   `dc = {1, -1, 2, -2, 2, -2, 1, -1}`
2.  **Helper Recursive Function `isValidTour(grid, n, currentRow, currentCol, currentMoveValue)`**:
    *   **Base Case 1 (Invalid Cell or Value)**:
        *   First, check if `currentRow` or `currentCol` are out of bounds (i.e., `< 0` or `>= n`). If so, this path is invalid, return `false`.
        *   Next, check if the value at `grid[currentRow][currentCol]` is *not* equal to `currentMoveValue`. This means the knight did not make the `currentMoveValue`-th move to this cell as expected by the tour configuration. If so, return `false`.
    *   **Base Case 2 (Tour Complete)**:
        *   If `currentMoveValue` is equal to `(n * n) - 1` (which is the last move, as moves are 0-indexed), it means we have successfully verified all moves up to the last one. The tour is valid from this point. Return `true`.
    *   **Recursive Step**: If neither base case is met, it means we are at `grid[currentRow][currentCol] == currentMoveValue`, and it's not the last move. We need to find the cell for `currentMoveValue + 1`.
        *   Initialize a boolean variable `foundNextMove = false`.
        *   Iterate through all 8 possible knight moves using the `dr` and `dc` arrays:
            *   Calculate `nextRow = currentRow + dr[i]` and `nextCol = currentCol + dc[i]`.
            *   Recursively call `isValidTour(grid, n, nextRow, nextCol, currentMoveValue + 1)`.
            *   If this recursive call returns `true`, it means we found a valid path for the next step. Set `foundNextMove = true` and immediately `break` the loop (since we only need one valid next step to continue the tour).
        *   Return `foundNextMove`.
3.  **Main Function `checkValidGrid(grid)`**:
    *   Get the size of the grid, `n = grid.size()`.
    *   The problem states that a valid tour must start at `(0,0)` with value `0`. Therefore, initiate the verification by calling `isValidTour(grid, n, 0, 0, 0)`. The result of this call is the final answer.

## 💻 Solution
```cpp
class Solution {
public:
    // Helper function to recursively validate the knight's tour
    // grid: The n x n chessboard configuration
    // n: The size of the board
    // row, col: Current coordinates of the knight
    // val: The expected value (move number) at the current (row, col)
    bool isvalid(vector<vector<int>>& grid, int n, int row, int col, int val) {
        // Base Case 1: Check for invalid conditions
        // 1. Out of bounds: If the current row or column is outside the board
        // 2. Incorrect value: If grid[row][col] does not match the expected 'val'
        if (row >= n || row < 0 || col >= n || col < 0 || grid[row][col] != val) {
            return false; // This path is invalid
        }

        // Base Case 2: Tour completion
        // If 'val' is the last move (n*n - 1), it means we have successfully
        // verified all moves up to the end of the tour.
        if (val == (n * n) - 1) {
            return true; // The tour is valid
        }
        
        // Recursive Step: Explore all 8 possible knight moves from the current position
        // We need to find if any of these moves lead to the cell containing 'val + 1'
        // and continue a valid tour.

        // Define knight's move offsets (dr for row changes, dc for column changes)
        // These arrays represent the 8 possible L-shaped moves
        int dr[] = {-2, -2, -1, -1, 1, 1, 2, 2};
        int dc[] = {1, -1, 2, -2, 2, -2, 1, -1};

        // Iterate through all 8 possible moves
        for (int i = 0; i < 8; ++i) {
            int nextRow = row + dr[i];
            int nextCol = col + dc[i];
            // Recursively call isvalid for the next expected move (val + 1)
            // If this recursive call returns true, it means a valid path was found
            // for the subsequent moves. We can immediately return true.
            if (isvalid(grid, n, nextRow, nextCol, val + 1)) {
                return true;
            }
        }

        // If none of the 8 possible moves from (row, col) lead to a valid
        // cell containing 'val + 1', then this path is invalid.
        return false;
    }

    // Main function to check if the given grid represents a valid knight's tour
    bool checkValidGrid(vector<vector<int>>& grid) {
        int n = grid.size(); // Get the size of the board

        // According to the problem statement, a valid knight's tour must
        // start at cell (0,0) and this cell must contain the value 0.
        // We initiate the recursive validation from this starting point.
        return isvalid(grid, n, 0, 0, 0);
    }
};

```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N^2) | The `isvalid` function is called for each `val` from `0` to `n*n-1`. In each call, it iterates through 8 possible knight moves. Since the `grid[row][col] != val` check ensures that the recursion effectively follows a single path (the one defined by the grid values), the total number of "successful" recursive calls is `n*n`. Each such call involves 8 constant-time checks. Therefore, the total time complexity is proportional to `n*n * 8`, which simplifies to O(N^2) where N is the number of cells (`n*n`). |
| **Space** | O(N^2) | The recursion depth can go up to `n*n` (the total number of cells in the tour). Each recursive call adds a frame to the call stack. Thus, the space complexity is proportional to the maximum depth of the recursion, which is O(N^2) where N is the number of cells (`n*n`). |

## 🔗 Related Problems
- 79. Word Search
- 329. Longest Increasing Path in a Matrix
- 671. Knight Dialer