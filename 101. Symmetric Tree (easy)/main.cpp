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
    static bool isSymmetric(TreeNode* root) {
        if (root->left == nullptr && root->right == nullptr)
            return true;
        if (root->left == nullptr || root->right == nullptr)
            return false;
        return Solution::isSymmetricSubtrees(root->left, root->right);
    }

    static bool isSymmetricSubtrees(TreeNode* p, TreeNode* q) {
        // co,pare roots
        if (p == nullptr && q == nullptr)
            return true;
        if (p == nullptr || q == nullptr)
            return false;
        if (p->val != q->val)
            return false;
        // p->val == q->val

        if ((p->left == nullptr && q->right)
            || (p->left && q->right == nullptr))
            return false;
        if (p->left && q->right && p->val != q->val)
            return false;
        bool leftTreeCheck = isSymmetricSubtrees(p->left, q->right);
        if (!leftTreeCheck)
            return false;

        if ((p->right == nullptr && q->left) || (p->right && q->left == nullptr))
            return false;
        if (p->right && q->left && p->val != q->val)
            return false;
        bool rightTreeCheck = isSymmetricSubtrees(p->right, q->left);
        if (!rightTreeCheck)
            return false;

        return true;
    }
};

int main() {
    return 0;
}
