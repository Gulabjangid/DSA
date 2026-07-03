# 0113-path-sum-ii

## 📋 Problem Description
Given the `root` of a binary tree and an integer `targetSum`, the task is to find all root-to-leaf paths where the sum of the node values along the path equals `targetSum`. Each such path should be returned as a list of its node values.

A **root-to-leaf** path is defined as a path starting from the root node and ending at any leaf node. A **leaf** node is a node that has no children (i.e., both its left and right pointers are null).

The function should return a list of lists of integers, where each inner list represents a valid root-to-leaf path.

## 🔍 Examples

**Example 1:**
```
Input: root = [5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22
Output: [[5,4,11,2],[5,8,4,5]]
Explanation: There are two paths whose sum equals targetSum:
5 + 4 + 11 + 2 = 22
5 + 8 + 4 + 5 = 22
```

**Example 2:**
```
Input: root = [1,2,3], targetSum = 5
Output: []
Explanation: No root-to-leaf path sums to 5.
```

**Example 3:**
```
Input: root = [1,2], targetSum = 0
Output: []
Explanation: No root-to-leaf path sums to 0. (The only root-to-leaf path is [1,2] which sums to 3).
```

## 📌 Constraints
*   The number of nodes in the tree is in the range `[0, 5000]`.
*   `-1000 <= Node.val <= 1000`
*   `-1000 <= targetSum <= 1000`

## 🤔 Understanding the Problem
The problem asks us to find *all* paths from the root to any leaf node that sum up to a specific `targetSum`. This means we need to explore every possible root-to-leaf path. We're not just checking if *any* such path exists (like in "Path Sum I"), but we need to collect the actual node values for *all* such paths. Edge cases include an empty tree (no paths, return empty list) or a tree where no path sums to the target. The challenge lies in efficiently traversing the tree, keeping track of the current path and its sum, and correctly handling the collection and backtracking of paths.

## 💡 Core Idea
The core idea is to traverse the tree using Depth-First Search (DFS), maintaining the current path and its running sum. When a leaf node is reached, we check if the current path's sum matches the `targetSum`. If it does, we record this path.

## 🧠 Approach — Depth-First Search (DFS) with Backtracking
This problem is a classic application of **Depth-First Search (DFS)** combined with **Backtracking**.

DFS is suitable because we need to explore every path from the root down to a leaf. It naturally explores one branch completely before moving to the next. Backtracking is crucial here: as we go deeper into the tree, we add node values to our current path and sum. When we finish exploring all paths from a certain node (i.e., return from its recursive calls), we need to "undo" the changes made by that node – specifically, remove its value from the current path list. This allows us to explore sibling branches correctly without carrying over values from previous, unrelated paths.

## 📝 Step-by-Step Algorithm

1.  **Initialization**:
    *   Create an empty list of lists, `OUTPUT`, to store all the valid root-to-leaf paths found.
    *   Create an empty list, `ans`, to temporarily store the node values of the current path being explored.

2.  **Define a Recursive Helper Function (`dfs`)**:
    *   The `dfs` function will take three parameters:
        *   `node`: The current `TreeNode` being visited.
        *   `tar`: The `targetSum` we are looking for.
        *   `sum`: The current sum of node values from the root to the `node` (exclusive of `node->val` initially, but updated inside the function).

3.  **Base Case for Recursion**:
    *   If `node` is `nullptr` (meaning we've gone past a leaf or started with an empty tree), simply return. There's no path to explore from here.

4.  **Process Current Node**:
    *   Add the `node->val` to the `sum`.
    *   Add the `node->val` to the `ans` list (to record the current path).

5.  **Check for Leaf Node and Target Sum**:
    *   If the current `node` is a leaf node (i.e., `node->left` is `nullptr` AND `node->right` is `nullptr`):
        *   Check if the `sum` equals `tar`.
        *   If `sum == tar`, it means we've found a valid root-to-leaf path. Add a *copy* of the current `ans` list to the `OUTPUT` list.
        *   **Backtrack**: After checking, remove the `node->val` from `ans` (because we are done with this leaf node and its path, and will return to its parent to explore other branches). Then, return from the function.

6.  **Recursive Calls for Children**:
    *   Recursively call `dfs` for the left child: `dfs(node->left, tar, sum)`.
    *   Recursively call `dfs` for the right child: `dfs(node->right, tar, sum)`.

7.  **Backtracking (after exploring children)**:
    *   After the recursive calls for both children return (meaning all paths through the current `node` have been explored), remove the `node->val` from the `ans` list. This is crucial for backtracking, allowing the parent node to explore its other child or return to its own parent without `node->val` being part of subsequent paths.

8.  **Main Function (`pathSum`)**:
    *   Call the `dfs` helper function starting from the `root` with the `targetSum` and an initial `currentSum` of `0`.
    *   Return the `OUTPUT` list containing all the found paths.

## 💻 Solution

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
 * right(right) {}
 * };
 */
