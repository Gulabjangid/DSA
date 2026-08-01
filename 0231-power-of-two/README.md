# 0231-power-of-two

## 📋 Problem Description
Given an integer `n`, determine if it is a power of two. An integer `n` is considered a power of two if there exists an integer `x` such that `n` is equal to 2 raised to the power of `x` (i.e., `n == 2^x`). The function should return `true` if `n` is a power of two, and `false` otherwise.

## 🔍 Examples
```
Input: n = 1
Output: true
Explanation: 2^0 = 1
```
```
Input: n = 16
Output: true
Explanation: 2^4 = 16
```
```
Input: n = 3
Output: false
Explanation: 3 cannot be expressed as 2 raised to an integer power.
```

## 📌 Constraints
*   `-2^31 <= n <= 2^31 - 1`

## 🤔 Understanding the Problem
The problem asks us to identify if a given integer `n` is a number that can be obtained by raising 2 to some non-negative integer power (e.g., 2^0=1, 2^1=2, 2^2=4, 2^3=8, etc.). This means `n` must always be a positive integer. Numbers like 0, negative integers, or positive integers that are not perfectly divisible by 2 until they reach 1 (like 3, 5, 6, 7, etc.) are not powers of two. The key is to check if `n` can be repeatedly divided by 2 until it becomes 1.

## 💡 Core Idea
A positive integer `n` is a power of two if and only if it is perfectly divisible by 2 (unless `n=1`), and the result of that division (`n/2`) is also a power of two. This recursive definition provides a straightforward way to solve the problem by continuously reducing `n` until a base case is met.

## 🧠 Approach — Recursion
This problem is well-suited for a **Recursive** approach. The property of being a "power of two" can be defined in terms of itself for smaller values. If a number `n` (greater than 1) is a power of two, it must be an even number, and `n/2` must also be a power of two. This recursive structure allows us to break down the problem into smaller, identical subproblems until we reach a simple base case that can be solved directly (e.g., `n=1`).

## 📝 Step-by-Step Algorithm
1.  **Handle Non-Positive Numbers**: If the input integer `n` is less than or equal to 0, it cannot be a power of two (as powers of two are always positive). Immediately return `false`.
2.  **Handle Base Case (1)**: If `n` is exactly 1, it is `2^0`, which is a power of two. Immediately return `true`.
3.  **Check for Odd Numbers**: If `n` is greater than 1 and is an odd number (i.e., `n % 2 != 0`), it cannot be a power of two (since all powers of two greater than 1 are even). Immediately return `false`.
4.  **Recursive Step**: If `n` is an even number greater than 1, then for `n` to be a power of two, `n/2` must also be a power of two. Recursively call the `isPowerOfTwo` function with `n / 2` and return its result. This process continues until one of the base cases (1, 0, or odd number) is hit.

## 💻 Solution
```cpp
class Solution {
public:
    bool isPowerOfTwo(int n) {
        // Step 1: Handle non-positive numbers.
        // Powers of two are always positive (2^x where x is an integer).
        // So, 0 or any negative number cannot be a power of two.
        if (n <= 0) {
            return false;
        }

        // Step 2: Handle the base case for recursion.
        // 1 is 2^0, which is a power of two.
        if (n == 1) {
            return true;
        }

        // Step 3: Check for odd numbers (except 1, which is handled above).
        // If n is greater than 1 and is odd, it cannot be a power of two.
        // All powers of two greater than 1 are even.
        if (n % 2 != 0) {
            return false;
        }

        // Step 4: Recursive step.
        // If n is an even number greater than 1, then for n to be a power of two,
        // n / 2 must also be a power of two.
        // We recursively call the function with n / 2.
        return isPowerOfTwo(n / 2);
    }
};

```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(log n) | In each recursive call, the value of `n` is divided by 2. The number of divisions required to reduce `n` to 1 is logarithmic with base 2 (log₂n). |
| **Space** | O(log n) | This is due to the recursion stack. Each recursive call adds a new frame to the call stack. In the worst case, there will be `log₂n` active stack frames. |

## 🔗 Related Problems
- 326. Power of Three
- 342. Power of Four
- 191. Number of 1 Bits