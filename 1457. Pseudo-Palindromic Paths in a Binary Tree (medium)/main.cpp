#include <bits/stdc++.h>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    explicit TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* l, TreeNode* r) : val(x), left(l), right(r) {}
};

int DFS(TreeNode* node, int mask) {
  if (!node->left && !node->right) {
    return static_cast<int>(__builtin_popcount(mask) <= 1);
  }
  return (node->left ? DFS(node->left, mask^(1<<(node->left->val))) : 0)
      + (node->right ? DFS(node->right, mask^(1<<(node->right->val))) : 0);
}

class Solution {
 public:
  static int pseudoPalindromicPaths(TreeNode* root) {
    const auto res = DFS(root, (1<<(root->val)));
    return res;
  }
};

int main() {
  return 0;
}
