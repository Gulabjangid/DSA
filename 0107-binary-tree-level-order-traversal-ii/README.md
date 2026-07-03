# 0107-binary-tree-level-order-traversal-ii

## 📋 Problem Description
Given the `root` of a binary tree, the task is to return the bottom-up level order traversal of its nodes' values. This means the traversal should proceed level by level, from left to right within each level, but the overall output should list the deepest level first, followed by the next deepest, and so on, until the root level is listed last.

The function receives a pointer to the `root` of the binary tree. It must return a `vector<vector<int>>`, where each inner `vector<int>` contains the values of nodes at a specific level, ordered from left to right. The outer `vector` should contain these level lists in bottom-up order (from leaves to root).

## 🔍 Examples
```
Input: root = [3,9,20,null,null,15,7]
Output: [[15,7],[9,20],[3]]
Explanation:
The tree structure is:
    3
   / \
  9  20
    /  \
   15   7
Level 3 (deepest): [15, 7]
Level 2: [9, 20]
Level 1 (root): [3]
Bottom-up order: [[15,7], [9,20], [3]]
```

```
Input: root = [1]
Output: [[1]]
Explanation:
The tree has only one node, which is also the root and the deepest level.
```

```
Input: root = []
Output: []
Explanation:
An empty tree has no nodes, so an empty list is returned.
```

## 📌 Constraints
*   The number of nodes in the tree is in the range `[0, 2000]`.
*   `-1000 <= Node.val <= 1000`

## 🤔 Understanding the Problem
This problem asks for a level-by-level traversal of a binary tree, which is a common pattern. The key difference from a standard level-order traversal (like LeetCode 102) is the "bottom-up" requirement. This means we need to collect the nodes from the deepest level first, then the next deepest, and so on, until the root level is last. Within each level, nodes should still be ordered from left to right. Edge cases include an empty tree or a tree with only a single node.

## 💡 Core Idea
The most straightforward approach is to first perform a standard top-down level-order traversal to collect all levels. Once all levels are gathered in the correct left-to-right order for each level, and in top-down order for the levels themselves, we simply reverse the order of these collected levels to achieve the desired bottom-up result.

## 🧠 Approach — Breadth-First Search (BFS)
This problem is a classic application of the Breadth-First Search (BFS) algorithm. BFS is perfectly suited for traversing a tree or graph level by level because it explores all nodes at the current depth before moving on to nodes at the next depth. A queue data structure is fundamental to implementing BFS, as it naturally maintains the order of nodes to be visited level by level. By processing nodes from the front of the queue and adding their children to the back, we ensure that all nodes at a given level are processed before any nodes from the subsequent level. This allows us to easily group nodes by their respective levels.

## 📝 Step-by-Step Algorithm
1.  **Initialize Data Structures**:
    *   Create an empty `queue<TreeNode*>` named `q` to manage nodes for the BFS traversal.
    *   Create an empty `vector<vector<int>>` named `ans` to store the collected levels of node values. This will initially store levels in top-down order.

2.  **Handle Empty Tree**:
    *   Check if the `root` is `nullptr`. If it is, the tree is empty, so return an empty `vector<vector<int>>` immediately.

3.  **Start BFS**:
    *   Push the `root` node into the queue `q`.

4.  **Level-by-Level Traversal**:
    *   Enter a `while` loop that continues as long as the queue `q` is not empty.
    *   Inside the loop, at the beginning of each iteration, get the current size of the queue. Let this be `n`. This `n` represents the exact number of nodes at the current level we are about to process.
    *   Create an empty `vector<int>` named `currentLevelNodes` to temporarily store the values of all nodes at this specific level.
    *   Start a `for` loop that iterates `n` times (from `i = 0` to `n-1`):
        *   Dequeue a node from the front of `q`. Let's call this `node`.
        *   Add `node->val` to `currentLevelNodes`.
        *   If `node` has a left child (`node->left` is not `nullptr`), push `node->left` into `q`.
        *   If `node` has a right child (`node->right` is not `nullptr`), push `node->right` into `q`.
    *   After the `for` loop finishes (meaning all nodes at the current level have been processed), add `currentLevelNodes` to `ans`. At this point, `ans` will contain levels in top-down order (root level first, deepest level last).

5.  **Reverse for Bottom-Up Order**:
    *   Once the `while` loop completes, `ans` contains all levels in top-down order. To achieve the required bottom-up order, use the `std::reverse` function to reverse the entire `ans` vector.

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
        // Initialize a queue for Breadth-First Search (BFS).
        // The queue will store TreeNode pointers to process nodes level by level.
        queue<TreeNode*> q;
        
        // Initialize a vector of vectors to store the final result.
        // Each inner vector will represent a level of the tree.
        vector<vector<int>> ans;
        
        // Handle the edge case: if the tree is empty (root is nullptr),
        // there are no nodes to traverse, so return an empty list of levels.
        if (root == nullptr) {
            return {};
        }
        
        // Start BFS by pushing the root node into the queue.
        q.push(root);
        
        // Continue BFS as long as there are nodes in the queue to process.
        while (!q.empty()) {
            // Get the number of nodes currently in the queue.
            // This 'n' represents all nodes at the current level.
            int n = q.size();
            
            // Create a temporary vector to store the values of nodes at the current level.
            vector<int> currentLevelNodes;
            
            // Iterate 'n' times to process all nodes at the current level.
            // This loop ensures we only process nodes from the current level
            // before moving to the next level's children.
            for (int i = 0; i < n; i++) {
                // Get the front node from the queue. This is the node to process.
                TreeNode* node = q.front();
                
                // Remove the processed node from the queue.
                q.pop();
                
                // Add the value of the current node to our current level's list.
                currentLevelNodes.push_back(node->val);
                
                // If the current node has a left child, add it to the queue
                // for processing in the next level.
                if (node->left) {
                    q.push(node->left);
                }
                
                // If the current node has a right child, add it to the queue
                // for processing in the next level.
                if (node->right) {
                    q.push(node->right);
                }
            }
            // After processing all nodes at the current level, add the
            // 'currentLevelNodes' vector to our main answer list.
            // At this point, 'ans' is being built in top-down order (root to leaves).
            ans.push_back(currentLevelNodes);
        }
        
        // The problem requires a bottom-up traversal.
        // Since 'ans' currently holds levels in top-down order (root first, leaves last),
        // we need to reverse the order of levels in 'ans'.
        reverse(ans.begin(), ans.end());
        
        // Return the final bottom-up level order traversal.
        return ans;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | Each node is visited and processed exactly once (pushed to queue, popped from queue, value added to list, children pushed). The final reversal takes O(L) time, where L is the number of levels, and L <= N. Thus, total time is O(N). |
| **Space** | O(N) | In the worst case (e.g., a complete binary tree), the queue can hold up to N/2 nodes (the last level), which is O(N). The `ans` vector stores all N node values, also taking O(N) space. |

## 🔗 Related Problems
- 102. Binary Tree Level Order Traversal
- 103. Binary Tree Zigzag Level Order Traversal
- 199. Binary Tree Right Side View