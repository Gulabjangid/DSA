# 0136-single-number

## 📋 Problem Description
Given a non-empty array of integers, `nums`, where every element appears exactly twice, except for one element which appears only once. The task is to find and return that single unique number.

The solution must adhere to specific constraints: it must have a linear runtime complexity (O(N)) and use only constant extra space (O(1)).

**Input:** A `std::vector<int>` named `nums`.
**Output:** An `int` representing the single unique number.

## 🔍 Examples
```
Input: nums = [2,2,1]
Output: 1
Explanation: The number 1 appears once, while 2 appears twice.
```

```
Input: nums = [4,1,2,1,2]
Output: 4
Explanation: The number 4 appears once. Numbers 1 and 2 each appear twice.
```

```
Input: nums = [1]
Output: 1
Explanation: The array contains only one element, which is the single number.
```

## 📌 Constraints
*   `1 <= nums.length <= 3 * 10^4`
*   `-3 * 10^4 <= nums[i] <= 3 * 10^4`
*   Each element in the array appears twice except for one element which appears only once.

## 🤔 Understanding the Problem
The problem asks us to identify a unique number in an array where all other numbers appear in pairs. The crucial part is the efficiency requirement: we need a solution that processes the array in a single pass (or equivalent linear time) and does not use any additional data structures that grow with the input size (like hash maps or auxiliary arrays). This rules out common approaches like sorting (which is typically O(N log N)) or using a hash set/map (which uses O(N) space). We need a clever trick that can handle duplicates and isolate the unique element within these strict constraints.

## 💡 Core Idea
The core idea leverages the properties of the bitwise XOR (exclusive OR) operation. Specifically, XORing a number with itself results in 0 (`x ^ x = 0`), and XORing a number with 0 results in the number itself (`x ^ 0 = x`). Furthermore, XOR is commutative and associative, meaning the order of operations doesn't matter.

## 🧠 Approach — Bit Manipulation
This problem is perfectly suited for a **Bit Manipulation** approach using the XOR operator. The properties of XOR allow us to "cancel out" numbers that appear twice. When we XOR all numbers in the array together, every number that appears an even number of times will effectively cancel itself out (e.g., `A ^ B ^ A = (A ^ A) ^ B = 0 ^ B = B`). Since all numbers except one appear exactly twice, their XOR sum will be 0. The single unique number, XORed with this 0, will remain as the final result. This approach naturally satisfies both the linear time and constant space complexity requirements.

## 📝 Step-by-Step Algorithm
1.  Initialize an integer variable, let's call it `singleNum`, to `0`. This variable will store the cumulative XOR sum of all elements.
2.  Iterate through each number (`num`) in the input array `nums`.
3.  In each iteration, update `singleNum` by performing a bitwise XOR operation with the current `num`: `singleNum = singleNum ^ num`.
4.  After the loop finishes, `singleNum` will hold the value of the unique element that appeared only once.
5.  Return `singleNum`.

**Dry Run Example: `nums = [4,1,2,1,2]`**

*   Initialize `singleNum = 0`.
*   **Iteration 1:** `num = 4`
    *   `singleNum = singleNum ^ 4 = 0 ^ 4 = 4`
*   **Iteration 2:** `num = 1`
    *   `singleNum = singleNum ^ 1 = 4 ^ 1 = 5` (binary: `100 ^ 001 = 101`)
*   **Iteration 3:** `num = 2`
    *   `singleNum = singleNum ^ 2 = 5 ^ 2 = 7` (binary: `101 ^ 010 = 111`)
*   **Iteration 4:** `num = 1`
    *   `singleNum = singleNum ^ 1 = 7 ^ 1 = 6` (binary: `111 ^ 001 = 110`)
*   **Iteration 5:** `num = 2`
    *   `singleNum = singleNum ^ 2 = 6 ^ 2 = 4` (binary: `110 ^ 010 = 100`)
*   End of loop.
*   Return `singleNum`, which is `4`.

## 💻 Solution
```cpp
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        // Initialize a variable 'result' to 0.
        // This variable will accumulate the XOR sum of all numbers.
        // The property 'x ^ 0 = x' means XORing any number with 0
        // results in the number itself. This makes 0 an ideal
        // starting point for our XOR accumulation.
        int result = 0;

        // Iterate through each number in the input vector 'nums'.
        // This is a range-based for loop, which is convenient for
        // iterating over all elements of a container.
        for(int num : nums){
            // Perform a bitwise XOR operation between the current 'result'
            // and the current number 'num'.
            //
            // Key properties of XOR that make this work:
            // 1. x ^ x = 0: XORing a number with itself yields 0.
            // 2. x ^ 0 = x: XORing a number with 0 yields the number itself.
            // 3. XOR is commutative and associative: The order of operations
            //    does not affect the final result (e.g., a ^ b ^ c = c ^ a ^ b).
            //
            // Because every element in the array appears exactly twice except for one,
            // when we XOR all numbers together, each pair of identical numbers
            // will effectively cancel each other out to 0 (e.g., 2 ^ 2 = 0).
            // The unique number, appearing only once, will be XORed with this
            // accumulated 0 (from all the pairs canceling out) and thus will
            // remain as the final value in 'result'.
            result = result ^ num;
        }

        // After iterating through all numbers, 'result' will hold the
        // value of the single number that appeared only once.
        return result;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | We iterate through the array `nums` exactly once. The XOR operation for each element is a constant time operation. |
| **Space** | O(1) | We only use a single integer variable (`result`) to store the XOR sum, regardless of the input array's size. No additional data structures are allocated. |

## 🔗 Related Problems
*   137. Single Number II
*   260. Single Number III
*   191. Number of 1 Bits