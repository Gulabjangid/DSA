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
    vector<int> ans;
    vector<vector<int>> OUTPUT;

    void dfs(TreeNode* node, int tar, int sum) {

        if (!node)
            return;
     
        sum += node->val;
        ans.push_back(node->val);
      

        if (!node->left && !node->right) {
            
            if (sum == tar) {

                OUTPUT.push_back(ans);

            }
            ans.pop_back();
            return;
        }
        dfs(node->left, tar,sum);
        dfs(node->right, tar,sum);
        ans.pop_back();
        
    }
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {

        dfs(root, targetSum, 0);
        return OUTPUT;
    }
};