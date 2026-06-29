# 0189-rotate-array

## 📋 Problem Description
Given an integer array `nums`, rotate the array to the right by `k` steps. The rotation should be performed in-place, meaning you should modify the original array directly. `k` is a non-negative integer.

The function `rotate` receives two arguments:
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
The problem asks us to shift elements of an array to the right by a specified number of positions, `k`. Elements that "fall off" the end of the array should wrap around to the beginning. A key challenge is to perform this operation efficiently, ideally in-place (without using significant extra memory) and with optimal time complexity. We also need to handle cases where `k` might be larger than the array's length, in which case `k` effectively wraps around multiple times.

## 💡 Core Idea
The core idea is that rotating an array to the right by `k` steps is equivalent to reversing the entire array, then reversing the first `k` elements, and finally reversing the remaining `n-k` elements. This clever sequence of three reversals achieves the desired rotation in-place.

## 🧠 Approach — Array Reversal Technique
This problem can be elegantly solved using the **Array Reversal Technique**. This pattern is particularly useful for in-place array manipulations involving rotations or rearranging segments. It fits this problem perfectly because a right rotation essentially swaps the "tail" part of the array with the "head" part. By reversing the entire array, then reversing these two now-separated parts, we can achieve the desired order without needing extra space.

## 📝 Step-by-Step Algorithm
1.  **Handle effective `k`**: Calculate `k = k % n`, where `n` is the length of the array. This ensures that `k` is always less than `n`, as rotating by `n` steps (or any multiple of `n`) results in the original array.
2.  **Reverse the entire array**: Reverse all elements from the beginning to the end of the array. After this step, the elements are in reverse order.
3.  **Reverse the first `k` elements**: Reverse the elements from the beginning of the array up to (but not including) the `k`-th element. These are the elements that should now be at the beginning of the rotated array.
4.  **Reverse the remaining `n-k` elements**: Reverse the elements from the `k`-th element to the end of the array. These are the elements that should now form the tail of the rotated array.

After these three reversals, the array will be correctly rotated to the right by `k` steps.

## 💻 Solution
```cpp
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        // Get the size of the array.
        int n = nums.size();

        // Calculate the effective number of rotations.
        // If k is greater than n, rotating k times is the same as rotating k % n times.
        // This handles cases like k = 7 for an array of size 5 (equivalent to k = 2).
        k = k % n;

        // Step 1: Reverse the entire array.
        // Example: [1,2,3,4,5,6,7], k=3
        // After this: [7,6,5,4,3,2,1]
        reverse(nums.begin(), nums.end());

        // Step 2: Reverse the first k elements.
        // These k elements (which were originally the last k elements) are now at the beginning.
        // Example: [7,6,5,4,3,2,1]
        // k=3, so reverse first 3 elements: [7,6,5] -> [5,6,7]
        // Array becomes: [5,6,7,4,3,2,1]
        reverse(nums.begin(), nums.begin() + k);

        // Step 3: Reverse the remaining n-k elements.
        // These n-k elements (which were originally the first n-k elements) are now at the end.
        // Example: [5,6,7,4,3,2,1]
        // Reverse elements from index k (3) to end: [4,3,2,1] -> [1,2,3,4]
        // Array becomes: [5,6,7,1,2,3,4] - which is the correct rotated array.
        reverse(nums.begin() + k, nums.end());
    }
};

```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | Each `reverse` operation iterates through a portion of the array. We perform three such operations, each taking O(N) time in the worst case (where N is the array length). Thus, the total time complexity is O(N). |
| **Space** | O(1) | The `reverse` function in C++ (and similar standard library functions) operates in-place, modifying the array directly without allocating any significant additional data structures. |

## 🔗 Related Problems
- 344. Reverse String
- 151. Reverse Words in a String
- 186. Reverse Words in a String II