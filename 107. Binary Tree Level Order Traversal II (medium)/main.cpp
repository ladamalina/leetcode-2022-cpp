#include <iostream>
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
    std::vector<std::vector<int>> levelOrderBottom(TreeNode* root) {
        if (!root)
            return {};
        levelsToNums = {};
        levelsToNums.reserve(11);
        traverse(root, 0);
        levelsToNums.shrink_to_fit();
        for (auto& numsOnLevel : levelsToNums)
            numsOnLevel.shrink_to_fit();
        std::vector<std::vector<int>> res(levelsToNums.rbegin(), levelsToNums.rend());

        return res;
    }

    void traverse(TreeNode* root, int currentDepth) {
        if (levelsToNums.size() < currentDepth + 1) {
            levelsToNums.emplace_back();
        }
        levelsToNums[currentDepth].push_back(root->val);

        if (root->left)
            traverse(root->left, currentDepth + 1);
        if (root->right)
            traverse(root->right, currentDepth + 1);
    }
private:
    std::vector<std::vector<int>> levelsToNums;
};

int main() {
    auto tn15 = TreeNode(15);
    auto tn7 = TreeNode(7);
    auto tn20 = TreeNode(20, &tn15, &tn7);
    auto tn9 = TreeNode(9);
    auto tn3 = TreeNode(3, &tn9, &tn20);

    auto s1 = Solution();
    std::vector<std::vector<int>> levelOrder1 = s1.levelOrderBottom(&tn3);
    for (int l = 0; l < levelOrder1.size(); ++l) {
        std::cout << "level " << l << ": ";
        for (auto num : levelOrder1[l])
            std::cout << num << ", ";
        std::cout << std::endl;
    }

    return 0;
}
