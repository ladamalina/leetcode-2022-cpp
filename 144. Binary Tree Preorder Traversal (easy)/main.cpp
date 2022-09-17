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
    std::vector<int> preorderTraversal(TreeNode* root) {
        if (!root)
            return {};
        nums.reserve(100);

        traverse(root);
        nums.shrink_to_fit();
        return nums;
    }
    void traverse(TreeNode* root) {
        nums.push_back(root->val);
        if (root->left)
            traverse(root->left);
        if (root->right)
            traverse(root->right);
    }
private:
    std::vector<int> nums = {};
};

int main() {
    return 0;
}
