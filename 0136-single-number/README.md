# 0136-single-number

## 📋 Problem Description
You are given a non-empty array of integers, `nums`. In this array, every element appears exactly twice, except for one element which appears only once. Your task is to find and return that single unique number.

The solution must adhere to specific efficiency requirements: it must have a linear runtime complexity (O(N)) and use only constant extra space (O(1)).

## 🔍 Examples
```
Input:  nums = [2,2,1]
Output: 1
Explanation: The number '1' appears once, while '2' appears twice.

Input:  nums = [4,1,2,1,2]
Output: 4
Explanation: The number '4' appears once. '1' and '2' each appear twice.

Input:  nums = [1]
Output: 1
Explanation: The array contains only one element, which is the single number.
```

## 📌 Constraints
*   `1 <= nums.length <= 3 * 10^4`
*   `-3 * 10^4 <= nums[i] <= 3 * 10^4`
*   Each element in the array appears twice except for one element which appears only once.

## 🤔 Understanding the Problem
The problem asks us to identify a unique number in an array where all other numbers have a duplicate. The key challenge is to do this efficiently, specifically in linear time without using additional memory proportional to the input size. This rules out common approaches like using hash maps (which would use O(N) space) or sorting (which often takes O(N log N) time). We need a clever way to "cancel out" the duplicate numbers.

## 💡 Core Idea
The core idea leverages the properties of the bitwise XOR operation. XORing a number with itself results in zero (`A ^ A = 0`), and XORing a number with zero results in the number itself (`A ^ 0 = A`). Furthermore, XOR is commutative and associative (`A ^ B ^ A = B ^ A ^ A`).

## 🧠 Approach — Bit Manipulation
This problem can be elegantly solved using the **Bit Manipulation** pattern, specifically by utilizing the properties of the XOR (exclusive OR) bitwise operator. The reason this pattern fits perfectly is due to XOR's unique behavior:
1.  Any number XORed with itself results in `0`.
2.  Any number XORed with `0` results in the number itself.
3.  XOR operations are commutative and associative, meaning the order of operations does not matter.

If we XOR all the numbers in the array together, all numbers that appear twice will effectively cancel each other out (e.g., `A ^ A = 0`). The single unique number, which only appears once, will be XORed with `0` (the result of all pairs canceling out) and thus remain as the final result.

## 📝 Step-by-Step Algorithm
1.  Initialize a variable, let's call it `result`, to `0`. This variable will accumulate the XOR sum of all numbers.
2.  Iterate through each number (`num`) in the input array `nums`.
3.  In each iteration, update `result` by XORing it with the current number: `result = result ^ num`.
4.  After iterating through all numbers in the array, the `result` variable will hold the single number that appears only once.
5.  Return the final `result`.

## 💻 Solution
```cpp
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        // Initialize a variable 'result' to 0.
        // The XOR property A ^ 0 = A ensures that XORing with 0
        // initially does not change the first number.
        int result = 0; 
        
        // Iterate through each number in the input vector 'nums'.
        for(int num : nums){
            // Apply the XOR operation: result = result ^ num.
            //
            // Key properties of XOR:
            // 1. A ^ A = 0 (XORing a number with itself yields 0)
            // 2. A ^ 0 = A (XORing a number with 0 yields the number itself)
            // 3. XOR is commutative and associative (order doesn't matter)
            //
            // Example dry run with nums = [4, 1, 2, 1, 2]:
            // Initial: result = 0
            // 1. num = 4: result = 0 ^ 4 = 4
            // 2. num = 1: result = 4 ^ 1
            // 3. num = 2: result = (4 ^ 1) ^ 2
            // 4. num = 1: result = (4 ^ 1 ^ 2) ^ 1  =>  4 ^ (1 ^ 1) ^ 2  =>  4 ^ 0 ^ 2  =>  4 ^ 2
            // 5. num = 2: result = (4 ^ 2) ^ 2      =>  4 ^ (2 ^ 2)      =>  4 ^ 0      =>  4
            //
            // All numbers appearing twice cancel each other out, leaving only the single number.
            result = result ^ num;
        }
        
        // After iterating through all numbers, 'result' will hold the single unique number.
        return result;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | We iterate through the array exactly once, performing a constant-time XOR operation for each element. |
| **Space** | O(1) | We only use a single integer variable (`result`) to store the accumulated XOR sum, regardless of the input array size. |

## 🔗 Related Problems
- 137. Single Number II
- 260. Single Number III
- 268. Missing Number