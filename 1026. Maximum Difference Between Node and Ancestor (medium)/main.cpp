// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  explicit TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

using ii = std::pair<int, int>;

class Solution {
  public:
  static int maxAncestorDiff(TreeNode* root) {
    int res = 0;
    std::function<void(TreeNode*,ii)> dfs = [&](TreeNode* node, const ii& a) {
      res = std::max(res, std::max(std::abs(a.first - node->val), std::abs(a.second - node->val)));
      if (!node->left && !node->right)
        return;
      const ii a_next{std::min(a.first, node->val), std::max(a.second, node->val)};
      if (node->left)
        dfs(node->left, a_next);
      if (node->right)
        dfs(node->right, a_next);
    };
    const ii a_init{root->val, root->val};
    dfs(root, a_init);
    return res;
  }
};

/*[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    auto root = new TreeNode(1, new TreeNode(5, nullptr, new TreeNode(4, new TreeNode(9), new TreeNode(2))),
      new TreeNode(3, new TreeNode(10), new TreeNode(6)));
    const auto a_out = Solution::amountOfTime(root, 3);
    assert(a_out == 4);
    
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  std::cerr << "TestSolution OK"sv << std::endl;
}*/

int main() {
#ifndef NDEBUG
  // TestSolution();
#endif
  return 0;
}
