class Solution {
public:
    TreeNode* head = nullptr;
    TreeNode* prev = nullptr;

    void inorder(TreeNode* root) {
        if (!root) return;

        inorder(root->left);

        if (!head)
            head = root;

        if (prev) {
            prev->left = nullptr;
            prev->right = root;
        }

        prev = root;

        inorder(root->right);
    }

    TreeNode* increasingBST(TreeNode* root) {
        inorder(root);

        prev->left = nullptr;
        prev->right = nullptr;

        return head;
    }
}; 