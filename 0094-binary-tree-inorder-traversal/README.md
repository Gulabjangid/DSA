# 0094-binary-tree-inorder-traversal

## 📋 Problem Description
Given the `root` of a binary tree, the task is to return a list containing the values of its nodes in *inorder traversal* order.

Inorder traversal follows the pattern:
1.  Visit the left subtree.
2.  Visit the current node.
3.  Visit the right subtree.

The function should receive a pointer to the `root` of the binary tree and must return a `std::vector<int>` (or equivalent list in other languages) containing the node values in the specified order.

## 🔍 Examples
```
Input: root = [1,null,2,3]
Output: [1,3,2]
Explanation: The tree structure is:
    1
     \
      2
     /
    3
Inorder traversal:
1. Traverse left of 1 (empty).
2. Visit 1.
3. Traverse right of 1 (subtree rooted at 2).
   - Traverse left of 2 (node 3).
   - Visit 3.
   - Traverse right of 3 (empty).
   - Visit 2.
   - Traverse right of 2 (empty).
Result: [1,3,2]
```

```
Input: root = [1,2,3,4,5,null,8,null,null,6,7,9]
Output: [4,2,6,5,7,1,3,9,8]
Explanation: This example shows a larger, more complex tree. The inorder sequence correctly extracts the values following the Left-Root-Right rule for each subtree.
```

```
Input: root = []
Output: []
Explanation: An empty tree has no nodes, so an empty list is returned.
```

## 📌 Constraints
*   The number of nodes in the tree is in the range `[0, 100]`.
*   `-100 <= Node.val <= 100`

## 🤔 Understanding the Problem
The problem asks us to implement a specific type of Depth-First Search (DFS) traversal on a binary tree, known as "inorder traversal." This means that for any given node, we must first process all nodes in its left child's subtree, then process the node itself, and finally process all nodes in its right child's subtree. The challenge lies in correctly sequencing these operations, especially considering the recursive nature of tree structures. Edge cases include an empty tree (where the result should be an empty list) and a tree with only a single node.

## 💡 Core Idea
The definition of inorder traversal (Left -> Root -> Right) directly suggests a recursive solution. A function that processes a single node can naturally be defined to first call itself on the left child, then add the current node's value, and finally call itself on the right child.

## 🧠 Approach — Recursion (DFS)
This problem is a classic application of **Recursion**, specifically a type of Depth-First Search (DFS). Recursion is an ideal pattern for tree traversal problems because trees are inherently recursive data structures (a subtree is itself a tree). The "Left-Root-Right" pattern of inorder traversal maps perfectly to a recursive function: the function calls itself for the left child, then performs an action on the current node, and then calls itself for the right child. This naturally explores the tree's depth before moving to siblings.

## 📝 Step-by-Step Algorithm
1.  **Initialize Result List**: Create an empty `std::vector<int>` named `ans` (or similar) to store the values of the nodes in inorder sequence.
2.  **Define a Helper Function**: Create a recursive helper function, let's call it `inorder`, that takes two arguments: a pointer to the current `TreeNode` (`root`) and a reference to the `ans` vector.
3.  **Base Case for Recursion**: Inside the `inorder` helper function, check if the current `root` is `NULL`. If it is, this means we've traversed past a leaf node or are dealing with an empty tree/subtree. In this case, simply return, as there's nothing to add.
4.  **Traverse Left Subtree**: If `root` is not `NULL`, recursively call the `inorder` helper function on `root->left`. This ensures that all nodes in the left subtree are processed and added to `ans` before the current node.
5.  **Process Current Node**: After the recursive call for the left subtree returns (meaning all left subtree nodes are processed), add the value of the current `root` node (`root->val`) to the `ans` vector.
6.  **Traverse Right Subtree**: Finally, recursively call the `inorder` helper function on `root->right`. This ensures that all nodes in the right subtree are processed and added to `ans` after the current node.
7.  **Initiate Traversal**: In the main `inorderTraversal` function, call the `inorder` helper function with the initial `root` of the entire tree and the `ans` vector.
8.  **Return Result**: After the initial call to the helper function completes, the `ans` vector will contain all node values in inorder sequence. Return this `ans` vector.

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
    // Helper function to perform inorder traversal recursively.
    // It takes the current node and a reference to the result vector.
    void inorder(TreeNode* root, vector<int> &ans){
        // Base case for the recursion:
        // If the current node is NULL, it means we've reached the end of a path
        // (e.g., beyond a leaf node) or an empty subtree.
        // There's nothing to process, so we simply return.
        if(root == NULL){
            return;
        }

        // Step 1: Recursively traverse the left subtree.
        // This ensures that all nodes in the left subtree are visited
        // and their values are added to 'ans' before the current node.
        inorder(root->left, ans);

        // Step 2: Visit the current node.
        // After the left subtree is fully processed, add the value of the
        // current node to our result vector.
        ans.push_back(root->val);

        // Step 3: Recursively traverse the right subtree.
        // This ensures that all nodes in the right subtree are visited
        // and their values are added to 'ans' after the current node.
        inorder(root->right, ans);
    }

    // Main function to initiate the inorder traversal for the given tree.
    vector<int> inorderTraversal(TreeNode* root) {
        // Initialize an empty vector to store the inorder traversal result.
        vector<int> ans;
        
        // Call the recursive helper function, starting from the root of the tree.
        // The 'ans' vector is passed by reference so the helper function can populate it.
        inorder(root, ans);
        
        // After the helper function completes, 'ans' will contain all node values
        // in inorder sequence. Return this vector.
        return ans;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | Each node in the binary tree is visited exactly once during the traversal to be added to the result list. |
| **Space** | O(N) | In the worst case (a skewed tree, e.g., a linked list), the recursion stack depth can go up to N (number of nodes). Additionally, the `ans` vector stores N elements. |

## 🔗 Related Problems
- 144. Binary Tree Preorder Traversal
- 145. Binary Tree Postorder Traversal
- 102. Binary Tree Level Order Traversal