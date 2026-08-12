# 0078-subsets

## 📋 Problem Description
Given an integer array `nums` containing unique elements, the task is to return all possible subsets (also known as the power set). The solution set must not contain duplicate subsets, and the order in which the subsets are returned does not matter.

The function `subsets` receives one argument:
- `nums`: An integer array of unique elements.

It must return:
- A `vector<vector<int>>`: A list of all possible subsets of `nums`.

## 🔍 Examples
```
Input: nums = [1,2,3]
Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
Explanation: These are all 2^3 = 8 possible subsets of [1,2,3].
```

```
Input: nums = [0]
Output: [[],[0]]
Explanation: These are all 2^1 = 2 possible subsets of [0].
```

## 📌 Constraints
*   `1 <= nums.length <= 10`
*   `-10 <= nums[i] <= 10`
*   All the numbers of `nums` are unique.

## 🤔 Understanding the Problem
The problem asks us to generate every possible combination of elements from the given input array `nums`, including the empty set. Since the elements in `nums` are unique, we don't need to worry about generating duplicate subsets due to repeated numbers. The core challenge is systematically exploring all `2^N` possibilities, where `N` is the number of elements in `nums`, to ensure no subset is missed and no duplicates are included.

## 💡 Core Idea
For each element in the input array `nums`, we have two fundamental choices: either include the element in the current subset we are building, or exclude it. By exhaustively exploring both of these choices for every element, we can generate all unique subsets.

## 🧠 Approach — Backtracking / Recursion
This problem is a classic example of a **Backtracking** problem.
Backtracking is an algorithmic technique for solving problems recursively by trying to build a solution incrementally, one piece at a time, removing those solutions that fail to satisfy the constraints of the problem at any point of time (backtracking) and trying another path.

This pattern fits perfectly here because:
1.  **Decision Tree**: For each number, we make a decision (include or exclude), which branches our search space.
2.  **Incremental Building**: We build a subset element by element.
3.  **Exploration**: We need to explore *all* possible combinations, not just one optimal solution.
4.  **Undo Choices**: After exploring a path (e.g., including an element), we need to "undo" that choice (remove the element) to explore alternative paths where that element is excluded. This "undoing" is the essence of backtracking.

## 📝 Step-by-Step Algorithm
1.  **Initialization**:
    *   Create an empty list `allsubsets` to store all the generated subsets.
    *   Create an empty list `current_subset` to temporarily store the subset being built during the recursion.
    *   Start the recursive process from the first element of `nums` (index `0`).

2.  **Recursive Function `getallsubsets(nums, current_subset, index, allsubsets)`**:
    *   **Base Case**: If `index` reaches the size of `nums` (meaning all elements have been considered), then the `current_subset` is complete. Add a copy of `current_subset` to `allsubsets`. Then, return from the function.

    *   **Recursive Step 1: Include the current element `nums[index]`**:
        *   Add `nums[index]` to `current_subset`.
        *   Recursively call `getallsubsets` for the next element (`index + 1`).

    *   **Recursive Step 2: Exclude the current element `nums[index]` (Backtrack)**:
        *   Remove the last element added to `current_subset` (which was `nums[index]`). This "undoes" the choice made in Step 1, allowing us to explore the path where `nums[index]` is *not* included.
        *   Recursively call `getallsubsets` for the next element (`index + 1`).

3.  **Return**: After the initial call to `getallsubsets` completes, `allsubsets` will contain all unique subsets. Return `allsubsets`.

## 💻 Solution
```cpp
class Solution {
public:
    // Helper function to generate all subsets using backtracking
    // nums: The original array of unique integers
    // ans: The current subset being built
    // i: The current index in nums we are considering
    // allsubsets: The final list to store all generated subsets
    void getallsubsets(vector<int> &nums, vector<int> &ans, int i, vector<vector<int>> &allsubsets) {
        // Base Case: If we have considered all elements in 'nums'
        if (i == nums.size()) {
            // The 'ans' vector now represents a complete subset
            // Add a copy of this subset to our list of all subsets
            allsubsets.push_back(ans);
            return; // End this recursive path
        }

        // Decision 1: Include the current element nums[i] in the subset
        ans.push_back(nums[i]); // Add nums[i] to the current subset
        // Recursively call for the next element (i+1)
        getallsubsets(nums, ans, i + 1, allsubsets);

        // Backtrack: Undo the decision made in Decision 1
        // Remove nums[i] from 'ans' so we can explore the path where nums[i] is NOT included
        ans.pop_back();

        // Decision 2: Exclude the current element nums[i] from the subset
        // We already removed nums[i] in the pop_back() step, so 'ans' is now without nums[i]
        // Recursively call for the next element (i+1)
        getallsubsets(nums, ans, i + 1, allsubsets);
    }

    // Main function to find all subsets
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> allsubsets; // This will store all the final subsets
        vector<int> ans; // This will store the current subset being built during recursion

        // Start the backtracking process from the first element (index 0)
        getallsubsets(nums, ans, 0, allsubsets);

        return allsubsets; // Return the collected list of all subsets
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N * 2^N) | There are `2^N` total subsets. For each subset, copying it to the result list takes O(N) time in the worst case (for a subset of size N). |
| **Space** | O(N * 2^N) | The space required to store all `2^N` subsets. In the worst case, each subset can have up to `N` elements. Additionally, the recursion stack depth is O(N). |

## 🔗 Related Problems
- 46. Permutations
- 77. Combinations
- 90. Subsets II