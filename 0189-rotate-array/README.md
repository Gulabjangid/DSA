# 0189-rotate-array

## 📋 Problem Description
Given an integer array `nums` and a non-negative integer `k`, the task is to rotate the array to the right by `k` steps. This means that elements from the end of the array will move to the beginning, and existing elements will shift to the right. The modification must be performed in-place, meaning you should modify the original `nums` array directly without using extra space proportional to the input size.

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
The problem asks us to shift all elements of an array to the right by `k` positions. An important detail is that `k` can be larger than the array's length, meaning the array might be rotated multiple full times; only the remainder of `k` after division by `n` (array length) truly matters. The core challenge is to achieve this rotation efficiently and, as a follow-up suggests, in-place, using minimal or no extra memory.

## 💡 Core Idea
The key insight is that rotating an array to the right by `k` positions can be achieved by performing three strategic reversals: first, reverse the entire array; then, reverse the first `k` elements; finally, reverse the remaining `n-k` elements.

## 🧠 Approach — Reversal Algorithm
This problem is elegantly solved using the "Reversal Algorithm" or "Three Reversals" pattern. This pattern is ideal for array rotation problems because it allows for an in-place modification with optimal time complexity. By carefully reversing segments of the array, we can achieve the desired rotation without the need for auxiliary arrays or costly element-by-element shifting. The method leverages the property that reversing a segment twice restores its original order, and a single reversal can effectively move elements from one end to another.

## 📝 Step-by-Step Algorithm
1.  **Normalize `k`**: First, calculate the effective number of rotations needed. This is done by taking `k` modulo the array's length (`n`). So, `k = k % n`. This handles cases where `k` is greater than `n`, reducing it to the minimum equivalent rotations. If `k` becomes 0 after this, no rotation is needed, and the function can return.
2.  **Reverse the entire array**: Reverse all elements in the `nums` array from index `0` to `n-1`. After this step, the elements that should eventually end up at the beginning of the rotated array are now at the end, but in reverse order.
3.  **Reverse the first `k` elements**: Reverse the elements from index `0` to `k-1`. This brings the `k` elements that originally were at the very end of the array (and are now at the beginning after the first reversal) into their correct relative order.
4.  **Reverse the remaining `n-k` elements**: Reverse the elements from index `k` to `n-1`. This similarly arranges the remaining `n-k` elements into their correct relative order.
After these three reversals, the array will be correctly rotated to the right by `k` steps.

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | Each reversal operation iterates through a portion of the array, and we perform a constant number (three) of these reversals. |
| **Space** | O(1) | The rotation is performed in-place by modifying the original array directly, without using any additional data structures proportional to the input size. |

## 🔗 Related Problems
- 151. Reverse Words in a String
- 557. Reverse Words in a String III
- 186. Reverse Words in a String II