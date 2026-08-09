# 0015-3sum

## 📋 Problem Description
Given an integer array `nums`, the task is to find and return all unique triplets `[nums[i], nums[j], nums[k]]` such that `i`, `j`, and `k` are distinct indices, and their corresponding values sum up to zero (`nums[i] + nums[j] + nums[k] == 0`).

The solution set must not contain any duplicate triplets. The order of the triplets or the order of elements within a triplet does not matter.

## 🔍 Examples
```
Input: nums = [-1,0,1,2,-1,-4]
Output: [[-1,-1,2],[-1,0,1]]
Explanation: 
The distinct triplets that sum to 0 are:
(-1) + 0 + 1 = 0
(-1) + (-1) + 2 = 0
```

```
Input: nums = [0,1,1]
Output: []
Explanation: No triplet sums up to 0.
```

```
Input: nums = [0,0,0]
Output: [[0,0,0]]
Explanation: The only possible triplet sums up to 0.
```

## 📌 Constraints
*   `3 <= nums.length <= 3000`
*   `-10^5 <= nums[i] <= 10^5`

## 🤔 Understanding the Problem
The core of this problem is to find three numbers in an array that add up to zero. The main challenges are ensuring that the three numbers come from distinct indices, efficiently finding all such combinations, and critically, making sure that the final list of triplets contains no duplicates. A naive approach of checking all possible combinations (O(N^3)) would be too slow for the given constraints, and handling duplicates would still be complex.

## 💡 Core Idea
The most effective way to solve this problem efficiently and handle duplicates is to first sort the input array. Once sorted, we can iterate through each number and use a Two Pointers technique on the remaining part of the array to find the other two numbers that sum to the required target.

## 🧠 Approach — Two Pointers
This problem is a classic application of the **Two Pointers** pattern, combined with sorting.
The Two Pointers technique is ideal here because once the array is sorted, we can fix one element and then efficiently search for the remaining two elements that complete the sum. By moving two pointers (one from the left, one from the right) inwards, we can adjust the sum based on whether it's too small or too large, quickly converging to the target. Sorting also simplifies the process of skipping duplicate elements, which is crucial for ensuring a unique set of triplets in the output.

## 📝 Step-by-Step Algorithm

1.  **Sort the Array**: Begin by sorting the input array `nums` in non-decreasing order. This step is fundamental for both the Two Pointers approach and for effectively handling duplicate triplets.

2.  **Initialize Result List**: Create an empty `vector<vector<int>>` called `ans` to store all the unique triplets that sum to zero.

3.  **Iterate for the First Element**:
    *   Loop through the sorted array using an index `i` from `0` up to `nums.size() - 3` (we need at least two elements after `nums[i]` to form a triplet).
    *   **Skip Duplicates for `nums[i]`**: To avoid duplicate triplets, if `i > 0` and `nums[i]` is the same as `nums[i-1]`, `continue` to the next iteration. This ensures that we only consider unique values for the first element of our triplet.

4.  **Two Pointers for Remaining Elements**:
    *   Inside the loop for `i`, initialize two pointers: `j` starting at `i + 1` (the element immediately after `nums[i]`) and `k` starting at `nums.size() - 1` (the last element of the array).
    *   Enter a `while` loop that continues as long as `j < k`. This loop searches for the second and third elements of the triplet.

5.  **Calculate Sum and Adjust Pointers**:
    *   Calculate the current sum: `current_sum = nums[i] + nums[j] + nums[k]`. It's good practice to cast to `long long` for `sum` to prevent potential integer overflow, especially if `nums[i]` could be large positive values, though for this problem's constraints, `int` would usually suffice.
    *   **If `current_sum == 0`**:
        *   A valid triplet `[nums[i], nums[j], nums[k]]` has been found. Add it to the `ans` list.
        *   **Skip Duplicates for `nums[j]` and `nums[k]`**: To ensure uniqueness of triplets, increment `j` while `j < k` and `nums[j]` is equal to `nums[j+1]`. Similarly, decrement `k` while `j < k` and `nums[k]` is equal to `nums[k-1]`. This moves the pointers past any identical elements.
        *   After skipping duplicates, move `j` one step forward (`j++`) and `k` one step backward (`k--`) to find the next potential unique pair.
    *   **If `current_sum < 0`**: The sum is too small. To increase the sum, increment the left pointer `j` (`j++`).
    *   **If `current_sum > 0`**: The sum is too large. To decrease the sum, decrement the right pointer `k` (`k--`).

