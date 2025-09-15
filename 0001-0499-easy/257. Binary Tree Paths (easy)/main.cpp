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
    static std::vector<std::string> binaryTreePaths(TreeNode* root) {
        if (!root)
            return {};

        std::string initPath;
        std::vector<std::string> strPaths = getPathes(root, initPath);

        return strPaths;
    }

    static std::vector<std::string> getPathes(TreeNode* root, std::string& prevPath) {
        std::string currentPath;
        if (prevPath.empty())
            currentPath = std::to_string(root->val);
        else
            currentPath = prevPath + "->" + std::to_string(root->val);

        if (!root->left && !root->right)
            return {currentPath};

        std::vector<std::string> leftPathes;
        if (root->left)
            leftPathes = getPathes(root->left, currentPath);

        std::vector<std::string> rightPathes;
        if (root->right)
            rightPathes = getPathes(root->right, currentPath);

        if (leftPathes.size() >= rightPathes.size()) {
            leftPathes.insert(leftPathes.end(), rightPathes.begin(), rightPathes.end());
            return leftPathes;
        }

        if (leftPathes.size() < rightPathes.size()) {
            rightPathes.insert(rightPathes.end(), leftPathes.begin(), leftPathes.end());
            return rightPathes;
        }

        return {};
    }
};

int main() {
//    auto n3 = TreeNode(3);
//    auto n5 = TreeNode(5);
//    auto n4 = TreeNode(4, &n3, &n5);
//    auto n0 = TreeNode(0);
//    auto n2 = TreeNode(2, &n0, &n4);
//    auto n7 = TreeNode(7);
//    auto n9 = TreeNode(9);
//    auto n8 = TreeNode(8, &n7, &n9);
//    auto n6 = TreeNode(6, &n2, &n8);
//    assert(Solution::lowestCommonAncestor(&n6, &n2, &n4) == &n2);

    return 0;
}
