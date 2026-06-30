# 0238-product-of-array-except-self

## 📋 Problem Description
Given an integer array `nums`, the task is to return a new array, `answer`, where `answer[i]` is equal to the product of all the elements of `nums` *except* `nums[i]`.

The problem guarantees that the product of any prefix or suffix of `nums` will fit within a 32-bit integer.

The algorithm must adhere to two specific constraints:
1. It must run in `O(n)` time complexity.
2. It must *not* use the division operation.

## 🔍 Examples
```
Input: nums = [1,2,3,4]
Output: [24,12,8,6]
Explanation:
For answer[0] (nums[0]=1): product of [2,3,4] is 24
For answer[1] (nums[1]=2): product of [1,3,4] is 12
For answer[2] (nums[2]=3): product of [1,2,4] is 8
For answer[3] (nums[3]=4): product of [1,2,3] is 6
```

```
Input: nums = [-1,1,0,-3,3]
Output: [0,0,9,0,0]
Explanation:
For answer[0] (nums[0]=-1): product of [1,0,-3,3] is 0
For answer[1] (nums[1]=1): product of [-1,0,-3,3] is 0
For answer[2] (nums[2]=0): product of [-1,1,-3,3] is 9
For answer[3] (nums[3]=-3): product of [-1,1,0,3] is 0
For answer[4] (nums[4]=3): product of [-1,1,0,-3] is 0
```

## 📌 Constraints
*   `2 <= nums.length <= 10^5`
*   `-30 <= nums[i] <= 30`
*   The product of any prefix or suffix of `nums` is guaranteed to fit in a 32-bit integer.
*   The input is generated such that `answer[i]` is guaranteed to fit in a 32-bit integer.
*   Must run in `O(n)` time.
*   Must not use the division operation.
*   Follow-up: Can be solved in `O(1)` extra space complexity? (The output array does not count as extra space for space complexity analysis.)

## 🤔 Understanding the Problem
The core of this problem is to calculate the product of all elements *except* the one at the current index. A naive approach might involve iterating through the array for each element, calculating the product of the remaining `n-1` elements, leading to an `O(n^2)` solution. Another straightforward approach would be to calculate the total product of all elements and then divide by `nums[i]` for each `answer[i]`. However, the problem explicitly forbids division and requires an `O(n)` time complexity. This means we need a more clever way to compute these products. The "no division" constraint is the primary challenge, especially when `nums[i]` could be zero.

## 💡 Core Idea
For any given index `i`, the product of all elements *except* `nums[i]` can be expressed as the product of all elements to its left multiplied by the product of all elements to its right.

## 🧠 Approach — Prefix/Suffix Products
This problem is perfectly suited for the **Prefix/Suffix Products** pattern. This pattern involves making multiple passes over an array to precompute cumulative values (like sums or products) from both the beginning (prefix) and the end (suffix).

The reason this pattern fits so well here is that it allows us to break down the complex "product of everything except self" into two simpler, independent calculations:
1.  **Prefix Products**: For each index `i`, calculate the product of all elements `nums[0]` through `nums[i-1]`.
2.  **Suffix Products**: For each index `i`, calculate the product of all elements `nums[i+1]` through `nums[n-1]`.

By combining these two precomputed values for each index `i`, we can obtain the final `answer[i]` in `O(1)` time per element, leading to an overall `O(n)` solution without using division. The solution also cleverly reuses the output array to store these intermediate products, achieving `O(1)` extra space.

## 📝 Step-by-Step Algorithm

1.  **Initialize Result Array**: Create an array `answer` of the same size as `nums`, and initialize all its elements to `1`. This array will eventually hold our final result.

2.  **First Pass (Calculate Left Products)**:
    *   Initialize a variable `leftProduct` to `1`. This variable will keep track of the product of elements encountered so far from the left.
    *   Iterate through the `nums` array from left to right (from index `0` to `n-1`).
    *   For each index `i`:
        *   Set `answer[i]` to the current value of `leftProduct`. At this point, `answer[i]` stores the product of all elements *before* `nums[i]`.
        *   Update `leftProduct` by multiplying it with `nums[i]`. This prepares `leftProduct` for the next iteration, so it will correctly represent the product of elements up to and including `nums[i]`.

