# 0897-increasing-order-search-tree

## 📋 Problem Description
Given the `root` of a binary search tree (BST), the task is to rearrange the tree such that it becomes an "increasing order" tree. In this new tree, the leftmost node of the original BST will become the new root. Furthermore, every node in the rearranged tree must have no left child and only one right child. Essentially, the tree should be transformed into a singly linked list where nodes are ordered by their values in ascending order.

The function receives a `TreeNode* root` representing the root of the input BST and must return a `TreeNode*` representing the root of the newly constructed increasing order tree.

## 🔍 Examples
```
Input: root = [5,3,6,2,4,null,8,1,null,null,null,7,9]
Output: [1,null,2,null,3,null,4,null,5,null,6,null,7,null,8,null,9]
Explanation: The original BST is transformed into a "linked list" where 1 is the root, 2 is its right child, 3 is 2's right child, and so on, up to 9. Each node has no left child.
```

```
Input: root = [5,1,7]
Output: [1,null,5,null,7]
Explanation: The smallest node (1) becomes the root. Its right child is 5, and 5's right child is 7.
```

## 📌 Constraints
*   The number of nodes in the given tree will be in the range `[1, 100]`.
*   `0 <= Node.val <= 1000`

## 🤔 Understanding the Problem
The problem asks us to take a standard Binary Search Tree and flatten it into a specific structure: a "right-skewed" tree. This means all nodes should be arranged in increasing order of their values, connected only by right pointers, with no left children. The key here is that a Binary Search Tree naturally stores its elements in a way that allows for easy retrieval in increasing order. The challenge is to perform this transformation in-place or by constructing new links efficiently.

## 💡 Core Idea
The fundamental property of a Binary Search Tree is that an in-order traversal visits nodes in ascending order of their values. We can leverage this property to build our new tree by modifying the `left` and `right` pointers during an in-order traversal.

## 🧠 Approach — Depth-First Search (DFS) / In-order Traversal
This problem is perfectly suited for a **Depth-First Search (DFS)** approach, specifically an **in-order traversal**.

An in-order traversal of a BST visits nodes in the sequence: left subtree, current node, right subtree. This sequence naturally yields the nodes in ascending order of their values. Since the problem requires us to arrange nodes in increasing order, an in-order traversal is the most intuitive and efficient way to process the nodes in the desired sequence. As we visit each node, we can maintain a pointer to the previously visited node and link the current node as its right child, effectively building the new right-skewed tree structure.

## 📝 Step-by-Step Algorithm
1.  **Initialize Global Pointers**:
    *   `head`: A `TreeNode*` pointer that will eventually point to the root of our new increasing order tree (the smallest node). Initialize it to `nullptr`.
    *   `prev`: A `TreeNode*` pointer that will keep track of the previously visited node during the in-order traversal. This is crucial for linking nodes. Initialize it to `nullptr`.

2.  **Define `inorder` Helper Function**: Create a recursive helper function, `inorder(TreeNode* root)`, which performs the in-order traversal and modifies the tree structure.
    *   **Base Case**: If `root` is `nullptr` (we've gone past a leaf), simply return.
    *   **Traverse Left**: Recursively call `inorder(root->left)`. This ensures we process the left subtree first to find the smallest elements.
    *   **Process Current Node**: After visiting the left subtree, we are at the current `root` node (which is the next smallest node in sequence).
        *   **Set New Head**: If `head` is `nullptr`, it means this is the very first node we are processing in the in-order traversal (which will be the smallest node in the entire tree). Set `head = root`.
        *   **Link Nodes**: If `prev` is not `nullptr`, it means we have a node that was visited immediately before the current `root`. We need to link `prev` to `root`.
            *   Set `prev->right = root`. This makes the current `root` the right child of the `prev` node.
            *   Set `prev->left = nullptr`. This ensures the `prev` node has no left child, fulfilling the problem's requirement.
        *   **Update `prev`**: Set `prev = root`. The current `root` now becomes the "previous" node for the next node that will be processed.
    *   **Traverse Right**: Recursively call `inorder(root->right)`. This processes the right subtree.

3.  **Main Function `increasingBST(TreeNode* root)`**:
    *   Call the `inorder` helper function with the original `root`: `inorder(root)`. This will populate `head` and modify the tree's pointers.
    *   **Clean up Last Node**: After the `inorder` traversal completes, the `prev` pointer will be pointing to the largest node in the original BST. This node might still have its original `left` and `right` children. To ensure it also conforms to the "no left child and only one right child" rule (or no children if it's the last node), explicitly set `prev->left = nullptr` and `prev->right = nullptr`.
    *   **Return Result**: Return the `head` pointer, which now points to the root of the newly formed increasing order tree.

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
    // 'head' will point to the root of the new increasing order tree (the smallest node).
    TreeNode* head = nullptr;
    // 'prev' will keep track of the node visited immediately before the current node
    // during the in-order traversal. This is used to link nodes.
    TreeNode* prev = nullptr;

    // Helper function to perform an in-order traversal and modify tree pointers.
    void inorder(TreeNode* root) {
        // Base case: if the current node is null, we've gone past a leaf, so return.
        if (!root) return;

        // 1. Recursively traverse the left subtree.
        // This ensures we process nodes in ascending order.
        inorder(root->left);

        // 2. Process the current node (root).
        // If 'head' is null, it means this is the very first node we've visited
        // in the in-order traversal. This node will be the new root of our
        // increasing order tree.
        if (!head) {
            head = root;
        }

        // If 'prev' is not null, it means we have a node that was visited
        // immediately before the current 'root'. We need to link 'prev' to 'root'.
        if (prev) {
            // Set the right child of the previous node to the current node.
            // This forms the increasing order link.
            prev->right = root;
            // Ensure the previous node has no left child.
            prev->left = nullptr;
        }

        // Update 'prev' to the current 'root' for the next iteration.
        prev = root;

        // 3. Recursively traverse the right subtree.
        inorder(root->right);
    }

    // Main function to transform the BST.
    TreeNode* increasingBST(TreeNode* root) {
        // Start the in-order traversal from the original root.
        // This call will populate 'head' and modify the tree structure.
        inorder(root);

        // After the traversal, 'prev' points to the largest node in the original BST.
        // This node might still have its original left/right children.
        // We need to ensure it also has no left child and no right child (as it's the last node).
        if (prev) { // Check if prev is not null (tree might be empty, though constraints say 1-100 nodes)
            prev->left = nullptr;
            prev->right = nullptr;
        }
        
        // Return the 'head' of the newly formed increasing order tree.
        return head;
    }
};
```

## ⏱️ Complexity Analysis

| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | Every node in the tree is visited exactly once during the in-order traversal. N is the number of nodes. |
| **Space** | O(H) | The space complexity is determined by the maximum depth of the recursion stack during the DFS traversal. H is the height of the tree. In the worst case (a skewed tree, like a linked list), H can be N. In the best case (a balanced tree), H is log N. |

## 🔗 Related Problems
*   94. Binary Tree Inorder Traversal
*   230. Kth Smallest Element in a BST
*   108. Convert Sorted Array to Binary Search Tree