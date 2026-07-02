# 0918-maximum-sum-circular-subarray

## 📋 Problem Description
Given a circular integer array `nums` of length `n`, the task is to find and return the maximum possible sum of a non-empty subarray.

A "circular array" implies that the end of the array connects to its beginning. For example, the element after `nums[i]` is `nums[(i + 1) % n]`, and the element before `nums[i]` is `nums[(i - 1 + n) % n]`.

A "subarray" must include each element of the fixed buffer `nums` at most once. This means a subarray like `nums[i], nums[i + 1], ..., nums[j]` cannot wrap around multiple times to include the same physical element more than once.

The function receives a `std::vector<int> nums` as input and must return an `int` representing the maximum subarray sum.

## 🔍 Examples
```
Input: nums = [1,-2,3,-2]
Output: 3
Explanation: The subarray [3] has the maximum sum of 3.
```

```
Input: nums = [5,-3,5]
Output: 10
Explanation: The subarray [5,5] (which wraps around, taking nums[0] and nums[2]) has the maximum sum of 5 + 5 = 10.
```

```
Input: nums = [-3,-2,-3]
Output: -2
Explanation: The subarray [-2] has the maximum sum of -2. In this case, all numbers are negative, so the maximum sum is the least negative number.
```

## 📌 Constraints
*   `n == nums.length`
*   `1 <= n <= 3 * 10^4`
*   `-3 * 10^4 <= nums[i] <= 3 * 10^4`

## 🤔 Understanding the Problem
This problem extends the classic "Maximum Subarray Sum" problem by introducing a circular array. This means a subarray can potentially wrap around from the end of the array back to the beginning. The challenge lies in efficiently handling both standard (non-wrapping) subarrays and those that span across the array's circular boundary, while ensuring each element is used at most once. An important edge case to consider is when all numbers in the array are negative.

## 💡 Core Idea
The core idea is to realize that a maximum sum circular subarray can be one of two types: either it's a standard non-wrapping subarray (which can be found using Kadane's Algorithm), or it's a wrapping subarray. A wrapping subarray can be thought of as the total sum of the array minus the minimum sum non-wrapping subarray.

## 🧠 Approach — Kadane's Algorithm Variation
This problem is solved by applying a variation of **Kadane's Algorithm**. Kadane's Algorithm is a dynamic programming approach used to find the maximum sum of a contiguous subarray within a one-dimensional array.

This pattern fits the problem because we can break down the "maximum sum circular subarray" into two distinct cases:
1.  **Case 1: The maximum sum subarray does NOT wrap around.** This is the standard maximum subarray problem, directly solvable with Kadane's Algorithm.
2.  **Case 2: The maximum sum subarray DOES wrap around.** If a subarray wraps around, it means it includes elements from both the beginning and the end of the linear array. This implies that some contiguous block of elements in the *middle* of the linear array is *excluded*. The sum of such a wrapping subarray is equivalent to `(Total Sum of Array) - (Minimum Sum Subarray in the middle)`. We can find the minimum sum subarray using a modified version of Kadane's Algorithm.

By comparing the maximum sum from Case 1 and Case 2, we can determine the overall maximum sum circular subarray. A crucial edge case is when all numbers in the array are negative, where the `Total Sum - Minimum Sum Subarray` logic might yield an incorrect positive result (e.g., 0), so this scenario needs special handling.

## 📝 Step-by-Step Algorithm

