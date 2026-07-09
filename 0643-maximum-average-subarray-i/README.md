# 0643-maximum-average-subarray-i

## 📋 Problem Description
You are given an integer array `nums` consisting of `n` elements, and an integer `k`. Your task is to find a contiguous subarray (a sequence of adjacent elements) within `nums` whose length is exactly `k` and which has the maximum possible average value. You must return this maximum average value. Any answer with a calculation error less than `10^-5` will be accepted, indicating that floating-point arithmetic is expected.

**Input:**
*   `nums`: An array of integers.
*   `k`: An integer representing the required length of the subarray.

**Output:**
*   A `double` representing the maximum average value found among all contiguous subarrays of length `k`.

## 🔍 Examples
```
Input: nums = [1,12,-5,-6,50,3], k = 4
Output: 12.75000
Explanation: The contiguous subarray of length 4 with the maximum average is [12, -5, -6, 50].
Its sum is 12 - 5 - 6 + 50 = 51.
Its average is 51 / 4 = 12.75.
Other subarrays of length 4:
[1, 12, -5, -6] sum = 2, avg = 0.5
[-5, -6, 50, 3] sum = 42, avg = 10.5
```

```
Input: nums = [5], k = 1
Output: 5.00000
Explanation: The only contiguous subarray of length 1 is [5]. Its sum is 5, and its average is 5 / 1 = 5.
```

## 📌 Constraints
*   `n == nums.length`
*   `1 <= k <= n <= 10^5`
*   `-10^4 <= nums[i] <= 10^4`

## 🤔 Understanding the Problem
The problem asks us to identify a specific segment of `k` consecutive numbers within a larger array `nums` such that the average of these `k` numbers is the highest possible. Since `k` is fixed, maximizing the average is equivalent to maximizing the sum of the `k` numbers. The core challenge is to efficiently calculate and compare the sums (or averages) of all possible contiguous subarrays of length `k` without redundant computations, especially given that `n` can be up to `10^5`.

## 💡 Core Idea
To efficiently find the maximum sum (and thus maximum average) for all contiguous subarrays of a fixed length `k`, we can use a "sliding window" technique. Instead of recalculating the sum for each new subarray from scratch, we maintain a window of size `k` and update its sum in constant time as it slides across the array.

## 🧠 Approach — Sliding Window
The "Sliding Window" pattern is perfectly suited for this problem. This pattern is used when you need to perform an operation (like finding sum, max, min, or counting) on a contiguous subarray or substring of a given array or string. Here, we are looking for a contiguous subarray of a *fixed* length `k`.

The sliding window approach works by:
1.  Calculating the sum of the first `k` elements to establish the initial window.
2.  Then, as we move the window one position to the right, we "slide" it. This involves subtracting the element that is leaving the window from the left side and adding the new element that is entering the window from the right side.
3.  This way, the sum of the current window can be updated in O(1) time for each step, making the overall process highly efficient.

## 📝 Step-by-Step Algorithm
1.  Initialize `current_sum` to `0.0` (using a double to handle potential floating-point averages) to store the sum of elements within the current sliding window.
2.  Initialize `max_average` to a very small negative double value (e.g., `INT_MIN` cast to double, or `-1e9 * 1.0`) to ensure any valid average found will be greater and update it.
3.  Initialize a `left` pointer to `0`, representing the starting index of the current window.
4.  Initialize a `count` variable to `0` to keep track of how many elements are currently in the window.
5.  Iterate with a `right` pointer from `0` to `nums.size() - 1` (inclusive):
    a.  Add `nums[right]` to `current_sum`.
    b.  Increment `count`.
    c.  Check if the `count` (i.e., the current window size) is equal to `k`:
        i.  If it is, calculate the average of the current window: `current_sum / k`.
        ii. Update `max_average` if this calculated average is greater than the current `max_average`.
        iii. To slide the window forward, subtract `nums[left]` from `current_sum` (this element is now leaving the window).
        iv. Increment the `left` pointer by one.
        v.  Decrement `count` by one (as one element left the window).
6.  After the loop finishes, `max_average` will hold the maximum average value found among all contiguous subarrays of length `k`. Return `max_average`.

## 💻 Solution
```cpp
class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        // 'left' pointer marks the beginning of our current sliding window.
        int left = 0;
        
        // 'current_sum' will store the sum of elements within the current window.
        // Using double for sum to avoid potential integer overflow for large sums
        // and to ensure accurate division for average calculation.
        double current_sum = 0;
        
        // 'count' tracks the number of elements currently in the window.
        // This is equivalent to (right - left + 1).
        int count = 0;
        
        // 'max_average' stores the maximum average found across all valid windows.
        // Initialize it to INT_MIN (smallest possible integer value).
        // When compared with double values, INT_MIN will implicitly convert to double,
        // ensuring any valid average (which can be positive or negative but much larger than INT_MIN)
        // will correctly update 'max_average'.
        double max_average = INT_MIN; 

        // 'right' pointer iterates through the array, expanding the window to the right.
        for (int right = 0; right < nums.size(); right++) {
            // Add the current element at 'right' to the 'current_sum'.
            current_sum += nums[right];
            // Increment the count of elements in the window.
            count++;

            // Once the window size ('count') reaches 'k', we have a valid subarray.
            if (count == k) {
                // Calculate the average of the current window.
                // Update 'max_average' if the current window's average is greater.
                max_average = max(max_average, current_sum / k);

                // To slide the window one position to the right:
                // 1. Subtract the element at 'left' from 'current_sum' (it's leaving the window).
                current_sum -= nums[left];
                // 2. Move the 'left' pointer one step to the right.
                left++;
                // 3. Decrement 'count' as one element left the window.
                count--;
            }
        }
        // After iterating through all possible windows, 'max_average' holds the maximum average found.
        return max_average;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | The `right` pointer iterates through the `nums` array exactly once. Each element is added to `current_sum` once and subtracted once. All operations inside the loop (addition, subtraction, comparison, division) are constant time (O(1)). |
| **Space** | O(1) | We only use a few constant extra variables (`left`, `current_sum`, `count`, `max_average`) regardless of the input array size `N`. |

## 🔗 Related Problems
*   3. Longest Substring Without Repeating Characters
*   209. Minimum Size Subarray Sum
*   1456. Maximum Number of Vowels in a Substring of Given Length