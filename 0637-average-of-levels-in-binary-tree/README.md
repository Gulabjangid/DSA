# 0637-average-of-levels-in-binary-tree

## 📋 Problem Description
Given the `root` of a binary tree, the task is to compute the average value of the nodes on each level and return these averages in an array. The order of averages in the output array should correspond to the levels from top to bottom (level 0, level 1, and so on). Answers that are within `10^-5` of the actual average will be accepted.

**Input:** A `TreeNode* root` representing the root of a binary tree.
**Output:** A `vector<double>` where each element is the average of node values for a corresponding level.

## 🔍 Examples
```
Input: root = [3,9,20,null,null,15,7]
Output: [3.00000,14.50000,11.00000]
Explanation:
Level 0: Node value is 3. Average = 3 / 1 = 3.0
Level 1: Nodes are 9, 20. Average = (9 + 20) / 2 = 14.5
Level 2: Nodes are 15, 7. Average = (15 + 7) / 2 = 11.0
```

```
Input: root = [3,9,20,15,7]
Output: [3.00000,14.50000,11.00000]
Explanation: (Same as above, just a different tree representation)
Level 0: Node value is 3. Average = 3 / 1 = 3.0
Level 1: Nodes are 9, 20. Average = (9 + 20) / 2 = 14.5
Level 2: Nodes are 15, 7. Average = (15 + 7) / 2 = 11.0
```

## 📌 Constraints
*   The number of nodes in the tree is in the range `[1, 10^4]`.
*   `-2^31 <= Node.val <= 2^31 - 1`.

## 🤔 Understanding the Problem
The problem asks us to calculate the average of node values for each horizontal "slice" or "level" of a binary tree. This means we need to process all nodes at depth 0, then all nodes at depth 1, then all nodes at depth 2, and so on, calculating their sum and count to find the average for each level. Since node values can be large integers, their sum might exceed the capacity of a standard `int`, and the averages themselves will likely be floating-point numbers, requiring `double` for calculations and storage.

## 💡 Core Idea
To process a binary tree level by level, the most suitable traversal algorithm is Breadth-First Search (BFS). BFS naturally explores nodes layer by layer, making it straightforward to group nodes belonging to the same level.

## 🧠 Approach — Breadth-First Search (BFS)
This problem is a classic application of Breadth-First Search (BFS). BFS is chosen because it systematically explores all nodes at the current depth level before moving on to nodes at the next depth level. This "level-by-level" processing is exactly what's required to calculate averages for each level independently. By using a queue, we can easily keep track of all nodes that belong to the current level and then add their children to the queue for the subsequent level.

## 📝 Step-by-Step Algorithm
1.  **Initialization**:
    *   Create an empty `vector<double>` called `ans` to store the calculated averages for each level.
    *   Create an empty `queue<TreeNode*>` called `q` to manage nodes for BFS.
2.  **Handle Empty Tree**:
    *   If the `root` is `nullptr` (meaning an empty tree), return the empty `ans` vector immediately. (Note: Constraints state `N >= 1`, so `root` will not be `nullptr` initially, but this is good practice).
3.  **Start BFS**:
    *   Push the `root` node into the queue `q`.
4.  **Level-by-Level Traversal**:
    *   While the queue `q` is not empty:
        a.  **Get Current Level Size**: Store the current number of nodes in the queue into an integer variable, say `level_size`. This `level_size` represents the total number of nodes at the current level we are about to process.
        b.  **Initialize Level Sum**: Initialize a `double` variable `current_level_sum` to `0.0`. This will accumulate the sum of node values for the current level.
        c.  **Process Current Level Nodes**: Loop `level_size` times (from `i = 0` to `level_size - 1`):
            i.  **Dequeue Node**: Get the node at the front of the queue (`q.front()`) and store it in a temporary `TreeNode*` variable, say `node`. Then, remove this node from the queue (`q.pop()`).
            ii. **Accumulate Sum**: Add `node->val` to `current_level_sum`.
            iii. **Enqueue Children**: If `node->left` is not `nullptr`, push `node->left` into the queue. If `node->right` is not `nullptr`, push `node->right` into the queue. These children will be processed in the *next* level.
        d.  **Calculate and Store Average**: After the loop finishes (meaning all nodes of the current level have been processed), calculate the average for this level: `current_level_sum / level_size`. Push this average into the `ans` vector.
5.  **Return Result**: After the `while` loop finishes (meaning all levels have been processed), return the `ans` vector.

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
    vector<double> averageOfLevels(TreeNode* root) {
        // Initialize a queue for Breadth-First Search (BFS) to process nodes level by level.
        queue<TreeNode*> q;
        // Initialize a vector to store the average of values for each level.
        vector<double> ans;

        // Handle the edge case where the tree is empty.
        // Although constraints state N >= 1, this check is good practice for robustness.
        if (root == nullptr) {
            return {}; // Return an empty vector if the tree is empty.
        }

        // Start BFS by pushing the root node into the queue.
        q.push(root);

        // Continue as long as there are nodes to process in the queue.
        // Each iteration of this while loop processes one full level of the tree.
        while (!q.empty()) {
            // 'level_size' stores the number of nodes at the current level.
            // We capture this size at the beginning of the loop to know how many nodes
            // belong to the current level, before adding children for the next level.
            int level_size = q.size();
            // 'current_level_sum' will accumulate the sum of node values for the current level.
            // It's a double to ensure accurate floating-point arithmetic for averages,
            // especially since node values can be large and their sum might exceed int limits.
            double current_level_sum = 0;

            // Iterate 'level_size' times to process all nodes currently in the queue.
            // These are all the nodes belonging to the current level.
            for (int i = 0; i < level_size; i++) {
                // Get the front node from the queue. This is a node from the current level.
                TreeNode* node = q.front();
                // Remove the node from the queue as it's being processed.
                q.pop();

                // Add the node's value to the sum for the current level.
                // The node's integer value is implicitly converted to double before addition.
                current_level_sum += node->val;

                // If the node has a left child, add it to the queue.
                // This child will be processed in the *next* level.
                if (node->left) {
                    q.push(node->left);
                }
                // If the node has a right child, add it to the queue.
                // This child will also be processed in the *next* level.
                if (node->right) {
                    q.push(node->right);
                }
            }
            // After processing all nodes of the current level, calculate the average.
            // Cast 'level_size' to double to ensure floating-point division,
            // preventing integer division truncation.
            ans.push_back(current_level_sum / level_size);
        }
        // Return the vector containing the average of each level.
        return ans;
    }
};

```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | Each node in the tree is visited, enqueued, and dequeued exactly once. Operations within the loop (summing, checking children, pushing to queue) are constant time. N is the total number of nodes. |
| **Space** | O(W) | The space complexity is determined by the maximum number of nodes stored in the queue at any given time. This corresponds to the maximum width (number of nodes) of the binary tree. In the worst case (a complete binary tree), the last level can contain up to N/2 nodes, making the space complexity O(N). |

## 🔗 Related Problems
*   102. Binary Tree Level Order Traversal
*   107. Binary Tree Level Order Traversal II
*   515. Find Largest Value in Each Tree Row