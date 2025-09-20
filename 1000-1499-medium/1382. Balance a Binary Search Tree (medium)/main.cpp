#include <bits/stdc++.h>

using namespace std::literals;

using ll = long long;
using ii [[maybe_unused]] = std::pair<int, int>;
using vi [[maybe_unused]] = std::vector<int>;
using vl [[maybe_unused]] = std::vector<ll>;
using vvi [[maybe_unused]] = std::vector<vi>;
using vii [[maybe_unused]] = std::vector<ii>;
using vb [[maybe_unused]] = std::vector<bool>;
using vd [[maybe_unused]] = std::vector<double>;
using vs [[maybe_unused]] = std::vector<std::string>;

#define FOR(_i, _a, _b) for (int _i = (_a); _i <= (_b); ++(_i))
#define FORD(_i, _a, _b) for (int _i = (_a); _i >= (_b); --(_i))
#define RNG(_l) (_l).begin(), (_l).end()
#define SORT(_l) std::sort((_l).begin(), (_l).end())
#define CI(_v) static_cast<int>(_v)
#define CL(_v) static_cast<ll>(_v)
#define CD(_v) static_cast<double>(_v)
#define F first
#define S second

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
  TreeNode* balanceBST(TreeNode* root) {
    std::set<int> x_set;
    DFS(root, x_set);
    vi x_vec(RNG(x_set));
    const auto n = CI(x_vec.size());
    if (n == 1)
      return new TreeNode(x_vec[0]);
    auto l = 0, r = n-1;
    auto m = (l+r)/2;
    auto node = new TreeNode(x_vec[m]);
    Build(node, x_vec, l, m-1, true);
    Build(node, x_vec, m+1, r, false);
    return node;
  }

private:
  void DFS(TreeNode* root, std::set<int>& x_set) {
    if (!root) return;
    x_set.insert(root->val);
    DFS(root->left, x_set);
    DFS(root->right, x_set);
  }

  void Build(TreeNode* root, const vi& x_vec, int l, int r, bool is_left) {
    if (l>r) return;
    if (l==r) {
      if (is_left) root->left = new TreeNode(x_vec[l]);
      else root->right = new TreeNode(x_vec[l]);
      return;
    }
    auto m = (l+r)/2;
    auto node = new TreeNode(x_vec[m]);
    if (is_left) root->left = node;
    else root->right = node;
    Build(node, x_vec, l, m-1, true);
    Build(node, x_vec, m+1, r, false);
  }
};

[[maybe_unused]] void TestSolution() {
  /*{
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().solve();
    assert(a_out == 6);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }*/
  std::cerr << "TestSolution OK"sv << std::endl;
}

int main() {
#ifndef NDEBUG
  TestSolution();
#endif
  return 0;
}
