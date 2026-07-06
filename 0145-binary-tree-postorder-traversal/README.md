# 0145-binary-tree-postorder-traversal

## 📋 Problem Description
Given the `root` of a binary tree, the task is to return the postorder traversal of its nodes' values. Postorder traversal means that for any given node, its left subtree is visited first, then its right subtree, and finally the node itself is visited.

**Input**: A pointer to the `root` node of a binary tree.
**Output**: A `std::vector<int>` containing the values of the tree nodes in postorder.

## 🔍 Examples
```
Input: root = [1,null,2,3]
Output: [3,2,1]
Explanation:
The tree structure is:
    1
     \
      2
     /
    3
Postorder: Visit left subtree (empty), then right subtree (which is 2 -> left 3), then root 1.
Right subtree (2,3): Visit left (3), then right (empty), then root (2). So, [3,2].
Combining: [3,2,1].
```

```
Input: root = [1,2,3,4,5,null,8,null,null,6,7,9]
Output: [4,6,7,5,2,9,8,3,1]
Explanation: A more complex tree, demonstrating the Left-Right-Root order.
```

```
Input: root = []
Output: []
Explanation: An empty tree has no nodes to traverse, so an empty list is returned.
```

## 📌 Constraints
*   The number of nodes in the tree is in the range `[0, 100]`.
*   `-100 <= Node.val <= 100`.

## 🤔 Understanding the Problem
The problem asks us to perform a specific type of Depth-First Search (DFS) on a binary tree called postorder traversal. The key characteristic of postorder is the order of operations: for any node, we must fully process its left child's subtree, then fully process its right child's subtree, and *only then* process the node itself. This means the root node will always be the last element in the traversal list for any non-empty tree. Edge cases include an empty tree (returning an empty list) or a tree with only one node (returning a list with that node's value).

## 💡 Core Idea
The most natural and straightforward way to implement postorder traversal is through recursion. The recursive definition directly mirrors the traversal order: `traverse(left_child)`, `traverse(right_child)`, `process(current_node)`.

## 🧠 Approach — Recursion / Depth-First Search (DFS)
This problem is a classic application of **Recursion**, specifically a type of **Depth-First Search (DFS)**. DFS is ideal for tree traversals because it systematically explores each branch of the tree as deeply as possible before backtracking. For postorder traversal, we need to ensure that all descendants of a node are visited before the node itself. Recursion elegantly handles this by allowing us to define the traversal for a node in terms of the traversal of its children, with the base case being an empty node. The call stack implicitly manages the order of operations and backtracking.

## 📝 Step-by-Step Algorithm
1.  **Initialize Result List**: Create an empty `std::vector<int>` (e.g., `ans`) to store the values of the nodes in postorder.
2.  **Define Recursive Helper Function**: Create a helper function, let's call it `postorderHelper(node, resultList)`, which takes a `TreeNode* node` and a reference to the `resultList`.
3.  **Base Case**: Inside `postorderHelper`, check if the current `node` is `NULL`. If it is, it means we've reached beyond a leaf node or an empty tree, so there's nothing to process. Simply return from the function.
4.  **Recursive Call for Left Subtree**: Recursively call `postorderHelper(node->left, resultList)`. This ensures that the entire left subtree is traversed in postorder, and all its node values are added to `resultList` *before* the current node or its right subtree are processed.
5.  **Recursive Call for Right Subtree**: Recursively call `postorderHelper(node->right, resultList)`. This ensures that the entire right subtree is traversed in postorder, and all its node values are added to `resultList` *before* the current node is processed.
6.  **Process Current Node**: After both the left and right subtrees have been fully traversed and their values added to `resultList`, add the `node->val` to `resultList`.
7.  **Initiate Traversal**: In the main `postorderTraversal` function, call `postorderHelper` with the initial `root` and the `ans` vector.
8.  **Return Result**: Finally, return the `ans` vector containing the postorder traversal.

## 💻 Solution
```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(right) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:

    // Helper function to perform postorder traversal recursively.
    // Note: The function is named 'inorder' but implements postorder traversal logic.
    void inorder(TreeNode* root, vector<int> &ans){

        // Base case: If the current node is NULL, there's nothing to traverse or add.
        // This signifies reaching the end of a branch or an empty tree/subtree.
        if(root == NULL){
            return;
        }
        
        // 1. Recursively traverse the left subtree.
        // This ensures that all nodes in the left subtree are processed
        // and added to 'ans' before moving to the right subtree or the current node.
        inorder(root->left, ans);
      
        // 2. Recursively traverse the right subtree.
        // This ensures that all nodes in the right subtree are processed
        // and added to 'ans' before the current node itself.
        inorder(root->right, ans);
        
        // 3. Process the current node.
        // After both left and right subtrees have been fully visited,
        // add the current node's value to our result vector.
        ans.push_back(root->val);

    }

    // Main function to initiate the postorder traversal.
    vector<int> postorderTraversal(TreeNode* root) {

        // Initialize an empty vector to store the postorder traversal result.
        vector<int> ans;
        
        // Call the recursive helper function, starting from the given 'root'.
        // The 'ans' vector is passed by reference so that the helper function
        // can populate it with node values.
        inorder(root, ans); // Calling the helper function.
        
        // Return the collected postorder traversal.
        return ans;
        
    }
  
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | Each of the N nodes in the tree is visited and processed exactly once. |
| **Space** | O(H) | The space complexity is determined by the maximum depth of the recursion stack, which in the worst case (a skewed tree) can be O(N) (where N is the number of nodes) and in the best/average case (a balanced tree) is O(log N). The `ans` vector also uses O(N) space to store the result, but this is typically considered output space. |

## 🔗 Related Problems
- 94. Binary Tree Inorder Traversal
- 144. Binary Tree Preorder Traversal
- 102. Binary Tree Level Order Traversal