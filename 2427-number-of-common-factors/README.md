# 2427-number-of-common-factors

## 📋 Problem Description
Given two positive integers, `a` and `b`, the task is to determine and return the total count of their common factors. An integer `x` is considered a common factor of `a` and `b` if `x` divides both `a` and `b` without leaving any remainder.

## 🔍 Examples
```
Input: a = 12, b = 6
Output: 4
Explanation: The common factors of 12 and 6 are 1, 2, 3, and 6.
```

```
Input: a = 25, b = 30
Output: 2
Explanation: The common factors of 25 and 30 are 1 and 5.
```

## 📌 Constraints
*   `1 <= a, b <= 1000`

## 🤔 Understanding the Problem
The problem asks us to find how many positive integers can perfectly divide both `a` and `b`. For example, if `a=12` and `b=6`, we're looking for numbers `x` such that `12 % x == 0` AND `6 % x == 0`. The smallest possible common factor is always 1. A key observation is that any factor of a number `N` cannot be greater than `N` itself. Therefore, a common factor of `a` and `b` cannot be greater than the smaller of the two numbers.

## 💡 Core Idea
Any common factor `x` of `a` and `b` must satisfy `x <= a` and `x <= b`. This implies that `x` must also be less than or equal to the minimum of `a` and `b`. This significantly limits the range of numbers we need to check for common factors.

## 🧠 Approach — Direct Iteration / Brute Force
This problem can be efficiently solved using a direct iteration approach, often referred to as brute force, given the small constraints on `a` and `b` (up to 1000). The strategy is to systematically check every integer starting from 1 up to the minimum of `a` and `b`. For each integer `i` in this range, we perform a simple check: if `i` divides both `a` and `b` evenly, then `i` is a common factor, and we increment a counter. This pattern is suitable because the search space for potential common factors is small and easily enumerable.

## 📝 Step-by-Step Algorithm
1.  Initialize an integer variable `count` to 0. This variable will keep track of the number of common factors found.
2.  Determine the smaller value between `a` and `b`. Store this value in a variable, say `n`. This `n` will serve as the upper limit for our iteration, as no common factor can exceed `min(a, b)`.
3.  Start a `for` loop that iterates with an integer variable `i` from 1 up to `n` (inclusive).
4.  Inside the loop, for each value of `i`:
    a.  Check if `a` is perfectly divisible by `i` (i.e., `a % i == 0`).
    b.  Simultaneously, check if `b` is perfectly divisible by `i` (i.e., `b % i == 0`).
5.  If both conditions from step 4 are true, it means `i` is a common factor of both `a` and `b`. Increment `count` by 1.
6.  After the loop has finished iterating through all numbers from 1 to `n`, the `count` variable will hold the total number of common factors. Return `count`.

## 💻 Solution
```cpp
class Solution {
public:
    int commonFactors(int a, int b) {
        // Determine the upper limit for checking potential factors.
        // A common factor cannot be greater than the smaller of the two numbers.
        // For example, if a=12, b=6, factors can't exceed 6.
        int n = std::min(a, b); 
        
        // Initialize a counter to store the number of common factors found.
        int count = 0;
        
        // Iterate from 1 up to 'n' (inclusive).
        // 'i' represents each potential common factor we are testing.
        for (int i = 1; i <= n; ++i) {
            // Check if 'i' divides 'a' evenly (remainder is 0).
            // And simultaneously check if 'i' divides 'b' evenly.
            if (a % i == 0 && b % i == 0) {
                // If 'i' divides both 'a' and 'b', it is a common factor.
                count++; // Increment the counter.
            }
        }
        
        // After checking all numbers up to min(a, b), return the total count.
        return count;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(min(a, b)) | The `for` loop iterates `min(a, b)` times. Inside the loop, operations like modulo (`%`), comparison (`==`, `&&`), and increment (`++`) take constant time. |
| **Space** | O(1) | The solution uses a fixed number of variables (`n`, `count`, `i`) regardless of the input values `a` and `b`. No additional data structures are allocated. |

## 🔗 Related Problems
- 1979. Find Greatest Common Divisor of Array
- 2154. Keep Multiplying Found Values by Two
- 1716. Calculate Money in Leetcode Bank