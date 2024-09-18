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
using ii [[maybe_unused]] = std::pair<int, int>;
using vi [[maybe_unused]] = std::vector<int>;
using vl [[maybe_unused]] = std::vector<ll>;
using vvi [[maybe_unused]] = std::vector<vi>;
using vvl [[maybe_unused]] = std::vector<vl>;
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
#define SZ(_v) static_cast<int>((_v).size())
#define F first
#define S second

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  explicit TreeNode(const int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(const int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

constexpr int MAX_V = 1000;

class Solution {
public:
  TreeNode* lcaDeepestLeaves(TreeNode* root) {
    int max_d = -1, max_d_cnt = 0;
    const std::function<void(TreeNode*,int)> dfs1 = [&](TreeNode* node, int d) {
      if (d > max_d) { max_d = d; max_d_cnt = 1; }
      else if (d == max_d) ++max_d_cnt;

      if (node->left) dfs1(node->left, d+1);
      if (node->right) dfs1(node->right, d+1);
    };
    dfs1(root, 0);

    TreeNode* res = nullptr;
    const std::function<int(TreeNode*,int)> dfs2 = [&](TreeNode* node, int d) {
      if (d == max_d) {
        if (max_d_cnt == 1)
          res = node;
        return 1;
      }
      if (!node->left && !node->right)
        return 0;
      const auto cnt = (node->left ? dfs2(node->left, d+1) : 0) + (node->right ? dfs2(node->right, d+1) : 0);
      if (cnt == max_d_cnt && !res)
        res = node;
      return cnt;
    };
    dfs2(root, 0);

    return res;

    /*vi sub_cnt(MAX_V+1);
    vvi sub_vs(MAX_V+1);
    const std::function<void(TreeNode*,int)> dfs2 = [&](TreeNode* node, int d) {
      if (d == max_d) {
        ++sub_cnt[node->val];
        sub_vs[node->val].push_back(node->val);
        return;
      }
      if (!node->left && !node->right)
        return;
      if (node->left) {
        dfs2(node->left, d+1);
        sub_cnt[node->val] += sub_cnt[node->left->val];
        const auto need = 2 - SZ(sub_vs[node->val]);
        FOR(i, 0, std::min(need, SZ(sub_vs[node->left->val]))-1) {
          sub_vs[node->val].push_back(sub_vs[node->left->val][i]);
        }
      }
      if (node->right) {
        dfs2(node->right, d+1);
        sub_cnt[node->val] += sub_cnt[node->right->val];
        const auto need = 2 - SZ(sub_vs[node->val]);
        FOR(i, 0, std::min(need, SZ(sub_vs[node->right->val]))-1) {
          sub_vs[node->val].push_back(sub_vs[node->right->val][i]);
        }
      }
    };

    int max_lca_d = 0, lca = -1;
    FOR(v, 1, MAX_V) {
      if (sub_cnt[v])
    }*/
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
