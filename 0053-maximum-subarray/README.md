# 0053-maximum-subarray

## 📋 Problem Description
Given an integer array `nums`, the task is to find a contiguous subarray (a sequence of elements that are adjacent in the array) that has the largest possible sum. The subarray must contain at least one number. After finding this subarray, you should return its sum.

**Input:** An integer array `nums`.
**Output:** An integer representing the maximum sum of any contiguous subarray within `nums`.

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
The problem asks us to identify a continuous segment within a given array of numbers such that the sum of elements in that segment is maximized. The key challenge lies in handling negative numbers: a negative number can decrease the sum of a potentially good subarray, but it might also be followed by large positive numbers that could turn the overall sum positive again. We need a strategy to decide when to extend a current subarray and when to discard it and start a new one. An important edge case is when all numbers in the array are negative; in this scenario, the maximum sum will be the largest (least negative) single number in the array.

## 💡 Core Idea
The core idea is Kadane's Algorithm. It's based on the observation that if the sum of a current subarray becomes negative, then this subarray can never be part of a larger sum by extending it further. Any subsequent positive numbers would yield a larger sum if we started a new subarray from them, rather than carrying forward a negative prefix.

## 🧠 Approach — Kadane's Algorithm (Dynamic Programming / Greedy)
This problem is a classic application of **Kadane's Algorithm**, which can be categorized as both a **Dynamic Programming** and a **Greedy** approach. It's dynamic programming because the maximum subarray sum ending at the current position depends on the maximum subarray sum ending at the previous position. It's greedy because at each step, we make the locally optimal choice: either extend the current subarray or start a new one, which ultimately leads to the globally optimal solution. This pattern fits because we only need to maintain two pieces of information: the maximum sum found *so far* across all subarrays, and the maximum sum of the subarray *ending at the current position*.

## 📝 Step-by-Step Algorithm
1.  Initialize two variables:
    *   `max_so_far`: This will store the overall maximum subarray sum found throughout the array. Initialize it to `INT_MIN` (the smallest possible integer value) to correctly handle cases where all numbers are negative.
    *   `current_max`: This will store the maximum sum of the subarray ending at the current position. Initialize it to `0`.

2.  Iterate through each number `num` in the input array `nums`:
    *   Add the current `num` to `current_max`.
    *   Update `max_so_far`: Compare `current_max` with `max_so_far` and set `max_so_far` to the larger of the two. This step ensures `max_so_far` always holds the greatest sum encountered up to the current point.
    *   Check if `current_max` has become negative: If `current_max < 0`, reset `current_max` to `0`. This is the crucial step of Kadane's algorithm. A negative `current_max` means that the subarray ending at the current position is contributing negatively to any future sums, so it's better to discard it and start a new potential subarray from the next element.

3.  After iterating through all numbers in the array, `max_so_far` will hold the maximum subarray sum. Return `max_so_far`.

## 💻 Solution
```cpp
#include <vector> // Required for std::vector
#include <algorithm> // Required for std::max
#include <limits> // Required for std::numeric_limits<int>::min()

class Solution {
public:
    int maxSubArray(std::vector<int>& nums) {
        // 'current_subarray_sum' (named 'count' in the original code) keeps track of
        // the sum of the current subarray being considered.
        // If this sum ever drops below zero, it means this subarray is no longer
        // beneficial to extend, so we reset it to zero to start a new subarray
        // from the next element.
        int current_subarray_sum = 0;

        // 'overall_max_sum' (named 'maxsum' in the original code) stores the
        // maximum subarray sum found so far across the entire array.
        // Initialize it to the smallest possible integer value to correctly handle
        // cases where all numbers in the array are negative (e.g., [-2, -1, -3]
        // should return -1).
        int overall_max_sum = std::numeric_limits<int>::min(); // Equivalent to INT_MIN

        // Iterate through each number in the input array 'nums'.
        for (int i = 0; i < nums.size(); ++i) {
            // Add the current number to the sum of the current subarray.
            current_subarray_sum += nums[i];
            
            // Update the overall maximum sum found so far.
            // We compare the 'current_subarray_sum' (which is the max sum ending
            // at the current position) with the 'overall_max_sum' found previously.
            overall_max_sum = std::max(overall_max_sum, current_subarray_sum);
            
            // If the 'current_subarray_sum' becomes negative, it means this
            // subarray is no longer contributing positively to a larger sum.
            // We discard it by resetting 'current_subarray_sum' to 0, effectively
            // starting a new potential subarray from the next element.
            // This is the core greedy decision of Kadane's algorithm.
            if (current_subarray_sum < 0) {
                current_subarray_sum = 0;
            }
        }
        
        // After iterating through all elements, 'overall_max_sum' will hold
        // the maximum sum of any contiguous subarray.
        return overall_max_sum;
    }
};

```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | The algorithm iterates through the input array `nums` exactly once, performing a constant number of operations for each element. |
| **Space** | O(1) | The algorithm uses a fixed number of extra variables (`current_subarray_sum`, `overall_max_sum`) regardless of the input array's size. |

## 🔗 Related Problems
-   152. Maximum Product Subarray
-   121. Best Time to Buy and Sell Stock
-   209. Minimum Size Subarray Sum