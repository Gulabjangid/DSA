# 0136-single-number

## 📋 Problem Description
You are given a non-empty array of integers, `nums`. In this array, every integer appears exactly twice, except for one integer which appears only once. Your task is to find and return that single unique integer.

The solution must adhere to specific efficiency requirements: it must have a linear runtime complexity (O(N)) and use only constant extra space (O(1)).

## 🔍 Examples
```
Input: nums = [2,2,1]
Output: 1
Explanation: The number 1 appears once, while 2 appears twice.

Input: nums = [4,1,2,1,2]
Output: 4
Explanation: The number 4 appears once. Numbers 1 and 2 each appear twice.

Input: nums = [1]
Output: 1
Explanation: The array contains only one element, which is the single number.
```

## 📌 Constraints
*   `1 <= nums.length <= 3 * 10^4`
*   `-3 * 10^4 <= nums[i] <= 3 * 10^4`
*   Each element in the array appears twice except for one element which appears only once.

## 🤔 Understanding the Problem
The problem asks us to identify a unique element in an array where all other elements have a duplicate. The key challenge lies in the strict efficiency requirements: we need a solution that processes the array in a single pass (or equivalent linear time) and does not use any additional memory proportional to the input size. This rules out common approaches like using hash maps to count frequencies (which would use O(N) space) or sorting the array (which is typically O(N log N) time).

## 💡 Core Idea
The core idea leverages the properties of the bitwise XOR (exclusive OR) operation. Specifically, XORing a number with itself results in 0 (`A ^ A = 0`), and XORing any number with 0 results in the number itself (`A ^ 0 = A`). Furthermore, XOR is commutative and associative, meaning the order of operations doesn't matter.

## 🧠 Approach — Bit Manipulation
This problem is perfectly suited for a **Bit Manipulation** approach using the XOR operator. The reason this pattern fits so well is due to the unique properties of XOR:
1.  **Self-cancellation**: Any number XORed with itself results in zero (e.g., `5 ^ 5 = 0`).
2.  **Identity element**: Any number XORed with zero results in the number itself (e.g., `5 ^ 0 = 5`).
3.  **Commutativity and Associativity**: The order of XOR operations does not affect the final result (e.g., `A ^ B ^ C = C ^ A ^ B`).

When we XOR all the numbers in the array together, all the numbers that appear twice will effectively cancel each other out (e.g., `X ^ Y ^ X ^ Z ^ Y` becomes `(X ^ X) ^ (Y ^ Y) ^ Z = 0 ^ 0 ^ Z = Z`). The only number that will remain is the one that appeared only once.

## 📝 Step-by-Step Algorithm
1.  Initialize a variable, let's call it `result`, to `0`. This variable will accumulate the XOR sum of all elements.
2.  Iterate through each number (`num`) in the input array `nums`.
3.  In each iteration, update `result` by performing a bitwise XOR operation with the current `num`: `result = result ^ num`.
4.  After the loop finishes and all numbers in the array have been XORed with `result`, the `result` variable will hold the value of the single unique number.
5.  Return the final `result`.

## 💻 Solution
```cpp
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        // Initialize a variable 'result' to 0.
        // This variable will accumulate the XOR sum of all numbers.
        // The property of XOR is that A ^ 0 = A, so initializing with 0
        // does not affect the first number XORed with it.
        int result = 0;

        // Iterate through each number in the input array 'nums'.
        // This is a range-based for loop, convenient for iterating over collections.
        for(int num : nums){
            // Perform a bitwise XOR operation between the current 'result'
            // and the current number 'num'.
            //
            // Key properties of XOR that make this work:
            // 1. A ^ A = 0: If a number appears twice, XORing it with itself cancels it out.
            // 2. A ^ 0 = A: If a number appears only once, it will eventually be XORed with 0
            //                 (from all the cancelled pairs) and remain itself.
            // 3. Associativity and Commutativity: The order of numbers in the array
            //    does not matter for the final XOR sum.
            //
            // Example: nums = [4, 1, 2, 1, 2]
            // result = 0
            // result = 0 ^ 4 = 4
            // result = 4 ^ 1
            // result = (4 ^ 1) ^ 2
            // result = (4 ^ 1 ^ 2) ^ 1  => (4 ^ 2) ^ (1 ^ 1) => (4 ^ 2) ^ 0 => 4 ^ 2
            // result = (4 ^ 2) ^ 2      => 4 ^ (2 ^ 2) => 4 ^ 0 => 4
            result = result ^ num;
        }

        // After iterating through all numbers, 'result' will hold the single number
        // that appeared only once, as all paired numbers have cancelled each other out.
        return result;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | The algorithm iterates through the input array `nums` exactly once. Each XOR operation is a constant-time operation. |
| **Space** | O(1) | The algorithm uses a single integer variable (`result`) to store the XOR sum, regardless of the input array's size. No additional data structures are allocated. |

## 🔗 Related Problems
- 137. Single Number II
- 260. Single Number III
- 389. Find the Difference