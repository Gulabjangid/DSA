# 0078-subsets

## 📋 Problem Description
Given an integer array `nums` containing unique elements, the task is to return all possible subsets (also known as the power set). The solution set must not contain duplicate subsets, and the order in which the subsets are returned does not matter.

The function `subsets` receives a `vector<int> nums` as input and must return a `vector<vector<int>>` containing all unique subsets.

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
The problem asks us to find every possible combination of elements from the given input array `nums`, including the empty set and the set itself. Since the elements in `nums` are unique, we don't need to worry about generating duplicate subsets due to repeated numbers in the input. The key challenge is systematically exploring all possibilities without missing any subset or generating duplicates.

## 💡 Core Idea
The fundamental insight is that for each element in the input array, we have two distinct choices: either include it in the current subset being formed or exclude it. By systematically exploring all combinations of these choices for every element, we can generate every possible subset.

## 🧠 Approach — Backtracking
This problem is a classic application of **Backtracking**. Backtracking is an algorithmic technique for solving problems recursively by trying to build a solution incrementally, one piece at a time. If a partial solution can't be completed into a valid full solution, or if it violates constraints, we "backtrack" (undo the last step) and try a different path.

Here's why it fits: We are building subsets by making a decision for each element (include or exclude). We start with an empty subset and iterate through the `nums` array. For each number, we recursively explore two branches: one where the number is added to the current subset, and one where it's not. Once we've made a decision for all numbers, a complete subset is formed. The "backtracking" part comes when we remove an element after exploring the "include" branch, allowing the recursion to explore the "exclude" branch for the same element in the context of the previous state.

## 📝 Step-by-Step Algorithm
1.  **Initialization**:
    *   Create an empty `vector<vector<int>>` called `allsubsets` to store all the generated subsets.
    *   Create an empty `vector<int>` called `ans` to store the current subset being built during the recursion.
    *   Start the recursive process by calling a helper function, say `getallsubsets`, with the input `nums`, the current subset `ans`, an initial index `0`, and the `allsubsets` container.

2.  **Recursive Helper Function `getallsubsets(nums, ans, index, allsubsets)`**:
    *   **Base Case**: If `index` reaches `nums.size()` (meaning we have considered all elements in `nums`):
        *   The current `ans` vector represents a complete subset. Add a copy of `ans` to `allsubsets`.
        *   Return from the function.

    *   **Recursive Step (Choice 1: Include `nums[index]`)**:
        *   Add `nums[index]` to the `ans` vector.
        *   Recursively call `getallsubsets` with `index + 1` (to consider the next element).

    *   **Backtrack**: After the recursive call for "include" returns, remove `nums[index]` from `ans`. This is crucial for backtracking, as it undoes the choice and restores `ans` to its state before `nums[index]` was added, allowing us to explore the "exclude" branch.

    *   **Recursive Step (Choice 2: Exclude `nums[index]`)**:
        *   Recursively call `getallsubsets` with `index + 1` (to consider the next element), without adding `nums[index]` to `ans`.

3.  **Return Result**: After the initial call to `getallsubsets` completes, `allsubsets` will contain all unique subsets. Return `allsubsets`.

## 💻 Solution
```cpp
class Solution {
public:
    // Helper function to recursively generate all subsets
    // nums: The input array of unique integers
    // ans: The current subset being built
    // i: The current index in nums we are considering
    // allsubsets: The final list to store all generated subsets
    void getallsubsets(vector<int> &nums, vector<int> &ans, int i, vector<vector<int>> &allsubsets) {
        // Base case: If we have considered all elements in nums
        if (i == nums.size()) {
            // The 'ans' vector now holds a complete subset.
            // Add a copy of this subset to our collection of all subsets.
            allsubsets.push_back(ans);
            return; // End this recursive path
        }

        // --- Decision 1: Include the current element nums[i] ---
        // Add the current element to our temporary subset
        ans.push_back(nums[i]);
        // Recursively call for the next element (i+1)
        // This path explores subsets that include nums[i]
        getallsubsets(nums, ans, i + 1, allsubsets);

        // --- Backtrack ---
        // After the recursive call for including nums[i] returns,
        // we remove nums[i] from 'ans'. This is crucial for backtracking.
        // It reverts 'ans' to its state before nums[i] was added,
        // allowing us to explore the path where nums[i] is excluded.
        ans.pop_back();

        // --- Decision 2: Exclude the current element nums[i] ---
        // Recursively call for the next element (i+1) without adding nums[i].
        // This path explores subsets that exclude nums[i].
        getallsubsets(nums, ans, i + 1, allsubsets);
    }

    // Main function to find all subsets
    vector<vector<int>> subsets(vector<int>& nums) {
        // This will store all the final subsets
        vector<vector<int>> allsubsets;
        // This will store the current subset being constructed
        vector<int> ans;

        // Start the recursive process from the first element (index 0)
        getallsubsets(nums, ans, 0, allsubsets);

        // Return the collection of all subsets
        return allsubsets;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N \* 2^N) | There are 2^N total subsets. For each subset, we perform operations (like copying to `allsubsets`) that take up to O(N) time, where N is the number of elements in `nums`. |
| **Space** | O(N \* 2^N) | The recursion stack depth can go up to O(N). The dominant factor is storing all 2^N subsets. In the worst case, each subset can contain up to N elements, leading to O(N \* 2^N) space for the output. |

## 🔗 Related Problems
- 77. Combinations
- 90. Subsets II
- 40. Combination Sum II