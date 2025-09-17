#include <algorithm>
#include <cmath>
#include <iostream>
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
  static int rob(TreeNode* root) {
    const auto [_, prev2_max, prev1_max] = traverse(root);
    int current_max = std::max(prev2_max, prev1_max);
    return current_max;
  }
 private:
  static std::tuple<int, int, int> traverse(TreeNode* root) {
    if (!root->left && !root->right) {
      return {0, 0, root->val};
    }
    int left_prev3_max = 0, left_prev2_max = 0, left_prev1_max = 0;
    if (root->left) {
      std::tie(left_prev3_max, left_prev2_max, left_prev1_max) = traverse(root->left);
    }
    int right_prev3_max = 0, right_prev2_max = 0, right_prev1_max = 0;
    if (root->right) {
      std::tie(right_prev3_max, right_prev2_max, right_prev1_max) = traverse(root->right);
    }
    int current_max = std::max({root->val + left_prev3_max + right_prev3_max,
                                root->val + left_prev3_max + right_prev2_max,
                                root->val + left_prev2_max + right_prev3_max,
                                root->val + left_prev2_max + right_prev2_max});
    int prev1_max = std::max({left_prev1_max + right_prev1_max,
                              left_prev1_max + right_prev2_max,
                              left_prev2_max + right_prev1_max,
                              left_prev2_max + right_prev2_max});
    int prev2_max = std::max({left_prev2_max + right_prev2_max,
                              left_prev2_max + right_prev3_max,
                              left_prev3_max + right_prev2_max,
                              left_prev3_max + right_prev3_max});

    return {prev2_max, prev1_max, current_max};
  }
};

int main() {
  auto t1_n3_1 = TreeNode(3);
  auto t1_n2 = TreeNode(2, nullptr, &t1_n3_1);
  auto t1_n1 = TreeNode(1);
  auto t1_n3_2 = TreeNode(3, nullptr, &t1_n1);
  auto t1_n3_3 = TreeNode(3, &t1_n2, &t1_n3_2);
  assert(Solution::rob(&t1_n3_3) == 7);

  auto t2_n1_1 = TreeNode(1);
  auto t2_n3_1 = TreeNode(3);
  auto t2_n4 = TreeNode(4, &t2_n1_1, &t2_n3_1);
  auto t2_n1_2 = TreeNode(1);
  auto t2_n5 = TreeNode(5, nullptr, &t2_n1_2);
  auto t2_n3_2 = TreeNode(3, &t2_n4, &t2_n5);
  assert(Solution::rob(&t2_n3_2) == 9);

  // [2,1,3,null,4]
  // output   6
  // expected 7
  auto t3_n4 = TreeNode(4);
  auto t3_n1 = TreeNode(1, nullptr, &t3_n4);
  auto t3_n3 = TreeNode(3);
  auto t3_n2 = TreeNode(2, &t3_n1, &t3_n3);
  assert(Solution::rob(&t3_n2) == 7);

  return 0;
}
