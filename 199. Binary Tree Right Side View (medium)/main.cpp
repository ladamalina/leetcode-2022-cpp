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
  std::vector<int> rightSideView(TreeNode* root) {
    if (root == nullptr)
      return {};
    levels.reserve(7);
    traverse(root, 0);
    return levels;
  }
  void traverse(TreeNode* root, size_t level) {
    if (levels.size() < level + 1)
      levels.push_back(root->val);
    if (root->right != nullptr)
      traverse(root->right, level+1);
    if (root->left != nullptr)
      traverse(root->left, level+1);
  }
private:
  std::vector<int> levels;
};

void checkAssertion(const std::vector<int>& actual, const std::vector<int>& expected) {
    std::cout << "expected: ";
    for (const auto expected_val: expected)
        std::cout << expected_val << ' ';
    std::cout << std::endl;

    std::cout << "actual_res: ";
    for (const auto expected_val: actual)
        std::cout << expected_val << ' ';
    std::cout << std::endl;

    assert(expected.size() == actual.size());
    for (size_t i = 0; i < expected.size(); ++i) {
        assert(expected[i] == actual[i]);
    }
}

int main() {

//  std::numeric_limits<int32_t>::min()
  auto n1_5 = TreeNode(5);
  auto n1_2 = TreeNode(2, nullptr, &n1_5);
  auto n1_4 = TreeNode(4);
  auto n1_3 = TreeNode(3, nullptr, &n1_4);
  auto n1_1 = TreeNode(1, &n1_2, &n1_3);
  auto actual1 = Solution().rightSideView(&n1_1);
  std::vector<int> expected1 = {1,3,4};
  checkAssertion(actual1, expected1);

  return 0;
}
