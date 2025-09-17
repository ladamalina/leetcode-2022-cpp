#include <cassert>
#include <vector>

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  explicit TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class Solution {
 public:
  std::vector<TreeNode*> generateTrees(int n) {
    return generateTreesInRange(1, n);
  }
 private:
  std::vector<TreeNode*> generateTreesInRange(int min_n, int max_n) {
    int range = max_n - min_n;
    if (range < 0) {
      return {};
    }
    if (range == 0) { // min_n == max_n
      auto child_ptr = new TreeNode(max_n);
      return {child_ptr};
    } // min_n < max_n
    std::vector<TreeNode*> subtrees;
    for (int mid_n = min_n; mid_n <= max_n; ++mid_n) {
      auto left_subtrees = generateTreesInRange(min_n, mid_n - 1);
      auto right_subtrees = generateTreesInRange(mid_n + 1, max_n);

      if (left_subtrees.empty()) {
        for (const auto& right_subtree : right_subtrees) {
          auto mid_node = new TreeNode(mid_n, nullptr, right_subtree);
          subtrees.push_back(mid_node);
        }
        continue;
      }
      if (right_subtrees.empty()) {
        for (const auto& left_subtree : left_subtrees) {
          auto mid_node = new TreeNode(mid_n, left_subtree, nullptr);
          subtrees.push_back(mid_node);
        }
        continue;
      }
      // left_subtrees not empty && right_subtrees not empty
      for (const auto& right_subtree : right_subtrees) {
        for (const auto& left_subtree : left_subtrees) {
          auto mid_node = new TreeNode(mid_n, left_subtree, right_subtree);
          subtrees.push_back(mid_node);
        }
      }
    }
    return subtrees;
  }
};

int main() {
  assert(Solution().generateTrees(3).size() == 5);
  assert(Solution().generateTrees(1).size() == 1);

  return 0;
}
