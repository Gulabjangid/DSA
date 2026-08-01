# 0326-power-of-three

## 📋 Problem Description
Given an integer `n`, determine if it is a power of three. An integer `n` is considered a power of three if there exists an integer `x` such that `n` is equal to `3` raised to the power of `x` (i.e., `n == 3^x`). The function should return `true` if `n` is a power of three, and `false` otherwise.

## 🔍 Examples
```
Input: n = 27
Output: true
Explanation: 27 = 3^3
```

```
Input: n = 0
Output: false
Explanation: There is no integer x such that 3^x = 0.
```

```
Input: n = -1
Output: false
Explanation: There is no integer x such that 3^x = -1. Powers of three are always positive.
```

## 📌 Constraints
*   `-2^31 <= n <= 2^31 - 1`

## 🤔 Understanding the Problem
The problem asks us to verify if a given integer `n` can be perfectly represented as 3 multiplied by itself some number of times. This means `n` must be a positive integer, and if we repeatedly divide `n` by 3, we should eventually reach 1. We need to be careful with edge cases like `n` being zero, negative, or one. Zero and negative numbers can never be powers of three, as `3^x` is always positive for any integer `x`. The number 1 is a power of three (`3^0`).

## 💡 Core Idea
A positive integer `n` is a power of three if and only if it is divisible by 3, and the result of that division (`n / 3`) is also a power of three. The ultimate base case for this property is the number 1, which is `3^0`.

## 🧠 Approach — Recursion
This problem is a classic candidate for a **recursive** approach. The definition of a "power of three" can be broken down into a smaller, similar subproblem. If `n` is a power of three, then `n` must be divisible by 3, and `n/3` must also be a power of three. This self-referential property makes recursion a very natural fit. We define a base case (when `n` is 1) and a recursive step that reduces the problem size (`n` becomes `n/3`).

## 📝 Step-by-Step Algorithm
1.  **Handle Non-Positive Numbers**: First, check if the input integer `n` is less than or equal to 0. Since any integer power of 3 (e.g., 3^0=1, 3^1=3, 3^-1=1/3) will always result in a positive value, `n` cannot be a power of three if it's 0 or negative. In this case, immediately return `false`.
2.  **Base Case (n = 1)**: Next, check if `n` is equal to 1. The number 1 is `3^0`, which is a power of three. If `n` is 1, return `true`. This is our stopping condition for the recursion.
3.  **Check Divisibility by 3**: If `n` is positive but not 1, we need to check if it's a candidate for being a power of three. A number that is a power of three must be perfectly divisible by 3. If `n` modulo 3 is not 0 (i.e., `n % 3 != 0`), then `n` is not divisible by 3 and therefore cannot be a power of three. In this case, return `false`.
4.  **Recursive Step**: If `n` has passed all the above checks (it's positive, not 1, and divisible by 3), then its status as a power of three depends entirely on whether `n / 3` is also a power of three. Recursively call the `isPowerOfThree` function with `n / 3` as the new input. The result of this recursive call will be the final answer for the current `n`.

## 💻 Solution
```cpp
class Solution {
public:
    bool isPowerOfThree(int n) {
        // Step 1: Handle non-positive numbers.
        // Powers of three are always positive (3^x > 0 for any integer x).
        // So, if n is 0 or negative, it cannot be a power of three.
        if (n <= 0) {
            return false;
        }
        
        // Step 2: Base case.
        // 1 is 3^0, which is a power of three. This is our stopping condition.
        if (n == 1) {
            return true;
        }
        
        // Step 3: Check divisibility.
        // If n is a power of three (and not 1), it must be perfectly divisible by 3.
        // If n % 3 is not 0, then n is not a power of three.
        if (n % 3 != 0) {
            return false;
        }
        
        // Step 4: Recursive call.
        // If n is positive, not 1, and divisible by 3,
        // then it is a power of three if and only if n/3 is also a power of three.
        // We recursively call the function with n/3 to continue the check.
        return isPowerOfThree(n / 3);        
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(log₃ N) | In each recursive call, the input `n` is divided by 3. The number of divisions required to reach 1 is proportional to `log₃ N`. |
| **Space** | O(log₃ N) | The space complexity is determined by the maximum depth of the recursion stack. Since `n` is divided by 3 in each step, the stack depth will be `log₃ N`. |

## 🔗 Related Problems
- 231. Power of Two
- 342. Power of Four
- 50. Pow(x, n)