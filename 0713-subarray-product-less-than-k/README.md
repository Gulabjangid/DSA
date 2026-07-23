# 0713-subarray-product-less-than-k

## 📋 Problem Description
Given an array of positive integers `nums` and an integer `k`, the task is to find and return the total number of contiguous subarrays where the product of all elements within that subarray is strictly less than `k`.

The function `numSubarrayProductLessThanK` receives:
- `nums`: A vector (array) of integers.
- `k`: An integer.

It must return:
- An integer representing the count of valid subarrays.

## 🔍 Examples
```
Input: nums = [10,5,2,6], k = 100
Output: 8
Explanation: The 8 subarrays with a product strictly less than 100 are:
[10], [5], [2], [6], [10, 5], [5, 2], [2, 6], [5, 2, 6]
Note that [10, 5, 2] is not included because its product (100) is not strictly less than k.

Input: nums = [1,2,3], k = 0
Output: 0
Explanation: No subarray can have a product strictly less than 0, as all numbers in nums are positive.

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
The problem asks us to count all contiguous subarrays whose elements, when multiplied together, result in a value strictly less than `k`. This means we need to consider every possible subarray. A key challenge is that the product can grow very large quickly, potentially exceeding standard integer limits if not handled carefully (though `long long` helps). Additionally, `k` can be 0 or 1, in which case no product of positive integers can be strictly less than `k`, so the answer would be 0. The "contiguous" requirement means elements must be adjacent in the original array.

## 💡 Core Idea
The core idea behind this solution is to systematically check every possible subarray. For each starting position `i`, we extend a subarray to the right, multiplying elements one by one. As long as the product remains less than `k`, we count the current subarray. If the product becomes `k` or greater, we stop extending from the current starting position `i` because any further extension will only result in an even larger product.

## 🧠 Approach — Brute Force with Early Exit Optimization
This solution employs a "Brute Force with Early Exit Optimization" strategy. It iterates through all possible starting points (`i`) for subarrays. For each starting point, it then iterates through all possible ending points (`j`) from `i` to the end of the array. This forms every possible contiguous subarray. The "early exit optimization" comes into play: if the product of elements in a subarray `nums[i...j]` becomes greater than or equal to `k`, there's no need to extend this subarray further (i.e., check `nums[i...j+1]`, `nums[i...j+2]`, etc.) because their products will also be greater than or equal to `k` (since all `nums[i]` are positive). This optimization helps prune the search space, though in the worst case, it still checks many subarrays.

## 📝 Step-by-Step Algorithm
1.  Initialize a counter `count` to 0. This variable will store the total number of valid subarrays.
2.  Start an outer loop with an index `i` from `0` to `nums.size() - 1`. This `i` represents the starting index of a potential subarray.
3.  Inside the outer loop, initialize a `long long` variable `prod` to `1`. This `prod` will keep track of the product of elements in the current subarray being considered, starting from `nums[i]`. Using `long long` is important to prevent overflow, as products can become large.
4.  Also, inside the outer loop, a `vector<int> temp` is declared. While present in the provided solution, it's not strictly necessary for counting and can be ignored for the core logic.
5.  Start an inner loop with an index `j` from `i` to `nums.size() - 1`. This `j` represents the ending index of the current subarray.
6.  In each iteration of the inner loop, multiply `prod` by `nums[j]`. This extends the current subarray `nums[i...j]` by including `nums[j]`.
7.  Check if the updated `prod` is strictly less than `k`:
    *   If `prod < k`: This means the subarray `nums[i...j]` is a valid subarray. Increment `count` by 1. (The `temp.push_back(nums[j]);` line in the code would add `nums[j]` to `temp`, but as mentioned, `temp` is not used for the final count).
    *   If `prod >= k`: This means the subarray `nums[i...j]` (and any longer subarray starting at `i`) is not valid. Since all numbers are positive, extending this subarray further will only make the product larger. Therefore, `break` out of the inner loop and proceed to the next starting index `i+1`.
8.  After both loops complete, return the final `count`.

## 💻 Solution
```cpp
class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        // Initialize a counter for valid subarrays.
        int count = 0;

        // Outer loop: iterates through all possible starting points 'i' for subarrays.
        for (int i = 0; i < nums.size(); i++) {
            // 'temp' vector is declared here. It's not strictly necessary for the counting logic
            // but would store the elements of the current valid subarray if needed for other purposes.
            // It gets re-initialized for each new starting 'i'.
            vector<int> temp; 

            // Initialize product for the current subarray starting at 'i'.
            // Use long long to prevent potential integer overflow, as products can grow large.
            long long prod = 1;

            // Inner loop: iterates through all possible ending points 'j' for subarrays
            // starting from the current 'i'.
            for (int j = i; j < nums.size(); j++) {
                // Multiply the current product by the element at index 'j'.
                // This extends the subarray nums[i...j].
                prod *= nums[j];

                // Check if the product of the current subarray nums[i...j] is strictly less than 'k'.
                if (prod < k) {
                    // If it is, this subarray is valid.
                    // Add the current element to 'temp' (if 'temp' were being used to store valid subarrays).
                    // temp.push_back(nums[j]); 
                    // Increment the total count of valid subarrays.
                    count++;
                } else {
                    // If the product is no longer strictly less than 'k' (i.e., prod >= k),
                    // then any further extension of this subarray (nums[i...j+1], etc.)
                    // will also have a product >= k (since all nums[x] are positive).
                    // So, we can stop checking subarrays starting at 'i' and break out of the inner loop.
                    break;
                }
            }
        }
        // Return the total count of subarrays whose product is strictly less than 'k'.
        return count;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N^2) | The solution uses nested loops. The outer loop runs `N` times. In the worst-case scenario (e.g., `nums = [1,1,1,...,1]` and `k` is a very large number), the inner loop also runs approximately `N` times for each iteration of the outer loop. This results in `N * N` operations. |
| **Space** | O(N) | The `temp` vector is declared inside the outer loop. In the worst case (e.g., `nums = [1,1,1,...,1]`, `k` is large), `temp` could store up to `N` elements for a single iteration of the outer loop before being re-initialized. If `temp` were removed (as it's not strictly needed for the count), the auxiliary space complexity would be O(1). |

## 🔗 Related Problems
- 209. Minimum Size Subarray Sum
- 3. Longest Substring Without Repeating Characters
- 1004. Max Consecutive Ones III