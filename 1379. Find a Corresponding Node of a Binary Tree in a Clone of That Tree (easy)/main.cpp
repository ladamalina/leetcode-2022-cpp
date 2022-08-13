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
    static TreeNode* getTargetCopy(TreeNode* original, TreeNode* cloned, TreeNode* target) {
        if (original == target)
            return cloned;
        if (original->left != nullptr) {
            auto targetOnLeft = getTargetCopy(original->left, cloned->left, target);
            if (targetOnLeft != nullptr)
                return targetOnLeft;
        }
        if (original->right != nullptr) {
            auto targetOnRight = getTargetCopy(original->right, cloned->right, target);
            if (targetOnRight != nullptr)
                return targetOnRight;
        }

        return nullptr;
    }
};

int main() {
    auto n6 = TreeNode(6);
    auto n19 = TreeNode(19);
    auto n3 = TreeNode(3, &n6, &n19);
    auto n4 = TreeNode(4);
    auto n7 = TreeNode(7, &n4, &n3);

    auto n6c = TreeNode(6);
    auto n19c = TreeNode(19);
    auto n3c = TreeNode(3, &n6c, &n19c);
    auto n4c = TreeNode(4);
    auto n7c = TreeNode(7, &n4c, &n3c);
    assert(Solution::getTargetCopy(&n7, &n7c, &n3) == &n3c);

    return 0;
}
