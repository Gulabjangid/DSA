# 0145-binary-tree-postorder-traversal

## 📋 Problem Description
Given the `root` of a binary tree, the task is to return a list of its nodes' values in *postorder traversal*.

In a postorder traversal, for any given node, its left subtree is visited first, then its right subtree, and finally the node itself. This process is applied recursively to all nodes in the tree.

**Input:** The `root` node of a binary tree.
**Output:** A `vector` (or list) of integers representing the values of the tree nodes in postorder.

## 🔍 Examples
```
Input: root = [1,null,2,3]
Output: [3,2,1]
Explanation:
   1
    \
     2
    /
   3
Postorder: Left (none), Right (2 -> Left (3), Right (none)), Root (1)
Visiting 2: Left (3), Right (none), Root (2) -> 3, 2
So, the order is 3, 2, 1.
```

```
Input: root = [1,2,3,4,5,null,8,null,null,6,7,9]
Output: [4,6,7,5,2,9,8,3,1]
Explanation:
         1
       /   \
      2     3
     / \     \
    4   5     8
       / \   /
      6   7 9
Postorder traversal visits left subtree, then right subtree, then the root.
For root 1:
  Left subtree (root 2): [4,6,7,5,2]
  Right subtree (root 3): [9,8,3]
  Root 1
Combining these gives [4,6,7,5,2,9,8,3,1].
```

```
Input: root = []
Output: []
```

```
Input: root = [1]
Output: [1]
```

## 📌 Constraints
*   The number of nodes in the tree is in the range `[0, 100]`.
*   `-100 <= Node.val <= 100`

## 🤔 Understanding the Problem
The problem asks us to perform a specific type of tree traversal called "postorder traversal." This means that for any node, we must process all nodes in its left subtree, then all nodes in its right subtree, and *only then* process the node itself. This recursive definition is key. Edge cases include an empty tree (return an empty list) and a tree with a single node (return a list containing that node's value). The problem statement also includes a follow-up asking for an iterative solution, implying the recursive one is considered more straightforward.

## 💡 Core Idea
The fundamental idea behind postorder traversal is its recursive definition: process the left child, then the right child, then the current node. This structure naturally maps to a recursive function call where the base case handles null nodes.

## 🧠 Approach — Recursion (Depth-First Search / DFS)
This problem is perfectly suited for a **Recursive Depth-First Search (DFS)** approach. Tree traversals like postorder, inorder, and preorder are inherently recursive because a tree itself is a recursive data structure (a node has left and right children, which are themselves roots of subtrees). DFS explores as far as possible along each branch before backtracking. For postorder, this means diving deep into the left subtree, then the right, and only then "visiting" the current node. This pattern directly mirrors the recursive function calls and their return order.

## 📝 Step-by-Step Algorithm
1.  **Initialize Result List**: Create an empty `vector` (or list) to store the postorder traversal result.
2.  **Define Recursive Helper Function**: Create a helper function, let's call it `traversePostorder`, that takes a `TreeNode* root` and a reference to the result `vector<int>& ans`.
3.  **Base Case**: Inside `traversePostorder`, check if the current `root` is `NULL`. If it is, simply return, as there's nothing to process for a non-existent node.
4.  **Recurse Left**: Call `traversePostorder` on `root->left`. This ensures that the entire left subtree is processed before moving to the right.
5.  **Recurse Right**: Call `traversePostorder` on `root->right`. This ensures that the entire right subtree is processed after the left and before the current node.
6.  **Process Current Node**: After both the left and right subtrees have been fully processed (i.e., the recursive calls for them have returned), add the `root->val` to the `ans` vector.
7.  **Main Function**: In the `postorderTraversal` function, initialize the `ans` vector and then call the `traversePostorder` helper function with the initial `root` and `ans`.
8.  **Return Result**: Finally, return the `ans` vector.

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

    // This helper function performs a postorder traversal.
    // Note: The function name 'inorder' is a misnomer here; its implementation
    // correctly performs a postorder traversal (Left -> Right -> Root).
    void inorder(TreeNode* root, vector<int> &ans){

        // Base case: If the current node is NULL, there's nothing to process.
        // We simply return from this recursive call.
        if(root == NULL){
            return;
        }

        // Step 1: Recursively traverse the left subtree.
        // This ensures all nodes in the left subtree are processed first.
        inorder(root->left, ans);
      
        // Step 2: Recursively traverse the right subtree.
        // This ensures all nodes in the right subtree are processed after the left.
        inorder(root->right, ans);
        
        // Step 3: Process the current node.
        // After both left and right subtrees have been visited, add the current node's value
        // to our result vector. This is the defining characteristic of postorder traversal.
        ans.push_back(root->val);
    }

    // The main function to initiate the postorder traversal.
    vector<int> postorderTraversal(TreeNode* root) {
        // Create an empty vector to store the traversal result.
        vector<int> ans;
        
        // Call the recursive helper function to populate the 'ans' vector.
        // It starts the traversal from the given root node.
        inorder(root, ans); // Calling the helper function (named 'inorder' but implements postorder)
        
        // Return the vector containing the postorder traversal of the tree.
        return ans;
    }
};

```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | Each node in the tree is visited exactly once to be processed. N is the number of nodes. |
| **Space** | O(H) | The space complexity is determined by the maximum depth of the recursion stack. In the worst case (a skewed tree), the height H can be N. In the best case (a balanced tree), H is log N. |

## 🔗 Related Problems
-   94. Binary Tree Inorder Traversal
-   144. Binary Tree Preorder Traversal
-   102. Binary Tree Level Order Traversal