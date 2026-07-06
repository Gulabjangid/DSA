# 0145-binary-tree-postorder-traversal

## 📋 Problem Description
Given the `root` of a binary tree, the task is to return a list containing the values of its nodes in postorder traversal.

In a postorder traversal, for any given node, we first visit all nodes in its left subtree, then all nodes in its right subtree, and finally the node itself.

The function `postorderTraversal` receives a `TreeNode* root` as input and must return a `vector<int>` representing the postorder traversal of the tree.

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
Postorder: Visit left subtree of 1 (empty), then right subtree of 1 (which is 2 and its children), then 1 itself.
For node 2: Visit left subtree of 2 (which is 3), then right subtree of 2 (empty), then 2 itself.
So, 3, then 2, then 1.
```

```
Input: root = [1,2,3,4,5,null,8,null,null,6,7,9]
Output: [4,6,7,5,2,9,8,3,1]
Explanation: A more complex tree demonstrating the postorder sequence.
```

```
Input: root = []
Output: []
Explanation: An empty tree results in an empty traversal list.
```

```
Input: root = [1]
Output: [1]
Explanation: A single-node tree results in just that node's value.
```

## 📌 Constraints
*   The number of nodes in the tree is in the range `[0, 100]`.
*   `-100 <= Node.val <= 100`

## 🤔 Understanding the Problem
This problem asks us to perform a specific type of tree traversal called "postorder traversal." The key characteristic of postorder is the order in which nodes are visited: left child, then right child, then the current node. This means a node's value is added to the result list *after* all its descendants have been processed. We need to handle edge cases like an empty tree (returning an empty list) or a tree with just a single root node. The problem also includes a follow-up about an iterative solution, but the provided solution is recursive.

## 💡 Core Idea
The most natural and intuitive way to implement tree traversals like postorder is through recursion. The definition of postorder traversal (left, right, then current node) directly translates into a recursive function where we first make recursive calls for the left and right children, and then process the current node.

## 🧠 Approach — Recursion (DFS)
This problem is a classic application of Depth-First Search (DFS), specifically implemented using recursion. DFS explores as far as possible along each branch before backtracking. Recursion is an excellent fit for tree problems because the tree's hierarchical structure maps perfectly to recursive function calls. For postorder traversal, the recursive calls to process the left and right subtrees are made first, and only after those calls return (meaning the subtrees are fully traversed) is the current node's value added to the result. This ensures the "left, right, current" order.

## 📝 Step-by-Step Algorithm
1.  **Initialize Result List**: Create an empty `vector<int>` named `ans` to store the values of the nodes in postorder.
2.  **Define a Recursive Helper Function**: Create a helper function, let's call it `postorderHelper`, that takes two arguments: a `TreeNode* node` (the current node being processed) and a reference to the `ans` vector.
3.  **Base Case for Helper Function**: Inside `postorderHelper`, check if the current `node` is `NULL`. If it is, this means we've reached past a leaf node or an empty tree, so simply return without doing anything.
4.  **Recursive Traversal (Left)**: Recursively call `postorderHelper` on `node->left`. This ensures that the entire left subtree is traversed in postorder before moving to the right subtree or the current node.
5.  **Recursive Traversal (Right)**: Recursively call `postorderHelper` on `node->right`. This ensures that the entire right subtree is traversed in postorder after the left subtree but before the current node.
6.  **Process Current Node**: After both the left and right subtrees have been fully traversed and their nodes added to `ans`, add the `node->val` (value of the current node) to the `ans` vector.
7.  **Initiate Traversal**: In the main `postorderTraversal` function, call `postorderHelper` with the `root` of the tree and the `ans` vector.
8.  **Return Result**: After the initial call to `postorderHelper` completes, the `ans` vector will contain all node values in postorder. Return this `ans` vector.

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

    // Helper function to perform postorder traversal recursively.
    // Note: The original code named this 'inorder', but its implementation
    // correctly performs postorder traversal (left, right, then root).
    void postorderHelper(TreeNode* root, vector<int> &ans){
        // Base case: If the current node is NULL, there's nothing to traverse.
        // This handles empty subtrees or the initial call with an empty tree.
        if(root == NULL){
            return;
        }
        
        // 1. Recursively traverse the left subtree.
        // This call ensures that all nodes in the left subtree are processed
        // (left-right-root order) before we move to the right subtree.
        postorderHelper(root->left, ans); 
      
        // 2. Recursively traverse the right subtree.
        // This call ensures that all nodes in the right subtree are processed
        // (left-right-root order) after the left subtree and before the current node.
        postorderHelper(root->right, ans);
        
        // 3. Visit the current node.
        // After both the left and right subtrees have been fully traversed
        // and their values added to 'ans', add the current node's value.
        // This is the defining characteristic of postorder traversal.
        ans.push_back(root->val);
    }

    // Main function to initiate the postorder traversal.
    vector<int> postorderTraversal(TreeNode* root) {
        // Initialize an empty vector to store the results of the traversal.
        vector<int> ans;
        
        // Call the recursive helper function starting from the root of the tree.
        // The 'ans' vector is passed by reference so that the helper function
        // can accumulate the node values directly into it.
        postorderHelper(root, ans); 
        
        // Return the final list of node values, which are now in postorder.
        return ans;
    }
};

```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | Each node in the tree is visited exactly once to add its value to the result list. |
| **Space** | O(H) | This is due to the recursion stack. In the worst case (a skewed tree), the height `H` can be `N` (number of nodes). In the best case (a balanced tree), `H` is `log N`. |

## 🔗 Related Problems
- 94. Binary Tree Inorder Traversal
- 144. Binary Tree Preorder Traversal
- 102. Binary Tree Level Order Traversal