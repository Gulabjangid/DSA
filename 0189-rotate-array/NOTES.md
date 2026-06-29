# 0189-rotate-array

## 📋 Problem Description
Given an integer array `nums` and a non-negative integer `k`, rotate the array `nums` to the right by `k` steps. This means the last `k` elements of the array will move to the beginning, and all other elements will shift `k` positions to the right. The rotation should be performed in-place, modifying the original array directly.

The function `rotate` receives:
- `nums`: A reference to an integer array.
- `k`: An integer representing the number of steps to rotate.

The function does not return anything; it modifies `nums` directly.

## 🔍 Examples
```
Input: nums = [1,2,3,4,5,6,7], k = 3
Output: [5,6,7,1,2,3,4]
Explanation:
rotate 1 steps to the right: [7,1,2,3,4,5,6]
rotate 2 steps to the right: [6,7,1,2,3,4,5]
rotate 3 steps to the right: [5,6,7,1,2,3,4]
```

```
Input: nums = [-1,-100,3,99], k = 2
Output: [3,99,-1,-100]
Explanation: 
rotate 1 steps to the right: [99,-1,-100,3]
rotate 2 steps to the right: [3,99,-1,-100]
```

## 📌 Constraints
*   `1 <= nums.length <= 10^5`
*   `-2^31 <= nums[i] <= 2^31 - 1`
*   `0 <= k <= 10^5`

## 🤔 Understanding the Problem
The problem asks us to shift elements of an array to the right by `k` positions. When an element shifts past the end of the array, it wraps around to the beginning. A key aspect is that `k` can be larger than the array's length, `n`. In such cases, `k` rotations are equivalent to `k % n` rotations. For example, rotating an array of length 7 by 10 steps is the same as rotating it by `10 % 7 = 3` steps. The follow-up questions strongly suggest finding an in-place solution with `O(1)` extra space.

## 💡 Core Idea
The most efficient in-place solution leverages the property that reversing segments of an array can achieve rotation. By performing three specific reversals, we can rotate the array to the right by `k` steps without using significant extra space.

## 🧠 Approach — Array Reversal / In-place Manipulation
This problem can be elegantly solved using an in-place array manipulation technique involving reversals. This pattern is suitable because we need to rearrange elements within the existing array structure without allocating a new array. Reversing segments allows us to effectively move elements from one end to the other and then correctly orient them, fulfilling the rotation requirement with minimal overhead.

## 📝 Step-by-Step Algorithm
1.  **Normalize `k`**: First, calculate the effective number of rotations by taking `k` modulo the array's length (`n`). This handles cases where `k` is greater than or equal to `n`, ensuring we only perform the necessary rotations. If `k` becomes 0 after this step, no rotation is needed, and we can