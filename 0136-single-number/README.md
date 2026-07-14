# 0136-single-number

## 📋 Problem Description
Given a non-empty array of integers `nums`, every element appears exactly twice, except for one element which appears only once. The task is to find that single unique number.

The solution must adhere to strict efficiency requirements: it must have a linear runtime complexity (meaning its execution time grows proportionally to the size of the input array) and use only constant extra space (meaning it uses a fixed amount of memory regardless of the input size).

**Input:** An array of integers, `nums`.
**Output:** The single integer that appears only once.

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
The problem asks us to identify a unique number in an array where all other numbers appear in pairs. The key challenge lies in the efficiency constraints: we need to solve this in `O(N)` time (meaning we can likely iterate through the array once) and `O(1)` extra space (meaning we cannot use auxiliary data structures like hash maps or additional arrays that grow with the input size). This rules out straightforward approaches like sorting the array (which usually takes `O(N log N)` time) or using a hash set/map to count frequencies (which takes `O(N)` space).

## 💡 Core Idea
The core idea leverages the properties of the bitwise XOR operation (`^`). XOR has three crucial properties that make it perfect for this problem:
1.  **`A ^ A = 0`**: XORing a number with itself results in zero.
2.  **`A ^ 0 = A`**: XORing a number with zero results in the number itself.
3.  **Commutativity and Associativity**: `A ^ B ^ C` is the same as `(A ^ B) ^ C` or `A ^ (B ^ C)`. This means the order of XOR operations doesn't matter.

If we XOR all the numbers in the array together, all the numbers that appear twice will cancel each other out (because `X ^ X = 0`). The single unique number will be XORed with zero (the result of all pairs canceling out), leaving the unique number itself as the final result.

## 🧠 Approach — Bit Manipulation
The algorithm uses the **Bit Manipulation** pattern, specifically the XOR operator. This pattern is ideal because it allows us to perform operations directly on the binary representations of numbers, which can be extremely efficient. For this problem, XOR's unique properties enable us to "filter out" duplicate elements without needing to store them or sort the array. This directly satisfies both the linear time complexity and constant space complexity requirements, as we only need a single variable to accumulate the XOR sum.

## 📝 Step-by-Step Algorithm
1.  Initialize a variable, let's call it `result`, to `0`. This variable will store the cumulative XOR sum of all numbers encountered so far.
2.  Iterate through each number (`num`) in the input array `nums` from beginning to end.
3.  In each iteration, update `result` by XORing its current value with the current number `num`. That is, `result = result ^ num`.
4.  After the loop finishes, `result` will hold the value of the single number that appears only once. This is because all numbers that appeared twice would have XORed with themselves, effectively becoming `0`, and `0` XORed with the unique number leaves the unique number itself.
5.  Return the final value of `result`.

## 💻 Solution
```cpp
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        // Initialize a variable 'result' to 0.
        // This variable will accumulate the XOR sum of all numbers.
        // The property A ^ 0 = A ensures that XORing with 0 initially doesn't
        // change the first number XORed into 'result'.
        int result = 0; 
        
        // Iterate through each number in the input array 'nums'.
        for(int num : nums){
            // Perform a bitwise XOR operation between the current 'result'
            // and the current number 'num'.
            //
            // Key properties of XOR:
            // 1. A ^ A = 0 (XORing a number with itself results in 0)
            // 2. A ^ 0 = A (XORing a number with 0 results in the number itself)
            // 3. XOR is commutative and associative (order doesn't matter)
            //
            // Example: nums = [4, 1, 2, 1, 2]
            // Initial result = 0
            //
            // 1. num = 4: result = 0 ^ 4 = 4
            // 2. num = 1: result = 4 ^ 1
            // 3. num = 2: result = 4 ^ 1 ^ 2
            // 4. num = 1: result = 4 ^ 1 ^ 2 ^ 1
            //             Since 1 ^ 1 = 0, this simplifies to 4 ^ 0 ^ 2 = 4 ^ 2
            // 5. num = 2: result = 4 ^ 2 ^ 2
            //             Since 2 ^ 2 = 0, this simplifies to 4 ^ 0 = 4
            //
            // All paired numbers cancel each other out, leaving only the single number.
            result = result ^ num;
        }
        
        // After iterating through all numbers, 'result' will hold the
        // value of the single unique number.
        return result;
    }
};

```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | The algorithm iterates through the `nums` array exactly once, performing a constant number of operations (XOR) for each element. |
| **Space** | O(1) | Only a single integer variable (`result`) is used to store the XOR sum, regardless of the input array's size. |

## 🔗 Related Problems
- 137. Single Number II
- 260. Single Number III
- 191. Number of 1 Bits