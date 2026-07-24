# 0414-third-maximum-number

## 📋 Problem Description
Given an integer array `nums`, the task is to find and return the **third distinct maximum** number in this array. If there are fewer than three distinct maximum numbers, the function should instead return the **maximum** number present in the array.

The function receives:
- `nums`: An array of integers.

The function must return:
- An integer representing the third distinct maximum, or the overall maximum if the third distinct maximum does not exist.

## 🔍 Examples
```
Input: nums = [3,2,1]
Output: 1
Explanation:
The first distinct maximum is 3.
The second distinct maximum is 2.
The third distinct maximum is 1.
```

```
Input: nums = [1,2]
Output: 2
Explanation:
The first distinct maximum is 2.
The second distinct maximum is 1.
The third distinct maximum does not exist, so the maximum (2) is returned instead.
```

```
Input: nums = [2,2,3,1]
Output: 1
Explanation:
The first distinct maximum is 3.
The second distinct maximum is 2 (both 2's are counted together since they have the same value).
The third distinct maximum is 1.
```

## 📌 Constraints
*   `1 <= nums.length <= 10^4`
*   `-2^31 <= nums[i] <= 2^31 - 1`

## 🤔 Understanding the Problem
The core of this problem lies in correctly identifying "distinct maximums." This means that if an array contains duplicate numbers (e.g., `[2,2,3,1]`), we only count `2` once when determining the distinct maximums. The problem also has an important edge case: if there are fewer than three unique numbers in the array, we must return the largest number instead of trying to find a non-existent third maximum. This requires a mechanism to track not only the top three numbers but also whether a valid third distinct maximum was actually found.

## 💡 Core Idea
The key insight is to maintain three variables that continuously track the largest, second largest, and third largest *distinct* numbers encountered so far as we iterate through the input array.

## 🧠 Approach — Iterative Tracking
This problem can be solved using an **Iterative Tracking** approach. We maintain three variables, `first`, `second`, and `third`, which will store the largest, second largest, and third largest distinct numbers, respectively. As we iterate through the input array, we compare each number with our current `first`, `second`, and `third` values and update them accordingly. This approach is efficient because it processes each number only once and uses a constant amount of extra space.

## 📝 Step-by-Step Algorithm
1.  **Initialization**:
    *   Initialize three `long long` variables: `first`, `second`, and `third`. Set them all to `LLONG_MIN` (the smallest possible `long long` value). We use `long long` to ensure that even if `INT_MIN` is present in the input array, our initial placeholder values are strictly smaller, allowing `INT_MIN` to be correctly identified as a maximum if it appears.
2.  **Iterate Through Numbers**:
    *   Loop through each `num` in the input array `nums`.
3.  **Handle Duplicates**:
    *   Inside the loop, first check if the current `num` is already equal to `first`, `second`, or `third`. If it is, this means we've already processed this distinct value, so `continue` to the next number to ensure we only consider *distinct* maximums.
4.  **Update Maximums**:
    *   **If `num` is greater than `first`**: This means `num` is the new largest distinct number.
        *   Shift the current `second` to `third`.
        *   Shift the current `first` to `second`.
        *   Set `first` to `num`.
    *   **Else if `num` is greater than `second`**: This means `num` is not the largest, but it's the new second largest distinct number.
        *   Shift the current `second` to `third`.
        *   Set `second` to `num`.
    *   **Else if `num` is greater than `third`**: This means `num` is not the largest or second largest, but it's the new third largest distinct number.
        *   Set `third` to `num`.
5.  **Final Check and Return**:
    *   After iterating through all numbers, check if `third` is still `LLONG_MIN`.
        *   If `third == LLONG_MIN`, it implies that fewer than three distinct maximum numbers were found in the array. In this case, return `first` (which will hold the overall maximum number).
        *   Otherwise (if `third` has been updated from `LLONG_MIN`), return `third` as it represents the third distinct maximum.

## 💻 Solution

```cpp
#include <vector>     // Required for std::vector
#include <limits>     // Required for LLONG_MIN

class Solution {
public:
    int thirdMax(std::vector<int>& nums) {
        // Initialize three long long variables to track the first, second, and third distinct maximums.
        // Using long long and LLONG_MIN is crucial:
        // 1. Input numbers can be INT_MIN (-2^31), so we need a value strictly smaller than INT_MIN
        //    to correctly identify INT_MIN as a maximum if it appears.
        // 2. long long prevents overflow issues if intermediate comparisons involve large numbers,
        //    though for this problem, int would generally suffice for the numbers themselves.
        //    The main reason for long long here is LLONG_MIN being a reliable sentinel.
        long long first = LLONG_MIN;
        long long second = LLONG_MIN;
        long long third = LLONG_MIN;

        // Iterate through each number in the input array.
        for (int num : nums) {
            // Check for duplicates: If the current number is already one of our top three distinct maximums,
            // we skip it to ensure we only count distinct values.
            if (num == first || num == second || num == third) {
                continue;
            }

            // If the current number 'num' is greater than the current 'first' maximum:
            // It means 'num' is the new largest distinct number.
            // We shift the existing maximums down: first -> second, second -> third.
            if (num > first) {
                third = second;
                second = first;
                first = num;
            }
            // Else if 'num' is not greater than 'first', but is greater than 'second':
            // It means 'num' is the new second largest distinct number.
            // We shift the current 'second' to 'third'.
            else if (num > second) {
                third = second;
                second = num;
            }
            // Else if 'num' is not greater than 'first' or 'second', but is greater than 'third':
            // It means 'num' is the new third largest distinct number.
            else if (num > third) {
                third = num;
            }
        }

        // After iterating through all numbers, check if a valid third distinct maximum was found.
        // If 'third' is still LLONG_MIN, it means we never encountered three distinct numbers
        // large enough to populate 'third'. In this case, the problem asks to return the overall maximum.
        if (third == LLONG_MIN) {
            return static_cast<int>(first); // 'first' will hold the overall maximum.
        }

        // Otherwise, a valid third distinct maximum was found, so return it.
        return static_cast<int>(third);
    }
};

```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | The algorithm iterates through the input array `nums` exactly once. Each comparison and assignment operation inside the loop takes constant time. |
| **Space** | O(1) | The algorithm uses a fixed number of variables (`first`, `second`, `third`) regardless of the input array's size. |

## 🔗 Related Problems
- 215. Kth Largest Element in an Array
- 703. Kth Largest Element in a Stream
- 164. Maximum Gap