3.  **Second Pass (Calculate Right Products and Combine)**:
    *   Initialize a variable `rightProduct` to `1`. This variable will keep track of the product of elements encountered so far from the right.
    *   Iterate through the `nums` array from right to left (from index `n-1` down to `0`).
    *   For each index `i`:
        *   Multiply `answer[i]` (which currently holds the product of elements to its left) by the current value of `rightProduct`. This combines the left product with the product of all elements *after* `nums[i]`, giving us the final desired product for `answer[i]`.
        *   Update `rightProduct` by multiplying it with `nums[i]`. This prepares `rightProduct` for the next iteration, so it will correctly represent the product of elements from the right up to and including `nums[i]`.

4.  **Return Result**: After both passes, the `answer` array will contain the product of all elements except `nums[i]` at each index `i`. Return this `answer` array.

## 💻 Solution
```cpp
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        // Initialize the result array 'r' with size 'n' and all elements set to 1.
        // This array will store our final answer.
        // It's also used to store intermediate prefix products.
        vector<int> r(n, 1); 
        
        // Step 1: Calculate prefix products (everything to the left of current index)
        // 'leftProduct' will accumulate the product of elements from the beginning of the array.
        int leftProduct = 1;
        for(int i = 0; i < n; i++) {
            // At index 'i', r[i] should store the product of elements BEFORE nums[i].
            // So, we assign the current 'leftProduct' (which is the product of nums[0]...nums[i-1]) to r[i].
            r[i] = leftProduct;
            
            // Then, update 'leftProduct' by multiplying it with the current element nums[i].
            // This prepares 'leftProduct' for the next iteration (i+1), where it will represent
            // the product of nums[0]...nums[i].
            leftProduct *= nums[i];
        }
        
        // After this loop, r[i] contains:
        // r[0] = 1 (product of nothing to the left of nums[0])
        // r[1] = nums[0]
        // r[2] = nums[0] * nums[1]
        // ...
        // r[i] = nums[0] * ... * nums[i-1]

        // Step 2: Calculate suffix products (everything to the right of current index)
        // and combine them with the prefix products already stored in 'r'.
        // 'rightProduct' will accumulate the product of elements from the end of the array.
        int rightProduct = 1;
        for(int i = n - 1; i >= 0; i--) {
            // r[i] currently holds the product of elements to its left (prefix product).
            // We multiply it by 'rightProduct' (which is the product of nums[i+1]...nums[n-1]).
            // This combines the left and right products to get the final answer for r[i].
            r[i] *= rightProduct; 
            
            // Then, update 'rightProduct' by multiplying it with the current element nums[i].
            // This prepares 'rightProduct' for the next iteration (i-1), where it will represent
            // the product of nums[i]...nums[n-1].
            rightProduct *= nums[i];
        }
        
        // After this loop, r[i] contains:
        // (product of nums[0]...nums[i-1]) * (product of nums[i+1]...nums[n-1])
        // which is exactly the product of all elements except nums[i].
        
        return r; // Return the final result array.
    }
};

```

## ⏱️ Complexity Analysis

| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | The algorithm involves two separate passes over the `nums` array. Each pass iterates `N` times, performing constant time operations. Therefore, the total time complexity is O(N) + O(N) = O(N). |
| **Space** | O(1) | The problem statement specifies that the output array does not count as extra space. Aside from the output array, we only use a few constant extra variables (`n`, `leftProduct`, `rightProduct`). Thus, the auxiliary space complexity is O(1). |

## 🔗 Related Problems
- 724. Find Pivot Index (Prefix Sums)
- 53. Maximum Subarray (Kadane's Algorithm, can be seen as a form of prefix sum optimization)
- 209. Minimum Size Subarray Sum (Sliding Window, but often involves prefix sums for alternative solutions)