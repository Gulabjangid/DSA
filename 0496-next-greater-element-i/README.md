# 0496-next-greater-element-i

## 📋 Problem Description
The problem defines the "next greater element" of an element `x` in an array as the first element to its right in the same array that is strictly greater than `x`.

You are given two distinct 0-indexed integer arrays, `nums1` and `nums2`. It's guaranteed that `nums1` is a subset of `nums2`.

Your task is to find the next greater element for each number in `nums1`. Specifically, for each `nums1[i]`, you need to:
1. Find its corresponding value in `nums2`.
2. Determine the next greater element for that value within `nums2`.
3. If no such greater element exists to its right in `nums2`, the answer for that query is -1.

Finally, you must return an array `ans` of the same length as `nums1`, where `ans[i]` contains the next greater element for `nums1[i]` as described above.

## 🔍 Examples
```
Input: nums1 = [4,1,2], nums2 = [1,3,4,2]
Output: [-1,3,-1]
Explanation: The next greater element for each value of nums1 is as follows:
- For 4 (found in nums2 = [1,3,4,2]): There is no element to its right that is greater than 4. So, the answer is -1.
- For 1 (found in nums2 = [1,3,4,2]): The first element to its right that is greater than 1 is 3. So, the answer is 3.
- For 2 (found in nums2 = [1,3,4,2]): There is no element to its right that is greater than 2. So, the answer is -1.

Input: nums1 = [2,4], nums2 = [1,2,3,4]
Output: [3,-1]
Explanation: The next greater element for each value of nums1 is as follows:
- For 2 (found in nums2 = [1,2,3,4]): The first element to its right that is greater than 2 is 3. So, the answer is 3.
- For 4 (found in nums2 = [1,2,3,4]): There is no element to its right that is greater than 4. So, the answer is -1.
```

## 📌 Constraints
*   `1 <= nums1.length <= nums2.length <= 1000`
*   `0 <= nums1[i], nums2[i] <= 10^4`
*   All integers in `nums1` and `nums2` are unique.
*   All the integers of `nums1` also appear in `nums2`.

## 🤔 Understanding the Problem
The core of this problem is to efficiently find the "next greater element" for a set of specific numbers (`nums1`) within a larger array (`nums2`). The key is that we need the *first* greater element *to the right*. A naive approach would involve iterating through `nums2` for each number in `nums1`, which could be slow. The problem essentially asks us to precompute these "next greater elements" for all relevant numbers in `nums2` to answer queries from `nums1` quickly.

## 💡 Core Idea
Instead of repeatedly searching for the next greater element for each number in `nums1`, we can precompute the next greater element for *every* number in `nums2` in a single pass. This precomputed information can then be stored in a hash map for O(1) average time lookups when processing `nums1`.

## 🧠 Approach — Monotonic Stack
This problem is a classic application of the **Monotonic Stack** pattern. A monotonic stack is a stack that maintains its elements in a strictly increasing or strictly decreasing order. It's particularly useful for problems that require finding the "next greater/smaller element" (or previous) for all elements in an array. By iterating through the array (often from right to left for "next greater" problems) and using the stack to keep track of potential candidates, we can determine the next greater element for each number in a single, efficient pass. In this specific problem, we iterate `nums2` from right to left, maintaining a decreasing monotonic stack, which allows us to quickly find the first element to the right that is greater than the current element.

