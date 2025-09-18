#include <iostream>
#include <string>

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
  static std::string tree2str(TreeNode* root) {
    std::string node_str = std::to_string(root->val);
    if (!root->left && !root->right)
      return node_str;

    std::string left_str, right_str;
    if (root->left) {
      left_str = tree2str(root->left);
      node_str += "(" + left_str + ")";
    } else {
      node_str += "()";
    }

    if (root->right) {
      right_str = tree2str(root->right);
      node_str += "(" + right_str + ")";
    }

    return node_str;
  }
};

int main() {

  auto n1_4 = TreeNode(4);
  auto n1_2 = TreeNode(2, &n1_4, nullptr);
  auto n1_3 = TreeNode(3);
  auto n1_1 = TreeNode(1, &n1_2, &n1_3);
  auto tree2str1 = Solution::tree2str(&n1_1);
  assert(tree2str1 == "1(2(4))(3)");

  auto n2_4 = TreeNode(4);
  auto n2_2 = TreeNode(2, nullptr, &n2_4);
  auto n2_3 = TreeNode(3);
  auto n2_1 = TreeNode(1, &n2_2, &n2_3);
  auto tree2str2 = Solution::tree2str(&n2_1);
  assert(tree2str2 == "1(2()(4))(3)");

  return 0;
}
