# 0496-next-greater-element-i

## 📋 Problem Description
You are given two distinct 0-indexed integer arrays, `nums1` and `nums2`, where `nums1` is a subset of `nums2`.
The "next greater element" of an element `x` in an array is defined as the first element greater than `x` that appears to its right in the same array.

Your task is to find the next greater element for each number in `nums1` within the context of `nums2`. Specifically, for each `nums1[i]`, you need to:
1. Find its corresponding value in `nums2` (let's say `nums2[j] == nums1[i]`).
2. Determine the next greater element of `nums2[j]` in `nums2`.
3. If no such greater element exists to its right in `nums2`, the answer for that number is `-1`.

The function should return an array `ans` of the same length as `nums1`, where `ans[i]` is the next greater element for `nums1[i]` as described.

**Input:**
*   `nums1`: A vector of integers.
*   `nums2`: A vector of integers, containing all elements of `nums1`.

**Output:**
*   A vector of integers `ans`, where `ans[i]` is the next greater element for `nums1[i]` in `nums2`.

## 🔍 Examples
```
Input: nums1 = [4,1,2], nums2 = [1,3,4,2]
Output: [-1,3,-1]
Explanation:
- For 4 in nums1: It's 4 in nums2 = [1,3,4,2]. There is no element greater than 4 to its right. So, -1.
- For 1 in nums1: It's 1 in nums2 = [1,3,4,2]. The next greater element to its right is 3. So, 3.
- For 2 in nums1: It's 2 in nums2 = [1,3,4,2]. There is no element greater than 2 to its right. So, -1.
```

```
Input: nums1 = [2,4], nums2 = [1,2,3,4]
Output: [3,-1]
Explanation:
- For 2 in nums1: It's 2 in nums2 = [1,2,3,4]. The next greater element to its right is 3. So, 3.
- For 4 in nums1: It's 4 in nums2 = [1,2,3,4]. There is no element greater than 4 to its right. So, -1.
```

## 📌 Constraints
*   `1 <= nums1.length <= nums2.length <= 1000`
*   `0 <= nums1[i], nums2[i] <= 10^4`
*   All integers in `nums1` and `nums2` are **unique**.
*   All the integers of `nums1` also appear in `nums2`.

## 🤔 Understanding the Problem
The problem asks us to find the "next greater element" for specific numbers. The key challenge is that we need to find this "next greater element" within `nums2` for numbers that originate from `nums1`. Since `nums1` is a subset of `nums2`, every number in `nums1` is guaranteed to be present in `nums2`. The "next greater element" is always to the *right* of the current element. A naive approach would involve nested loops, which might be inefficient.

## 💡 Core Idea
The core idea is to efficiently pre-compute the "next greater element" for *every* number in `nums2` and store these results. Once pre-computed, we can quickly look up the answer for each number in `nums1`.

## 🧠 Approach — Monotonic Stack
This problem is a classic application of the **Monotonic Stack** pattern.
A monotonic stack is a stack that maintains its elements in a strictly increasing or strictly decreasing order. It's particularly useful for problems that involve finding the "next greater element," "next smaller element," "previous greater element," or "previous smaller element" for all elements in an array.
In this specific problem, we iterate through `nums2` from right to left. By maintaining a stack of elements in decreasing order, we can efficiently determine the next greater element for each number. When we encounter a number, any elements on top of the stack that are smaller than or equal to it cannot be the next greater element for *any* subsequent numbers (to their left), so they are popped. The first element remaining on the stack (if any) will be the next greater element.

## 📝 Step-by-Step Algorithm

1.  **Initialize Data Structures**:
    *   Create an `unordered_map` (hash map), let's call it `m`, to store the mapping from a number in `nums2` to its next greater element.
    *   Create an empty `stack` of integers, let's call it `s`. This will be our monotonic stack.

2.  **Populate the Map with Next Greater Elements**:
    *   Iterate through `nums2` from right to left (from index `nums2.size() - 1` down to `0`). Let the current element be `current_num = nums2[i]`.
    *   **Maintain Monotonicity**: While the stack `s` is not empty AND the element at the top of `s` is less than or equal to `current_num`, pop elements from `s`. This ensures that `s` only contains elements strictly greater than `current_num` that appear to its right.
    *   **Determine Next Greater Element**:
        *   If, after popping, the stack `s` becomes empty, it means there is no element greater than `current_num` to its right in `nums2`. In this case, store `m[current_num] = -1`.
        *   Otherwise (if `s` is not empty), the element at the top of `s` is the first element greater than `current_num` to its right. Store this mapping: `m[current_num] = s.top()`.
    *   **Push Current Element**: Finally, push `current_num` onto the stack `s`. This `current_num` might be the next greater element for elements encountered later (to its left).

3.  **Construct the Result Array**:
    *   Create an empty `vector<int>`, let's call it `ans`, to store the final results.
    *   Iterate through `nums1` from left to right (from index `0` to `nums1.size() - 1`).
    *   For each `nums1[i]`, look up its corresponding next greater element in the map `m` (i.e., `m[nums1[i]]`).
    *   Add this value to the `ans` vector.

4.  **Return Result**:
    *   Return the `ans` vector.

## 💻 Solution
```cpp
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        // m will store the mapping from a number in nums2 to its next greater element.
        // Key: number from nums2, Value: its next greater element in nums2.
        unordered_map<int ,int> m; 
        // s is a monotonic stack that will store elements from nums2 in decreasing order.
        // We process nums2 from right to left, so elements in the stack are to the right
        // of the current element being processed.
        stack<int> s; 

        // Iterate through nums2 from right to left.
        // This allows us to easily find elements to the 'right' of the current number.
        for(int i = nums2.size()-1; i >= 0; i--) {
            // While the stack is not empty AND the top element of the stack is less than or equal to
            // the current number (nums2[i]), pop elements from the stack.
            // These popped elements cannot be the next greater element for nums2[i]
            // because nums2[i] itself is greater than or equal to them.
            // Also, they cannot be the next greater element for any numbers to the left of nums2[i]
            // because nums2[i] would be a closer and greater (or equal) candidate.
            while(!s.empty() && s.top() <= nums2[i]) {
                s.pop();
            }

            // After popping, if the stack is empty, it means there's no element to the right
            // of nums2[i] that is greater than it. So, its next greater element is -1.
            if(s.empty()) {
                m[nums2[i]] = -1;
            }
            // Otherwise, the top element of the stack is the first element to the right
            // of nums2[i] that is greater than it. This is our next greater element.
            else {
                m[nums2[i]] = s.top();
            }

            // Push the current number onto the stack.
            // It might be the next greater element for numbers that appear to its left.
            s.push(nums2[i]);
        }

        // Now that we have pre-computed the next greater element for every number in nums2
        // and stored it in the map 'm', we can easily find the answers for nums1.
        vector<int> ans;
        for(int i = 0; i < nums1.size(); i++) {
            // Look up the next greater element for nums1[i] in our map 'm'.
            ans.push_back(m[nums1[i]]);
        }

        // Return the final result array.
        return ans;
    }
};
```

## ⏱️ Complexity Analysis

| | Complexity | Reason |
|---|---|---|
| **Time** | O(N + M) | The first loop iterates through `nums2` (N elements) once. Each element of `nums2` is pushed onto the stack at most once and popped at most once, making stack operations amortized O(1). Hash map operations (insertions) are average O(1). The second loop iterates through `nums1` (M elements) once, with average O(1) hash map lookups. Thus, total time is proportional to the sum of lengths of `nums1` and `nums2`. |
| **Space** | O(N) | The `unordered_map` `m` stores at most N key-value pairs (for all unique elements in `nums2`). The `stack` `s` can store up to N elements in the worst case. The `ans` vector stores M elements. Since M <= N, the dominant space complexity is O(N). |

## 🔗 Related Problems
- 503. Next Greater Element II
- 739. Daily Temperatures
- 84. Largest Rectangle in Histogram