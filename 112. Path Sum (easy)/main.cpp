#include <algorithm>
#include <iostream>
#include <vector>

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
    static bool hasPathSum(TreeNode* root, int& targetSum) {
        if (root == nullptr)
            return false;
        auto target = (int16_t) targetSum;
        int16_t initSum = 0;
        return traverse(root, target, initSum);
    }

    static bool traverse(TreeNode* root, int16_t& targetSum, int16_t& prevSum) {
        int16_t currentSum = prevSum + root->val;

        if (root->left == nullptr && root->right == nullptr)
            return currentSum == targetSum;

        if (root->left && traverse(root->left, targetSum, currentSum))
            return true;

        if (root->right && traverse(root->right, targetSum, currentSum))
            return true;

        return false;
    }
};

int main() {
    return 0;
}
