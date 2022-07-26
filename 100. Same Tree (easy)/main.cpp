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
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if (!p && !q)
            return true;
        if (!p || !q)
            return false;
        if (p->val != q->val)
            return false;
        // p->val == q->val

        if ((!p->left && q->left) || (p->left && !q->left))
            return false;
        if (p->left && q->left && p->val != q->val)
            return false;
        bool leftTreeCheck = isSameTree(p->left, q->left);
        if (!leftTreeCheck)
            return false;

        if ((!p->right && q->right) || (p->right && !q->right))
            return false;
        if (p->right && q->right && p->val != q->val)
            return false;
        bool rightTreeCheck = isSameTree(p->right, q->right);
        if (!rightTreeCheck)
            return false;

        return true;
    }
};

int main() {
    return 0;
}
