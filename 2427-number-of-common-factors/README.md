# 2427-number-of-common-factors

## 📋 Problem Description
Given two positive integers `a` and `b`, the task is to determine and return the total count of their common factors. An integer `x` is considered a common factor of `a` and `b` if `x` divides both `a` evenly (i.e., `a % x == 0`) and `b` evenly (i.e., `b % x == 0`).

## 🔍 Examples
```
Input: a = 12, b = 6
Output: 4
Explanation: The common factors of 12 and 6 are 1, 2, 3, and 6. There are 4 such factors.
```
```
Input: a = 25, b = 30
Output: 2
Explanation: The common factors of 25 and 30 are 1 and 5. There are 2 such factors.
```

## 📌 Constraints
*   `1 <= a, b <= 1000`

## 🤔 Understanding the Problem
The problem asks us to count how many positive integers can divide both `a` and `b` without leaving a remainder. For instance, if `a=12` and `b=6`, we're looking for numbers like 1 (divides 12 and 6), 2 (divides 12 and 6), 3 (divides 12 and 6), and 6 (divides 12 and 6). The largest possible common factor cannot be greater than the smaller of the two numbers `a` and `b`.

## 💡 Core Idea
The most straightforward way to find all common factors is to iterate through all possible candidate numbers, starting from 1, up to the smallest of the two given integers. For each candidate, we check if it divides both `a` and `b`.

## 🧠 Approach — Direct Iteration
This problem can be solved using a **Direct Iteration** or **Brute Force** approach. Given the small constraints on `a` and `b` (up to 1000), we can efficiently check every integer from 1 up to `min(a, b)`. If an integer `i` divides both `a` and `b`, it is a common factor, and we increment a counter. This approach works because any common factor `x` must satisfy `x <= a` and `x <= b`, which implies `x <= min(a, b)`.

## 📝 Step-by-Step Algorithm
1.  Initialize an integer variable `count` to `0`. This variable will store the number of common factors found.
2.  Determine the smaller of the two input integers, `a` and `b`. Store this value in a variable, say `n`. This is because any common factor cannot be greater than the minimum of `a` and `b`.
3.  Start a loop that iterates with an integer variable `i` from `1` up to `n` (inclusive).
4.  Inside the loop, for each value of `i`, perform two checks:
    *   Check if `a` is perfectly divisible by `i` (i.e., `a % i == 0`).
    *   Check if `b` is perfectly divisible by `i` (i.e., `b % i == 0`).
5.  If both conditions from step 4 are true, it means `i` is a common factor of `a` and `b`. In this case, increment the `count` variable by `1`.
6.  After the loop has finished iterating through all numbers from `1` to `n`, return the final value of `count`.

## 💻 Solution
```cpp
class Solution {
public:
    int commonFactors(int a, int b) {
        // Determine the maximum possible value a common factor can take.
        // A common factor cannot be greater than the smaller of 'a' and 'b'.
        int n = std::min(a, b); 
        
        // Initialize a counter for common factors found.
        int count = 0;
        
        // Iterate from 1 up to 'n' (inclusive).
        // 'i' represents a potential common factor.
        for (int i = 1; i <= n; ++i) {
            // Check if 'i' divides 'a' evenly AND 'i' divides 'b' evenly.
            if (a % i == 0 && b % i == 0) {
                // If both conditions are true, 'i' is a common factor.
                count++;
            }
        }
        
        // Return the total count of common factors.
        return count;
    }
};

```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(min(a, b)) | The loop runs `min(a, b)` times. Inside the loop, operations (modulo, comparison, increment) are constant time. |
| **Space** | O(1) | Only a few constant-size variables (`n`, `count`, `i`) are used, independent of the input values `a` and `b`. |

## 🔗 Related Problems
- 1979. Find Greatest Common Divisor of Array
- 1390. Four Divisors
- 263. Ugly Number