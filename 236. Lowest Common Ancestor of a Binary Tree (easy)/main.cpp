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
    static TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        std::vector<TreeNode*> pPath = getPathToNode(root, p);
        std::vector<TreeNode*> qPath = getPathToNode(root, q);
        size_t pi = 0;
        size_t qi = 0;
        if (pPath.size() > qPath.size())
            pi += pPath.size() - qPath.size();
        if (qPath.size() > pPath.size())
            qi += qPath.size() - pPath.size();
        while (pPath[pi] != qPath[qi]) {
            ++pi;
            ++qi;
        }
        return pPath[pi];
    }

    static std::vector<TreeNode*> getPathToNode(TreeNode* root, TreeNode* target) {
        if (root == target) {
            std::vector<TreeNode*> path = {target};
            path.reserve(17);
            return path;
        }
        if (root->left) {
            std::vector<TreeNode*> path = getPathToNode(root->left, target);
            if (!path.empty()) {
                path.push_back(root);
                return path;
            }
        }
        if (root->right) {
            std::vector<TreeNode*> path = getPathToNode(root->right, target);
            if (!path.empty()) {
                path.push_back(root);
                return path;
            }
        }
        return {};
    }
};

int main() {
    auto n3 = TreeNode(3);
    auto n5 = TreeNode(5);
    auto n4 = TreeNode(4, &n3, &n5);
    auto n0 = TreeNode(0);
    auto n2 = TreeNode(2, &n0, &n4);
    auto n7 = TreeNode(7);
    auto n9 = TreeNode(9);
    auto n8 = TreeNode(8, &n7, &n9);
    auto n6 = TreeNode(6, &n2, &n8);
    assert(Solution::lowestCommonAncestor(&n6, &n2, &n4) == &n2);

    return 0;
}
