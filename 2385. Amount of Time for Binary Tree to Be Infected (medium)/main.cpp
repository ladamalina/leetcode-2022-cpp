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
ii h[100001];

class Solution {
  public:
  static int amountOfTime(TreeNode* root, int start) {
    std::fill(&h[0], &h[0] + sizeof(h) / sizeof(h[0]), ii{0, 0});

    int res = 0;
    std::function<int(TreeNode*)> dfs = [&](TreeNode* node) {
      int l_dep = 0;
      if (node->left) {
        l_dep = dfs(node->left);
        h[node->val].first = std::max(h[node->left->val].first, h[node->left->val].second) + 1;
      }
      int r_dep = 0;
      if (node->right) {
        r_dep = dfs(node->right);
        h[node->val].second = std::max(h[node->right->val].first, h[node->right->val].second) + 1;
      }
      if (node->val == start) {
        res = std::max(h[node->val].first, h[node->val].second);
        return 1;
      }
      if (l_dep) {
        res = std::max(res, l_dep + h[node->val].second);
        return l_dep + 1;
      }
      if (r_dep) {
        res = std::max(res, r_dep + h[node->val].first);
        return r_dep + 1;
      }
      return 0;
    };
    dfs(root);

    return res;
  }
};

[[maybe_unused]] void TestSolution() {
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
}

int main() {
#ifndef NDEBUG
  TestSolution();
#endif
  return 0;
}