6.  **Return Result**: After the outer loop finishes, return the `ans` list containing all unique triplets that sum to zero.

## 💻 Solution

```cpp
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> ans; // This will store our unique triplets.

        // Step 1: Sort the input array.
        // Sorting is crucial for two reasons:
        // 1. It allows us to use the Two Pointers technique efficiently.
        // 2. It makes it easy to skip duplicate elements.
        sort(nums.begin(), nums.end());

        // Step 2: Iterate through the array to fix the first element (nums[i]).
        // We iterate up to nums.size() - 2 because we need at least two more elements
        // (nums[j] and nums[k]) after nums[i] to form a triplet.
        for (int i = 0; i < nums.size(); i++) {
            // Step 3: Skip duplicates for the first element.
            // If the current element is the same as the previous one,
            // it means we've already considered this value as the first element
            // in a previous iteration, so we skip it to avoid duplicate triplets.
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }

            // Step 4: Initialize two pointers for the remaining part of the array.
            // 'j' starts right after 'i'.
            // 'k' starts at the end of the array.
            int j = i + 1;
            int k = nums.size() - 1;

            // Step 5: Use the Two Pointers technique to find the other two elements.
            // This loop continues as long as the left pointer 'j' is less than the right pointer 'k'.
            while (j < k) {
                // Calculate the sum of the three elements.
                // Using 'long long' for sum is a safer practice to prevent potential integer overflow,
                // although for the given constraints (-10^5 to 10^5), the sum would fit in an int.
                long long sum = (long long)nums[i] + nums[j] + nums[k];

                if (sum == 0) {
                    // If the sum is 0, we found a valid triplet.
                    ans.push_back({nums[i], nums[j], nums[k]});

                    // Step 6: Skip duplicates for the second and third elements.
                    // After finding a triplet, we need to move 'j' and 'k' to the next
                    // unique elements to avoid adding duplicate triplets.
                    while (j < k && nums[j] == nums[j + 1]) {
                        j++; // Increment 'j' as long as it points to a duplicate.
                    }
                    while (j < k && nums[k] == nums[k - 1]) {
                        k--; // Decrement 'k' as long as it points to a duplicate.
                    }

                    // Move pointers to the next unique elements.
                    // Even after skipping duplicates, we still need to move 'j' and 'k'
                    // one step further to continue the search for other triplets.
                    j++;
                    k--;
                } else if (sum < 0) {
                    // If the sum is less than 0, it means we need a larger sum.
                    // To increase the sum, we move the left pointer 'j' forward
                    // to consider a larger number.
                    j++;
                } else { // sum > 0
                    // If the sum is greater than 0, it means we need a smaller sum.
                    // To decrease the sum, we move the right pointer 'k' backward
                    // to consider a smaller number.
                    k--;
                }
            }
        }
        return ans; // Return the list of unique triplets.
    }
};

```

## ⏱️ Complexity Analysis

| | Complexity | Reason |
|---|---|---|
| **Time** | O(N^2) | Sorting takes O(N log N). The outer loop runs N times, and the inner Two Pointers loop runs at most N times for each outer iteration, resulting in O(N * N) = O(N^2). The dominant factor is O(N^2). |
| **Space** | O(log N) or O(N) | O(log N) for the sorting algorithm's auxiliary space (e.g., `std::sort` uses IntroSort, which is typically O(log N) for recursion stack). If the output list is counted, it could be O(N) in the worst case (e.g., if all numbers are 0, or many combinations sum to 0). |

## 🔗 Related Problems
- 1. Two Sum
- 16. 3Sum Closest
- 18. 4Sum