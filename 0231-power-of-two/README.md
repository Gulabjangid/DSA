# 0231-power-of-two

## 📋 Problem Description
Given an integer `n`, determine if it is a power of two. An integer `n` is considered a power of two if there exists an integer `x` such that `n` equals `2` raised to the power of `x` (i.e., `n == 2^x`). The function should return `true` if `n` is a power of two, and `false` otherwise.

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
```

## 📌 Constraints
*   `-2^31 <= n <= 2^31 - 1`

## 🤔 Understanding the Problem
The problem asks us to check if a given integer `n` can be expressed as `2` raised to some non-negative integer power `x`. This implies that `n` must be a positive integer, as `2^x` is always positive for any integer `x`. We need to handle edge cases such as `n=1` (which is `2^0`), as well as negative numbers or zero, which are not powers of two. The core challenge is to efficiently determine this property for any given `n`.

## 💡 Core Idea
A positive integer `n` is a power of two if and only if it is `1` (which is `2^0`) or it is an even number whose half (`n/2`) is also a power of two. This recursive definition allows us to repeatedly divide `n` by 2 until we either reach `1` (indicating it's a power of two) or encounter an odd number (indicating it's not).

## 🧠 Approach — Recursion
This problem is naturally suited for a recursive approach because the definition of a power of two exhibits a self-similar structure. If a number `n` (greater than 1) is a power of two, then it must be an even number, and `n/2` must also be a power of two. This allows us to break down the problem into smaller, identical subproblems (checking `n/2`) until we reach a simple base case (`n=1`). The recursion effectively models the process of repeatedly dividing by 2.

## 📝 Step-by-Step Algorithm
1.  **Handle Non-Positive Numbers:** First, check if `n` is less than or equal to `0`. Since powers of two are always positive integers (`2^x` is positive for any integer `x`), `0` or any negative number cannot be a power of two. If `n <= 0`, immediately return `false`.
2.  **Base Case - `n = 1`:** Next, check if `n` is `1`. `1` is `2^0`, which is a power of two. If `n == 1`, return `true`.
3.  **Handle Odd Numbers:** If `n` is greater than `1` and is an odd number (i.e., `n % 2 != 0`), it cannot be a power of two. All powers of two greater than `1` (like `2^1=2`, `2^2=4`, `2^3=8`, etc.) are even. If `n` is odd at this point, return `false`.
4.  **Recursive Step:** If `n` is an even number and greater than `1` (meaning it passed the checks in steps 1-3), then `n` is a power of two if and only if `n/2` is also a power of two. Recursively call the `isPowerOfTwo` function with `n / 2`. The result of this recursive call will be the final answer for the original `n`.

## 💻 Solution
```cpp
class Solution {
public:
    bool isPowerOfTwo(int n) {
        // Step 1: Handle non-positive numbers.
        // Powers of two are always positive integers (2^x where x is an integer).
        // So, 0 or any negative number cannot be a power of two.
        if (n <= 0) {
            return false;
        }

        // Step 2: Handle the base case where n is 1.
        // 1 is 2^0, which is a power of two. This is our stopping condition for valid powers of two.
        if (n == 1) {
            return true;
        }

        // Step 3: Handle odd numbers (other than 1).
        // If n is greater than 1 and odd, it cannot be a power of two.
        // All powers of two greater than 1 (2^1, 2^2, ...) are even.
        if (n % 2 != 0) {
            return false;
        }

        // Step 4: Recursive step.
        // If n is an even number greater than 1, it is a power of two
        // if and only if n/2 is also a power of two.
        // We continue dividing by 2 until we hit 1 (true) or an odd number (false).
        return isPowerOfTwo(n / 2);
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(log n) | In each recursive call, the value of `n` is divided by 2. The number of recursive calls is proportional to the number of times `n` can be divided by 2 until it reaches 1, which is `log₂n`. Each operation (comparison, modulo, division) takes constant time. |
| **Space** | O(log n) | The recursive calls build up a call stack. The maximum depth of this stack is `log₂n`, corresponding to the number of recursive calls. Each stack frame consumes constant space. |

## 🔗 Related Problems
- 326. Power of Three
- 342. Power of Four
- 191. Number of 1 Bits (This problem explores bit manipulation, which offers an alternative, often more efficient, way to check for powers of two.)