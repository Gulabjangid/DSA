# 0102-binary-tree-level-order-traversal

## 📋 Problem Description
Given the `root` of a binary tree, the task is to return the level order traversal of its nodes' values. This means you should collect all node values level by level, starting from the root, and within each level, process nodes from left to right. The output should be a list of lists, where each inner list contains the values of nodes at a specific level.

**Input:** A pointer to the `root` node of a binary tree.
**Output:** A `vector<vector<int>>` representing the level order traversal. Each inner `vector<int>` corresponds to a level of the tree.

## 🔍 Examples
```
Input: root = [3,9,20,null,null,15,7]
Output: [[3],[9,20],[15,7]]
Explanation:
Level 0: [3]
Level 1: [9, 20]
Level 2: [15, 7]
```

```
Input: root = [1]
Output: [[1]]
Explanation:
Level 0: [1]
```

```
Input: root = []
Output: []
Explanation: An empty tree results in an empty traversal.
```

## 📌 Constraints
*   The number of nodes in the tree is in the range `[0, 2000]`.
*   `-1000 <= Node.val <= 1000`

## 🤔 Understanding the Problem
The problem asks us to traverse a binary tree in a specific order: level by level, from top to bottom, and from left to right within each level. This is distinct from depth-first traversals like pre-order, in-order, or post-order. The main challenge is to correctly identify and group nodes belonging to the same level while ensuring they are processed in the correct left-to-right sequence. An important edge case is an empty tree, which should result in an empty list.

## 💡 Core Idea
To traverse a tree level by level, a queue is the most suitable data structure. By adding nodes to a queue and processing them in a First-In, First-Out (FIFO) manner, we can naturally explore all nodes at the current depth before moving to the next.

## 🧠 Approach — Breadth-First Search (BFS)
This problem is a classic application of the **Breadth-First Search (BFS)** algorithm. BFS is ideal for problems that require exploring a graph or tree level by level, or finding the shortest path in an unweighted graph. In this specific problem, we need to visit all nodes at depth `d` before visiting any nodes at depth `d+1`. A queue naturally facilitates this by storing nodes to be visited, ensuring that nodes enqueued earlier (from shallower levels) are processed before nodes enqueued later (from deeper levels). By carefully tracking the size of the queue at the beginning of each level's processing, we can isolate and collect all nodes belonging to that specific level.

## 📝 Step-by-Step Algorithm
1.  Initialize an empty `vector<vector<int>>` called `ans` to store the final level order traversal.
2.  **Handle the edge case**: If the `root` of the tree is `NULL` (meaning an empty tree), return `ans` immediately.
3.  Initialize a `queue` of `TreeNode*` and push the `root` node into it. This queue will hold nodes to be visited.
4.  Start a `while` loop that continues as long as the queue is not empty. This loop processes the tree level by level.
    a.  Inside the loop, get the current size of the queue. Let's call this `n`. This `n` represents the exact number of nodes currently at the *current level* that we are about to process.
    b.  Initialize an empty `vector<int>` called `level` to store the values of nodes belonging to the current level.
    c.  Start a `for` loop that iterates `n` times (from `i = 0` to `i < n`). This loop processes all nodes at the current level.
        i.  Dequeue a node from the front of the queue. Let's call it `currentNode`.
        ii. Add `currentNode->val` to the `level` vector.
        iii. Check if `currentNode` has a left child (`currentNode->left != NULL`). If it does, enqueue `currentNode->left` into the queue.
        iv. Check if `currentNode` has a right child (`currentNode->right != NULL`). If it does, enqueue `currentNode->right` into the queue.
    d.  After the `for` loop finishes (meaning all nodes at the current level have been processed and their children enqueued), add the `level` vector to `ans`.
5.  Once the `while` loop finishes (the queue is empty, meaning all nodes have been visited), return the `ans` vector.

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
    vector<vector<int>> levelOrder(TreeNode* root) {

        // This vector of vectors will store the final result.
        // Each inner vector will represent a level of the tree.
        vector<vector<int>> ans;

        // Handle the edge case: if the tree is empty (root is NULL),
        // there's no traversal to perform, so return an empty result.
        if (root == NULL) {
            return ans;
        }

        // Initialize a queue for Breadth-First Search (BFS).
        // The queue will store TreeNode pointers to be visited.
        queue<TreeNode*> q;
        // Start BFS by pushing the root node into the queue.
        q.push(root);

        // Continue the BFS as long as there are nodes in the queue to visit.
        while (!q.empty()) {
            // Get the number of nodes currently in the queue.
            // This 'n' represents all nodes at the current level.
            int n = q.size();

            // Create a temporary vector to store the values of nodes
            // at the current level.
            vector<int> level;

            // Iterate 'n' times to process all nodes at the current level.
            for (int i = 0; i < n; i++) {
                // Get the node at the front of the queue. This is the
                // next node to be processed for the current level.
                TreeNode* node = q.front();
                // Remove the node from the front of the queue.
                q.pop();
                // Add the value of the current node to our 'level' vector.
                level.push_back(node->val);

                // If the current node has a left child, add it to the queue
                // to be processed in the next level.
                if (node->left) {
                    q.push(node->left);
                }
                // If the current node has a right child, add it to the queue
                // to be processed in the next level.
                if (node->right) {
                    q.push(node->right);
                }
            }
            // After processing all nodes for the current level,
            // add the 'level' vector to our 'ans' result.
            ans.push_back(level);
        }
        // Once the queue is empty, all nodes have been visited level by level.
        // Return the accumulated result.
        return ans;
    }
};

```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | Each node in the tree is enqueued and dequeued exactly once. Processing each node (adding its value, checking children) takes constant time. |
| **Space** | O(W) or O(N) | In the worst case, the queue might hold all nodes at the widest level. For a complete binary tree, this is O(N/2) = O(N). For a skewed tree (like a linked list), the queue might hold only one node at a time, O(1). In general, it's bounded by the maximum width of the tree, which can be O(N). |

## 🔗 Related Problems
- 107. Binary Tree Level Order Traversal II
- 103. Binary Tree Zigzag Level Order Traversal
- 199. Binary Tree Right Side View