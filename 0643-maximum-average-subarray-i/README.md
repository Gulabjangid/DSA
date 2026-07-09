# 0643-maximum-average-subarray-i

## 📋 Problem Description
You are given an integer array `nums` of `n` elements and an integer `k`. Your task is to find a contiguous subarray (a sequence of adjacent elements) within `nums` that has a length exactly equal to `k`. Among all such subarrays, you need to find the one with the maximum average value and return this maximum average. Any answer with a calculation error less than `10^-5` will be accepted.

**Input:**
*   `nums`: An array of integers.
*   `k`: An integer representing the required length of the subarray.

**Output:**
*   A `double` representing the maximum average value found.

## 🔍 Examples
```
Input: nums = [1,12,-5,-6,50,3], k = 4
Output: 12.75000
Explanation: The subarray [12, -5, -6, 50] has a sum of 12 - 5 - 6 + 50 = 51.
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
The problem asks us to identify a specific segment of `k` consecutive numbers within a larger array `nums` such that the average of these `k` numbers is as high as possible. Since `k` is fixed, maximizing the average is equivalent to maximizing the sum of the `k` numbers. The challenge lies in efficiently checking all possible contiguous subarrays of length `k` without redundant calculations.

## 💡 Core Idea
To find the maximum sum (and thus maximum average) of a fixed-length subarray efficiently, we can use a "sliding window" approach. Instead of re-calculating the sum for each new subarray of length `k`, we can maintain a running sum and update it incrementally as the window slides.

## 🧠 Approach — Sliding Window
This problem is a classic application of the **Sliding Window** pattern. This pattern is ideal when you need to find something (like a maximum sum, minimum length, or specific count) in a contiguous subarray or substring of a given size, or when the size can vary but needs to satisfy certain conditions.

Here, we are looking for a contiguous subarray of *fixed length* `k`. A sliding window allows us to process each element of the array exactly twice (once when it enters the window, once when it leaves), leading to an optimal linear time complexity. We maintain a window of size `k`, calculate its sum, update our maximum average, and then "slide" the window one position to the right by adding the new element entering the window and subtracting the element leaving it.

## 📝 Step-by-Step Algorithm
1.  **Initialization**:
    *   Initialize a variable `current_window_sum` to `0.0` to store the sum of elements in the current window. We use `double` to avoid potential integer overflow for sums and for accurate average calculation.
    *   Initialize a variable `max_average` to a very small negative number (e.g., `-(double)INT_MAX` or the average of the first `k` elements) to ensure any valid average will be greater.
    *   Initialize a `left` pointer to `0`, representing the start of our sliding window.
    *   Initialize a `count` variable to `0` to track the number of elements currently in the window.

2.  **Iterate and Slide**:
    *   Use a `right` pointer to iterate through the `nums` array from index `0` to `n-1` (where `n` is `nums.size()`).
    *   In each iteration, add `nums[right]` to `current_window_sum` and increment `count`. This expands the window to the right.

3.  **Check Window Size and Update**:
    *   Once `count` becomes equal to `k` (meaning the window has reached the desired length):
        *   Calculate the `current_average` as `current_window_sum / k`.
        *   Update `max_average = max(max_average, current_average)`.
        *   To slide the window forward, subtract `nums[left]` from `current_window_sum` (removing the element that is now leaving the window).
        *   Increment `left` by `1` (moving the window's start).
        *   Decrement `count` by `1` (as one element left the window).

4.  **Return Result**:
    *   After the `right` pointer has traversed the entire array, `max_average` will hold the maximum average value found. Return `max_average`.

## 💻 Solution
```cpp
class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        // 'left' pointer marks the beginning of our current sliding window.
        int left = 0;
        
        // 'current_window_sum' stores the sum of elements within the current window.
        // It's declared as double to ensure accurate division for average calculation
        // and to prevent potential integer overflow if sums are very large.
        double current_window_sum = 0;
        
        // 'count' keeps track of how many elements are currently in the window.
        int count = 0;
        
        // 'max_average' will store the maximum average found across all valid windows.
        // Initialized to a very small double value to ensure any valid average will be greater.
        // INT_MIN is an int, but when compared with a double, it will be promoted.
        // Using -(double)INT_MAX or similar would be more explicit for doubles.
        double max_average = -2000000000.0; // A value smaller than any possible average (-10^4 * 10^5 / 10^5 = -10^4)

        // The 'right' pointer iterates through the array, expanding the window.
        for (int right = 0; right < nums.size(); right++) {
            // Add the element at the 'right' pointer to the current window sum.
            current_window_sum += nums[right];
            // Increment the count of elements in the window.
            count++;
            
            // Check if the window has reached the desired length 'k'.
            // The condition 'left <= right' is always true when 'count == k' for k >= 1,
            // so it's technically redundant but harmless.
            if (count == k) {
                // Calculate the average for the current window.
                // Update 'max_average' if the current window's average is higher.
                max_average = std::max(max_average, current_window_sum / k);
                
                // To slide the window, remove the element at the 'left' pointer
                // from the 'current_window_sum'.
                current_window_sum -= nums[left];
                // Move the 'left' pointer one step to the right.
                left++;
                // Decrement the count as one element has left the window.
                count--;
            }
        }
        // After iterating through all possible windows, return the maximum average found.
        return max_average;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | The `right` pointer iterates through the `nums` array exactly once. Each element is added to `current_window_sum` once and subtracted once. All operations inside the loop are constant time. |
| **Space** | O(1) | Only a few constant extra variables (`left`, `current_window_sum`, `count`, `max_average`) are used, regardless of the input array size. |

## 🔗 Related Problems
*   209. Minimum Size Subarray Sum
*   3. Longest Substring Without Repeating Characters
*   713. Subarray Product Less Than K