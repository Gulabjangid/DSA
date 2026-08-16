# 0152-maximum-product-subarray

## 📋 Problem Description
Given an integer array `nums`, the task is to find a contiguous non-empty subarray within it that has the largest product, and then return that product.

The problem guarantees that the product of any subarray will fit within a 32-bit integer. It's important to note that a subarray consisting of a single element has a product equal to its value.

**Input:** An integer array `nums`.
**Output:** An integer representing the maximum product of any subarray in `nums`.

## 🔍 Examples
```
Input: nums = [2,3,-2,4]
Output: 6
Explanation: The subarray [2,3] has the largest product 6.
```

```
Input: nums = [-2,0,-1]
Output: 0
Explanation: The subarray [-2,-1] has a product of 2, but it's not a valid subarray if 0 is included. A subarray must be contiguous. The maximum product here is 0, which can be achieved by the subarray [0].
```

## 📌 Constraints
*   `1 <= nums.length <= 2 * 10^4`
*   `-10 <= nums[i] <= 10`
*   The product of any subarray of `nums` is guaranteed to fit in a 32-bit integer.

## 🤔 Understanding the Problem
This problem asks us to find the maximum product of a contiguous subarray. It's similar to the "Maximum Subarray Sum" problem (Kadane's Algorithm), but multiplication introduces a crucial difference: negative numbers. A negative number multiplied by another negative number yields a positive number, which could potentially be a new maximum. This means we cannot simply discard negative products as we would negative sums. Zeros also act as "reset" points, as any product involving zero becomes zero.

## 💡 Core Idea
The key insight is that because multiplying by a negative number flips the sign, a very small (negative) product could become a very large (positive) product if multiplied by another negative number. Therefore, at each step, we need to track not only the maximum product ending at the current position but also the minimum product ending at the current position.

## 🧠 Approach — Dynamic Programming (Kadane's Algorithm Adaptation)
This problem can be solved using a dynamic programming approach, which is an adaptation of Kadane's algorithm. Kadane's algorithm is typically used for finding the maximum sum subarray. Here, we extend it to handle products. The reason this pattern fits is that the maximum (or minimum) product ending at the current index `i` depends only on the maximum and minimum products ending at the previous index `i-1`. We iterate through the array, maintaining two values: `max_product_ending_here` and `min_product_ending_here`. These values are updated at each step, considering the current number and its potential to extend or start a new product sequence.

## 📝 Step-by-Step Algorithm
1.  Initialize three variables:
    *   `maxp`: Stores the maximum product found so far ending at the current position. Initialize with `nums[0]`.
    *   `minp`: Stores the minimum product found so far ending at the current position. Initialize with `nums[0]`.
    *   `ans`: Stores the overall maximum product found across the entire array. Initialize with `nums[0]`.
2.  Iterate through the `nums` array starting from the second element (index `1`) up to the end.
3.  For each `num` at the current index `i`:
    *   We need to calculate the new maximum and minimum products that *could* end at this `num`. These new products depend on `num` itself, `maxp * num`, and `minp * num`.
    *   Crucially, if `num` is negative, `maxp * num` will be a smaller (more negative) number, and `minp * num` will be a larger (less negative or positive) number. This means the roles of `maxp` and `minp` effectively swap when multiplied by a negative number.
    *   To handle this elegantly, calculate `new_maxp` and `new_minp` using the current `num`, `maxp * num`, and `minp * num`.
    *   `new_maxp` will be the maximum of these three values: `num`, `maxp * num`, `minp * num`.
    *   `new_minp` will be the minimum of these three values: `num`, `maxp * num`, `minp * num`.
    *   Update `maxp` to `new_maxp`.
    *   Update `minp` to `new_minp`.
4.  After updating `maxp` for the current position, compare it with `ans` and update `ans = max(ans, maxp)` to keep track of the overall maximum product found so far.
5.  After the loop finishes, `ans` will hold the largest product of any subarray. Return `ans`.

## 💻 Solution
```cpp
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        // Initialize maxp (max product ending at current position),
        // minp (min product ending at current position),
        // and ans (overall maximum product found so far).
        // All are initialized with the first element, as a single element
        // is a valid subarray.
        int maxp = nums[0]; 
        int minp = nums[0];
        int ans = nums[0];

        // Iterate through the array starting from the second element.
        for (int i = 1; i < nums.size(); i++) {
            int num = nums[i]; // Current number in the array

            // We need to calculate the new maximum and minimum products that
            // can end at 'num'. These depend on:
            // 1. 'num' itself (starting a new subarray)
            // 2. 'maxp * num' (extending the previous max product)
            // 3. 'minp * num' (extending the previous min product - crucial for negatives)

            // Store previous maxp temporarily, as maxp will be updated first
            // and minp needs the *old* maxp value for its calculation.
            // Or, as done here, calculate newminp and newmaxp using the old maxp and minp
            // before updating them.
            
            // Calculate the new minimum product ending at 'num'.
            // It could be 'num' itself, or 'num' multiplied by the previous min product,
            // or 'num' multiplied by the previous max product (if 'num' is negative).
            int newminp = min({num, minp * num, maxp * num});
            
            // Calculate the new maximum product ending at 'num'.
            // It could be 'num' itself, or 'num' multiplied by the previous max product,
            // or 'num' multiplied by the previous min product (if 'num' is negative).
            int newmaxp = max({num, maxp * num, minp * num});

            // Update maxp and minp for the current position.
            maxp = newmaxp;
            minp = newminp;
            
            // Update the overall maximum product found so far.
            // The current maxp is a candidate for the global maximum.
            ans = max(ans, maxp);
        }
        
        // Return the overall maximum product.
        return ans;
    }
};

```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | The algorithm iterates through the `nums` array exactly once. Each step involves a constant number of arithmetic operations and comparisons. |
| **Space** | O(1) | The algorithm uses a fixed number of variables (`maxp`, `minp`, `ans`, `num`, `newminp`, `newmaxp`) regardless of the input array size. |

## 🔗 Related Problems
- 53. Maximum Subarray
- 1567. Maximum Length of Subarray With Positive Product
- 221. Maximal Square (General Dynamic Programming)