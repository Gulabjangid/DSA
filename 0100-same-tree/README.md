# 0100-same-tree

## 📋 Problem Description
Given the roots of two binary trees, `p` and `q`, determine if they are structurally identical and have the same node values. Two binary trees are considered the same if they have the exact same structure (e.g., if one node has a left child, the corresponding node in the other tree must also have a left child) and all corresponding nodes contain identical values.

The function `isSameTree` should receive two pointers to `TreeNode` objects, `p` and `q`, representing the roots of the two binary trees. It must return `true` if the trees are identical, and `false` otherwise.

## 🔍 Examples

**Example 1:**
```
Input: p = [1,2,3], q = [1,2,3]
Output: true
Explanation: Both trees have root 1, left child 2, and right child 3. They are identical.
```
**Example 2:**
```
Input: p = [1,2], q = [1,null,2]
Output: false
Explanation: Tree p has root 1 with a left child 2. Tree q has root 1 with a right child 2. Their structures are different.
```
**Example 3:**
```
Input: p = [1,2,1], q = [1,1,2]
Output: false
Explanation: Tree p has root 1, left child 2, right child 1. Tree q has root 1, left child 1, right child 2. Although they have the same values, their positions are different, making the trees non-identical.
```

## 📌 Constraints
*   The number of nodes in both trees is in the range `[0, 100]`.
*   `-10^4 <= Node.val <= 10^4`

## 🤔 Understanding the Problem
The problem asks us to perform a deep comparison of two binary trees. It's not enough for them to contain the same set of values; their structure must also be an exact match. This means if a node exists in one tree, its corresponding node must exist in the other tree, and they must have the same value. Furthermore, if a node has a left child, its counterpart must also have a left child, and those children (and their subtrees) must also be identical, and the same applies to right children. Edge cases include when both trees are empty (which should return `true`), or when one tree is empty and the other is not (which should return `false`).

## 💡 Core Idea
The core idea is that two binary trees are identical if and only if:
1.  Their root nodes have the same value.
2.  Their left subtrees are identical.
3.  Their right subtrees are identical.
This recursive definition naturally leads to a recursive solution.

## 🧠 Approach — Recursion / Depth-First Search (DFS)
This problem is perfectly suited for a **Recursive** approach, which inherently performs a **Depth-First Search (DFS)** traversal. Trees are recursive data structures by nature: each node can be considered the root of its own subtree. By defining a function that checks the "sameness" of two subtrees, we can recursively apply this definition to the left and right children of the current nodes. This allows us to systematically compare corresponding nodes at each level of both trees, moving deeper into the tree structure until we hit empty nodes (null pointers).

## 📝 Step-by-Step Algorithm

1.  **Define the Recursive Function**: Create a function, `isSameTree(p, q)`, that takes two pointers to `TreeNode` objects, `p` and `q`, representing the current nodes being compared.

2.  **Base Case 1: Both are NULL**: If both `p` and `q` are `NULL` (meaning both trees or subtrees have ended at this point), it implies that this branch is identical. Return `true`.

3.  **Base Case 2: One is NULL, the other is not**: If one of `p` or `q` is `NULL` but the other is not (e.g., `p` is `NULL` but `q` is not, or vice-versa), it means their structures differ at this point. Return `false`.

4.  **Recursive Step: Neither is NULL**: If neither `p` nor `q` is `NULL` (meaning both nodes exist):
    a.  **Value Check**: First, compare the values of the current nodes: `p->val` and `q->val`. If they are not equal, the trees are not the same. Return `false`.
    b.  **Left Subtree Check**: Recursively call `isSameTree` for their left children: `isSameTree(p->left, q->left)`. This will return `true` if the left subtrees are identical, `false` otherwise.
    c.  **Right Subtree Check**: Recursively call `isSameTree` for their right children: `isSameTree(p->right, q->right)`. This will return `true` if the right subtrees are identical, `false` otherwise.
    d.  **Combine Results**: The trees are identical *only if* the current node values match AND their left subtrees are identical AND their right subtrees are identical. So, return the logical AND of these three conditions: `(p->val == q->val) && isSameTree(p->left, q->left) && isSameTree(p->right, q->right)`.

5.  **Initial Call**: The initial call to the function will be `isSameTree(root_p, root_q)`, where `root_p` and `root_q` are the roots of the two input trees.

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
    // Function to check if two binary trees are the same.
    // Two trees are the same if they are structurally identical and
    // the nodes have the same value.
    bool isSameTree(TreeNode* p, TreeNode* q) {
        // Base Case 1: If both nodes are NULL, it means we've reached the end
        // of a branch in both trees simultaneously. This part is identical.
        if (p == NULL && q == NULL) {
            return true;
        }

        // Base Case 2: If one node is NULL and the other is not,
        // their structures differ at this point. They cannot be the same.
        if (p == NULL || q == NULL) {
            return false;
        }

        // Recursive Step: If neither node is NULL, we need to check three conditions:
        // 1. The values of the current nodes must be equal.
        // 2. Their left subtrees must be identical.
        // 3. Their right subtrees must be identical.
        // All three conditions must be true for the trees to be considered the same.
        return (p->val == q->val) &&          // Check if current node values are equal
               isSameTree(p->left, q->left) && // Recursively check left subtrees
               isSameTree(p->right, q->right); // Recursively check right subtrees
    }
};

```

## ⏱️ Complexity Analysis

| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | In the worst case, we visit each node in the smaller of the two trees exactly once. N is the minimum number of nodes in `p` and `q`. |
| **Space** | O(H) | The space complexity is determined by the maximum depth of the recursion stack. H is the height of the tree. In the worst case (a skewed tree), H can be N, leading to O(N) space. In the best case (a balanced tree), H is log N, leading to O(log N) space. |

## 🔗 Related Problems
- 101. Symmetric Tree
- 104. Maximum Depth of Binary Tree
- 226. Invert Binary Tree