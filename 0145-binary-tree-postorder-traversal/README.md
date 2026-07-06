# 0145-binary-tree-postorder-traversal

## 📋 Problem Description
Given the `root` of a binary tree, the task is to return the postorder traversal of its nodes' values.

A postorder traversal visits the nodes in the following order:
1.  Traverse the left subtree.
2.  Traverse the right subtree.
3.  Visit the root node itself.

The function `postorderTraversal` receives a pointer to the `root` node of a binary tree. It must return a `std::vector<int>` containing the values of the tree nodes in postorder.

## 🔍 Examples
```
Input: root = [1,null,2,3]
Output: [3,2,1]
Explanation:
The tree structure is:
  1
   \
    2
   /
  3
Postorder: Left (none), Right (2 -> Left (3), Right (none)), Root (1)
Visiting 3 first, then 2, then 1.
```

```
Input: root = [1,2,3,4,5,null,8,null,null,6,7,9]
Output: [4,6,7,5,2,9,8,3,1]
Explanation:
The tree structure is:
      1
     / \
    2   3
   / \   \
  4   5   8
     / \ /
    6  7 9
Postorder traversal sequence.
```

```
Input: root = []
Output: []
Explanation: An empty tree has no nodes to traverse.
```

```
Input: root = [1]
Output: [1]
Explanation: A single-node tree visits the root itself.
```

## 📌 Constraints
*   The number of nodes in the tree is in the range `[0, 100]`.
*   `-100 <= Node.val <= 100`

## 🤔 Understanding the Problem
The problem asks us to perform a specific type of depth-first traversal on a binary tree called "postorder traversal." This means for any given node, we must process all nodes in its left subtree, then all nodes in its right subtree, and *finally* the node itself. The result should be a list of node values in this specific order. Edge cases include an empty tree or a tree with a single node. The "Follow up" suggests an iterative solution, implying the recursive approach is straightforward.

## 💡 Core Idea
The fundamental definition of postorder traversal (Left -> Right -> Root) naturally lends itself to a recursive solution. For any node, we can recursively call the traversal function on its left child, then its right child, and only after both subtrees are processed, add the current node's value to our result.

## 🧠 Approach — Tree Traversal / Recursion (DFS)
This problem is a classic example of a **Tree Traversal** problem, specifically utilizing **Recursion** which is a form of **Depth-First Search (DFS)**. Recursion is an ideal pattern for tree problems because trees are inherently recursive data structures: a tree is either empty or consists of a root node and two child subtrees (which are themselves trees). The postorder definition (process children first, then parent) perfectly aligns with the recursive call stack's behavior, where child calls complete before the parent call resumes.

## 📝 Step-by-Step Algorithm
1.  **Initialize Result List**: Create an empty list (e.g., `std::vector<int>`) to store the postorder traversal result.
2.  **Define Recursive Helper Function**: Create a helper function, let's call it `postorderHelper`, that takes a `TreeNode* root` and a reference to the result list.
3.  **Base Case**: Inside `postorderHelper`, if the current `root` is `NULL` (meaning we've reached past a leaf node or an empty tree), simply return, as there's nothing to process.
4.  **Recurse Left**: Call `postorderHelper` on `root->left`. This ensures that all nodes in the left subtree are processed first.
5.  **Recurse Right**: Call `postorderHelper` on `root->right`. This ensures that all nodes in the right subtree are processed after the left subtree.
6.  **Process Current Node**: After both recursive calls for the left and right children have returned (meaning their subtrees have been fully traversed), add the current `root->val` to the result list.
7.  **Initial Call**: From the main `postorderTraversal` function, call `postorderHelper` with the initial `root` of the tree and the empty result list.
8.  **Return Result**: After the initial call to `postorderHelper` completes, return the populated result list.

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
    // Note: The function name 'inorder' is a misnomer here; it correctly implements postorder.
    void inorder(TreeNode* root, vector<int> &ans){ // Renamed to postorderHelper for clarity in comments

        // Base case: If the current node is NULL, we've gone past a leaf or have an empty subtree.
        // There's nothing to process, so we simply return.
        if(root == NULL){
            return;
        }

        // 1. Recursively traverse the left subtree.
        // This ensures all nodes in the left subtree are processed before the current node.
        inorder(root->left, ans);
      
        // 2. Recursively traverse the right subtree.
        // This ensures all nodes in the right subtree are processed after the left subtree
        // but before the current node.
        inorder(root->right, ans);
        
        // 3. Visit the current node.
        // After both left and right subtrees have been traversed, add the current node's value
        // to our result vector. This is the "Root" part of Left-Right-Root.
        ans.push_back(root->val);

    }

    // Main function to initiate the postorder traversal.
    vector<int> postorderTraversal(TreeNode* root) {

        // Create an empty vector to store the results of the traversal.
        vector<int> ans;
        
        // Call the recursive helper function to populate the 'ans' vector.
        // It starts the traversal from the given root node.
        inorder(root, ans); // Using the original function name 'inorder' as per the provided code
        
        // Return the vector containing the nodes' values in postorder.
        return ans;
        
    }
  
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | Each of the N nodes in the tree is visited exactly once to add its value to the result. |
| **Space** | O(N) | In the worst case (a skewed tree), the recursion stack depth can be N. Additionally, the `ans` vector stores N elements. Thus, total space is dominated by O(N). In a balanced tree, recursion stack space would be O(log N). |

## 🔗 Related Problems
- 144. Binary Tree Preorder Traversal
- 94. Binary Tree Inorder Traversal
- 102. Binary Tree Level Order Traversal