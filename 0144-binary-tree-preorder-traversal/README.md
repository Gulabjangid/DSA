# 0144-binary-tree-preorder-traversal

## 📋 Problem Description
Given the `root` of a binary tree, the task is to return the preorder traversal of its nodes' values. Preorder traversal means that for any given node, we first visit the node itself, then recursively traverse its left subtree, and finally recursively traverse its right subtree.

The function should accept a `TreeNode* root` as input and return a `vector<int>` containing the values of the nodes in preorder sequence.

## 🔍 Examples
```
Input: root = [1,null,2,3]
Output: [1,2,3]
Explanation: The tree structure is: 1 (root) -> null (left), 2 (right). Node 2 -> 3 (left), null (right).
Preorder sequence: Visit 1, then its left subtree (empty), then its right subtree (rooted at 2).
For node 2: Visit 2, then its left subtree (rooted at 3), then its right subtree (empty).
For node 3: Visit 3, then its left subtree (empty), then its right subtree (empty).
Result: [1, 2, 3].
```

```
Input: root = [1,2,3,4,5,null,8,null,null,6,7,9]
Output: [1,2,4,5,6,7,3,8,9]
Explanation: A larger tree demonstrating the root -> left -> right order.
```

```
Input: root = []
Output: []
Explanation: An empty tree results in an empty traversal list.
```

```
Input: root = [1]
Output: [1]
Explanation: A single-node tree simply returns the value of that node.
```

## 📌 Constraints
*   The number of nodes in the tree is in the range `[0, 100]`.
*   `-100 <= Node.val <= 100`

## 🤔 Understanding the Problem
This problem asks us to implement one of the fundamental ways to traverse a binary tree: preorder traversal. The core idea is to visit the current node, then explore its left branch, and finally its right branch. We need to collect the values of the nodes in this specific order. Edge cases include an empty tree (where the root is `NULL`) or a tree with just a single node. Understanding the recursive nature of trees is key to solving this efficiently.

## 💡 Core Idea
The core idea is to directly translate the definition of preorder traversal into a recursive function: for any given node, first add its value to the result, then recursively call the function on its left child, and finally recursively call it on its right child.

## 🧠 Approach — Depth-First Search (DFS) / Recursion
This problem is a classic application of **Depth-First Search (DFS)**, specifically implemented using **recursion**. DFS is a natural fit for tree traversal problems because trees are inherently recursive data structures: a tree is either empty or consists of a root node and two subtrees (left and right), which are themselves trees. Recursion allows us to define the traversal logic for a single node and then let the function call itself to handle the subtrees, naturally exploring one branch completely before moving to the next. The preorder definition (Root -> Left -> Right) maps perfectly to a recursive function's execution flow.

## 📝 Step-by-Step Algorithm
1.  **Define a Helper Function**: Create a recursive helper function, let's call it `preorder`, that takes two arguments:
    *   `TreeNode* root`: The current node being processed.
    *   `vector<int>& ans`: A reference to a vector where the node values will be stored.
2.  **Base Case**: Inside the `preorder` helper function, check if the current `root` is `NULL`. If it is, this means we've reached past a leaf node or an empty subtree, so there's nothing to add. Simply return from the function.
3.  **Process Current Node**: If `root` is not `NULL`, add the value of the current node (`root->val`) to the `ans` vector. This is the "pre" part of preorder traversal.
4.  **Recurse Left**: Call the `preorder` helper function recursively on the `root->left` child, passing the same `ans` vector. This explores the entire left subtree.
5.  **Recurse Right**: Call the `preorder` helper function recursively on the `root->right` child, passing the same `ans` vector. This explores the entire right subtree after the left subtree is fully processed.
6.  **Main Function**: In the `preorderTraversal` function (the entry point):
    a.  Initialize an empty `vector<int>` named `ans`.
    b.  Call the `preorder` helper function with the initial `root` of the tree and the `ans` vector.
    c.  Return the `ans` vector, which now contains all node values in preorder.

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
    // Helper function to perform the recursive preorder traversal
    // It takes the current node and a reference to the result vector.
    void preorder(TreeNode* root, vector<int>& ans) {
        // Base case: If the current node is NULL, we've reached the end of a path
        // or an empty subtree. There's nothing to process, so we simply return.
        if (root == NULL) {
            return;
        }

        // 1. Visit the current node: Add its value to our result list.
        // This is the "pre" part of preorder traversal (Root -> Left -> Right).
        ans.push_back(root->val);

        // 2. Traverse the left subtree: Recursively call the 'preorder' function
        // on the left child of the current node.
        preorder(root->left, ans);

        // 3. Traverse the right subtree: Recursively call the 'preorder' function
        // on the right child of the current node. This happens after the left
        // subtree has been fully traversed.
        preorder(root->right, ans);
    }

    // Main function to initiate the preorder traversal
    // This is the public interface called by LeetCode.
    vector<int> preorderTraversal(TreeNode* root) {
        // Initialize an empty vector to store the results of the traversal.
        // This vector will accumulate node values in preorder.
        vector<int> ans;

        // Call the recursive helper function starting from the root of the tree.
        // The 'ans' vector is passed by reference, allowing the helper function
        // to modify and populate it directly.
        preorder(root, ans);

        // After the recursive calls complete, 'ans' will contain all node values
        // in preorder. Return this vector.
        return ans;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | Each node in the binary tree is visited exactly once to add its value to the result vector. |
| **Space** | O(H) | The space complexity is determined by the maximum depth of the recursion stack. In the worst case (a skewed tree, e.g., a linked list), the height `H` can be `N` (number of nodes). In the best case (a balanced tree), `H` is `log N`. |

## 🔗 Related Problems
- 94. Binary Tree Inorder Traversal
- 145. Binary Tree Postorder Traversal
- 102. Binary Tree Level Order Traversal