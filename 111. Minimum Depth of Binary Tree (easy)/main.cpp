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
    int minDepth(TreeNode* root) {
        if (root == nullptr)
            return 0;
        minDepthTraverse(root, 0);

        return minD;
    }

    void minDepthTraverse(TreeNode* root, int prevD) {
        // leaf
        if (root->left == nullptr && root->right == nullptr) {
            minD = std::min(minD, prevD + 1);
            return;
        }

        // not a leaf
        if (root->left)
            minDepthTraverse(root->left, prevD + 1);
        if (root->right)
            minDepthTraverse(root->right, prevD + 1);
    }

private:
    int minD = 999999;
};

int main() {
    return 0;
}
