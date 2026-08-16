# 0152-maximum-product-subarray

## 📋 Problem Description
Given an integer array `nums`, the task is to find a contiguous non-empty subarray within it that has the largest product. The function should return this maximum product.

The problem guarantees that the product of any subarray will fit within a 32-bit integer. It's important to note that a subarray with a single element has a product equal to its value.

## 🔍 Examples
```
Input: nums = [2,3,-2,4]
Output: 6
Explanation: The subarray [2,3] has the largest product 6.
```

```
Input: nums = [-2,0,-1]
Output: 0
Explanation: The subarray [0] has a product of 0. While [-2,-1] would yield 2, it's not a contiguous subarray due to the 0 in between. The maximum product here is 0.
```

## 📌 Constraints
*   `1 <= nums.length <= 2 * 10^4`
*   `-10 <= nums[i] <= 10`
*   The product of any subarray of `nums` is **guaranteed** to fit in a 32-bit integer.

## 🤔 Understanding the Problem
This problem asks us to find the maximum product of a contiguous subarray. It's a variation of the classic "Maximum Subarray Sum" problem (Kadane's Algorithm), but with a crucial difference: negative numbers. In sum problems, negative numbers always decrease the sum, so we can often discard negative prefixes. However, with products, multiplying two negative numbers results in a positive number. This means a very small (large negative) product could potentially become the largest product if multiplied by another negative number. Zeros also act as separators, effectively resetting any product calculation.

## 💡 Core Idea
The key insight is that at any given position `i`, the maximum product of a subarray ending at `i` can be influenced by three factors: the current number `nums[i]` itself, `nums[i]` multiplied by the previous maximum product, or `nums[i]` multiplied by the previous *minimum* product. The last case is vital because if `nums[i]` is negative, multiplying it by a previous minimum (large negative) product can yield a new maximum (large positive) product. Therefore, we need to track both the maximum and minimum products ending at each position.

## 🧠 Approach — Dynamic Programming (Kadane's Variation)
This problem can be efficiently solved using a dynamic programming approach, drawing inspiration from Kadane's algorithm. The pattern fits because the optimal solution for a subarray ending at the current index `i` can be derived from the optimal solutions (maximum and minimum products) for subarrays ending at `i-1`. By maintaining both the maximum and minimum products ending at the current position, we effectively handle the unique challenge posed by negative numbers, where a minimum product can become a maximum product after multiplication.

## 📝 Step-by-Step Algorithm
1.  Initialize `max_overall_product` (let's call it `G` as in the code) with `nums[0]`. This variable will store the global maximum product found across all subarrays.
2.  Initialize `max_product_ending_here` and `min_product_ending_here` with `nums[0]`. These variables will track the maximum and minimum products of any subarray that *ends* at the current index.
3.  Iterate through the `nums` array starting from the second element (index `i = 1`) up to the end.
4.  For each `nums[i]` (let's call it `current_num`):
    a.  **Crucially**, store the current `max_product_ending_here` and `min_product_ending_here` into temporary variables (e.g., `prev_max_prod`, `prev_min_prod`). This is necessary because both values from the *previous* step are needed to calculate the new `max_product_ending_here` and `min_product_ending_here` for the current step. If we update them directly, one calculation might use an already updated value meant for the next step.
    b.  Calculate the new `max_product_ending_here`. It will be the maximum of three values:
        i.  `current_num` itself (representing a new subarray starting from `current_num`).
        ii. `current_num * prev_max_prod` (extending the previous maximum product).
        iii. `current_num * prev_min_prod` (extending the previous minimum product, which could become a new maximum if `current_num` is negative).
    c.  Calculate the new `min_product_ending_here`. It will be the minimum of three values:
        i.  `current_num` itself.
        ii. `current_num * prev_max_prod`.
        iii. `current_num * prev_min_prod`.
    d.  Update `max_overall_product` (`G`) by taking the maximum of its current value and the newly calculated `max_product_ending_here`.
5.  After the loop finishes iterating through all elements, `max_overall_product` (`G`) will hold the largest product found among all contiguous subarrays. Return `G`.

## 💻 Solution
```cpp
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        // G stores the overall maximum product found across all subarrays.
        // It's initialized with the first element, as a single element is a valid subarray
        // and could be the answer if all other products are smaller.
        int G = nums[0];
        
        // minprod stores the minimum product of a subarray ending at the current position.
        // maxprod stores the maximum product of a subarray ending at the current position.
        // Both are initialized with the first element.
        int minprod = nums[0];
        int maxprod = nums[0];

        // Iterate through the array starting from the second element (index 1).
        // The base cases for the first element are handled by the initializations above.
        for (int i = 1; i < nums.size(); i++) {
            // 'ans' represents the current number being processed from the array.
            int ans = nums[i];
            
            // To correctly calculate the new minprod and maxprod for the current position 'i',
            // we need the minprod and maxprod values from the *previous* position 'i-1'.
            // If we update minprod/maxprod directly, we would lose the previous values needed for the other calculation.
            // Therefore, we store the potential new min/max products in temporary variables first.

            // Tempmin will be the new minimum product of a subarray ending at index 'i'.
            // It can be the minimum of three possibilities:
            // 1. 'ans' itself: Starting a new subarray from just 'ans'.
            // 2. 'ans' * minprod: Extending the previous minimum product.
            // 3. 'ans' * maxprod: Extending the previous maximum product. This is crucial if 'ans' is negative,
            //    as it can turn a large positive maxprod into a large negative minprod.
            int Tempmin = min({ans, ans * minprod, ans * maxprod});
            
            // Tempmax will be the new maximum product of a subarray ending at index 'i'.
            // It can be the maximum of three possibilities:
            // 1. 'ans' itself: Starting a new subarray from just 'ans'.
            // 2. 'ans' * minprod: Extending the previous minimum product. This is crucial if 'ans' is negative,
            //    as it can turn a large negative minprod into a large positive maxprod.
            // 3. 'ans' * maxprod: Extending the previous maximum product.
            int Tempmax = max({ans, ans * minprod, ans * maxprod});

            // Update minprod and maxprod for the current position 'i' using the temporary values.
            maxprod = Tempmax;
            minprod = Tempmin;

            // Update the overall maximum product found so far.
            // G should always store the largest product encountered up to the current point.
            G = max(G, maxprod);
        }
        // After iterating through all elements, G holds the largest product found among all subarrays.
        return G;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | We iterate through the input array `nums` exactly once. Each step within the loop involves a constant number of arithmetic operations and comparisons. |
| **Space** | O(1) | We only use a few constant extra variables (`G`, `minprod`, `maxprod`, `Tempmin`, `Tempmax`) regardless of the size of the input array. |

## 🔗 Related Problems
- 53. Maximum Subarray
- 1567. Maximum Length of Subarray With Positive Product
- 209. Minimum Size Subarray Sum