1.  **Calculate Maximum Non-Wrapping Subarray Sum (Kadane's `kedans` function):**
    *   Initialize `max_so_far` and `current_max` to the first element of the array.
    *   Iterate through the array starting from the second element:
        *   For each element, `current_max` becomes the maximum of the current element itself, or the current element added to `current_max`. This ensures we either extend the current subarray or start a new one.
        *   Update `max_so_far` with the maximum of `max_so_far` and `current_max`.
    *   Return `max_so_far`. This value represents the maximum sum of a subarray that does not wrap around.

2.  **Handle All Negative Numbers Edge Case:**
    *   If the `max_so_far` calculated in step 1 is negative, it means all numbers in the array are negative (or zero, but the largest sum would still be the least negative number). In this scenario, any wrapping subarray would involve summing more negative numbers, resulting in an even smaller (more negative) sum. Therefore, if `max_so_far` is negative, this is the overall maximum sum, and we can return it immediately.

3.  **Calculate Total Sum of the Array:**
    *   Iterate through the entire array and sum all its elements. Store this in `total_sum`.

4.  **Calculate Minimum Non-Wrapping Subarray Sum (Kadane's `Rkedans` function):**
    *   Initialize `min_so_far` and `current_min` to the first element of the array.
    *   Iterate through the array starting from the second element:
        *   For each element, `current_min` becomes the minimum of the current element itself, or the current element added to `current_min`. This finds the minimum sum ending at the current position.
        *   Update `min_so_far` with the minimum of `min_so_far` and `current_min`.
    *   Return `min_so_far`. This value represents the minimum sum of a subarray that does not wrap around.

5.  **Calculate Maximum Wrapping Subarray Sum:**
    *   The maximum sum of a subarray that wraps around is `total_sum - min_so_far`. This is because removing the minimum sum subarray leaves the remaining elements, which form a wrapping subarray with the maximum possible sum.

6.  **Determine Overall Maximum:**
    *   The final answer is the maximum of the `max_so_far` (from step 1, representing non-wrapping subarrays) and `total_sum - min_so_far` (from step 5, representing wrapping subarrays).

## 💻 Solution

```cpp
class Solution {
public:
    // Helper function to find the maximum sum of a contiguous subarray (Kadane's Algorithm)
    int kedans(vector<int>& nums){
        // cursum tracks the maximum sum of a subarray ending at the current position
        int cursum = nums[0];
        // maxsum tracks the overall maximum sum found so far
        int maxsum = nums[0];

        // Iterate through the array starting from the second element
        for(int i = 1; i < nums.size(); i++){
            // For each element, decide whether to extend the current subarray
            // or start a new one from the current element.
            // If (cursum + nums[i]) is less than nums[i], it means cursum was negative
            // and starting a new subarray from nums[i] is better.
            cursum = max(nums[i], cursum + nums[i]);
            
            // Update the overall maximum sum found
            maxsum = max(cursum, maxsum);
            
            // This line is a common variation in Kadane's. If cursum becomes negative,
            // it means the subarray ending here is detrimental to future sums,
            // so we effectively "reset" it to 0 to start a new positive sequence.
            // However, since maxsum is updated *before* this reset, and cursum is
            // initialized to nums[0] and updated with max(nums[i], ...),
            // this specific reset isn't strictly necessary for correctness in this context
            // but doesn't harm it either. It ensures cursum doesn't drag down future sums
            // if it's already negative.
            if(cursum < 0){
                cursum = 0;
            }
        }
        return maxsum;
    }

    // Helper function to find the minimum sum of a contiguous subarray (Modified Kadane's)
    int Rkedans(vector<int>& nums){
        // cursum tracks the minimum sum of a subarray ending at the current position
        int cursum = nums[0];
        // minsum tracks the overall minimum sum found so far
        int minsum = nums[0];

        // Iterate through the array starting from the second element
        for(int i = 1; i < nums.size(); i++){
            // For each element, decide whether to extend the current subarray
            // or start a new one from the current element.
            // If (cursum + nums[i]) is greater than nums[i], it means cursum was positive
            // and starting a new subarray from nums[i] is better for minimizing.
            cursum = min(nums[i], cursum + nums[i]);
            
            // Update the overall minimum sum found
            minsum = min(cursum, minsum);
        }
        return minsum;
    }

    // Main function to find the maximum sum of a circular subarray
    int maxSubarraySumCircular(vector<int>& nums) {
        // Step 1: Find the maximum sum of a non-wrapping subarray using Kadane's
        int maxsub = kedans(nums);

        // Step 2: Handle the edge case where all numbers are negative.
        // If maxsub is negative, it means the largest single element (or sum of elements)
        // is negative. In this case, any wrapping subarray would involve summing more
        // negative numbers, resulting in an even smaller sum.
        // So, maxsub itself is the answer.
        if(maxsub < 0)
            return maxsub;
        
        // Step 3: Calculate the total sum of all elements in the array
        int total = 0;
        for(int i = 0; i < nums.size(); i++){
            total += nums[i];
        }

        // Step 4: Find the minimum sum of a non-wrapping subarray
        int rked = Rkedans(nums);
        
        // Step 5: Calculate the maximum sum of a wrapping subarray.
        // This is equivalent to the total sum minus the minimum sum subarray.
        // The minimum sum subarray represents the "gap" in the circular array.
        int minisub = total - rked;

        // Step 6: The overall maximum sum is the greater of the two cases:
        // 1. The maximum non-wrapping subarray sum (maxsub)
        // 2. The maximum wrapping subarray sum (minisub)
        int answer = max(minisub, maxsub);
        return answer;  
    }
};
```

## ⏱️ Complexity Analysis

| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | The solution involves three linear passes over the array: one for `kedans`, one for `Rkedans`, and one for calculating the `total` sum. Each pass takes O(N) time, where N is the number of elements in `nums`. |
| **Space** | O(1) | The solution uses a constant amount of extra space for variables like `cursum`, `maxsum`, `minsum`, `total`, etc., regardless of the input array size. |

## 🔗 Related Problems
- 53. Maximum Subarray
- 152. Maximum Product Subarray
- 209. Minimum Size Subarray Sum