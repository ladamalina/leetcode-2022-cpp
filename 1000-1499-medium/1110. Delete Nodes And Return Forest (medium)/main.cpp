#include <bits/stdc++.h>

/*#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <deque>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <numeric>
#include <optional>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <variant>
#include <vector>*/

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

constexpr int MAX_N = 1000;
std::array<int, MAX_N+1> to_del{};

class Solution {
public:
  std::vector<TreeNode*> delNodes(TreeNode* root, const vi& to_delete) {
    std::fill(RNG(to_del), 0);
    for (const auto x : to_delete) to_del[x] = 1;

    std::vector<TreeNode*> res;
    
    const std::function<void(TreeNode*)> dfs = [&](TreeNode* node) {
      if (!node) return;
      dfs(node->left);
      dfs(node->right);
      if (node->left && to_del[node->left->val]) node->left = nullptr;
      if (node->right && to_del[node->right->val]) node->right = nullptr;
      if (to_del[node->val] && node->left) res.push_back(node->left);
      if (to_del[node->val] && node->right) res.push_back(node->right);
    };
    dfs(root);

    if (!to_del[root->val]) res.push_back(root);

    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    auto n4 = new TreeNode(4);
    auto n5 = new TreeNode(5);
    auto n6 = new TreeNode(6);
    auto n7 = new TreeNode(7);
    auto n2 = new TreeNode(2, n4, n5);
    auto n3 = new TreeNode(3, n6, n7);
    auto n1 = new TreeNode(1, n2, n3);
    const auto a_out = Solution().delNodes(n1, {3,5});
    assert(!a_out.empty());
  
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
