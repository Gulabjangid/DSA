# 0053-maximum-subarray

## 📋 Problem Description
Given an integer array `nums`, the task is to find a contiguous subarray (a non-empty sequence of elements) within it that has the largest possible sum. You need to return this maximum sum.

The function `maxSubArray` receives one argument:
*   `nums`: An integer array.

It must return:
*   An integer representing the maximum sum found among all possible contiguous subarrays.

## 🔍 Examples

**Example 1:**
```
Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
Output: 6
Explanation: The subarray [4,-1,2,1] has the largest sum 6.
```

**Example 2:**
```
Input: nums = [1]
Output: 1
Explanation: The subarray [1] has the largest sum 1.
```

**Example 3:**
```
Input: nums = [5,4,-1,7,8]
Output: 23
Explanation: The subarray [5,4,-1,7,8] has the largest sum 23.
```

## 📌 Constraints
*   `1 <= nums.length <= 10^5`
*   `-10^4 <= nums[i] <= 10^4`

## 🤔 Understanding the Problem
The problem asks us to find the maximum sum of a contiguous subarray. This means we cannot skip elements; the chosen elements must be adjacent in the original array. The challenge arises when negative numbers are present. A negative number might reduce the current sum, but it might be followed by large positive numbers that make the overall subarray sum greater than starting a new subarray. We need to decide whether to extend the current subarray or start a new one at each step to maximize the sum. An important detail is that the subarray must be non-empty.

## 💡 Core Idea
The core idea is that if the sum of a current subarray becomes negative, it's always better to discard that subarray and start a new one from the next element. A negative prefix will only decrease the sum of any future subarray it's part of.

## 🧠 Approach — Kadane's Algorithm (Dynamic Programming / Greedy)
This problem is a classic application of **Kadane's Algorithm**, which can be viewed as a specific type of dynamic programming or a greedy approach. It fits because we can build the solution iteratively by making locally optimal choices. At each element, we decide whether to extend the current subarray or start a new one. This greedy choice (discarding a negative-sum prefix) guarantees the global optimum because a negative prefix can never contribute positively to a future sum. The algorithm efficiently tracks the maximum sum ending at the current position and the overall maximum sum found so far.

## 📝 Step-by-Step Algorithm
1.  Initialize two variables:
    *   `current_max_sum`: This will store the maximum sum of the subarray ending at the current position. Initialize it to `0`.
    *   `overall_max_sum`: This will store the maximum sum found across all subarrays encountered so far. Initialize it to `INT_MIN` (the smallest possible integer value) to correctly handle cases where all numbers are negative.

2.  Iterate through each number `num` in the input array `nums`:
    a.  Add the current number `num` to `current_max_sum`.
    b.  Update `overall_max_sum`: Compare `overall_max_sum` with `current_max_sum` and store the larger of the two. This ensures `overall_max_sum` always holds the largest sum found so far.
    c.  Check if `current_max_sum` has become negative: If `current_max_sum < 0`, reset `current_max_sum` to `0`. This is the crucial step of Kadane's algorithm: if the sum of the subarray ending at the current position is negative, it means this subarray is detrimental to any future sums, so we effectively "start a new subarray" from the next element.

3.  After iterating through all numbers in the array, `overall_max_sum` will hold the maximum subarray sum. Return `overall_max_sum`.

## 💻 Solution

```cpp
#include <vector>    // Required for using std::vector
#include <algorithm> // Required for std::max
#include <limits>    // Required for std::numeric_limits<int>::min() or INT_MIN

class Solution {
public:
    int maxSubArray(std::vector<int>& nums) {
        // 'current_subarray_sum' (named 'count' in the original code)
        // tracks the sum of the current subarray ending at the current position.
        // If this sum ever drops below zero, it means the subarray ending here
        // is not contributing positively, so we reset it to 0 to start a new subarray.
        int current_subarray_sum = 0; 
        
        // 'overall_max_sum' (named 'maxsum' in the original code)
        // tracks the maximum sum found across all subarrays encountered so far.
        // Initialize it to the smallest possible integer value to correctly
        // handle cases where all numbers in the array are negative (e.g., [-2, -1]).
        int overall_max_sum = std::numeric_limits<int>::min(); 
        
        // Iterate through each number in the input array 'nums'.
        for (int i = 0; i < nums.size(); ++i) {
            // Add the current number to the sum of the current subarray.
            current_subarray_sum += nums[i];
            
            // Update the overall maximum sum found so far.
            // We compare 'overall_max_sum' with the 'current_subarray_sum'
            // because 'current_subarray_sum' represents the maximum sum
            // ending at the current position 'i'.
            overall_max_sum = std::max(overall_max_sum, current_subarray_sum);
            
            // If the 'current_subarray_sum' becomes negative, it means
            // this subarray (ending at 'i') is no longer beneficial.
            // Reset it to 0 to effectively start a new subarray from the next element.
            // A negative prefix will only decrease any future sum.
            if (current_subarray_sum < 0) {
                current_subarray_sum = 0;
            }
        }
        
        // After iterating through all elements, 'overall_max_sum' will hold
        // the largest sum of any contiguous subarray.
        return overall_max_sum;
    }
};

```

## ⏱️ Complexity Analysis

| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | The algorithm iterates through the input array `nums` exactly once. Each operation inside the loop (addition, comparison, assignment) takes constant time. |
| **Space** | O(1) | The algorithm uses a fixed number of extra variables (`current_subarray_sum`, `overall_max_sum`) regardless of the input array size. |

## 🔗 Related Problems
- 152. Maximum Product Subarray
- 121. Best Time to Buy and Sell Stock (can be reframed as finding max subarray sum of price differences)
- 209. Minimum Size Subarray Sum