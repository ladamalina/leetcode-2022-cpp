#include <bits/stdc++.h>

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  explicit TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class Solution {
 public:
  static bool isSameTree(TreeNode* p, TreeNode* q) {
    if (!p && !q)
      return true;
    if (!p || !q)
      return false;
    if (p->val != q->val)
      return false;
    // p->val == q->val

    return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
  }
};

int main() {
  return 0;
}
