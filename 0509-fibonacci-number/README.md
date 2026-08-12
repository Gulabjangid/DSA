# 0509-fibonacci-number

## 📋 Problem Description
The Fibonacci numbers, denoted `F(n)`, form a sequence where each number is the sum of the two preceding ones, starting from `0` and `1`.
The sequence is defined as follows:
*   `F(0) = 0`
*   `F(1) = 1`
*   `F(n) = F(n - 1) + F(n - 2)`, for `n > 1`.

Given an integer `n`, the task is to calculate and return the `n`-th Fibonacci number, `F(n)`.

## 🔍 Examples
```
Input: n = 2
Output: 1
Explanation: F(2) = F(1) + F(0) = 1 + 0 = 1.
```

```
Input: n = 3
Output: 2
Explanation: F(3) = F(2) + F(1) = 1 + 1 = 2.
```

```
Input: n = 4
Output: 3
Explanation: F(4) = F(3) + F(2) = 2 + 1 = 3.
```

## 📌 Constraints
*   `0 <= n <= 30`

## 🤔 Understanding the Problem
This problem asks us to compute a specific term in the Fibonacci sequence based on its mathematical definition. The core of the problem lies in correctly implementing the recursive relationship `F(n) = F(n - 1) + F(n - 2)`. We need to pay special attention to the base cases for `n=0` and `n=1`, as these are the starting points for the sequence and terminate the recursion. While the problem seems straightforward due to the explicit definition, a naive recursive implementation can be inefficient for larger `n` due to repeated calculations, though for the given constraint `n <= 30`, it typically passes.

## 💡 Core Idea
The most direct approach is to translate the mathematical definition of the Fibonacci sequence, including its base cases and recursive relation, directly into code.

## 🧠 Approach — Recursion
The problem statement itself provides a recursive definition for the Fibonacci sequence: `F(n) = F(n - 1) + F(n - 2)`. This makes recursion a natural and intuitive pattern to apply. We can define a function `fib(n)` that directly calls itself for `fib(n-1)` and `fib(n-2)`. The base cases `F(0) = 0` and `F(1) = 1` serve as the stopping conditions for the recursion, preventing infinite loops and providing the initial values to build up the sequence.

## 📝 Step-by-Step Algorithm
1.  **Handle Base Case 1:** If the input `n` is `0`, the Fibonacci number `F(0)` is `0`. Immediately return `0`.
2.  **Handle Base Case 2:** If the input `n` is `1`, the Fibonacci number `F(1)` is `1`. Immediately return `1`.
3.  **Recursive Step:** If `n` is greater than `1`, calculate `F(n)` by recursively calling the `fib` function for `n-1` and `n-2`, and then summing their results. That is, return `fib(n - 1) + fib(n - 2)`.

## 💻 Solution
```cpp
class Solution {
public:
    int fib(int n) {
        // Base case 1: F(0) is defined as 0.
        // This is the first stopping condition for our recursion.
        if (n == 0) {
            return 0;
        }
        // Base case 2: F(1) is defined as 1.
        // This is the second stopping condition for our recursion.
        if (n == 1) {
            return 1;
        }
        // Recursive step: For n > 1, F(n) is the sum of the two preceding numbers.
        // We call the fib function for n-1 and n-2 and add their results.
        // This directly implements the recurrence relation F(n) = F(n-1) + F(n-2).
        return fib(n - 1) + fib(n - 2);
    }
};

```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(2^n) | Each call to `fib(n)` makes two recursive calls, leading to an exponential growth in the number of function calls. Many subproblems (e.g., `fib(2)`) are recomputed multiple times. |
| **Space** | O(n) | The maximum depth of the recursion stack can go up to `n` (e.g., `fib(n)` calls `fib(n-1)`, which calls `fib(n-2)`, and so on, until `fib(0)` or `fib(1)` is reached). |

*Note: For the given constraint `n <= 30`, this exponential time complexity is acceptable because `2^30` is roughly 1 billion, but the actual number of operations is closer to `phi^n` (where `phi` is the golden ratio, approx 1.618), which for `n=30` is about 1.6 million, making it feasible within typical time limits.*

## 🔗 Related Problems
- 70. Climbing Stairs
- 1137. N-th Tribonacci Number
- 746. Min Cost Climbing Stairs