## 📝 Step-by-Step Algorithm
1.  **Initialize Data Structures**:
    *   Create an empty `unordered_map` (let's call it `nextGreaterMap`). This map will store each number from `nums2` as a key and its corresponding next greater element in `nums2` as its value.
    *   Create an empty `stack` (let's call it `monoStack`). This stack will be used to maintain a decreasing sequence of numbers encountered so far, helping us find the next greater element efficiently.

2.  **Process `nums2` from Right to Left**:
    *   Iterate through `nums2` starting from the last element (index `nums2.size() - 1`) down to the first element (index `0`). Let the current element be `currentNum = nums2[i]`.

3.  **Maintain Monotonic Stack**:
    *   **While** the `monoStack` is not empty AND the element at the top of `monoStack` is less than or equal to `currentNum`:
        *   Pop elements from `monoStack`. These popped elements cannot be the next greater element for `currentNum` (since `currentNum` is greater or equal). More importantly, they also cannot be the next greater element for any numbers to the *left* of `currentNum`, because `currentNum` itself is a larger or equal candidate that appears earlier (to their right).
    *   After the loop, the `monoStack` contains only elements that are strictly greater than `currentNum` (if any).

4.  **Determine Next Greater Element for `currentNum`**:
    *   **If** `monoStack` is now empty:
        *   It means there is no element to the right of `currentNum` (or any elements that were to its right were smaller or equal and thus popped) that is greater than `currentNum`. So, `currentNum` has no next greater element. Store this in the map: `nextGreaterMap[currentNum] = -1`.
    *   **Else** (if `monoStack` is not empty):
        *   The element at the top of `monoStack` is the first element to the right of `currentNum` that is strictly greater than it. Store this in the map: `nextGreaterMap[currentNum] = monoStack.top()`.

5.  **Push `currentNum` to Stack**:
    *   Push `currentNum` onto `monoStack`. This ensures that `monoStack` continues to maintain its decreasing monotonic property for subsequent elements processed to the left.

6.  **Generate Result for `nums1`**:
    *   After the loop completes, `nextGreaterMap` will contain the next greater element for every number that appeared in `nums2`.
    *   Create an empty `vector<int>` called `ans`.
    *   Iterate through `nums1` from left to right (from index `0` to `nums1.size() - 1`).
    *   For each `nums1[i]`, look up its precomputed next greater element in `nextGreaterMap` (i.e., `nextGreaterMap[nums1[i]]`) and add this value to the `ans` vector.

7.  **Return `ans`**:
    *   Return the `ans` vector, which now contains the next greater elements for all numbers in `nums1`.

## 💻 Solution
```cpp
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {

        // nextGreaterMap: Stores the next greater element for each number in nums2.
        // Key: A number from nums2.
        // Value: Its next greater element in nums2 (or -1 if none exists).
        unordered_map<int ,int> nextGreaterMap;
        
        // monoStack: A monotonic stack that will store elements in decreasing order.
        // This helps us efficiently find the next greater element for numbers
        // as we iterate through nums2 from right to left.
        stack<int> monoStack;

        // Iterate through nums2 from right to left.
        // This direction is crucial because we are looking for elements "to the right".
        for(int i = nums2.size()-1; i >= 0; i--) {
            int currentNum = nums2[i];

            // While the stack is not empty AND the top element of the stack
            // is less than or equal to the current number:
            // Pop elements from the stack. These elements cannot be the next greater
            // element for currentNum (since currentNum is greater or equal).
            // Furthermore, they also cannot be the next greater element for any numbers
            // to the left of currentNum, because currentNum itself is a larger or equal
            // candidate that appears earlier (to their right).
            while(!monoStack.empty() && monoStack.top() <= currentNum) {
                monoStack.pop();
            }

            // After popping, we check the state of the stack:
            // If the stack is empty, it means there are no elements to the right of currentNum
            // that are greater than it. So, its next greater element is -1.
            if(monoStack.empty()) {
                nextGreaterMap[currentNum] = -1;
            }
            // Otherwise, the top element of the stack is the first element
            // to the right of currentNum that is strictly greater than it.
            else {
                nextGreaterMap[currentNum] = monoStack.top();
            }

            // Push the current number onto the stack.
            // This maintains the decreasing monotonic property of the stack.
            // For any future numbers to the left of currentNum, currentNum will be
            // a candidate for their next greater element if it's greater than them.
            monoStack.push(currentNum);
        }

        // Now that nextGreaterMap is populated with all next greater elements for nums2,
        // we can easily find the answers for nums1.
        vector<int> ans;

        // Iterate through nums1.
        for(int i = 0; i < nums1.size(); i++) {
            // Look up the next greater element for nums1[i] in our precomputed map
            // and add it to the result vector.
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
| **Time** | O(N + M) | The first loop iterates through `nums2` once (M elements). Each element of `nums2` is pushed onto the stack and popped from it at most once. `unordered_map` operations (insertion, lookup) take O(1) on average. The second loop iterates through `nums1` once (N elements), with O(1) average time map lookups. Thus, the total time complexity is linear with respect to the combined lengths of `nums1` and `nums2`. |
| **Space** | O(M) | In the worst case, the `unordered_map` stores an entry for each unique element in `nums2` (M elements). The `stack` can also store up to M elements if `nums2` is sorted in decreasing order (e.g., `[5,4,3,2,1]`). |

## 🔗 Related Problems
- 503. Next Greater Element II
- 739. Daily Temperatures
- 42. Trapping Rain Water