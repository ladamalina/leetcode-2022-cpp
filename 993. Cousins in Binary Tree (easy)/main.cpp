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
    static bool isCousins(TreeNode* root, int x, int y) {
      if (x == root->val || y == root->val)
        return false;
      auto find_x = findNode(root, x, 0);
      auto find_y = findNode(root, y, 0);

      return find_x.second == find_y.second && find_x.first != find_y.first;
    }

    static std::pair<TreeNode*, int> findNode(TreeNode* root, const int val, const int level) {
      if (root->left) {
        if (root->left->val == val) {
          return {root, level + 1};
        }
        auto find_left = findNode(root->left, val, level+1);
        if (find_left.first) {
          return find_left;
        }
      }
      if (root->right) {
        if (root->right->val == val) {
          return {root, level + 1};
        }
        auto find_right = findNode(root->right, val, level+1);
        if (find_right.first) {
          return find_right;
        }
      }

      return {nullptr, -1};
    }
};

int main() {
  auto n1_4 = TreeNode(4);
  auto n1_2 = TreeNode(2, &n1_4, nullptr);
  auto n1_3 = TreeNode(3);
  auto n1_1 = TreeNode(1, &n1_2, &n1_3);
  assert(Solution::isCousins(&n1_1, 4, 3) == false);

  auto n2_4 = TreeNode(4);
  auto n2_2 = TreeNode(2, &n2_4, nullptr);
  auto n2_5 = TreeNode(5);
  auto n2_3 = TreeNode(3, &n2_5, nullptr);
  auto n2_1 = TreeNode(1, &n2_2, &n2_3);
  assert(Solution::isCousins(&n2_1, 5, 4));

  auto n3_4 = TreeNode(4);
  auto n3_2 = TreeNode(2, &n3_4, nullptr);
  auto n3_3 = TreeNode(3);
  auto n3_1 = TreeNode(1, &n3_2, &n3_3);
  assert(Solution::isCousins(&n3_1, 2, 3) == false);

  return 0;
}
