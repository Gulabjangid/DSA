# 0897-increasing-order-search-tree

## 📋 Problem Description
Given the `root` of a Binary Search Tree (BST), the task is to rearrange the tree into a new structure. This new tree must be in "in-order," meaning the nodes should appear in increasing value order. The specific structural requirement is that the leftmost node of the original tree becomes the new root, and every node in the new tree must have no left child and only one right child. Essentially, the tree is transformed into a "linked list" where each node's `right` pointer points to the next node in increasing order.

The function `increasingBST` receives a `TreeNode* root` representing the root of the original BST and should return a `TreeNode*` representing the root of the newly formed increasing order search tree.

## 🔍 Examples
**Example 1:**
```
Input:  root = [5,3,6,2,4,null,8,1,null,null,null,7,9]
Output: [1,null,2,null,3,null,4,null,5,null,6,null,7,null,8,null,9]
Explanation: The original BST is transformed into a right-skewed tree where nodes are linked in ascending order (1 -> 2 -> 3 -> ... -> 9) using only right pointers.
```

**Example 2:**
```
Input:  root = [5,1,7]
Output: [1,null,5,null,7]
Explanation: The BST is flattened. Node 1 becomes the root, its right child is 5, and 5's right child is 7.
```

## 📌 Constraints
*   The number of nodes in the given tree will be in the range `[1, 100]`.
*   `0 <= Node.val <= 1000`

## 🤔 Understanding the Problem
The problem asks us to flatten a given Binary Search Tree into a "right-skewed" tree. This means all nodes in the new tree will be connected via their `right` pointers, and no node will have a `left` child. The crucial part is that the order of nodes in this new structure must be the same as an in-order traversal of the original BST, meaning nodes are arranged from smallest to largest value. The challenge lies in modifying the tree structure in-place or by creating new links while preserving this specific in-order sequence.

## 💡 Core Idea
The fundamental property of a Binary Search Tree is that an in-order traversal visits nodes in ascending order of their values. Therefore, the core idea is to perform an in-order traversal and, during this traversal, re-link the nodes to form the desired right-skewed tree.

## 🧠 Approach — Depth-First Search (In-order Traversal)
The algorithm pattern used here is **Depth-First Search (DFS)**, specifically an **In-order Traversal**.
This pattern is perfectly suited because an in-order traversal of a Binary Search Tree naturally visits nodes in ascending order of their values (left subtree, current node, right subtree). This sequence directly corresponds to the required order of nodes in the output tree. By maintaining a pointer to the previously visited node (`prev`) and the head of the new tree (`head`), we can dynamically build the new structure by setting `prev->right = current_node` and `current_node->left = nullptr` as we traverse.

## 📝 Step-by-Step Algorithm
1.  Initialize two class member pointers:
    *   `head`: This will store the root of the new increasing BST. It's initialized to `nullptr` and will be set only once to the very first node encountered during the in-order traversal (which is the smallest node in the original BST).
    *   `prev`: This will keep track of the previously visited node during the in-order traversal. It's crucial for linking nodes: `prev->right = current_node`. Both are initially `nullptr`.
2.  Define a recursive helper function, `inorder(TreeNode* root)`, which performs an in-order traversal:
    a.  **Base Case**: If `root` is `nullptr`, return immediately as there's nothing to process.
    b.  **Traverse Left**: Recursively call `inorder(root->left)`. This ensures we process the smallest values first, adhering to the in-order sequence.
    c.  **Process Current Node**:
        i.  If `head` is `nullptr`, it means this is the very first node visited in the entire in-order traversal (the node with the smallest value). Set `head = root`. This node will be the new root of our increasing order search tree.
        ii. If `prev` is not `nullptr`, it means we have a previous node that needs to be linked to the current `root` node. Set `prev->right = root` to connect the previous node to the current node. Also, set `prev->left = nullptr` to ensure the previous node has no left child in the new tree.
        iii. Update `prev = root`. The current node now becomes the "previous" node for the next node that will be visited in the in-order sequence.
    d.  **Traverse Right**: Recursively call `inorder(root->right)`.
3.  In the main `increasingBST(TreeNode* root)` function:
    a.  Call the `inorder(root)` helper function. This call initiates the traversal, which will populate `head` and `prev` and re-link the nodes as it traverses.
    b.  After the traversal completes, the `prev` pointer will be pointing to the very last node processed (the node with the largest value in the original BST). This node should not have any children in the new tree. Explicitly set `prev->left = nullptr` and `prev->right = nullptr` to ensure it's properly terminated.
    c.  Return `head`, which now points to the root of the newly formed increasing order search tree.

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
    // 'head' will point to the root of the new increasing order search tree.
    // It's initialized to nullptr and set only once to the very first node encountered
    // during in-order traversal (which is the smallest node).
    TreeNode* head = nullptr;

    // 'prev' keeps track of the previously visited node during the in-order traversal.
    // This is crucial for linking nodes: prev->right = current_node.
    TreeNode* prev = nullptr;

    // Helper function to perform an in-order traversal.
    // During traversal, it modifies the tree structure to form the desired output.
    void inorder(TreeNode* root) {
        // Base case: If the current node is null, there's nothing to process.
        if (!root) {
            return;
        }

        // 1. Recursively traverse the left subtree.
        // This ensures we process nodes in ascending order, as per in-order traversal.
        inorder(root->left);

        // 2. Process the current node (root).
        // If 'head' is still nullptr, it means this is the first node we're visiting
        // in the entire in-order traversal (the node with the smallest value).
        // This node will be the new root of our increasing order search tree.
        if (!head) {
            head = root;
        }

        // If 'prev' is not nullptr, it means we have a previous node that needs to be
        // linked to the current 'root' node.
        if (prev) {
            // The previous node should not have a left child in the new tree.
            prev->left = nullptr;
            // Link the previous node's right child to the current node.
            // This forms the "linked list" structure.
            prev->right = root;
        }

        // Update 'prev' to the current 'root' node.
        // This 'root' will become the 'prev' for the next node in the in-order sequence.
        prev = root;

        // 3. Recursively traverse the right subtree.
        inorder(root->right);
    }

    // Main function to transform the BST.
    TreeNode* increasingBST(TreeNode* root) {
        // Start the in-order traversal. This call will populate 'head' and 'prev'
        // and re-link the nodes as it traverses.
        inorder(root);

        // After the traversal, 'prev' points to the very last node (largest value)
        // in the original BST. This node should not have any children in the new tree.
        // Ensure its left and right pointers are nullified.
        // The 'if (prev)' check handles the case where the input root might be null,
        // though constraints state 1 to 100 nodes.
        if (prev) {
            prev->left = nullptr;  // Ensure the last node has no left child.
            prev->right = nullptr; // Ensure the last node has no right child (terminates the list).
        }

        // Return the 'head' of the newly formed increasing order search tree.
        return head;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | Each node in the tree is visited exactly once during the in-order traversal, and constant time operations are performed at each node. |
| **Space** | O(H) | The space complexity is determined by the maximum depth of the recursion stack. In the worst-case scenario (a skewed tree), the height `H` can be equal to the number of nodes `N`. In the best-case scenario (a balanced tree), `H` is `log N`. |

## 🔗 Related Problems
- 94. Binary Tree Inorder Traversal
- 114. Flatten Binary Tree to Linked List
- 530. Minimum Absolute Difference in BST