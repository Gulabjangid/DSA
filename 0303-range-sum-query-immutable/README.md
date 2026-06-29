# 0303-range-sum-query-immutable

## 📋 Problem Description
You are given an integer array `nums`. Your task is to implement a `NumArray` class that can efficiently handle multiple queries to calculate the sum of elements within a specified range.

The `NumArray` class should support the following operations:

1.  **`NumArray(int[] nums)`**: This is the constructor. It initializes the object with the given integer array `nums`.
2.  **`int sumRange(int left, int right)`**: This method should return the sum of all elements in `nums` from index `left` to `right`, inclusive. That is, it should calculate `nums[left] + nums[left + 1] + ... + nums[right]`. It is guaranteed that `left` will always be less than or equal to `right`.

## 🔍 Examples

```
Input:
["NumArray", "sumRange", "sumRange", "sumRange"]
[[[-2, 0, 3, -5, 2, -1]], [0, 2], [2, 5], [0, 5]]

Output:
[null, 1, -1, -3]

Explanation:
NumArray numArray = new NumArray([-2, 0, 3, -5, 2, -1]);
numArray.sumRange(0, 2); // return (-2) + 0 + 3 = 1
numArray.sumRange(2, 5); // return 3 + (-5) + 2 + (-1) = -1
numArray.sumRange(0, 5); // return (-2) + 0 + 3 + (-5) + 2 + (-1) = -3
```

## 📌 Constraints
*   `1 <= nums.length <= 10^4`
*   `-10^5 <= nums[i] <= 10^5`
*   `0 <= left <= right < nums.length`
*   At most `10^4` calls will be made to `sumRange`.

## 🤔 Understanding the Problem
The core of this problem is to efficiently calculate the sum of elements within an arbitrary range `[left, right]` in a given array `nums`. The crucial aspect is that the `sumRange` method might be called many times (up to 10^4 times). A naive approach, where we iterate from `left` to `right` for each `sumRange` query, would be too slow if `nums` is large (up to 10^4 elements) and there are many queries. We need a way to pre-process the array once during initialization so that subsequent `sumRange` queries can be answered very quickly, ideally in constant time.

## 💡 Core Idea
The key insight is to pre-compute the cumulative sum of elements from the beginning of the array up to each index. This allows us to determine the sum of any sub-array `nums[left...right]` by performing a simple subtraction of two pre-computed cumulative sums.

## 🧠 Approach — Prefix Sums
This problem is a classic application of the **Prefix Sums** pattern. This pattern is highly effective when you need to perform multiple range sum queries (or similar range-based operations) on an array whose elements remain constant after initialization. By pre-calculating the sum of all elements from the start of the array up to each index, we can answer any range sum query `sum[left...right]` in O(1) time. This approach significantly improves performance compared to an O(N) per-query naive iteration, especially when the number of queries is large.

## 📝 Step-by-Step Algorithm

1.  **Constructor `NumArray(int[] nums)`**:
    *   Initialize a new array, let's call it `prefix`, of size `n + 1`, where `n` is the length of the input `nums` array. All elements of `prefix` should be initialized to `0`.
    *   The purpose of `prefix[i]` will be to store the sum of elements from `nums[0]` up to `nums[i-1]`.
    *   Iterate through the input `nums` array from index `i = 0` to `n-1`.
    *   For each `i`, calculate `prefix[i+1] = prefix[i] + nums[i]`. This means:
        *   `prefix[0]` will remain `0`.
        *   `prefix[1]` will store `nums[0]`.
        *   `prefix[2]` will store `nums[0] + nums[1]`.
        *   ...
        *   `prefix[k]` will store `nums[0] + ... + nums[k-1]`.

2.  **Method `int sumRange(int left, int right)`**:
    *   To find the sum of elements from `nums[left]` to `nums[right]` (inclusive), we can use the pre-computed `prefix` sums.
    *   The sum `nums[left] + ... + nums[right]` can be expressed as:
        `(sum of nums[0]...nums[right]) - (sum of nums[0]...nums[left-1])`.
    *   Using our `prefix` array definition:
        *   The sum of `nums[0]` through `nums[right]` is stored in `prefix[right + 1]`.
        *   The sum of `nums[0]` through `nums[left - 1]` is stored in `prefix[left]`.
    *   Therefore, the `sumRange(left, right)` can be calculated as `prefix[right + 1] - prefix[left]`.

## 💻 Solution

```cpp
class NumArray {
private:
    // 'prefix' array will store the cumulative sums.
    // prefix[i] will store the sum of nums[0]...nums[i-1].
    // This means prefix[0] = 0, prefix[1] = nums[0], prefix[2] = nums[0] + nums[1], etc.
    vector<int> prefix;

public:
    // Constructor: Initializes the object with the integer array nums.
    NumArray(vector<int>& nums) {
        int n = nums.size();
        // Resize the prefix array to n+1.
        // prefix[0] will be 0 (representing the sum of elements before index 0).
        // prefix[i+1] will store the sum of nums[0]...nums[i].
        prefix.resize(n + 1, 0);

        // Populate the prefix sum array.
        // For each index i in nums, calculate the cumulative sum up to nums[i].
        // prefix[i+1] = sum of nums[0]...nums[i]
        //             = (sum of nums[0]...nums[i-1]) + nums[i]
        //             = prefix[i] + nums[i]
        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + nums[i];
        }
    }

    // sumRange: Returns the sum of elements of nums between indices left and right inclusive.
    // The sum of elements from nums[left] to nums[right] can be found by:
    // (sum of nums[0]...nums[right]) - (sum of nums[0]...nums[left-1])
    // Using our prefix array definition:
    // The sum of nums[0]...nums[right] is stored in prefix[right + 1].
    // The sum of nums[0]...nums[left-1] is stored in prefix[left].
    int sumRange(int left, int right) {
        return prefix[right + 1] - prefix[left];
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * int param_1 = obj->sumRange(left,right);
 */
```

## ⏱️ Complexity Analysis

| | Complexity | Reason |
|---|---|---|
| **Time** | **`NumArray` constructor: O(N)** <br> **`sumRange` method: O(1)** | The constructor iterates through the `nums` array once to build the prefix sum array. The `sumRange` method performs a constant number of array lookups and a subtraction. |
| **Space** | **O(N)** | An additional `prefix` array of size `N+1` is used to store the cumulative sums. |

## 🔗 Related Problems
- 560. Subarray Sum Equals K
- 304. Range Sum Query 2D - Immutable
- 209. Minimum Size Subarray Sum