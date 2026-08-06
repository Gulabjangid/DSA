# 0100-same-tree

## 📋 Problem Description
Given the roots of two binary trees, `p` and `q`, determine if they are the same.

Two binary trees are considered the same if they are structurally identical (meaning they have the same shape and arrangement of nodes) and if the nodes at corresponding positions have the same value.

The function should receive two pointers to `TreeNode` objects, `p` and `q`, representing the roots of the two binary trees. It must return a boolean value: `true` if the trees are the same, and `false` otherwise.

## 🔍 Examples
```
Input: p = [1,2,3], q = [1,2,3]
Output: true
Explanation: Both trees have the same structure and corresponding nodes have the same values.
```

```
Input: p = [1,2], q = [1,null,2]
Output: false
Explanation: Tree p has a left child with value 2. Tree q has a right child with value 2. Their structures are different.
```

```
Input: p = [1,2,1], q = [1,1,2]
Output: false
Explanation: Although both trees have the same values, their arrangement is different. In p, the root's left child is 2 and right child is 1. In q, the root's left child is 1 and right child is 2.
```

## 📌 Constraints
*   The number of nodes in both trees is in the range `[0, 100]`.
*   `-10^4 <= Node.val <= 10^4`

## 🤔 Understanding the Problem
The problem asks us to compare two binary trees for exact equivalence. This means we need to check two conditions simultaneously: their structure must be identical, and the values stored in corresponding nodes must be the same. A key aspect to consider is how to handle null nodes, as they define the structure of the tree. For instance, if one tree has a left child and the other doesn't, they are not the same. Similarly, if both are null, they are considered identical at that point.

## 💡 Core Idea
The problem inherently involves comparing corresponding parts of two recursive data structures (trees). This naturally leads to a recursive solution where we compare the current nodes and then recursively compare their left and right subtrees.

## 🧠 Approach — Recursion / Depth-First Search (DFS)
This problem is perfectly suited for a **Recursive** approach, which can be thought of as a form of **Depth-First Search (DFS)**. We can define a base case for when nodes are null or when a mismatch is found. For the general case, we recursively check if the current nodes are valid and have the same value, and then extend this check to their left and right children. This pattern fits because trees are defined recursively (a tree is a root node, a left subtree, and a right subtree), allowing us to break down the problem into smaller, identical subproblems.

## 📝 Step-by-Step Algorithm
1.  **Base Case 1: Both nodes are null.** If both `p` and `q` are `NULL` (or `nullptr` in C++), it means we've reached the end of a branch in both trees simultaneously. In this scenario, these parts of the trees are identical, so return `true`.
2.  **Base Case 2: One node is null, the other is not.** If one of `p` or `q` is `NULL` but the other is not, it means the structures are different at this point. Therefore, the trees cannot be the same, so return `false`.
3.  **Recursive Step: Both nodes are non-null.** If both `p` and `q` are non-null:
    a.  First, check if their current values (`p->val` and `q->val`) are equal. If they are not, the trees are different, so return `false`.
    b.  If their values are equal, then recursively call the `isSameTree` function for their left children (`p->left` and `q->left`).
    c.  Also, recursively call the `isSameTree` function for their right children (`p->right` and `q->right`).
    d.  The trees are considered the same at this point only if all three conditions are true: their current values are equal, their left subtrees are the same, AND their right subtrees are the same. So, return the logical AND of these three checks.

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
        // Base Case 1: If both nodes are null, it means we've reached the end of
        // a branch in both trees simultaneously. They are identical at this point.
        if (p == nullptr && q == nullptr) {
            return true;
        }

        // Base Case 2: If one node is null and the other is not,
        // their structures are different. Thus, the trees are not the same.
        if (p == nullptr || q == nullptr) {
            return false;
        }

        // Recursive Step: Both nodes are non-null.
        // 1. Check if their current values are equal.
        // 2. Recursively check if their left subtrees are the same.
        // 3. Recursively check if their right subtrees are the same.
        // All three conditions must be true for the trees to be considered the same.
        return (p->val == q->val) &&
               isSameTree(p->left, q->left) &&
               isSameTree(p->right, q->right);
    }
};

```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N + M) | In the worst case (e.g., both trees are identical), we visit every node in both trees. If N is the number of nodes in tree `p` and M is the number of nodes in tree `q`, the total operations are proportional to N + M. |
| **Space** | O(H) | The space complexity is determined by the maximum depth of the recursion stack. H is the height of the tree. In the worst case (a skewed tree), H can be N (the number of nodes in that tree). In the best case (a balanced tree), H is log N. |

## 🔗 Related Problems
- 101. Symmetric Tree
- 104. Maximum Depth of Binary Tree
- 226. Invert Binary Tree