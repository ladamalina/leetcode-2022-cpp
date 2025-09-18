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
  static int rangeSumBST(TreeNode* root, int low, int high) {
    int range_sum = 0;
    if (low <= root->val && root->val <= high)
      range_sum += root->val;
    if (root->left)
      range_sum += rangeSumBST(root->left, low, high);
    if (root->right)
      range_sum += rangeSumBST(root->right, low, high);

    return range_sum;
  }
};

int main() {
  auto n1_3 = TreeNode(3);
  auto n1_7 = TreeNode(7);
  auto n1_5 = TreeNode(5, &n1_3, &n1_7);
  auto n1_18 = TreeNode(18);
  auto n1_15 = TreeNode(15, &n1_18, nullptr);
  auto n1_10 = TreeNode(10, &n1_5, &n1_15);

  assert(Solution::rangeSumBST(&n1_10, 7, 15) == 32);

  return 0;
}
