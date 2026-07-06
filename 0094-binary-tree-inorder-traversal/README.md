# 0094-binary-tree-inorder-traversal

## 📋 Problem Description
Given the `root` of a binary tree, the task is to return a list containing the values of its nodes in *inorder traversal* order.

Inorder traversal visits nodes in the following sequence:
1.  Traverse the left subtree.
2.  Visit the current node.
3.  Traverse the right subtree.

The function receives a pointer to the `root` node of a binary tree. It must return a `std::vector<int>` containing the values of the tree nodes in the specified inorder sequence.

## 🔍 Examples

**Example 1:**
```
Input: root = [1,null,2,3]
Output: [1,3,2]
Explanation:
The tree structure is:
    1
     \
      2
     /
    3
Inorder traversal:
- Traverse left of 1 (null)
- Visit 1
- Traverse right of 1 (subtree rooted at 2)
  - Traverse left of 2 (subtree rooted at 3)
    - Traverse left of 3 (null)
    - Visit 3
    - Traverse right of 3 (null)
  - Visit 2
  - Traverse right of 2 (null)
Combining these steps yields [1,3,2].
```

**Example 2:**
```
Input: root = []
Output: []
Explanation: An empty tree has no nodes to traverse, so an empty list is returned.
```

**Example 3:**
```
Input: root = [1]
Output: [1]
Explanation: For a single-node tree, the inorder traversal simply visits that node.
```

## 📌 Constraints
*   The number of nodes in the tree is in the range `[0, 100]`.
*   `-100 <= Node.val <= 100`

## 🤔 Understanding the Problem
The problem asks us to implement a specific type of Depth-First Search (DFS) on a binary tree, known as "inorder traversal." This means we need to process all nodes in the left subtree, then the current node, and finally all nodes in the right subtree. This process is applied recursively to every subtree. Edge cases include an empty tree (where `root` is `NULL`) or a tree consisting of just a single node.

## 💡 Core Idea
The fundamental definition of inorder traversal (Left -> Root -> Right) is inherently recursive. To traverse a tree in inorder, we can recursively traverse its left subtree, then process the current node, and finally recursively traverse its right subtree.

## 🧠 Approach — Recursion (Depth-First Search)
This problem is a classic application of recursion, specifically a form of Depth-First Search (DFS). Recursion is a natural fit for tree problems because trees themselves are recursive data structures: a tree is either empty or consists of a root and two (potentially empty) subtrees. The inorder traversal definition directly translates into a recursive function where the base case is an empty node, and the recursive step involves calling the function on the left child, processing the current node, and then calling it on the right child.

## 📝 Step-by-Step Algorithm
1.  Initialize an empty list (e.g., `std::vector<int>`) named `ans` to store the inorder traversal result.
2.  Define a helper recursive function, let's call it `inorder`, which takes two arguments: a `TreeNode* root` (the current node being processed) and a reference to the result list `ans` (`vector<int> &ans`).
3.  **Base Case for `inorder` function**: If the current `root` is `NULL` (meaning we've reached past a leaf node or an empty subtree), there's nothing to add or traverse. In this case, simply return from the function.
4.  **Recursive Step for `inorder` function**:
    a.  **Traverse Left**: Recursively call `inorder` on the `root->left` child, passing the `ans` list. This ensures that all nodes in the left subtree are processed and added to `ans` before the current node.
    b.  **Visit Current Node**: After the entire left subtree has been traversed, add the value of the current `root` node (`root->val`) to the `ans` list.
    c.  **Traverse Right**: Recursively call `inorder` on the `root->right` child, passing the `ans` list. This ensures that all nodes in the right subtree are processed and added to `ans` after the current node.
5.  From the main `inorderTraversal` function, create the empty `ans` list.
6.  Initiate the traversal by calling the helper `inorder` function with the initial `root` of the tree and the `ans` list.
7.  Finally, return the populated `ans` list.

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
    // Helper function to perform inorder traversal recursively
    // It takes the current node 'root' and a reference to the result vector 'ans'.
    void inorder(TreeNode* root, vector<int> &ans){
        // Base case: If the current node is NULL, it means we've reached
        // past a leaf node or an empty subtree. There's nothing to process,
        // so we simply return. This stops the recursion for this branch.
        if(root == NULL){
            return;
        }
        
        // 1. Traverse the left subtree:
        // Recursively call the 'inorder' function for the left child (root->left).
        // This ensures that all nodes in the left subtree are visited and their
        // values are added to 'ans' before the current node's value.
        inorder(root->left, ans);
        
        // 2. Visit the current node:
        // After the entire left subtree has been processed, add the value of
        // the current node (root->val) to our result list 'ans'.
        ans.push_back(root->val);
        
        // 3. Traverse the right subtree:
        // Recursively call the 'inorder' function for the right child (root->right).
        // This ensures that all nodes in the right subtree are visited and their
        // values are added to 'ans' after the current node's value.
        inorder(root->right, ans);
    }
    
    // Main function to initiate the inorder traversal
    // It takes the root of the binary tree and returns a vector of integers.
    vector<int> inorderTraversal(TreeNode* root) {
        // Create an empty vector to store the results of the inorder traversal.
        // This vector will be populated by the recursive helper function.
        vector<int> ans;
        
        // Call the recursive helper function 'inorder' starting from the given 'root'.
        // The 'ans' vector is passed by reference so that the helper function can
        // modify and populate it directly.
        inorder(root, ans);
        
        // After the recursive traversal is complete, 'ans' will contain all node
        // values in inorder sequence. Return this populated vector.
        return ans;
    }
};
```

## ⏱️ Complexity Analysis

| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | Each node in the tree is visited exactly once during the traversal. N is the number of nodes. |
| **Space** | O(N) | The space complexity is primarily due to two factors: 1. The `ans` vector, which stores N node values, requiring O(N) space. 2. The recursion stack, which in the worst case (a skewed tree) can go as deep as the height of the tree (H). In the worst case, H can be N. Since we must store all N node values, the dominant factor is O(N). |

## 🔗 Related Problems
- 144. Binary Tree Preorder Traversal
- 145. Binary Tree Postorder Traversal
- 102. Binary Tree Level Order Traversal