# 0107-binary-tree-level-order-traversal-ii

## 📋 Problem Description
Given the `root` of a binary tree, the task is to return the bottom-up level order traversal of its nodes' values. This means we need to traverse the tree level by level, from left to right within each level, but the final output should list the levels starting from the leaf nodes (bottom-most level) up to the root node (top-most level).

The function receives a `TreeNode* root` as input and must return a `vector<vector<int>>`, where each inner vector represents a level of the tree, and these levels are ordered from bottom to top.

## 🔍 Examples
```
Input: root = [3,9,20,null,null,15,7]
Output: [[15,7],[9,20],[3]]
Explanation:
The tree looks like:
    3
   / \
  9  20
    /  \
   15   7
Level 0: [3]
Level 1: [9, 20]
Level 2: [15, 7]
Bottom-up order: [[15,7],[9,20],[3]]
```

```
Input: root = [1]
Output: [[1]]
Explanation: A single node tree.
Level 0: [1]
Bottom-up order: [[1]]
```

```
Input: root = []
Output: []
Explanation: An empty tree.
```

## 📌 Constraints
*   The number of nodes in the tree is in the range `[0, 2000]`.
*   `-1000 <= Node.val <= 1000`

## 🤔 Understanding the Problem
The problem asks for a level-by-level traversal of a binary tree, which is a common task. The twist here is the "bottom-up" requirement. Normally, a level order traversal would start from the root and go downwards. For this problem, we need to collect all nodes at each level, but then present these levels in reverse order, from the deepest level up to the root level. An important edge case to consider is an empty tree, which should result in an empty list of lists.

## 💡 Core Idea
The most straightforward way to perform a level-by-level traversal is using Breadth-First Search (BFS). We can perform a standard BFS to collect all nodes for each level, store these levels in a temporary list, and then simply reverse the order of the levels in that list to achieve the "bottom-up" requirement.

## 🧠 Approach — Breadth-First Search (BFS)
This problem is a classic application of the **Breadth-First Search (BFS)** algorithm.
BFS is ideal for this problem because it naturally explores a tree level by level. By using a queue, we can process all nodes at the current depth before moving on to any nodes at the next depth. This allows us to easily group nodes by their respective levels. After collecting all levels in the standard top-down order, a simple reversal of the list of levels will yield the desired bottom-up result.

## 📝 Step-by-Step Algorithm
1.  **Initialize Data Structures**:
    *   Create an empty `vector<vector<int>> ans` to store the final result (levels of node values).
    *   Create a `queue<TreeNode*> q` to manage nodes for BFS.

2.  **Handle Edge Case**:
    *   If the `root` is `nullptr` (an empty tree), return an empty `ans` vector immediately.

3.  **Start BFS**:
    *   Push the `root` node into the queue.

4.  **Level-by-Level Traversal**:
    *   While the queue is not empty:
        a.  Get the current size of the queue. This size `n` represents the number of nodes at the current level.
        b.  Create an empty `vector<int> current_level_nodes` to store the values of nodes belonging to this specific level.
        c.  Loop `n` times (for each node at the current level):
            i.  Dequeue a `TreeNode* node` from the front of the queue.
            ii. Add `node->val` to `current_level_nodes`.
            iii. If `node->left` exists, enqueue it.
            iv. If `node->right` exists, enqueue it.
        d.  After the loop finishes, `current_level_nodes` now contains all values for the current level. Add `current_level_nodes` to `ans`.

5.  **Reverse for Bottom-Up Order**:
    *   Once the BFS completes and all levels have been added to `ans` in top-down order, use a `reverse` function (e.g., `std::reverse` in C++) to reverse the order of the `ans` vector itself. This transforms the top-down order into bottom-up.

6.  **Return Result**:
    *   Return the `ans` vector.

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
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        // Initialize a queue for BFS traversal.
        queue<TreeNode*> q;
        // Initialize a vector of vectors to store the result.
        // Each inner vector will represent a level.
        vector<vector<int>> ans;

        // Handle the edge case: if the tree is empty (root is nullptr),
        // return an empty vector of vectors.
        if (root == nullptr) {
            return {};
        }
        
        // Push the root node into the queue to start the BFS.
        q.push(root);

        // Continue BFS as long as there are nodes in the queue to process.
        while (!q.empty()) {
            // Get the number of nodes currently in the queue.
            // This represents all nodes at the current level.
            int n = q.size();
            // Create a temporary vector to store node values for the current level.
            vector<int> current_level_nodes;

            // Process all nodes at the current level.
            for (int i = 0; i < n; i++) {
                // Get the node at the front of the queue.
                TreeNode* node = q.front();
                // Remove the node from the queue.
                q.pop();
                // Add the node's value to the current level's list.
                current_level_nodes.push_back(node->val);

                // If the node has a left child, add it to the queue for the next level.
                if (node->left) {
                    q.push(node->left);
                }
                // If the node has a right child, add it to the queue for the next level.
                if (node->right) {
                    q.push(node->right);
                }
            }
            // After processing all nodes for the current level,
            // add the 'current_level_nodes' vector to our 'ans' result.
            // At this point, 'ans' is in top-down order.
            ans.push_back(current_level_nodes);
        }

        // The problem requires bottom-up traversal, so we reverse the 'ans' vector.
        // This changes the order of levels from [level0, level1, ..., levelK]
        // to [levelK, ..., level1, level0].
        reverse(ans.begin(), ans.end());
        
        // Return the final bottom-up level order traversal.
        return ans;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | Each node is visited (enqueued and dequeued) exactly once. Adding node values to `current_level_nodes` and `ans` takes O(N) in total. The final `reverse` operation takes O(L) where L is the number of levels, which is at most O(N). Thus, the total time complexity is dominated by visiting all N nodes. |
| **Space** | O(N) | In the worst case (e.g., a complete binary tree), the queue can hold up to N/2 nodes at the widest level, contributing O(N) space. The `ans` vector stores all N node values, also contributing O(N) space. Therefore, the total space complexity is O(N). |

## 🔗 Related Problems
- 102. Binary Tree Level Order Traversal
- 103. Binary Tree Zigzag Level Order Traversal
- 199. Binary Tree Right Side View