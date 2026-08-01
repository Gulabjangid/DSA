# 0342-power-of-four

## 📋 Problem Description
Given an integer `n`, determine if it is a power of four. An integer `n` is considered a power of four if there exists an integer `x` such that `n` is equal to 4 raised to the power of `x` (i.e., `n == 4^x`). The function should return `true` if `n` is a power of four, and `false` otherwise.

## 🔍 Examples
```
Input: n = 16
Output: true
Explanation: 16 is 4^2.
```
```
Input: n = 5
Output: false
Explanation: 5 cannot be expressed as 4 raised to any integer power.
```
```
Input: n = 1
Output: true
Explanation: 1 is 4^0.
```

## 📌 Constraints
*   `-2^31 <= n <= 2^31 - 1`

## 🤔 Understanding the Problem
The problem asks us to check if a given integer `n` belongs to the sequence 1, 4, 16, 64, 256, ... (i.e., 4^0, 4^1, 4^2, 4^3, 4^4, ...). We need to consider edge cases such as negative numbers and zero, which are not powers of four, and the number 1, which is 4^0. The core challenge is to efficiently verify this property for any given integer within the specified range.

## 💡 Core Idea
A positive integer `n` is a power of four if and only if it is 1, or it is divisible by 4 and `n/4` is also a power of four. This recursive definition allows us to break down the problem into smaller, identical subproblems.

## 🧠 Approach — Recursion
This problem is well-suited for a **Recursive** approach. The definition of a power of four naturally lends itself to recursion: if a number `n` is a power of four, then `n/4` must also be a power of four (unless `n` itself is 1). This recursive property allows us to repeatedly divide the number by 4 until we reach a base case. The base cases are when `n` becomes 1 (meaning it was a power of four) or when `n` is no longer divisible by 4 or becomes non-positive (meaning it was not a power of four).

## 📝 Step-by-Step Algorithm
1.  **Handle Non-Positive Numbers**: Check if the input integer `n` is less than or equal to 0. Powers of four are always positive integers (1, 4, 16, ...). If `n <= 0`, it cannot be a power of four, so immediately return `false`.
2.  **Base Case - 1**: Check if `n` is equal to 1. The number 1 is considered a power of four (specifically, 4^0). If `n == 1`, return `true`.
3.  **Check Divisibility by 4**: If `n` is greater than 1 but not equal to 1, check if `n` is perfectly divisible by 4. If `n % 4 != 0`, it means `n` cannot be formed by multiplying 4s, and thus cannot be a power of four. In this case, return `false`.
4.  **Recursive Step**: If `n` has passed all the above checks (i.e., it's positive, not 1, and divisible by 4), then its "power of four" status depends entirely on `n / 4`. Recursively call the `isPowerOfFour` function with `n / 4` as the new input and return its result. This process continues until one of the base cases (1, non-positive, or not divisible by 4) is met.

## 💻 Solution
```cpp
class Solution {
public:
    bool isPowerOfFour(int n) {
        // Step 1: Handle non-positive numbers.
        // Powers of four must be positive (1, 4, 16, ...).
        // 0 and negative numbers are not powers of four.
        if (n <= 0) {
            return false;
        }
        // Step 2: Base case - 1.
        // 1 is a power of four (4^0 = 1).
        if (n == 1) {
            return true;
        }
        // Step 3: Check divisibility by 4.
        // If n is not 1 and not divisible by 4, it cannot be a power of four.
        // For example, 5, 6, 7, 9, 10, 11, etc., would fail this check.
        if (n % 4 != 0) {
            return false;
        }
        // Step 4: Recursive step.
        // If n is positive, not 1, and divisible by 4,
        // then it is a power of four if and only if n/4 is also a power of four.
        // We recursively call the function with n/4.
        return isPowerOfFour(n / 4);        
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(log4(n)) | In each recursive call, the input `n` is divided by 4. The number of divisions required to reduce `n` to 1 is proportional to `log4(n)`. |
| **Space** | O(log4(n)) | The space complexity is determined by the maximum depth of the recursion stack. Since there are `log4(n)` recursive calls, the stack depth will be `log4(n)`. |

## 🔗 Related Problems
*   231. Power of Two
*   326. Power of Three