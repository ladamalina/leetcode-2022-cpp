#include <cassert>

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
  TreeNode* pruneTree(TreeNode* root) {
    if (root->left)
      pruneTreeTraverse(root->left, root, true);
    if (root->right)
      pruneTreeTraverse(root->right, root, false);

    if (root->left == nullptr && root->right == nullptr) {
      if (root->val == 0) {
//        delete root;
        return nullptr;
      }
    }
    return root;
  }

  void pruneTreeTraverse(TreeNode* node, TreeNode* parent, bool is_left) {
    if (node->left)
      pruneTreeTraverse(node->left, node, true);
    if (node->right)
      pruneTreeTraverse(node->right, node, false);

    if (node->left == nullptr && node->right == nullptr) { // leaf
      if (node->val == 0) {
        if (is_left) {
          parent->left = nullptr;
        } else {
          parent->right = nullptr;
        }
//        delete node;
      }
    }
  }
};

int main() {
  auto n1_0_1 = TreeNode(0);
  auto n1_0_2 = TreeNode(0);
  auto n1_0_3 = TreeNode(0, &n1_0_1, &n1_0_2);
  auto n1_0_4 = TreeNode(0);
  auto n1_1_1 = TreeNode(1);
  auto n1_1_2 = TreeNode(1, &n1_0_4, &n1_1_1);
  auto n1_1_3 = TreeNode(1, &n1_0_3, &n1_1_2);

  Solution().pruneTree(&n1_1_3);

  return 0;
}
