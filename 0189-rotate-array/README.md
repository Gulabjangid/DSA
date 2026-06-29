# 0189-rotate-array

## 📋 Problem Description
Given an integer array `nums`, rotate the array to the right by `k` steps. The rotation should be performed in-place, meaning you should modify the original array directly without using extra space proportional to the input size. The value `k` is non-negative.

The function `rotate` receives:
- `nums`: A reference to an integer vector (array) that needs to be rotated.
- `k`: An integer representing the number of steps to rotate the array to the right.

The function should modify `nums` in-place and does not need to return anything.

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
The problem asks us to shift elements of an array to the right by `k` positions. Elements that "fall off" the end of the array should wrap around to the beginning. A key challenge is to achieve this rotation in-place, meaning without creating a new array of the same size, and with minimal extra space (ideally O(1)). We also need to handle cases where `k` is larger than the array's length, as rotating by `k` steps is equivalent to rotating by `k % n` steps, where `n` is the array length.

## 💡 Core Idea
The core idea is that rotating an array to the right by `k` steps can be achieved by a series of reversals. Specifically, if we reverse the entire array, then reverse the first `k` elements, and finally reverse the remaining `n-k` elements, the array will be correctly rotated.

## 🧠 Approach — Array Reversal
This problem can be efficiently solved using the **Array Reversal** pattern. This pattern is suitable for problems involving cyclic shifts or rearrangements of array elements where in-place modification is required. The reason it fits here is that a right rotation essentially moves the last `k` elements to the front and shifts the first `n-k` elements to the back. Reversing segments of the array allows us to achieve this rearrangement without needing a temporary array.

## 📝 Step-by-Step Algorithm
1.  **Handle effective `k`**: Calculate `k` modulo the array's length (`n`). This ensures that `k` is always within the range `[0, n-1]`, as rotating by `n` steps brings the array back to its original state.
2.  **Reverse the entire array**: Reverse all elements from the beginning to the end of the array.
3.  **Reverse the first `k` elements**: Reverse the elements from the beginning of the array up to (but not including) the `k`-th element. These are now the elements that should be at the front.
4.  **Reverse the remaining `n-k` elements**: Reverse the elements from the `k`-th element up to the end of the array. These are now the elements that should be at the back.

After these three reversals, the array will be correctly rotated to the right by `k` steps.

## 💻 Solution
```cpp
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        // Get the size of the array.
        int n = nums.size();

        // Calculate the effective number of rotations.
        // If k is greater than n, rotating k times is equivalent to rotating k % n times.
        // For example, if n=7, k=10, then k%n = 3. Rotating 10 times is same as 3 times.
        k = k % n;

        // Step 1: Reverse the entire array.
        // Example: [1,2,3,4,5,6,7] becomes [7,6,5,4,3,2,1]
        reverse(nums.begin(), nums.end());

        // Step 2: Reverse the first k elements.
        // These k elements are now the ones that should be at the beginning after rotation.
        // Example (k=3): [7,6,5,4,3,2,1] -> reverse first 3 elements -> [5,6,7,4,3,2,1]
        reverse(nums.begin(), nums.begin() + k);

        // Step 3: Reverse the remaining n-k elements.
        // These n-k elements are now the ones that should follow the first k elements.
        // Example (k=3): [5,6,7,4,3,2,1] -> reverse remaining (from index 3 to end) -> [5,6,7,1,2,3,4]
        reverse(nums.begin() + k, nums.end());
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | Each `reverse` operation iterates through a portion of the array. We perform three such operations: one on the entire array (N elements), one on the first `k` elements, and one on the remaining `N-k` elements. The total number of element swaps/accesses is proportional to N + k + (N-k) = 2N, which simplifies to O(N). |
| **Space** | O(1) | The `reverse` function operates in-place, modifying the original `nums` vector directly. No additional data structures are allocated that scale with the input size. |

## 🔗 Related Problems
- 151. Reverse Words in a String
- 344. Reverse String
- 186. Reverse Words in a String II