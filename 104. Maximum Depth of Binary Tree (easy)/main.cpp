#include "algorithm"

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
    int maxDepth(TreeNode* root) {
        if (root == nullptr)
            return 0;
        maxDepthTraverse(root, 0);

        return maxD;
    }

    void maxDepthTraverse(TreeNode* root, int prevD) {
        maxD = std::max(maxD, prevD + 1);
        if (root->left != nullptr)
            maxDepthTraverse(root->left, prevD + 1);
        if (root->right != nullptr)
            maxDepthTraverse(root->right, prevD + 1);
    }

private:
    int maxD = 0;
};

int main() {
    return 0;
}
