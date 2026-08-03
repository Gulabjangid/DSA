# 0701-insert-into-a-binary-search-tree

## 📋 Problem Description
You are given the `root` node of a binary search tree (BST) and an integer `value` to insert into the tree. Your task is to return the root node of the BST after the insertion. It is guaranteed that the new value does not already exist in the original BST.

Note that there may be multiple valid ways to insert the value while maintaining the BST properties. You can return any one of these valid resulting trees.

The function receives two arguments:
1.  `root`: A pointer to the root node of the binary search tree.
2.  `val`: An integer representing the value to be inserted.

It must return a `TreeNode*` representing the root of the modified BST.

## 🔍 Examples
```
Input: root = [4,2,7,1,3], val = 5
Output: [4,2,7,1,3,5]
Explanation: The value 5 is inserted as the left child of 7, maintaining BST properties.
Another accepted tree could have 5 as the right child of 4.

Input: root = [40,20,60,10,30,50,70], val = 25
Output: [40,20,60,10,30,50,70,null,null,25]
Explanation: The value 25 is inserted as the right child of 20, which is the left child of 30.
```

## 📌 Constraints
*   The number of nodes in the tree will be in the range `[0, 10^4]`.
*   `-10^8 <= Node.val <= 10^8`
*   All the values `Node.val` are **unique**.
*   `-10^8 <= val <= 10^8`
*   It's **guaranteed** that `val` does not exist in the original BST.

## 🤔 Understanding the Problem
The problem asks us to add a new node with a given value (`val`) into an existing Binary Search Tree (BST) while preserving the fundamental BST property: for any given node, all values in its left subtree are smaller than its own value, and all values in its right subtree are larger. Since we are guaranteed that `val` does not already exist, we don't need to worry about duplicate values. The core challenge is to find the correct position for the new node, which will always be a leaf node (or an empty spot where a leaf node would be).

## 💡 Core Idea
The key insight is that the BST property itself dictates the exact path to traverse to find the correct insertion point. If the value to insert (`val`) is less than the current node's value, we must go left; if it's greater, we must go right. This process continues until we reach a `nullptr`, which signifies the empty spot where the new node should be attached.

## 🧠 Approach — Recursion / Tree Traversal
This problem is perfectly suited for a **Recursive Tree Traversal** approach.
The reason this pattern fits so well is that the decision-making process at each node is identical: compare `val` with the current node's value and decide whether to proceed to the left or right child. This self-similar structure is the hallmark of problems best solved with recursion. The base case for our recursion will be when we encounter a `nullptr`, indicating that we've found the correct empty slot to place our new node.

## 📝 Step-by-Step Algorithm
1.  **Base Case**: Check if the current `root` node is `nullptr`.
    *   If it is, this means we have traversed down to an empty spot where the new value should be inserted. Create a new `TreeNode` with the given `val` and return this new node. This node will become the child of the parent node that initiated this recursive call.
2.  **Recursive Step**: If the current `root` is not `nullptr`:
    *   **Compare Values**: Compare `val` with `root->val`.
    *   **Go Left**: If `val` is less than `root->val`, it means the new value belongs in the left subtree. Recursively call `insertIntoBST` on `root->left` with `val`. The result of this recursive call (which will either be the newly created node or the root of the modified left subtree) should be assigned back to `root->left`.
    *   **Go Right**: If `val` is greater than `root->val`, it means the new value belongs in the right subtree. Recursively call `insertIntoBST` on `root->right` with `val`. The result of this recursive call should be assigned back to `root->right`.
3.  **Return Current Root**: After the appropriate recursive call has completed and potentially updated one of its children, return the current `root` node. This ensures that the connections up the call stack are maintained, eventually returning the original (or newly created, if the tree was initially empty) root of the entire BST.

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
        // Base case: If the current node is nullptr, we've found the correct spot
        // to insert the new value. Create a new TreeNode with 'val' and return it.
        // This new node will become the child of the parent node that called this function.
        if (root == nullptr) {
            return new TreeNode(val);
        }

        // Recursive step: Traverse the tree based on BST properties.
        // If 'val' is less than the current node's value, it belongs in the left subtree.
        if (root->val > val) {
            // Recursively call insertIntoBST on the left child.
            // The result of this call (either the newly inserted node or the root
            // of the modified left subtree) is assigned back to root->left.
            root->left = insertIntoBST(root->left, val);
        }
        // If 'val' is greater than the current node's value, it belongs in the right subtree.
        // (We are guaranteed 'val' does not exist, so no need to check for equality).
        else {
            // Recursively call insertIntoBST on the right child.
            // The result is assigned back to root->right.
            root->right = insertIntoBST(root->right, val);
        }

        // After the recursive call returns and the appropriate child pointer is updated,
        // return the current root. This propagates the (potentially modified) subtree
        // up the call stack, maintaining the tree structure.
        return root;
    }
};

```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(H) | In the worst case, we might traverse from the root to a leaf node, where H is the height of the BST. H can be O(log N) for a balanced tree or O(N) for a skewed tree (like a linked list), where N is the number of nodes. |
| **Space** | O(H) | This is due to the recursion stack. In the worst case (skewed tree), the depth of recursion can be N, leading to O(N) space. For a balanced tree, it's O(log N). |

## 🔗 Related Problems
- 700. Search in a Binary Search Tree
- 450. Delete Node in a BST
- 98. Validate Binary Search Tree