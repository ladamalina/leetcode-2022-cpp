struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    static bool isValidBST(TreeNode* root) {
        if (!root)
            return true;
        if (root->left && !isValidBSTLeft(root->left, root->val))
            return false;
        if (root->right && !isValidBSTRight(root->right, root->val))
            return false;
        return true;
    }

    static bool isValidBSTLeft(TreeNode* root, int maxVal) {
        if (root->val >= maxVal)
            return false;
        if (root->left && !isValidBSTLeft(root->left, root->val))
            return false;
        if (root->right && !isValidBSTMiddle(root->right, root->val, maxVal))
            return false;
        return true;
    }

    static bool isValidBSTRight(TreeNode* root, int minVal) {
        if (root->val <= minVal)
            return false;
        if (root->left && !isValidBSTMiddle(root->left, minVal, root->val))
            return false;
        if (root->right && !isValidBSTRight(root->right, root->val))
            return false;
        return true;
    }

    static bool isValidBSTMiddle(TreeNode* root, int minVal, int maxVal) {
        if (root->val <= minVal || root->val >= maxVal)
            return false;
        if (root->left && !isValidBSTMiddle(root->left, minVal, root->val))
            return false;
        if (root->right && !isValidBSTMiddle(root->right, root->val, maxVal))
            return false;
        return true;
    }
};

int main() {
    return 0;
}
