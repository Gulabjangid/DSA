# 0015-3sum

## 📋 Problem Description
Given an integer array `nums`, the task is to find all unique triplets `[nums[i], nums[j], nums[k]]` such that `i`, `j`, and `k` are distinct indices, and their corresponding values sum up to zero (`nums[i] + nums[j] + nums[k] == 0`).

The solution set must not contain duplicate triplets. The order of the output triplets and the order of elements within a triplet does not matter.

The function `threeSum` receives an integer array `nums` as input and must return a `vector<vector<int>>` containing all such unique triplets.

## 🔍 Examples
```
Input: nums = [-1,0,1,2,-1,-4]
Output: [[-1,-1,2],[-1,0,1]]
Explanation: 
The triplets that sum to 0 are:
(-1) + 0 + 1 = 0 (from indices 0, 1, 2)
0 + 1 + (-1) = 0 (from indices 1, 2, 4)
(-1) + 2 + (-1) = 0 (from indices 0, 3, 4)
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
The problem asks us to find all combinations of three distinct numbers from a given array that add up to zero. The main challenge is twofold: first, to do this efficiently for arrays up to 3000 elements (a naive O(N^3) approach would be too slow); second, to ensure that the final list of triplets contains only unique combinations, even if the input array has duplicate numbers. For example, if `nums = [-1, -1, 2]`, `[-1, -1, 2]` is a valid triplet, but if the array was `[-1, -1, -1, 2, 2]`, we should still only output `[-1, -1, 2]` once.

## 💡 Core Idea
The most crucial insight is to first **sort the input array**. Sorting allows us to efficiently search for complementary numbers using a two-pointer technique and also simplifies the process of skipping duplicate elements to ensure unique triplets in the output.

## 🧠 Approach — Two Pointers
This problem is a classic application of the **Two Pointers** pattern, combined with an initial sorting step.
The Two Pointers pattern is highly effective when dealing with sorted arrays where you need to find pairs of elements that satisfy a certain condition (like summing to a target). By sorting the array, we can fix one element and then use two pointers (one starting from the element after the fixed one, and one from the end of the array) to search for the remaining two elements. This approach allows us to adjust the sum by moving the pointers inward or outward, drastically reducing the search space compared to a brute-force approach. The sorted order also makes it straightforward to detect and skip duplicate elements, which is essential for satisfying the "no duplicate triplets" requirement.

## 📝 Step-by-Step Algorithm
1.  **Sort the Array**: Begin by sorting the input array `nums` in non-decreasing order. This is crucial for both the two-pointer approach and for efficiently handling duplicates.
2.  **Initialize Result**: Create an empty `vector<vector<int>>` called `ans` to store the unique triplets.
3.  **Iterate with First Pointer (`i`)**: Loop through the sorted array using an index `i` from the beginning up to `nums.size() - 3`. This `nums[i]` will be the first element of our potential triplet.
    *   **Skip Duplicates for `nums[i]`**: To avoid duplicate triplets, if `i` is not the first element (`i > 0`) and `nums[i]` is the same as the previous element `nums[i-1]`, then skip this iteration and continue to the next `i`. This ensures that we only consider unique values for the first element of a triplet.
4.  **Initialize Two Pointers (`j` and `k`)**: For each `nums[i]`, set a second pointer `j` to `i + 1` (the element immediately after `nums[i]`) and a third pointer `k` to `nums.size() - 1` (the last element of the array).
5.  **Two-Pointer Search**: While `j` is less than `k` (meaning there are at least two elements remaining to form a pair):
    *   **Calculate Sum**: Compute the current sum: `current_sum = nums[i] + nums[j] + nums[k]`.
    *   **Found Triplet**: If `current_sum == 0`:
        *   A valid triplet `[nums[i], nums[j], nums[k]]` has been found. Add it to `ans`.
        *   **Skip Duplicates for `nums[j]` and `nums[k]`**: To ensure unique triplets, increment `j` while `j < k` and `nums[j]` is equal to `nums[j+1]`. Similarly, decrement `k` while `j < k` and `nums[k]` is equal to `nums[k-1]`. This moves `j` and `k` past any duplicate values they might be pointing to.
        *   **Move Pointers**: After handling duplicates, move `j` one step forward (`j++`) and `k` one step backward (`k--`) to search for the next distinct pair.
    *   **Sum Too Small**: If `current_sum < 0`: The sum is too small. To increase the sum, increment `j` (`j++`) to consider a larger second number.
    *   **Sum Too Large**: If `current_sum > 0`: The sum is too large. To decrease the sum, decrement `k` (`k--`) to consider a smaller third number.
6.  **Return Result**: After the outer loop completes, return the `ans` vector containing all unique triplets that sum to zero.

## 💻 Solution

```cpp
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> ans; // This will store our resulting unique triplets.
        
        // Step 1: Sort the input array.
        // Sorting is crucial for two reasons:
        // 1. It allows us to use the two-pointer technique efficiently.
        // 2. It makes it easy to skip duplicate elements to ensure unique triplets.
        sort(nums.begin(), nums.end());
        
        // Iterate through the array with 'i' as the first element of the triplet.
        // We go up to nums.size() - 2 because we need at least two more elements (j and k)
        // after 'i' to form a triplet.
        for (int i = 0; i < nums.size(); i++) {
            // Step 3a: Skip duplicates for the first element (nums[i]).
            // If 'i' is not the first element and nums[i] is the same as the previous element,
            // it means we've already processed this value as a first element in the previous iteration.
            // Skipping it prevents duplicate triplets in the output.
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue; 
            }
            
            // Step 4: Initialize two pointers, 'j' and 'k'.
            // 'j' starts right after 'i'.
            // 'k' starts at the end of the array.
            int j = i + 1;
            int k = nums.size() - 1;
            
            // Step 5: Two-pointer search.
            // Continue as long as 'j' is less than 'k' (meaning there are at least two elements
            // between or at 'j' and 'k' to form a pair).
            while (j < k) {
                // Calculate the sum of the three current elements.
                // Using long long for sum to prevent potential integer overflow,
                // as nums[i] can be up to 10^5, and 3 * 10^5 might exceed int max.
                long long sum = (long long)nums[i] + nums[j] + nums[k];
                
                if (sum == 0) {
                    // Step 5.i: Triplet found!
                    ans.push_back({nums[i], nums[j], nums[k]});
                    
                    // Step 5.ii: Skip duplicates for the second (nums[j]) and third (nums[k]) elements.
                    // After finding a valid triplet, we need to move 'j' and 'k' to the next
                    // *unique* elements to avoid adding duplicate triplets.
                    while (j < k && nums[j] == nums[j + 1]) {
                        j++; // Increment 'j' while it points to a duplicate.
                    }
                    while (j < k && nums[k] == nums[k - 1]) {
                        k--; // Decrement 'k' while it points to a duplicate.
                    }

                    // Step 5.iii: Move pointers to the next distinct elements.
                    // After skipping duplicates, move 'j' and 'k' one step further
                    // to continue the search for other triplets.
                    j++;
                    k--;
                } else if (sum < 0) {
                    // Step 5.iv: Sum is too small.
                    // To increase the sum, we need a larger second element.
                    // So, increment 'j' to move towards larger values.
                    j++;
                } else { // sum > 0
                    // Step 5.v: Sum is too large.
                    // To decrease the sum, we need a smaller third element.
                    // So, decrement 'k' to move towards smaller values.
                    k--;
                }
            }
        }
        
        // Step 6: Return the list of unique triplets.
        return ans;
    }
};

```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N^2) | Sorting takes O(N log N). The outer loop runs N times. The inner two-pointer loop runs at most N times for each `i`. Thus, N * N = O(N^2). Since O(N log N) is dominated by O(N^2), the overall time complexity is O(N^2). |
| **Space** | O(N) | O(N) space is used for storing the `ans` vector in the worst case (e.g., if all elements are 0, or many combinations exist). If we consider auxiliary space (excluding the output list), it's O(log N) or O(N) depending on the specific sorting algorithm's implementation (e.g., quicksort uses O(log N) stack space, merge sort uses O(N) auxiliary space). |

## 🔗 Related Problems
*   1. Two Sum
*   16. 3Sum Closest
*   18. 4Sum
*   259. 3Sum Smaller