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
  std::vector<int> largestValues(TreeNode* root) {
    if (!root)
      return {};

    largest_vals.reserve(15);
    traverse(root, 0);
    return largest_vals;
  }
  void traverse(TreeNode* root, const size_t level) {
    if (largest_vals.size() < level + 1)
      largest_vals.push_back(root->val);

    largest_vals[level] = std::max(largest_vals[level], root->val);
    if (root->left)
      traverse(root->left, level + 1);
    if (root->right)
      traverse(root->right, level + 1);
  }
private:
  std::vector<int> largest_vals;
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
  auto n1_3_1 = TreeNode(3);
  auto n1_3_2 = TreeNode(3, &n1_5, &n1_3_1);
  auto n1_9 = TreeNode(9);
  auto n1_2 = TreeNode(2, nullptr, &n1_9);
  auto n1_1 = TreeNode(1, &n1_3_2, &n1_2);
  auto actual1 = Solution().largestValues(&n1_1);
  std::vector<int> expected1 = {1,3,9};
  checkAssertion(actual1, expected1);

  return 0;
}
