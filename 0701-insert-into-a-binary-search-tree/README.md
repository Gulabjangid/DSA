# 0701-insert-into-a-binary-search-tree

## 📋 Problem Description
You are given the `root` node of a binary search tree (BST) and an integer `value` to insert into the tree. Your task is to insert this `value` while maintaining the properties of a BST. After the insertion, you must return the `root` node of the modified BST.

It is guaranteed that the `value` to be inserted does not already exist in the original BST. Additionally, there might be multiple valid ways to insert the value while preserving the BST properties; you can return any one of them.

**Input:**
*   `root`: A pointer to the root node of the binary search tree. Can be `nullptr` if the tree is empty.
*   `val`: An integer value to be inserted.

**Output:**
*   A pointer to the root node of the BST after the insertion.

## 🔍 Examples

```
Input: root = [4,2,7,1,3], val = 5
Output: [4,2,7,1,3,5]
Explanation: The value 5 is inserted as the left child of 7.
Another accepted tree is shown in the problem, where 5 could be the right child of 4.
```

```
Input: root = [40,20,60,10,30,50,70], val = 25
Output: [40,20,60,10,30,50,70,null,null,25]
Explanation: The value 25 is inserted as the right child of 20.
```

```
Input: root = [], val = 10
Output: [10]
Explanation: An empty tree becomes a tree with a single node, 10.
```

## 📌 Constraints
*   The number of nodes in the tree will be in the range `[0, 10^4]`.
*   `-10^8 <= Node.val <= 10^8`
*   All the values `Node.val` are **unique**.
*   `-10^8 <= val <= 10^8`
*   It's **guaranteed** that `val` does not exist in the original BST.

## 🤔 Understanding the Problem
The problem asks us to add a new node with a given `val` into an existing Binary Search Tree (BST) without violating the BST properties. A BST has a specific ordering: for any given node, all values in its left subtree are smaller than the node's value, and all values in its right subtree are larger. Since the new `val` is guaranteed not to exist, we just need to find the correct leaf position where it can be inserted. The key is to traverse the tree following the BST rules until we find an empty spot (a `nullptr`) where the new node can be attached.

## 💡 Core Idea
The fundamental idea is to simulate the search process for the `val` in the BST. Since `val` is guaranteed not to exist, this search will eventually lead us to a `nullptr` (an empty spot) where the new node can be created and attached as a child of the last visited non-null node.

## 🧠 Approach — Recursion / Depth-First Search (DFS)
This problem is perfectly suited for a **recursive** approach, which inherently performs a Depth-First Search (DFS) traversal. Binary Search Trees are recursive data structures by nature: each subtree is also a BST. This makes recursion a very natural and elegant way to navigate and modify them.

We can define a recursive function that takes the current node and the value to insert.
1.  If the current node is `nullptr`, it means we've found the correct position to insert the new value, so we create a new `TreeNode` and return it.
2.  If the `val` is less than the current node's value, we know it must belong in the left subtree. We recursively call the function on the left child and update the current node's `left` pointer with the result of this recursive call.
3.  If the `val` is greater than the current node's value, it must belong in the right subtree. We recursively call the function on the right child and update the current node's `right` pointer with the result.
This recursive structure ensures that the new node is correctly placed and the tree structure is updated as the calls unwind.

## 📝 Step-by-Step Algorithm

1.  **Base Case**: If the current `root` node is `nullptr` (meaning we've traversed down to an empty spot where a child should be), create a new `TreeNode` with the given `val` and return this new node. This new node will be attached as a child to the parent node that initiated this recursive call.

2.  **Compare and Recurse Left**: If the `val` to be inserted is less than the current `root->val`:
    *   Recursively call the `insertIntoBST` function on the `root->left` subtree with the same `val`.
    *   Assign the result of this recursive call back to `root->left`. This step is crucial because if `root->left` was `nullptr`, the base case would create a new node, and this assignment links it to the current `root`.

3.  **Compare and Recurse Right**: If the `val` to be inserted is greater than the current `root->val`:
    *   Recursively call the `insertIntoBST` function on the `root->right` subtree with the same `val`.
    *   Assign the result of this recursive call back to `root->right`. Similar to the left side, this links the newly created node (if `root->right` was `nullptr`) to the current `root`.

4.  **Return Current Root**: After potentially modifying one of its children, return the current `root` node. This ensures that the parent of the current `root` (in the call stack) receives the updated subtree.

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
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        
        // Base case: If the current node is nullptr, it means we've found the
        // correct empty spot to insert the new value.
        // Create a new TreeNode with the given 'val' and return it.
        // This new node will be linked as a child to the parent node that called this function.
        if(root == nullptr){
            return new TreeNode(val);
        }
        
        // If 'val' is less than the current node's value, it must be inserted
        // into the left subtree to maintain BST properties.
        if(root->val > val){
            // Recursively call insertIntoBST on the left child.
            // The result of this call (which could be the original left child,
            // or a new node if 'root->left' was nullptr) is assigned back to 'root->left'.
            root->left = insertIntoBST(root->left, val);
        }
        // If 'val' is greater than the current node's value, it must be inserted
        // into the right subtree. (We are guaranteed 'val' does not exist,
        // so no need to handle equality).
        else{ // root->val < val
            // Recursively call insertIntoBST on the right child.
            // Similar to the left side, the result is assigned back to 'root->right'.
            root->right = insertIntoBST(root->right, val);
        }
        
        // After the insertion (if any) in its subtrees, return the current root.
        // This propagates the (potentially modified) subtree back up to its parent.
        return root;
    }
};

```

## ⏱️ Complexity Analysis

| | Complexity | Reason |
|---|---|---|
| **Time** | O(H) | In the worst case, we traverse from the root to a leaf. H is the height of the tree. For a balanced BST, H = log N. For a skewed BST (like a linked list), H = N, where N is the number of nodes. |
| **Space** | O(H) | This is due to the recursion stack. In the worst case (skewed tree), the depth of recursion can be N. In the best/average case (balanced tree), it's log N. |

## 🔗 Related Problems
- 700. Search in a Binary Search Tree
- 98. Validate Binary Search Tree
- 450. Delete Node in a BST