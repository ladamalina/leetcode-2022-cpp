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
  explicit TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class Solution {
public:
  TreeNode* recoverFromPreorder(const std::string& s) {
    const auto sn = SZ(s);
    auto si = 0;

    const auto get_int = [&]() {
      if (si == sn)
        return -1;
      int x = 0;
      while (si < sn && '0' <= s[si] && s[si] <= '9') {
        x = x * 10 + (s[si] - '0');
        ++si;
      }
      return x;
    };

    const auto get_dist = [&]() {
      if (si == sn)
        return -1;
      int x = 0;
      while (si < sn && s[si] == '-') {
        ++x;
        ++si;
      }
      return x;
    };

    auto root = new TreeNode(get_int());
    auto next_dist = get_dist(), next_int = get_int();
    const std::function<void(TreeNode*,int)> dfs = [&](TreeNode* node, int dist) {
      if (next_dist < dist)
        return;

      node->left = new TreeNode(next_int);
      next_dist = get_dist(), next_int = get_int();
      dfs(node->left, dist + 1);

      if (next_dist == dist) {
        node->right = new TreeNode(next_int);
        next_dist = get_dist(), next_int = get_int();
        dfs(node->right, dist + 1);
      }
    };
    dfs(root, 1);

    return root;
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
