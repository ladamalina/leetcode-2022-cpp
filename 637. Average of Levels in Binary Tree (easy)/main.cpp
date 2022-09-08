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
    std::vector<double> averageOfLevels(TreeNode* root) {
        if (root == nullptr)
            return {};

        levels.reserve(14);
        traverse(root, 0);
        levels.shrink_to_fit();
        std::vector<double> res;
        res.reserve(levels.size());
        for (auto& level : levels)
            res.push_back(double(level.second) / level.first);

        return res;
    }
    void traverse(TreeNode* root, int level) {
        if (levels.size() < level + 1)
            levels.emplace_back();
        levels[level] = std::make_pair(++levels[level].first, levels[level].second + root->val);
        if (root->left)
            traverse(root->left, level + 1);
        if (root->right)
            traverse(root->right, level + 1);
    }
private:
    std::vector<std::pair<int, int64_t>> levels = {};
};

int main() {
    return 0;
}
