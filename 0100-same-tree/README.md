# 0100-same-tree

## 📋 Problem Description
Given the roots of two binary trees, `p` and `q`, determine if they are the same or not.

Two binary trees are considered the same if they are structurally identical (meaning they have the same shape and arrangement of nodes) and if the nodes at corresponding positions have the same value.

The function `isSameTree` should receive two pointers to `TreeNode` objects, `p` and `q`, representing the roots of the two binary trees. It must return a boolean value: `true` if the trees are identical, and `false` otherwise.

## 🔍 Examples
```
Input: p = [1,2,3], q = [1,2,3]
Output: true
Explanation: Both trees have the same structure and values at each corresponding node.
```

```
Input: p = [1,2], q = [1,null,2]
Output: false
Explanation: Tree p has a left child with value 2. Tree q has a right child with value 2. Their structures are different.
```

```
Input: p = [1,2,1], q = [1,1,2]
Output: false
Explanation: Although both trees have the same values, their arrangement is different. For p, the root's left child is 2 and right child is 1. For q, the root's left child is 1 and right child is 2.
```

## 📌 Constraints
*   The number of nodes in both trees is in the range `[0, 100]`.
*   `-10^4 <= Node.val <= 10^4`

## 🤔 Understanding the Problem
The problem asks us to compare two binary trees for exact equivalence. This means not only do the values of corresponding nodes need to match, but their structural positions must also be identical. A key aspect to consider are edge cases where one or both trees might be empty, or where one tree has a child node at a position where the other does not. This problem is non-trivial because we need to traverse both trees simultaneously and compare nodes at each step.

## 💡 Core Idea
The most natural way to compare two binary trees is recursively. To check if two trees are the same, we can compare their root nodes, then recursively compare their left subtrees, and finally recursively compare their right subtrees.

## 🧠 Approach — Recursion / Depth-First Search (DFS)
This problem is perfectly suited for a recursive approach, which is a form of Depth-First Search (DFS). Binary trees inherently have a recursive structure: a tree is composed of a root, a left subtree, and a right subtree. To determine if two trees are identical, we can define a base case for comparison (e.g., both are empty, or one is empty and the other is not) and then recursively apply the same logic to their children. This allows us to systematically explore all corresponding nodes in both trees.

## 📝 Step-by-Step Algorithm
1.  **Base Case 1: Both trees are empty.** If both `p` and `q` are `NULL` (representing empty trees or subtrees), they are considered identical. Return `true`.
2.  **Base Case 2: One tree is empty, the other is not.** If one of `p` or `q` is `NULL` but the other is not, then they cannot be identical (one has a node, the other doesn't at that position). Return `false`.
3.  **Recursive Step: Both trees are non-empty.** If both `p` and `q` are not `NULL`:
    *   First, compare the values of their current root nodes: `p->val` and `q->val`. If they are not equal, the trees are not identical.
    *   Second, recursively call the `isSameTree` function on their left children: `isSameTree(p->left, q->left)`.
    *   Third, recursively call the `isSameTree` function on their right children: `isSameTree(p->right, q->right)`.
    *   For the current nodes and their subtrees to be considered identical, all three conditions (current node values match, left subtrees are identical, and right subtrees are identical) must be true. Therefore, return the logical AND of these three results.

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
    bool isSameTree(TreeNode* p, TreeNode* q) {
        // Base Case 1: If both nodes are NULL, they are identical (both empty).
        if (p == NULL && q == NULL) {
            return true;
        }

        // Base Case 2: If one node is NULL and the other is not, they are not identical.
        // This covers cases like (p != NULL && q == NULL) or (p == NULL && q != NULL).
        if (p == NULL || q == NULL) {
            return false;
        }

        // Recursive Step: Both nodes are non-NULL.
        // 1. Check if their values are equal.
        // 2. Recursively check if their left subtrees are identical.
        // 3. Recursively check if their right subtrees are identical.
        // All three conditions must be true for the trees to be considered identical at this point.
        return (p->val == q->val) && 
               isSameTree(p->left, q->left) && 
               isSameTree(p->right, q->right);
    }
};

```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | We visit each node in both trees exactly once. N is the total number of nodes in the larger of the two trees. |
| **Space** | O(H) | The space complexity is determined by the maximum depth of the recursion stack. H is the height of the tree. In the worst case (a skewed tree), H can be N, leading to O(N) space. In the best case (a balanced tree), H is log N, leading to O(log N) space. |

## 🔗 Related Problems
- 101. Symmetric Tree
- 104. Maximum Depth of Binary Tree
- 226. Invert Binary Tree