#include <cassert>
#include <cmath>
#include <string>
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
    int sumNumbers(TreeNode* root) {
        if (root == nullptr)
            return 0;
        std::string digits;
        traverse(root, digits);

        return total;
    }

    void traverse(TreeNode* root, const std::string& prev_digits) {
        std::string digits = prev_digits;
        digits += std::to_string(root->val);

        if (root->left == nullptr && root->right == nullptr) {
            total += std::stoi(digits);
            return;
        }
        if (root->left)
            traverse(root->left, digits);
        if (root->right)
            traverse(root->right, digits);
    }

private:
    int total = 0;
};

int main() {
    auto n5 = TreeNode(5);
    auto n1 = TreeNode(1);
    auto n9 = TreeNode(9, &n5, &n1);
    auto n0 = TreeNode(0);
    auto n4 = TreeNode(4, &n9, &n0);

    int s1 = Solution().sumNumbers(&n4);
    assert(s1 == 1026);

    return 0;
}
