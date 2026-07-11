# 0015-3sum

## 📋 Problem Description
Given an integer array `nums`, the task is to find all unique triplets `[nums[i], nums[j], nums[k]]` such that `i`, `j`, and `k` are distinct indices, and their sum `nums[i] + nums[j] + nums[k]` equals 0.

The solution set must not contain duplicate triplets. This means if `[-1, 0, 1]` is a valid triplet, and another combination of indices also yields `[-1, 0, 1]`, it should only be included once in the final output. The order of elements within a triplet and the order of triplets in the output do not matter.

The function `threeSum` receives a `std::vector<int> nums` as input and must return a `std::vector<std::vector<int>>` containing all such unique triplets.

## 🔍 Examples
```
Input: nums = [-1,0,1,2,-1,-4]
Output: [[-1,-1,2],[-1,0,1]]
Explanation: 
The triplets that sum to 0 are:
(-1) + 0 + 1 = 0
(-1) + (-1) + 2 = 0
The distinct triplets are [-1,0,1] and [-1,-1,2].
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
The problem asks us to find combinations of three distinct numbers from an array that sum up to zero. The key challenges are efficiently finding these triplets and, crucially, ensuring that the final list of triplets contains no duplicates. A naive brute-force approach (checking all possible combinations of three numbers) would be too slow given the array size constraints. The requirement for unique triplets implies that sorting the input array might be beneficial, as it groups identical numbers together, simplifying duplicate handling.

## 💡 Core Idea
The core idea is to first sort the input array. Then, iterate through each number in the sorted array, treating it as the first element of a potential triplet. For the remaining two elements, use a two-pointer approach on the rest of the array to find a pair that sums to the negative of the first element.

## 🧠 Approach — Two Pointers
This problem is a classic application of the **Two Pointers** pattern, combined with sorting.
Sorting the array is crucial because it allows us to efficiently manage the search for the remaining two numbers and easily skip duplicate elements. Once sorted, for a fixed first element `nums[i]`, we can use two pointers (`j` and `k`) to search for `nums[j]` and `nums[k]` such that `nums[j] + nums[k] == -nums[i]`. The two-pointer technique is highly efficient for finding pairs with a specific sum in a sorted array, as it allows us to adjust the sum by moving pointers inwards based on whether the current sum is too high or too low.

## 📝 Step-by-Step Algorithm

1.  **Sort the Array**: Begin by sorting the input array `nums` in non-decreasing order. This step is essential for both the two-pointer approach and for efficiently handling duplicate triplets.

2.  **Initialize Result**: Create an empty vector of vectors, `ans`, to store the unique triplets that sum to zero.

3.  **Iterate through the Array (First Element)**:
    *   Loop through the sorted array using an index `i` from `0` to `n-3` (where `n` is the size of `nums`). This `nums[i]` will be our first element.
    *   **Skip Duplicates for `nums[i]`**: To avoid duplicate triplets, if `i > 0` and `nums[i]` is the same as `nums[i-1]`, skip this iteration using `continue`. This ensures that we only process unique values for the first element.

4.  **Two-Pointer Search (Second and Third Elements)**:
    *   Initialize two pointers: `j` starting at `i + 1` and `k` starting at `n - 1`. These pointers will search for the second and third elements of the triplet.
    *   Enter a `while` loop that continues as long as `j < k`.

5.  **Calculate Sum**: Inside the `while` loop, calculate the current sum: `current_sum = nums[i] + nums[j] + nums[k]`.

6.  **Adjust Pointers Based on Sum**:
    *   If `current_sum < 0`: The sum is too small. To increase the sum, increment `j` (move the left pointer to the right) to consider a larger second element.
    *   If `current_sum > 0`: The sum is too large. To decrease the sum, decrement `k` (move the right pointer to the left) to consider a smaller third element.
    *   If `current_sum == 0`: A triplet that sums to zero has been found!
        *   Add `[nums[i], nums[j], nums[k]]` to the `ans` vector.
        *   Increment `j` and decrement `k` to look for other potential triplets.
        *   **Skip Duplicates for `nums[j]` and `nums[k]`**: After finding a valid triplet and moving `j` and `k`, it's crucial to skip any duplicate values for `nums[j]` and `nums[k]` to ensure the uniqueness of triplets.
            *   While `j < k` and `nums[j]` is the same as `nums[j-1]`, increment `j`.
            *   (Similarly, while `j < k` and `nums[k]` is the same as `nums[k+1]`, decrement `k`. The provided solution only handles `j`'s duplicates, which is sufficient because `k` will naturally move past its duplicates or `j` will catch up.)

7.  **Return Result**: After the outer loop finishes, return the `ans` vector containing all unique triplets that sum to zero.

## 💻 Solution
```cpp
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> ans; // This will store our unique triplets.

        // Step 1: Sort the array. This is crucial for the two-pointer approach
        // and for efficiently handling duplicate triplets.
        sort(nums.begin(), nums.end());

        // Step 3: Iterate through the array to fix the first element (nums[i]).
        // We only need to iterate up to n-3 because we need at least two more elements (j and k).
        for (int i = 0; i < n; i++) {
            // Step 3 (cont.): Skip duplicates for the first element.
            // If the current element is the same as the previous one,
            // it means we've already considered triplets starting with this value,
            // so we skip it to avoid duplicate triplets in the output.
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }

            // Step 4: Initialize two pointers for the remaining part of the array.
            // 'j' starts right after 'i', and 'k' starts at the end of the array.
            int j = i + 1;
            int k = n - 1;

            // Step 4 (cont.): Use a while loop for the two-pointer search.
            // The loop continues as long as the left pointer 'j' is less than the right pointer 'k'.
            while (j < k) {
                // Step 5: Calculate the current sum of the triplet.
                int sum = nums[i] + nums[j] + nums[k];

                // Step 6: Adjust pointers based on the sum.
                if (sum < 0) {
                    // If the sum is less than 0, we need a larger sum.
                    // Move the left pointer 'j' to the right to pick a larger number.
                    j++;
                } else if (sum > 0) {
                    // If the sum is greater than 0, we need a smaller sum.
                    // Move the right pointer 'k' to the left to pick a smaller number.
                    k--;
                } else {
                    // If sum == 0, we found a valid triplet!
                    ans.push_back({nums[i], nums[j], nums[k]});

                    // Move both pointers to look for other potential triplets.
                    // It's important to move both to explore new combinations.
                    j++;
                    k--;

                    // Step 6 (cont.): Skip duplicates for the second element (nums[j]).
                    // After finding a triplet and incrementing 'j', if the new 'nums[j]'
                    // is the same as the previous 'nums[j-1]', we skip it.
                    // This prevents adding duplicate triplets like [-1, 0, 1] and [-1, 0, 1]
                    // if there are multiple 0s or 1s.
                    while (j < k && nums[j] == nums[j - 1]) {
                        j++;
                    }
                    // Note: The problem statement implies that skipping duplicates for 'k'
                    // is also necessary, but the current logic for 'j' often implicitly handles
                    // 'k' as well due to the sorted nature and how 'j' and 'k' converge.
                    // A more robust solution might also include:
                    // while (j < k && nums[k] == nums[k + 1]) {
                    //     k--;
                    // }
                    // However, the provided solution passes, indicating this specific duplicate handling for 'j' is sufficient.
                }
            }
        }
        // Step 7: Return the vector of unique triplets.
        return ans;
    }
};

```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N^2) | Sorting takes O(N log N). The outer loop runs N times. The inner two-pointer loop runs at most N times for each iteration of the outer loop. So, N * N = O(N^2). O(N log N) + O(N^2) simplifies to O(N^2). |
| **Space** | O(1) | We only use a few extra variables for pointers and sum. The space used by the `ans` vector for storing results is typically not counted towards auxiliary space complexity. If the sorting algorithm uses auxiliary space (e.g., merge sort), it could be O(N) or O(log N), but in-place sorts are O(1). |

## 🔗 Related Problems
- 1. Two Sum
- 16. 3Sum Closest
- 18. 4Sum