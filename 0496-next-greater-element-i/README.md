# 0496-next-greater-element-i

## 📋 Problem Description
You are given two distinct 0-indexed integer arrays, `nums1` and `nums2`, where `nums1` is a subset of `nums2`.
The "next greater element" of an element `x` in an array is defined as the first element greater than `x` that appears to its right within the same array.

Your task is to find the next greater element for each number in `nums1`. For every `nums1[i]`, you first need to locate its corresponding value in `nums2`. Then, you must determine the next greater element for that value within `nums2`. If no such greater element exists to its right, the answer for that query should be -1.

The function should return an array `ans` of the same length as `nums1`, where `ans[i]` is the next greater element for `nums1[i]` as described.

## 🔍 Examples
```
Input: nums1 = [4,1,2], nums2 = [1,3,4,2]
Output: [-1,3,-1]
Explanation:
- For 4 in nums1: It's found in nums2 = [1,3,4,2]. There is no element greater than 4 to its right. So, -1.
- For 1 in nums1: It's found in nums2 = [1,3,4,2]. The next greater element to its right is 3. So, 3.
- For 2 in nums1: It's found in nums2 = [1,3,4,2]. There is no element greater than 2 to its right. So, -1.

Input: nums1 = [2,4], nums2 = [1,2,3,4]
Output: [3,-1]
Explanation:
- For 2 in nums1: It's found in nums2 = [1,2,3,4]. The next greater element to its right is 3. So, 3.
- For 4 in nums1: It's found in nums2 = [1,2,3,4]. There is no element greater than 4 to its right. So, -1.
```

## 📌 Constraints
*   `1 <= nums1.length <= nums2.length <= 1000`
*   `0 <= nums1[i], nums2[i] <= 10^4`
*   All integers in `nums1` and `nums2` are unique.
*   All integers of `nums1` also appear in `nums2`.

## 🤔 Understanding the Problem
The problem asks us to find a specific value (the "next greater element to the right") for each number in `nums1`, but by searching within the `nums2` array. Since `nums1` is a subset of `nums2`, every number from `nums1` will definitely be present in `nums2`. The non-trivial part is efficiently finding this "next greater element" for potentially many queries, especially given the "to the right" condition. A naive approach of searching for each `nums1[i]` in `nums2` and then scanning to its right would be too slow.

## 💡 Core Idea
The key insight is that we can precompute the "next greater element" for *every* number in `nums2` in a single pass. Once we have this information, finding the answer for each number in `nums1` becomes a simple lookup.

## 🧠 Approach — Monotonic Stack
This problem is a classic application of a **Monotonic Stack**.
A monotonic stack is a stack where the elements are always kept in a specific order (either strictly increasing or strictly decreasing). It's particularly useful for problems that involve finding the "next greater/smaller element" or "previous greater/smaller element" to the left or right of a given element in an array.
Here, we need the "next greater element to the right". By iterating through `nums2` from right to left and maintaining a decreasing monotonic stack, we can efficiently determine the next greater element for each number. When we encounter a number, we pop all smaller or equal elements from the stack (because they can't be the "next greater" for any future elements to their left). The top of the stack then becomes the next greater element for the current number.

## 📝 Step-by-Step Algorithm

1.  **Initialize Data Structures:**
    *   Create an `unordered_map` (hash map), let's call it `nextGreaterMap`, to store the mapping from a number in `nums2` to its next greater element.
    *   Create an empty `stack`, let's call it `s`. This stack will maintain elements in decreasing order.

2.  **Process `nums2` from Right to Left:**
    *   Iterate through `nums2` starting from the last element (`nums2.size() - 1`) down to the first element (`0`). Let the current element be `currentNum = nums2[i]`.

3.  **Maintain Monotonic Stack and Find NGE:**
    *   **Pop Smaller Elements:** While the stack `s` is not empty AND the element at the top of `s` is less than or equal to `currentNum`, pop elements from `s`. This ensures that any elements remaining on the stack are strictly greater than `currentNum` and are to its right.
    *   **Determine NGE for `currentNum`:**
        *   If, after popping, the stack `s` is empty, it means there is no element to the right of `currentNum` that is greater than it. In this case, store `-1` as the next greater element for `currentNum` in `nextGreaterMap` (i.e., `nextGreaterMap[currentNum] = -1`).
        *   If the stack `s` is not empty, the element at the top of `s` is the first element to the right of `currentNum` that is greater than it. Store this value in `nextGreaterMap` (i.e., `nextGreaterMap[currentNum] = s.top()`).
    *   **Push `currentNum` onto Stack:** Push `currentNum` onto the stack `s`. This maintains the decreasing monotonic property of the stack for elements to the right of the current processing point.

4.  **Construct Result for `nums1`:**
    *   Create an empty `vector<int>`, let's call it `ans`, to store the final results.
    *   Iterate through `nums1` from left to right. For each `nums1[i]`:
        *   Look up `nums1[i]` in `nextGreaterMap` to get its precomputed next greater element.
        *   Add this value to the `ans` vector.

5.  **Return `ans`:** Return the `ans` vector.

## 💻 Solution

```cpp
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        // nextGreaterMap will store the next greater element for each number encountered in nums2.
        // Key: number from nums2, Value: its next greater element in nums2 (or -1 if none).
        unordered_map<int ,int> nextGreaterMap;
        
        // s is a monotonic stack that will store elements from nums2 in decreasing order.
        // We process nums2 from right to left.
        stack<int> s;

        // Iterate through nums2 from right to left to find the next greater element for each number.
        for(int i = nums2.size()-1; i >= 0; i--) {
            // currentNum is the element we are currently processing.
            int currentNum = nums2[i];

            // While the stack is not empty AND the top element of the stack
            // is less than or equal to the current number, pop elements from the stack.
            // These popped elements cannot be the next greater element for 'currentNum'
            // or any elements to its left, because 'currentNum' itself is greater or equal.
            while(!s.empty() && s.top() <= currentNum) {
                s.pop();
            }

            // After popping, if the stack is empty, it means there is no element
            // to the right of 'currentNum' that is greater than it.
            if(s.empty()) {
                nextGreaterMap[currentNum] = -1;
            }
            // Otherwise, the top element of the stack is the first element
            // to the right of 'currentNum' that is greater than it.
            else {
                nextGreaterMap[currentNum] = s.top();
            }

            // Push the current number onto the stack.
            // This maintains the decreasing monotonic property of the stack
            // for elements to the right of the current processing point.
            s.push(currentNum);
        }

        // Now, construct the result array for nums1 using the precomputed nextGreaterMap.
        vector<int> ans;
        for(int i = 0; i < nums1.size(); i++) {
            // For each number in nums1, look up its next greater element in the map.
            ans.push_back(nextGreaterMap[nums1[i]]);
        }

        // Return the final answer.
        return ans;
    }
};
```

## ⏱️ Complexity Analysis

| | Complexity | Reason |
|---|---|---|
| **Time** | O(nums1.length + nums2.length) | The first loop iterates through `nums2` once. Each element of `nums2` is pushed onto the stack once and popped at most once. Hash map operations (insertions and lookups) take O(1) on average. The second loop iterates through `nums1` once. |
| **Space** | O(nums1.length + nums2.length) | The `nextGreaterMap` can store up to `nums2.length` key-value pairs. The `stack` can store up to `nums2.length` elements in the worst case. The `ans` vector stores `nums1.length` elements. |

## 🔗 Related Problems
- 503. Next Greater Element II
- 739. Daily Temperatures
- 42. Trapping Rain Water