# 0257-binary-tree-paths

## 📋 Problem Description
Given the `root` of a binary tree, the task is to find and return all paths from the root node to any leaf node. A leaf node is defined as a node that has no children (i.e., both its left and right children are `nullptr`). The order in which the root-to-leaf paths are returned does not matter.

The function receives a `TreeNode* root` as input and must return a `vector<string>`, where each string represents a root-to-leaf path formatted as "val1->val2->...->valN".

## 🔍 Examples
**Example 1:**
```
Input: root = [1,2,3,null,5]
Output: ["1->2->5","1->3"]
Explanation: The tree has two root-to-leaf paths: 1->2->5 and 1->3.
```
**Example 2:**
```
Input: root = [1]
Output: ["1"]
Explanation: The tree has only one node, which is also a leaf. The path is "1".
```

## 📌 Constraints
*   The number of nodes in the tree is in the range `[1, 100]`.
*   `-100 <= Node.val <= 100`

## 🤔 Understanding the Problem
The problem requires us to systematically explore every possible path from the top of the tree (the root) down to its very ends (the leaf nodes). We need to construct a string representation for each of these paths, including the values of all nodes along the path, separated by "->". An important edge case to consider is a tree with only a single node, where the root itself is a leaf.

## 💡 Core Idea
The fundamental idea is to traverse the tree, keeping track of the path taken from the root to the current node. When a leaf node is encountered, the path accumulated so far represents a complete root-to-leaf path and should be recorded.

## 🧠 Approach — Depth-First Search (DFS)
This problem is a classic application of Depth-First Search (DFS) because we need to explore every path from the root down to its leaves. DFS naturally lends itself to this task by recursively visiting each child node until a base case (a leaf node or a null node) is reached. As we go deeper into the tree, we build up the current path string, and when we hit a leaf, we've found a complete path. The recursive nature of DFS allows us to easily backtrack and explore other branches without explicitly managing a stack.

## 📝 Step-by-Step Algorithm
1.  Initialize an empty `vector<string>` named `ans` (or similar) within the `Solution` class to store all the root-to-leaf paths found.
2.  Define a recursive helper function, let's call it `dfs`, which takes two arguments: the current `TreeNode* node` being visited and a `string current_path` representing the path from the root to the `node`'s parent.
3.  **Base Case 1**: Inside `dfs`, if the `node` is `nullptr` (meaning we've gone past a leaf or into an empty branch), simply return, as there's nothing to process further down this branch.
4.  **Build Current Path**:
    *   If `current_path` is not empty, it means this is not the very first node (root). In this case, append "->" to `current_path` to separate the current node's value from the previous ones.
    *   Convert the integer `node->val` to its string representation using `to_string()` and append it to `current_path`.
5.  **Base Case 2 (Leaf Node Check)**: If the `node` has no left child (`node->left == nullptr`) AND no right child (`node->right == nullptr`), it means `node` is a leaf node.
    *   In this case, the `current_path` string now represents a complete root-to-leaf path. Add this `current_path` to the `ans` vector.
    *   Since it's a leaf, we don't need to explore further down this branch, so return.
6.  **Recursive Calls**: If `node` is not a leaf, continue the DFS traversal:
    *   Recursively call `dfs` for its left child, passing the updated `current_path`: `dfs(node->left, current_path)`.
    *   Recursively call `dfs` for its right child, passing the updated `current_path`: `dfs(node->right, current_path)`.
    *   *Important Note*: The `current_path` string is passed by value in C++. This means each recursive call receives its own copy of the path, ensuring that changes made for one branch (e.g., exploring the left child) do not affect the path when exploring the other branch (the right child).
7.  The main `binaryTreePaths` function will initiate the process by calling `dfs(root, "")` with the initial `root` and an empty string for the path.
8.  Finally, after the `dfs` function completes its execution for all branches, the `binaryTreePaths` function returns the `ans` vector containing all collected root-to-leaf paths.

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
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    // This vector will store all the root-to-leaf paths found during the DFS traversal.
    vector<string> ans;

    // Helper function to perform Depth-First Search (DFS)
    // 'node': The current node being visited in the tree.
    // 'path': The string representing the path from the root to the current node's parent.
    void dfs(TreeNode* node, string path){
        // Base case 1: If the current node is null, it means we've traversed beyond a leaf
        // or into an empty branch. There's nothing to add to the path, so we simply return.
        if(!node) {
            return;
        }

        // If the 'path' string is not empty, it implies this is not the very first node (root).
        // Therefore, we need to append "->" to separate the current node's value from the previous ones.
        if(!path.empty()){
            path+="->";
        }
        // Convert the integer value of the current node to its string representation
        // and append it to the 'path' string.
        path+=to_string(node->val);

        // Base case 2: Check if the current node is a leaf node.
        // A leaf node is defined as a node that has no left child AND no right child.
        if(!node->left && !node->right){
            // If it's a leaf, the 'path' string now represents a complete root-to-leaf path.
            // Add this fully constructed path to our results vector.
            ans.push_back(path);
            // Since it's a leaf, we don't need to explore further down this branch, so return.
            return;
        }

        // If the current node is not a leaf, continue the DFS traversal.
        // Recursively call dfs for the left child, passing the updated 'path'.
        dfs(node->left,path);
        // Recursively call dfs for the right child, passing the updated 'path'.
        // Note: 'path' is passed by value (string path), which means a copy of the string
        // is made for each recursive call. This is crucial because it ensures that
        // changes made to 'path' in one branch (e.g., for the left child) do not
        // affect the 'path' when exploring the other branch (the right child).
    }

    // Main function to find all binary tree paths.
    // It initiates the DFS traversal and returns the collected paths.
    vector<string> binaryTreePaths(TreeNode* root) {
        // Start the DFS traversal from the root node with an empty initial path string.
        // The 'ans' vector will be populated by the dfs helper function.
        dfs(root,"");
        // After the DFS completes, 'ans' will contain all root-to-leaf paths.
        return ans;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N * L) | N is the number of nodes. L is the maximum length of a path (which is the height of the tree, H). Each node is visited once. At each node, string operations (concatenation, `to_string`) take time proportional to the current path length, which can be up to L. Summing this over all N nodes gives O(N * L). |
| **Space** | O(N * L) | N is the number of nodes. L is the maximum length of a path (tree height H). This accounts for two main factors: <br> 1. **Recursion Stack**: The maximum depth of the recursion stack is O(H). Each stack frame holds a copy of the `path` string, which can be up to O(L) characters long. So, stack space is O(H * L). <br> 2. **Result Storage**: The `ans` vector stores all root-to-leaf paths. In the worst case (e.g., a "comb" tree or a complete binary tree), the total length of all characters across all paths can be up to O(N * L). |

## 🔗 Related Problems
- 112. Path Sum
- 113. Path Sum II
- 129. Sum Root to Leaf Numbers