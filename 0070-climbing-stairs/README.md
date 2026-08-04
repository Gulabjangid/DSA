# 0070-climbing-stairs

## 📋 Problem Description
You are presented with a staircase that has `n` steps. Your goal is to climb to the top. In each move, you have two options: you can either climb 1 step or 2 steps. The problem asks you to determine the total number of *distinct ways* you can climb to the top of the staircase.

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
This problem asks us to count all unique sequences of 1-step and 2-step climbs that sum up to `n` steps. The key here is "distinct ways," meaning the order of steps matters (e.g., 1+2 is different from 2+1). This immediately suggests a combinatorial counting problem rather than just finding a single path. The constraint `n <= 45` hints that a solution with polynomial time complexity, possibly linear, would be efficient enough, while exponential solutions might be too slow unless heavily optimized.

## 💡 Core Idea
The number of ways to reach a particular step `i` can be determined by considering the last step taken. To reach step `i`, you must have either taken a 1-step from step `i-1` or a 2-step from step `i-2`. This forms a recurrence relation: `ways(i) = ways(i-1) + ways(i-2)`, which is the definition of the Fibonacci sequence.

## 🧠 Approach — Dynamic Programming
This problem is a classic example of Dynamic Programming.

**Why Dynamic Programming?**
1.  **Optimal Substructure**: The problem can be broken down into smaller, overlapping subproblems. The number of ways to reach step `n` depends on the number of ways to reach step `n-1` and step `n-2`. The solution to the larger problem is built from solutions to these smaller subproblems.
2.  **Overlapping Subproblems**: If we were to solve this recursively without memoization, we would repeatedly calculate the number of ways to reach the same intermediate steps multiple times. For example, to find `ways(5)`, we need `ways(4)` and `ways(3)`. To find `ways(4)`, we need `ways(3)` and `ways(2)`. Notice `ways(3)` is computed twice. Dynamic Programming avoids these redundant calculations by storing the results of subproblems.

The specific approach used in the solution is an iterative, bottom-up Dynamic Programming approach, further optimized to use constant space.

## 📝 Step-by-Step Algorithm
1.  **Handle Base Cases**:
    *   If `n` is 1, there's only one way to climb (take 1 step). Return 1.
    *   If `n` is 2, there are two ways to climb (1 step + 1 step, or 2 steps). Return 2.
    *   These base cases are crucial for the recurrence relation.

2.  **Initialize Variables for DP**:
    *   For `n > 2`, we need to compute the number of ways iteratively. We can observe that `ways(i)` only depends on `ways(i-1)` and `ways(i-2)`. Therefore, we don't need an entire array; we only need to keep track of the last two computed values.
    *   Initialize `a` to represent `ways(1)`, which is 1.
    *   Initialize `b` to represent `ways(2)`, which is 2.

3.  **Iterate and Compute**:
    *   Start a loop from `i = 3` up to `n` (inclusive). This loop calculates the number of ways for each step from 3 to `n`.
    *   Inside the loop, for each step `i`:
        *   Calculate `c` (the number of ways to reach the current step `i`) as the sum of `a` (ways to reach `i-2`) and `b` (ways to reach `i-1`). So, `c = a + b`.
        *   Update `a`: The previous `b` (ways to reach `i-1`) now becomes the "second-to-last" value for the next iteration. So, set `a = b`.
        *   Update `b`: The newly calculated `c` (ways to reach `i`) now becomes the "last" value for the next iteration. So, set `b = c`.

4.  **Return Result**:
    *   After the loop completes, `b` will hold the total number of distinct ways to reach step `n`. Return `b`.

## 💻 Solution
```cpp
class Solution {
public:
    int climbStairs(int n) {
        // Base cases:
        // If n = 1, there's only one way: (1 step)
        // If n = 2, there are two ways: (1 step + 1 step), (2 steps)
        // The problem constraints guarantee n >= 1.
        if (n <= 2) {
            return n;
        }

        // For n > 2, we can observe a Fibonacci-like pattern.
        // Let dp[i] be the number of ways to reach step i.
        // To reach step i, you can either:
        // 1. Take 1 step from step i-1.
        // 2. Take 2 steps from step i-2.
        // So, dp[i] = dp[i-1] + dp[i-2].

        // We can optimize space by only storing the last two values.
        // 'a' will store dp[i-2] (number of ways to reach step i-2)
        // 'b' will store dp[i-1] (number of ways to reach step i-1)

        int a = 1; // Corresponds to dp[1] - 1 way to reach step 1
        int b = 2; // Corresponds to dp[2] - 2 ways to reach step 2

        // Iterate from the 3rd step up to n
        // For each step 'i', we calculate dp[i] based on dp[i-1] and dp[i-2]
        for (int i = 3; i <= n; i++) {
            // 'c' will store dp[i] (number of ways to reach current step i)
            // It's the sum of ways to reach step i-1 (stored in 'b') and i-2 (stored in 'a')
            int c = a + b;

            // Update 'a' to become the previous 'b'
            // This means 'a' now holds dp[i-1] for the next iteration
            a = b;

            // Update 'b' to become the current 'c'
            // This means 'b' now holds dp[i] for the next iteration
            b = c;
        }

        // After the loop, 'b' will hold the number of ways to reach step 'n'.
        return b;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(n) | The algorithm iterates through a single loop from `i = 3` to `n`, performing a constant number of operations in each iteration. |
| **Space** | O(1) | The algorithm uses a fixed number of variables (`a`, `b`, `c`) regardless of the input `n`, thus requiring constant extra space. |

## 🔗 Related Problems
*   509. Fibonacci Number
*   746. Min Cost Climbing Stairs
*   1137. N-th Tribonacci Number