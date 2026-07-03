# 0404-sum-of-left-leaves

## 📋 Problem Description
Given the `root` of a binary tree, the task is to calculate and return the sum of the values of all "left leaves" in the tree.

A **leaf** node is defined as a node that has no children (neither a left child nor a right child).
A **left leaf** is a specific type of leaf node: it must be a leaf, and it must also be the left child of its parent node.

The function `sumOfLeftLeaves` takes a pointer to the `root` of the binary tree as input and should return an integer representing the total sum.

## 🔍 Examples
```
Input: root = [3,9,20,null,null,15,7]
Output: 24
Explanation: In this tree, the node with value 9 is a left leaf (it's a leaf and the left child of 3).
The node with value 15 is also a left leaf (it's a leaf and the left child of 20).
The node with value 7 is a leaf, but it's the right child of 20, so it's not a left leaf.
The sum of left leaves is 9 + 15 = 24.
```

```
Input: root = [1]
Output: 0
Explanation: The node with value 1 is a leaf, but it has no parent, so it cannot be a left child. Therefore, there are no left leaves.
```

```
Input: root = [1,2,3,4,5]
Output: 4
Explanation: Node 4 is a leaf and the left child of node 2. Node 5 is a leaf but the right child of node 2. Node 3 is not a leaf.
```

## 📌 Constraints
*   The number of nodes in the tree is in the range `[1, 1000]`.
*   `-1000 <= Node.val <= 1000`

## 🤔 Understanding the Problem
The problem asks us to identify a specific type of node in a binary tree: a "left leaf." This means a node must satisfy two conditions: it must be a leaf (no children), and it must be the left child of its parent. We then need to sum the values of all such nodes. The challenge lies in efficiently traversing the tree and correctly identifying these nodes while distinguishing them from right leaves or non-leaf left children. An empty tree or a tree with only a root node are important edge cases to consider.

## 💡 Core Idea
The core idea is to traverse the binary tree, and for each node, check if its *left child* is a leaf. If a node's left child exists and has no children of its own, then that left child is a "left leaf" and its value should be added to our total sum. This check needs to be performed at every node, and the process should be recursive for both left and right subtrees.

## 🧠 Approach — Depth-First Search (DFS) / Recursion
This problem is naturally suited for a **Depth-First Search (DFS)** approach, implemented recursively. DFS allows us to explore as far as possible along each branch before backtracking. Since a binary tree is a recursive data structure (each node is the root of its own subtree), a recursive solution elegantly mirrors this structure. We can define a function that calculates the sum of left leaves for a given subtree. This function will check if the current node's left child is a left leaf, add its value if it is, and then recursively call itself for the current node's left and right subtrees, summing up their results.

## 📝 Step-by-Step Algorithm
1.  **Define a recursive function**: Let's call it `sumOfLeftLeaves(TreeNode* root)`. This function will return the sum of all left leaves in the subtree rooted at `root`.
2.  **Base Case**: If the `root` is `nullptr` (meaning we've reached past a leaf node or the tree is empty), there are no left leaves in this subtree, so return `0`.
3.  **Initialize Sum**: Create a variable, say `currentSum`, and initialize it to `0`. This will store the sum of left leaves found in the current node's immediate children and its subtrees.
4.  **Check for Left Leaf**:
    *   First, check if the `root` has a left child (`root->left != nullptr`).
    *   If it does, then check if this left child is a leaf node itself. This means `root->left->left == nullptr` (no left grandchild) AND `root->left->right == nullptr` (no right grandchild).
    *   If both conditions are true, then `root->left` is a left leaf. Add its value (`root->left->val`) to `currentSum`.
5.  **Recurse on Left Subtree**: Call `sumOfLeftLeaves(root->left)` to find any left leaves in the left subtree of the current `root`. Add the result of this recursive call to `currentSum`.
6.  **Recurse on Right Subtree**: Call `sumOfLeftLeaves(root->right)` to find any left leaves in the right subtree of the current `root`. Add the result of this recursive call to `currentSum`.
7.  **Return Result**: Finally, return the total `currentSum`.

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
    int sumOfLeftLeaves(TreeNode* root) {
        // Base case: If the current node is null, it means we've traversed past a leaf
        // or the tree is empty. There are no left leaves here, so return 0.
        if (root == nullptr) {
            return 0;
        }

        int sum = 0; // Initialize sum for the current subtree

        // Check if the left child of the current 'root' is a left leaf.
        // A node is a left leaf if:
        // 1. It exists (root->left is not null).
        // 2. It has no left child (root->left->left is null).
        // 3. It has no right child (root->left->right is null).
        if (root->left &&             // Check if a left child exists
            !root->left->left &&      // Check if the left child has no left child (is a leaf)
            !root->left->right) {     // Check if the left child has no right child (is a leaf)
            
            // If all conditions are met, root->left is a left leaf.
            // Add its value to the total sum.
            sum += root->left->val;
        }
       
        // Recursively call the function for the left subtree.
        // Any left leaves found in the left subtree will be added to 'sum'.
        sum += sumOfLeftLeaves(root->left);

        // Recursively call the function for the right subtree.
        // Any left leaves found in the right subtree will be added to 'sum'.
        sum += sumOfLeftLeaves(root->right);

        // Return the total sum of left leaves found in this subtree.
        return sum;
    }
};

```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | Each node in the binary tree is visited exactly once to perform constant-time checks and make recursive calls. N is the total number of nodes in the tree. |
| **Space** | O(H) | The space complexity is determined by the maximum depth of the recursion stack. In the worst case (a skewed tree), the height H can be N. In the best case (a perfectly balanced tree), H is log N. |

## 🔗 Related Problems
- 104. Maximum Depth of Binary Tree
- 112. Path Sum
- 257. Binary Tree Paths
- 129. Sum Root to Leaf Numbers