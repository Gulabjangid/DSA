# 0342-power-of-four

## 📋 Problem Description
Given an integer `n`, determine if it is a power of four. An integer `n` is considered a power of four if there exists an integer `x` such that `n` is equal to 4 raised to the power of `x` (i.e., `n == 4^x`). The function should return `true` if `n` is a power of four, and `false` otherwise.

## 🔍 Examples
```
Input: n = 16
Output: true
Explanation: 16 can be expressed as 4^2.
```

```
Input: n = 5
Output: false
Explanation: 5 cannot be expressed as 4 raised to an integer power.
```

```
Input: n = 1
Output: true
Explanation: 1 can be expressed as 4^0.
```

## 📌 Constraints
*   `-2^31 <= n <= 2^31 - 1`

## 🤔 Understanding the Problem
The problem asks us to verify if a given integer `n` is a perfect power of 4. This means `n` must be a positive integer that can be obtained by raising 4 to some non-negative integer exponent (e.g., 4^0=1, 4^1=4, 4^2=16, 4^3=64, etc.). We need to handle edge cases such as `n=1`, negative numbers, and zero, none of which are typically considered powers of four in this context (except for 1).

## 💡 Core Idea
A positive integer `n` is a power of four if and only if it is 1, or it is strictly greater than 1, divisible by 4, and `n/4` is also a power of four. This recursive property allows us to repeatedly divide `n` by 4 until it either becomes 1 (indicating it's a power of four) or fails a condition.

## 🧠 Approach — Recursion
This problem is an excellent candidate for a recursive approach because the definition of a "power of four" can be expressed in terms of itself for a smaller value. If a number `n` is a power of four, then `n/4` must also be a power of four (unless `n` is 1, which is the base case). This self-referential nature allows us to break down the problem into smaller, identical subproblems until we reach a simple, directly solvable base case.

## 📝 Step-by-Step Algorithm
1.  **Handle Invalid Inputs and Base Case 1**: Check if `n` is less than or equal to 0. Powers of four are always positive, so if `n` falls into this range, it cannot be a power of four. Immediately return `false`.
2.  **Handle Base Case 2**: Check if `n` is equal to 1. Since 4^0 = 1, `n=1` is a power of four. Immediately return `true`.
3.  **Check Divisibility**: If `n` has not been handled by the above base cases, it must be a positive integer greater than 1. For `n` to be a power of four, it must be perfectly divisible by 4. If `n` modulo 4 is not 0 (i.e., `n % 4 != 0`), then `n` cannot be a power of four. Return `false`.
4.  **Recursive Step**: If `n` passes all the above checks (it's positive, not 1, and divisible by 4), then we know that if `n` is a power of four, `n/4` must also be a power of four. Therefore, recursively call the `isPowerOfFour` function with `n / 4` and return its result. This process continues until one of the base cases (1 or <=0) or the divisibility check is met.

## 💻 Solution
```cpp
class Solution {
public:
    bool isPowerOfFour(int n) {
        // Step 1: Handle invalid inputs.
        // Powers of four must be positive. 0 and negative numbers cannot be powers of four.
        if (n <= 0) {
            return false;
        }
        
        // Step 2: Handle base case for 4^0.
        // 1 is a power of four (4^0).
        if (n == 1) {
            return true;
        }
        
        // Step 3: Check divisibility.
        // If n is not 1 and not perfectly divisible by 4, it cannot be a power of four.
        // For example, 5, 6, 7, 9, 10, 11, etc., would fail this check.
        if (n % 4 != 0) {
            return false;
        }
        
        // Step 4: Recursive step.
        // If n is positive, greater than 1, and divisible by 4,
        // then recursively check if n/4 is a power of four.
        // This continues until n eventually becomes 1 (true) or fails a divisibility check (false).
        return isPowerOfFour(n / 4);        
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(log₄ n) | In each recursive call, the value of `n` is divided by 4. The number of divisions required to reach 1 from `n` is proportional to `log₄ n`. |
| **Space** | O(log₄ n) | The recursive calls consume stack space. The maximum depth of the recursion stack is proportional to `log₄ n`. |

## 🔗 Related Problems
- 231. Power of Two
- 326. Power of Three