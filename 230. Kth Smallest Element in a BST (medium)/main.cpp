#include <vector>

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

struct FoundNode {
  int val;
  int kth;
};

class Solution {
 public:
  int kthSmallest(TreeNode* root, int k) {
    auto kth_node = new FoundNode({0, 0});
    traverse(root, k, kth_node);
    return kth_node->val;
  }

  void traverse(const TreeNode* root, const int k, FoundNode* kth_node) {
    if (root->left == nullptr && root->right == nullptr) { // leaf
      kth_node->val = root->val;
      ++kth_node->kth;
      return;
    }
    // has leaves
    if (root->left) {
      traverse(root->left, k, kth_node);
      if (kth_node->kth == k) {
        return;
      }
    }
    kth_node->val = root->val;
    ++kth_node->kth;
    if (kth_node->kth == k) {
      return;
    }
    if (root->right) {
      traverse(root->right, k, kth_node);
      if (kth_node->kth == k) {
        return;
      }
    }
  }
};

int main() {
  auto n1 = TreeNode(1);
  auto n2 = TreeNode(2, &n1, nullptr);
  auto n4 = TreeNode(4);
  auto n3 = TreeNode(3, &n2, &n4);
  auto n6 = TreeNode(6);
  auto n5 = TreeNode(5, &n3, &n6);

  assert(Solution().kthSmallest(&n5, 3) == 3);

  return 0;
}
