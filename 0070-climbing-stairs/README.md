# 0070-climbing-stairs

## 📋 Problem Description
You are presented with a staircase that has `n` steps to reach its top. Your task is to determine the total number of distinct ways you can climb to the top. Each time you can choose to climb either 1 step or 2 steps.

The function `climbStairs` receives an integer `n`, representing the total number of steps in the staircase. It must return an integer, which is the count of distinct ways to reach the top.

## 🔍 Examples
```
Input: n = 2
Output: 2
Explanation: There are two distinct ways to climb to the top:
1. 1 step + 1 step
2. 2 steps
```

```
Input: n = 3
Output: 3
Explanation: There are three distinct ways to climb to the top:
1. 1 step + 1 step + 1 step
2. 1 step + 2 steps
3. 2 steps + 1 step
```

## 📌 Constraints
*   `1 <= n <= 45`

## 🤔 Understanding the Problem
The problem asks us to count the number of unique sequences of 1-step and 2-step climbs that sum up to `n` steps. This is not about permutations of a fixed set of steps (e.g., if we had two 1s and one 2, how many ways to arrange them), but rather about finding all possible sequences of 1s and 2s that sum to `n`. The order of steps matters (e.g., 1+2 is different from 2+1). This structure often hints at a recursive or dynamic programming solution, as the number of ways to reach `n` steps depends on the number of ways to reach previous steps.

## 💡 Core Idea
The key insight is that to reach the `n`-th step, you must have come from either the `(n-1)`-th step (by taking a 1-step climb) or the `(n-2)`-th step (by taking a 2-step climb). Therefore, the total number of ways to reach `n` steps is the sum of the ways to reach `(n-1)` steps and the ways to reach `(n-2)` steps. This forms a recurrence relation similar to the Fibonacci sequence.

## 🧠 Approach — Dynamic Programming (Iterative / Bottom-Up)
This problem is a classic example of Dynamic Programming. The pattern fits because it exhibits both **optimal substructure** (the optimal solution for `n` steps can be constructed from optimal solutions for `n-1` and `n-2` steps) and **overlapping subproblems** (the number of ways to reach a certain step `k` might be needed multiple times when calculating ways for `k+1` and `k+2`). By calculating the number of ways for smaller `n` values first and storing them, we can efficiently build up to the solution for the desired `n`, avoiding redundant calculations.

## 📝 Step-by-Step Algorithm
1.  **Handle Base Cases**:
    *   If `n` is 1, there's only one way: (1 step).
    *   If `n` is 2, there are two ways: (1 step + 1 step) or (2 steps).
    *   These base cases are crucial for the recurrence relation to start.

2.  **Initialize Variables**:
    *   Let `a` represent the number of ways to reach step `i-2`. Initialize `a = 1` (ways to reach step 1).
    *   Let `b` represent the number of ways to reach step `i-1`. Initialize `b = 2` (ways to reach step 2).

3.  **Iterate and Calculate**:
    *   Start a loop from `i = 3` up to `n`. This loop will calculate the number of ways for each step from 3 to `n`.
    *   In each iteration `i`:
        *   Calculate `c = a + b`. This `c` represents the number of ways to reach the current step `i`. It's the sum of ways to reach `i-2` (represented by `a`) and ways to reach `i-1` (represented by `b`).
        *   Update `a` to `b`. For the next iteration (`i+1`), the previous `i-1` (which was `b`) will become the new `i-2`.
        *   Update `b` to `c`. For the next iteration (`i+1`), the current `i` (which was `c`) will become the new `i-1`.

4.  **Return Result**:
    *   After the loop completes, `b` will hold the total number of distinct ways to reach step `n`. Return `b`.

## 💻 Solution
```cpp
class Solution {
public:
    int climbStairs(int n) {
        // Base cases:
        // If n = 1, there's only 1 way: (1)
        // If n = 2, there are 2 ways: (1+1), (2)
        if (n <= 2) {
            return n;
        }

        // Initialize variables to store the number of ways for the previous two steps.
        // 'a' will store ways to reach step (i-2)
        // 'b' will store ways to reach step (i-1)
        int a = 1; // Represents ways to reach step 1
        int b = 2; // Represents ways to reach step 2

        // Iterate from step 3 up to n
        for (int i = 3; i <= n; i++) {
            // 'c' calculates the number of ways to reach the current step 'i'.
            // This is the sum of ways to reach (i-1) and ways to reach (i-2).
            int c = a + b;
            
            // Update 'a' and 'b' for the next iteration:
            // The number of ways to reach (i-1) now becomes the 'a' for step (i+1).
            a = b;
            // The number of ways to reach 'i' now becomes the 'b' for step (i+1).
            b = c;
        }

        // After the loop, 'b' holds the total number of ways to reach step 'n'.
        return b;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(n) | The loop runs `n-2` times (from `i=3` to `n`). Each iteration involves a constant number of operations (addition, assignment). |
| **Space** | O(1) | Only a fixed number of variables (`a`, `b`, `c`, `i`) are used, regardless of the input `n`. No additional data structures are allocated. |

## 🔗 Related Problems
- 509. Fibonacci Number
- 746. Min Cost Climbing Stairs
- 198. House Robber