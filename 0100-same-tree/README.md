# 0100-same-tree

## 📋 Problem Description
Given the roots of two binary trees, `p` and `q`, write a function to check if they are the same or not.

Two binary trees are considered the same if they are structurally identical and their corresponding nodes have the same value. The function should return `true` if the trees are identical, and `false` otherwise.

## 🔍 Examples
```
Example 1:
Input: p = [1,2,3], q = [1,2,3]
Output: true
Explanation: Both trees have the same structure and node values.
```

```
Example 2:
Input: p = [1,2], q = [1,null,2]
Output: false
Explanation: Tree p has a left child with value 2. Tree q has a right child with value 2. They are structurally different.
```

```
Example 3:
Input: p = [1,2,1], q = [1,1,2]
Output: false
Explanation: At the second level, tree p has a left child with value 2 and a right child with value 1. Tree q has a left child with value 1 and a right child with value 2. The values at corresponding positions do not match.
```

## 📌 Constraints
*   The number of nodes in both trees is in the range `[0, 100]`.
*   `-10^4 <= Node.val <= 10^4`

## 🤔 Understanding the Problem
The problem asks us to determine if two given binary trees are exact duplicates of each other. This means we need to compare not only the values stored in the nodes but also their structural arrangement. If a node in one tree has a left child, the corresponding node in the other tree must also have a left child, and their values must match. The same applies to right children. An important aspect to consider is how to handle empty trees or empty subtrees (represented by `NULL` or `nullptr`).

## 💡 Core Idea
Binary trees are naturally recursive data structures. The core idea is that two trees are the same if and only if their root nodes have the same value, their left subtrees are the same, and their right subtrees are the same. This recursive definition forms the basis of the solution.

## 🧠 Approach — Depth-First Search (DFS) / Recursion
This problem is a classic application of Depth-First Search (DFS) using recursion. DFS is perfectly suited for tree problems because it allows us to explore each branch of the tree completely before backtracking. Recursion elegantly mirrors the self-similar nature of trees: a tree is composed of a root, a left subtree, and a right subtree. By defining the "sameness" of two nodes based on the "sameness" of their children, we can solve the problem by breaking it down into smaller, identical subproblems.

## 📝 Step-by-Step Algorithm
1.  **Base Case 1: Both are `NULL`**: If both `p` and `q` pointers are `NULL` (meaning both trees or subtrees are empty at this position), they are considered identical. Return `true`.
2.  **Base Case 2: One is `NULL`, the other is not**: If one of `p` or `q` is `NULL` but the other is not, it means one tree has a node where the other doesn't, or one tree is empty while the other is not. In this case, they cannot be the same. Return `false`.
3.  **Recursive Step: Both are non-`NULL`**: If both `p` and `q` are pointing to valid `TreeNode` objects:
    a.  First, compare their current node values: `p->val` and `q->val`. If they are not equal, the trees are different. Return `false`.
    b.  If their values are equal, recursively call the `isSameTree` function for their left children: `isSameTree(p->left, q->left)`.
    c.  Also, recursively call the `isSameTree` function for their right children: `isSameTree(p->right, q->right)`.
    d.  The trees are considered the same at this point only if the current node values match AND both recursive calls for the left and right subtrees return `true`. Return the logical AND of these three conditions.

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
        // Base Case 1: If both nodes are null, they are considered the same.
        // This handles the scenario where we've traversed past the leaf nodes
        // or if both input trees are initially empty.
        if (p == NULL && q == NULL) {
            return true;
        }
        // Base Case 2: If only one of the nodes is null, they cannot be the same.
        // This covers situations like:
        // - One tree has a node, the other doesn't at the corresponding position.
        // - One tree is empty, but the other is not (e.g., initial call with p=[1], q=null).
        if (p == NULL || q == NULL) {
            return false;
        }

        // Recursive Step: If both nodes are non-null, we need to check three conditions:
        // 1. Their current node values must be equal (p->val == q->val).
        // 2. Their left subtrees must be the same (isSameTree(p->left, q->left)).
        // 3. Their right subtrees must be the same (isSameTree(p->right, q->right)).
        // All three conditions must evaluate to true for the current nodes and their subtrees
        // to be considered "same". The '&&' operator ensures short-circuiting: if any
        // condition is false, the subsequent checks are skipped, and 'false' is returned immediately.
        return (p->val == q->val) &&         // Check if current node values are equal
               isSameTree(p->left, q->left) && // Recursively check if left subtrees are identical
               isSameTree(p->right, q->right); // Recursively check if right subtrees are identical
    }
};

```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | Each node in the smaller of the two trees (and its corresponding node in the larger tree) is visited at most once. N is the number of nodes in the smaller tree. If trees are identical, N is the total number of nodes in one tree. |
| **Space** | O(H) | The space complexity is determined by the maximum depth of the recursion stack, which is equal to the height (H) of the tree. In the worst case (a skewed tree), H can be N. In the best case (a balanced tree), H is log N. |

## 🔗 Related Problems
- 101. Symmetric Tree
- 104. Maximum Depth of Binary Tree
- 226. Invert Binary Tree