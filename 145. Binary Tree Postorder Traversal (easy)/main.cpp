#include <deque>
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
    std::vector<int> postorderTraversal(TreeNode* root) {
        if (root == nullptr)
            return {};
        nums.reserve(100);
        traverse(root);
        nums.shrink_to_fit();
        return nums;
    }
    void traverse(TreeNode* root) {
        if (root->left)
            traverse(root->left);
        if (root->right)
            traverse(root->right);
        nums.push_back(root->val);
    }
private:
    std::vector<int> nums = {};
};

int main() {
    return 0;
}