class Solution {
public:
    // 'ans' stores the current path being explored from root to the current node.
    vector<int> ans;
    // 'OUTPUT' stores all the valid root-to-leaf paths that sum up to targetSum.
    vector<vector<int>> OUTPUT;

    // Helper function to perform Depth-First Search (DFS)
    // node: The current node being visited
    // tar: The target sum we are looking for
    // sum: The current sum of node values from the root to the 'node' (inclusive of 'node->val' after the first line)
    void dfs(TreeNode* node, int tar, int sum) {

        // Base case: If the current node is null, there's nothing to process.
        // This handles cases where a child doesn't exist (e.g., node->left is null)
        // or if the initial root itself was null.
        if (!node)
            return;
     
        // Add the current node's value to the running sum.
        sum += node->val;
        // Add the current node's value to the temporary path list.
        ans.push_back(node->val);
      

        // Check if the current node is a leaf node.
        // A leaf node has no left child and no right child.
        if (!node->left && !node->right) {
            
            // If it's a leaf node, check if the current path sum equals the target sum.
            if (sum == tar) {
                // If it matches, we found a valid path.
                // Add a copy of the current path (ans) to our final results (OUTPUT).
                OUTPUT.push_back(ans);
            }
            // Backtrack: Remove the current node's value from 'ans'
            // as we are done exploring paths through this leaf node.
            // This prepares 'ans' for the parent's next child or its return.
            ans.pop_back();
            return; // Return from this leaf node's processing.
        }

        // Recursively call dfs for the left child.
        // The 'sum' passed here includes the current node's value.
        dfs(node->left, tar, sum);
        // Recursively call dfs for the right child.
        // The 'sum' passed here also includes the current node's value.
        dfs(node->right, tar, sum);
        
        // Backtrack: After exploring both left and right subtrees (or if one was null),
        // remove the current node's value from 'ans'.
        // This is essential for exploring other branches of the tree correctly.
        // For example, when returning from the right child, the parent needs to
        // remove its own value before returning to its grandparent.
        ans.pop_back();
        
    }

    // Main function to find all path sums.
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        // Start the DFS traversal from the root.
        // Initial sum is 0.
        dfs(root, targetSum, 0);
        // Return the collected paths.
        return OUTPUT;
    }
};

```

## ⏱️ Complexity Analysis

| | Complexity | Reason |
|---|---|---|
| **Time** | O(N * H) | Each of the `N` nodes is visited once. In the worst case, when a valid path is found, copying the `ans` vector to `OUTPUT` takes `O(H)` time, where `H` is the height of the tree. If there are `K` such paths, the total time for copying paths could be `O(K * H)`. In a skewed tree, `H` can be `N`, leading to `O(N^2)` in the worst case (e.g., if many paths are stored). For a balanced tree, `H = log N`, leading to `O(N log N)`. |
| **Space** | O(H + K * H) | `O(H)` for the recursion stack depth (where `H` is the height of the tree; `H=N` in worst case for skewed tree) and for the `ans` vector. Additionally, `O(K * H)` for storing the `OUTPUT` list, where `K` is the number of valid paths and `H` is the maximum path length. In the worst case (e.g., a tree where many paths are stored and `H` is large), this can be `O(N^2)`. |

## 🔗 Related Problems
- 112. Path Sum
- 437. Path Sum III
- 257. Binary Tree Paths