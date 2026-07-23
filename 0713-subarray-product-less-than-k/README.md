# 0713-subarray-product-less-than-k

## 📋 Problem Description
Given an array of positive integers `nums` and an integer `k`, the task is to find and return the total number of contiguous subarrays where the product of all elements within that subarray is strictly less than `k`.

The function `numSubarrayProductLessThanK` receives:
*   `nums`: A vector (array) of integers.
*   `k`: An integer.

It must return:
*   An integer representing the count of valid subarrays.

## 🔍 Examples
```
Input: nums = [10,5,2,6], k = 100
Output: 8
Explanation: The 8 subarrays with a product strictly less than 100 are:
[10], [5], [2], [6], [10, 5], [5, 2], [2, 6], [5, 2, 6]
Note that [10, 5, 2] has a product of 100, which is not strictly less than k, so it's not included.

Input: nums = [1,2,3], k = 0
Output: 0
Explanation: Since k is 0, no product of positive integers can be strictly less than 0.

Input: nums = [1,1,1], k = 2
Output: 6
Explanation: All possible subarrays have a product of 1, which is less than 2:
[1], [1], [1], [1,1], [1,1], [1,1,1]
```

## 📌 Constraints
*   `1 <= nums.length <= 3 * 10^4`
*   `1 <= nums[i] <= 1000`
*   `0 <= k <= 10^6`

## 🤔 Understanding the Problem
The problem asks us to count all continuous segments (subarrays) within a given array `nums` such that if we multiply all numbers in that segment, the result is strictly less than `k`. A key aspect is "contiguous" – elements must be adjacent in the original array. Also, the product must be *strictly* less than `k`. Edge cases include `k=0` or `k=1`, where no product of positive integers can be strictly less than `k` (resulting in 0 valid subarrays). The product can grow very large, potentially exceeding standard integer limits, so `long long` should be used for product calculation.

## 💡 Core Idea
The core idea behind this solution is to systematically check all possible contiguous subarrays. For each potential starting element, we extend the subarray to the right, calculating the product as we go. If the product remains less than `k`, we count that subarray. If the product becomes `k` or greater, we stop extending from the current starting point, as any further extension will only result in an even larger product.

## 🧠 Approach — Brute Force with Optimization (Nested Loops)
This solution employs a **Brute Force with Optimization** strategy, specifically using nested loops. This pattern is suitable because it directly enumerates all possible subarrays. The outer loop fixes the starting point of a subarray, and the inner loop extends this subarray to the right, considering all possible ending points. The optimization comes from an "early exit" condition: once the product of a subarray reaches or exceeds `k`, we know that any further extension of this subarray (by including more elements to its right) will also result in a product greater than or equal to `k`. Therefore, we can `break` out of the inner loop and move to the next starting point, avoiding unnecessary calculations.

## 📝 Step-by-Step Algorithm
1.  Initialize a counter `count` to 0. This variable will store the total number of valid subarrays.
2.  Start an outer loop that iterates from `i = 0` to `nums.size() - 1`. This `i` represents the starting index of a potential subarray.
3.  Inside the outer loop, initialize a `long long` variable `prod` to 1. This `prod` will keep track of the product of elements in the current subarray being considered.
4.  Also, inside the outer loop, initialize an empty `vector<int> temp`. This vector is used to store the elements of the current subarray being built (though it's not strictly necessary for the final count, it helps visualize the subarrays).
5.  Start an inner loop that iterates from `j = i` to `nums.size() - 1`. This `j` represents the ending index of the current subarray.
6.  In each iteration of the inner loop:
    *   Multiply `prod` by `nums[j]`. This extends the current subarray by one element to the right.
    *   Check if `prod` is strictly less than `k`.
        *   If `prod < k`:
            *   Add `nums[j]` to the `temp` vector.
            *   Increment `count` by 1, because we found a valid subarray (`nums[i...j]`).
        *   If `prod >= k`:
            *   The current subarray `nums[i...j]` is not valid, and any subarray starting at `i` and extending beyond `j` will also have a product greater than or equal to `k`.
            *   Therefore, `break` out of the inner loop and proceed to the next starting index `i`.
7.  After both loops complete, return the final `count`.

## 💻 Solution
```cpp
class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        // Initialize a counter for valid subarrays.
        int count = 0;

        // Outer loop: iterates through all possible starting points 'i' for a subarray.
        for (int i = 0; i < nums.size(); i++) {
            // 'temp' vector is used to store the elements of the current subarray.
            // It's reset for each new starting point 'i'.
            // While not strictly necessary for the count, it can help visualize.
            vector<int> temp; 

            // 'prod' stores the product of elements in the current subarray [i...j].
            // Use long long to prevent overflow, as products can become very large.
            long long prod = 1; 

            // Inner loop: iterates through all possible ending points 'j' for a subarray,
            // starting from the current 'i'.
            for (int j = i; j < nums.size(); j++) {
                // Multiply the current product by the new element nums[j].
                prod *= nums[j];

                // Check if the product of the subarray [i...j] is strictly less than 'k'.
                if (prod < k) {
                    // If it is, this is a valid subarray.
                    // Add the current element to 'temp' (for visualization/debugging).
                    temp.push_back(nums[j]);
                    // Increment the total count of valid subarrays.
                    count++;
                } else {
                    // If the product is k or greater, then this subarray [i...j]
                    // and any longer subarray starting at 'i' (e.g., [i...j+1], [i...j+2]...)
                    // will also have a product >= k.
                    // So, we can stop extending from the current starting point 'i'.
                    break; 
                }
            }
        }
        // Return the total count of subarrays whose product is less than 'k'.
        return count;
    }
};

```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N^2) | The outer loop runs `N` times. In the worst-case scenario (e.g., `nums = [1,1,1,...], k = 1000`), the inner loop also runs up to `N` times for each `i`. This results in `N * N` operations. |
| **Space** | O(N) | The `temp` vector is created in each outer loop iteration. In the worst case (e.g., `i=0`), it can grow up to `N` elements before being reset. If the `temp` vector were removed, the auxiliary space would be O(1). |

## 🔗 Related Problems
*   209. Minimum Size Subarray Sum
*   3. Longest Substring Without Repeating Characters
*   1004. Max Consecutive Ones III