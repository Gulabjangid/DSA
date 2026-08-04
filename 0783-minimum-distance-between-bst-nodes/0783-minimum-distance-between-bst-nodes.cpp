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
    void inorder(TreeNode* root,TreeNode* &prev, int &ans){
        if(root==nullptr){
            return;
        }
        inorder(root->left,prev,ans);

        if(prev!=nullptr){
            ans=min(ans,root->val - prev->val);
        }
        prev=root;
        inorder(root->right,prev,ans);

    }
    int minDiffInBST(TreeNode* root) {
        TreeNode *prev=nullptr;
        int ans=INT_MAX;
        inorder(root,prev,ans);
        return ans;        
    }
};