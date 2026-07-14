# 0136-single-number

## 📋 Problem Description
Given a non-empty array of integers `nums`, every element appears exactly twice except for one element which appears only once. The task is to find and return that single unique number.

The solution must be implemented with a linear runtime complexity (O(N)) and use only constant extra space (O(1)).

**Input:** An array of integers, `nums`.
**Output:** An integer, the single number that appears only once.

## 🔍 Examples
```
Input: nums = [2,2,1]
Output: 1
Explanation: The number 1 appears once, while 2 appears twice.

Input: nums = [4,1,2,1,2]
Output: 4
Explanation: The number 4 appears once. 1 and 2 both appear twice.

Input: nums = [1]
Output: 1
Explanation: The array contains only one element, which is the single number.
```

## 📌 Constraints
*   `1 <= nums.length <= 3 * 10^4`
*   `-3 * 10^4 <= nums[i] <= 3 * 10^4`
*   Each element in the array appears twice except for one element which appears only once.

## 🤔 Understanding the Problem
The problem asks us to identify a unique number in an array where all other numbers appear exactly twice. The key challenge lies in the strict efficiency requirements: linear time complexity (meaning we can likely iterate through the array once) and constant extra space (meaning we cannot use auxiliary data structures like hash maps or additional arrays that grow with the input size). This rules out common approaches like sorting or using frequency counts with hash maps.

## 💡 Core Idea
The core idea leverages the properties of the bitwise XOR operation. Specifically, XORing a number with itself results in 0 (`A ^ A = 0`), and XORing a number with 0 results in the number itself (`A ^ 0 = A`). These properties allow us to "cancel out" pairs of identical numbers.

## 🧠 Approach — Bit Manipulation
This problem is perfectly suited for a **Bit Manipulation** approach, specifically using the XOR operator. The reason this pattern fits so well is due to the unique properties of XOR:
1.  **Identity Property**: `x ^ 0 = x`. XORing any number with zero returns the number itself.
2.  **Self-Inverse Property**: `x ^ x = 0`. XORing any number with itself results in zero.
3.  **Commutative and Associative**: `x ^ y = y ^ x` and `(x ^ y) ^ z = x ^ (y ^ z)`. The order of XOR operations doesn't matter.

When we XOR all numbers in the array together, every number that appears twice will effectively cancel itself out (e.g., `A ^ B ^ C ^ B ^ A` becomes `(A ^ A) ^ (B ^ B) ^ C`, which simplifies to `0 ^ 0 ^ C = C`). The single unique number, having no pair to cancel it, will be the final result. This approach naturally satisfies both the linear time and constant space constraints.

## 📝 Step-by-Step Algorithm
1.  Initialize an integer variable, let's call it `singleNum`, to `0`. This variable will store the XOR sum of all elements.
2.  Iterate through each number `num` in the input array `nums`.
3.  In each iteration, update `singleNum` by performing a bitwise XOR operation with the current `num`: `singleNum = singleNum ^ num`.
4.  After the loop finishes (i.e., after all numbers in the array have been XORed with `singleNum`), the `singleNum` variable will hold the value of the unique element that appears only once.
5.  Return the final value of `singleNum`.

## 💻 Solution
```cpp
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        // Initialize a variable 'result' to 0.
        // This variable will accumulate the XOR sum of all numbers.
        // The property A ^ 0 = A ensures that XORing with 0 initially
        // does not change the first number's value.
        int result = 0;

        // Iterate through each number in the input array 'nums'.
        // This is a range-based for loop, convenient for iterating over collections.
        for(int num : nums){
            // Perform a bitwise XOR operation between the current 'result'
            // and the 'num' from the array.
            //
            // Key properties of XOR being utilized:
            // 1. A ^ A = 0: Any number XORed with itself results in 0.
            // 2. A ^ 0 = A: Any number XORed with 0 results in the number itself.
            // 3. XOR is commutative and associative: The order of operations doesn't matter.
            //
            // Example: For nums = [4, 1, 2, 1, 2]
            // Initial result = 0
            // 1. result = 0 ^ 4 = 4
            // 2. result = 4 ^ 1
            // 3. result = (4 ^ 1) ^ 2
            // 4. result = (4 ^ 1 ^ 2) ^ 1 = 4 ^ (1 ^ 1) ^ 2 = 4 ^ 0 ^ 2 = 4 ^ 2
            // 5. result = (4 ^ 2) ^ 2 = 4 ^ (2 ^ 2) = 4 ^ 0 = 4
            //
            // All numbers appearing twice cancel each other out, leaving only the single number.
            result = result ^ num;
        }

        // After iterating through all numbers, 'result' will contain the single unique number.
        return result;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | We iterate through the array `nums` exactly once. Each XOR operation takes constant time. |
| **Space** | O(1) | We only use a single integer variable (`result`) to store the XOR sum, regardless of the input array's size. |

## 🔗 Related Problems
*   137. Single Number II
*   260. Single Number III
*   191. Number of 1 Bits