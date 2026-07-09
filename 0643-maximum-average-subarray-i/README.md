# 0643-maximum-average-subarray-i

## 📋 Problem Description
You are given an integer array `nums` consisting of `n` elements, and an integer `k`.
Your task is to find a contiguous subarray (a sequence of adjacent elements) whose length is exactly `k` and which has the maximum possible average value. You must return this maximum average value. Any answer with a calculation error less than `10^-5` will be accepted.

The function `findMaxAverage` receives:
- `nums`: A `std::vector<int>` representing the input array.
- `k`: An `int` representing the required length of the subarray.

It must return:
- A `double` representing the maximum average value found.

## 🔍 Examples
```
Input: nums = [1,12,-5,-6,50,3], k = 4
Output: 12.75000
Explanation: The subarray [12,-5,-6,50] has a sum of 12 - 5 - 6 + 50 = 51.
Its average is 51 / 4 = 12.75. This is the maximum average for any subarray of length 4.

Input: nums = [5], k = 1
Output: 5.00000
Explanation: The only subarray of length 1 is [5]. Its sum is 5, and its average is 5 / 1 = 5.
```

## 📌 Constraints
*   `n == nums.length`
*   `1 <= k <= n <= 10^5`
*   `-10^4 <= nums[i] <= 10^4`

## 🤔 Understanding the Problem
The problem asks us to identify a specific type of subarray: it must be contiguous (elements must be adjacent in the original array) and have a fixed length `k`. Among all such subarrays, we need to find the one whose elements sum up to the largest value, as a larger sum directly translates to a larger average when the divisor (`k`) is constant. The core challenge is to efficiently calculate the sum for all possible `k`-length subarrays without redundant computations.

## 💡 Core Idea
Instead of recalculating the sum for each `k`-length subarray from scratch, we can maintain a "current sum" as we move a window of size `k` across the array. When the window slides one position to the right, we simply add the new element entering the window and subtract the element leaving the window, updating the sum in constant time.

## 🧠 Approach — Sliding Window
This problem is a classic example of the **Sliding Window** pattern.
The Sliding Window technique is ideal here because we are looking for a contiguous subarray of a *fixed size* (`k`). Instead of iterating through all possible starting positions and then summing `k` elements for each (which would be inefficient), we can use a window that "slides" across the array. This allows us to update the sum of elements within the window in O(1) time for each step, by adding the new element that enters the window and subtracting the element that leaves it. This significantly optimizes the overall time complexity.

## 📝 Step-by-Step Algorithm
1.  Initialize `current_sum` to `0.0` (using a double to ensure accurate average calculation).
2.  Initialize `max_average` to a very small negative number (e.g., `INT_MIN` cast to `double`) to ensure any valid average will be greater.
3.  Initialize a `left` pointer to `0`, representing the start of our sliding window.
4.  Initialize a `count` variable to `0`, which will track the number of elements currently in our `current_sum`.
5.  Iterate with a `right` pointer from `0` to `nums.size() - 1`:
    a.  Add `nums[right]` to `current_sum`.
    b.  Increment `count`.
    c.  Check if the `count` of elements in the window is equal to `k`. This means our window has reached the desired size.
        i.   Calculate the `current_average` by dividing `current_sum` by `k`.
        ii.  Update `max_average` to be the maximum of its current value and `current_average`.
        iii. To slide the window, subtract `nums[left]` from `current_sum` (removing the element that is now outside the window).
        iv.  Increment `left` to move the window's starting point one position to the right.
        v.   Decrement `count` (since one element left the window, and `right` will soon add a new one, keeping the effective window size `k`).
6.  After the loop finishes, `max_average` will hold the maximum average value found. Return `max_average`.

## 💻 Solution
```cpp
class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        // 'left' pointer marks the beginning of our sliding window.
        int left = 0;
        
        // 'current_sum' will store the sum of elements within the current window.
        // Use double to prevent integer division issues and maintain precision for average.
        double current_sum = 0;
        
        // 'count' tracks how many elements are currently included in 'current_sum'.
        // This helps determine when the window has reached size 'k'.
        int count = 0;
        
        // 'max_average' stores the maximum average found so far.
        // Initialize with the smallest possible double value to ensure any valid average is greater.
        double max_average = -2000000000.0; // A value smaller than any possible average (-10^4 * 10^5 / 10^5 = -10^4, so -2*10^9 is safe)
                                            // Or simply use std::numeric_limits<double>::lowest() if available and preferred.
                                            // For competitive programming, a sufficiently small constant is often used.
        
        // 'right' pointer iterates through the array, expanding the window.
        for (int right = 0; right < nums.size(); right++) {
            // Add the element at the 'right' pointer to our current sum.
            current_sum += nums[right];
            // Increment the count of elements in the window.
            count++;
            
            // Once the window size ('count') equals 'k', we have a valid subarray of length 'k'.
            if (count == k) {
                // Calculate the average for the current window.
                // Update 'max_average' if the current window's average is greater.
                max_average = std::max(max_average, current_sum / k);
                
                // To slide the window, remove the element at the 'left' pointer from 'current_sum'.
                current_sum -= nums[left];
                // Move the 'left' pointer one step to the right.
                left++;
                // Decrement 'count' as one element has left the window.
                // The next iteration will add a new element at 'right', bringing 'count' back to 'k'.
                count--;
            }
        }
        
        // After iterating through all possible windows, 'max_average' holds the result.
        return max_average;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | The `right` pointer iterates through the `nums` array exactly once. Each element is added to `current_sum` once and potentially subtracted once. All operations inside the loop (addition, subtraction, comparison, division) are constant time (O(1)). |
| **Space** | O(1) | We only use a few constant extra variables (`left`, `current_sum`, `count`, `max_average`) regardless of the input array size `N`. |

## 🔗 Related Problems
- 209. Minimum Size Subarray Sum
- 3. Longest Substring Without Repeating Characters
- 1456. Maximum Number of Vowels in a Substring of Given Length