#include <cassert>
#include <algorithm>

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
    static int goodNodes(TreeNode* root) {
      return countGoodNodes(root, root->val-1);
    }

    static int countGoodNodes(TreeNode* root, int prev_max) {
      int num = 0;
      if (root->val >= prev_max)
        ++num;
      if (root->left)
        num += countGoodNodes(root->left, std::max(root->val, prev_max));
      if (root->right)
        num += countGoodNodes(root->right, std::max(root->val, prev_max));

      return num;
    }
};

int main() {
  auto n3 = TreeNode(3);
  auto n1 = TreeNode(1);
  auto n5 = TreeNode(5);
  auto n4 = TreeNode(4, &n1, &n5);
  auto n1_2 = TreeNode(1, &n3, nullptr);
  auto n3_2 = TreeNode(3, &n1_2, &n4);
  assert(Solution::goodNodes(&n3_2) == 4);

  return 0;
}
