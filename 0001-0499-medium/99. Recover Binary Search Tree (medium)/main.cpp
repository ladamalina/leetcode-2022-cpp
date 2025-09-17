// #include <bits/stdc++.h>

#include <algorithm>
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
#include <random>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <variant>
#include <vector>

using namespace std::literals;

using ll = long long;
using ld = long double;
using ii = std::pair<int, int>;
using vi = std::vector<int>;
using vvi = std::vector<vi>;
using vvvi = std::vector<vvi>;
using vl = std::vector<ll>;
using vvl = std::vector<vl>;
using vvvl = std::vector<vvl>;
using vii = std::vector<ii>;
using vb = std::vector<bool>;
using vd = std::vector<ld>;
using vs = std::vector<std::string>;
using vc = std::vector<char>;

#define FOR(_i, _a, _b) for (auto _i = (_a); _i <= (_b); ++(_i))
#define FORD(_i, _a, _b) for (auto _i = (_a); _i >= (_b); --(_i))
#define RNG(_l) (_l).begin(), (_l).end()
#define SORT(_l) std::sort((_l).begin(), (_l).end())
#define CI(_v) static_cast<int>(_v)
#define CL(_v) static_cast<ll>(_v)
#define CD(_v) static_cast<ld>(_v)
#define CC(_v) static_cast<char>(_v)
#define SZ(_v) static_cast<int>((_v).size())
#define F first
#define S second
#define PB push_back

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  explicit TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

int v1, v2;

ii DFS1(TreeNode* node) {
  if (node->left && node->right) {
    const auto [l_mn, l_mx] = DFS1(node->left);
    const auto [r_mn, r_mx] = DFS1(node->right);
    if (node->val < l_mx)
      v1 = node->val, v2 = l_mx;
    if (node->val > r_mn)
      v1 = node->val, v2 = r_mn;
    if (l_mx > r_mn)
      v1 = l_mx, v2 = r_mn;
    return ii{std::min(node->val, std::min(l_mn, r_mn)), std::max(node->val, std::max(l_mx, r_mx))};
  }
  if (node->left) {
    const auto [l_mn, l_mx] = DFS1(node->left);
    if (node->val < l_mx)
      v1 = node->val, v2 = l_mx;
    return ii{std::min(node->val, l_mn), std::max(node->val, l_mx)};
  }
  if (node->right) {
    const auto [r_mn, r_mx] = DFS1(node->right);
    if (node->val > r_mn)
      v1 = node->val, v2 = r_mn;
    return ii{std::min(node->val, r_mn), std::max(node->val, r_mx)};
  }
  // a leaf
  return ii{node->val, node->val};
}

void DFS2(TreeNode* node) {
  if (node->val == v1)
    node->val = v2;
  else if (node->val == v2)
    node->val = v1;
  if (node->left) DFS2(node->left);
  if (node->right) DFS2(node->right);
}

class Solution {
public:
  void recoverTree(TreeNode* root) {
    DFS1(root);
    DFS2(root);
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    auto root = new TreeNode(1, new TreeNode(3, nullptr, new TreeNode(2)), nullptr);
    Solution().recoverTree(root);
    assert(root->val == 3);
  
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
