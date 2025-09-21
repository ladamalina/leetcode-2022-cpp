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

constexpr int MAX_N = 1e5;
std::array<vi, MAX_N> d_vals;

int MinSwapsToSort(const vi& arr) {
  const auto n = SZ(arr);
    
  // Create a copy of the array and sort it to know the final positions
  auto sorted_arr = arr;
  SORT(sorted_arr);
    
  // Create a map to store the current index of each element in the sorted array
  std::unordered_map<int, int> val_idx;
  for (int i = 0; i < n; ++i) {
    val_idx[sorted_arr[i]] = i;
  }
    
  // Track visited elements to avoid counting the same cycle more than once
  vi vis(n);
  int swap_cnt = 0;
    
  // Go through each element and form cycles
  for (int i = 0; i < n; ++i) {
    // If the element is already visited or in the correct position, skip it
    if (vis[i] || sorted_arr[i] == arr[i]) {
      continue;
    }
        
    // Find the length of the cycle
    int cycleLength = 0;
    int x = i;
    while (!vis[x]) {
      vis[x] = 1;
      x = val_idx[arr[x]];
      cycleLength++;
    }

    // If there is a cycle of length k, it can be sorted with (k-1) swaps
    if (cycleLength > 0) {
      swap_cnt += (cycleLength - 1);
    }
  }

  return swap_cnt;
}

class Solution {
public:
  int minimumOperations(TreeNode* root) {
    std::fill(RNG(d_vals), vi{});
    auto max_d = -1;
    
    const std::function<void(TreeNode*,int)> dfs = [&](TreeNode* node, int d) {
      if (!node)
        return;
      
      max_d = std::max(max_d, d);
      d_vals[d].push_back(node->val);
      
      dfs(node->left, d+1);
      dfs(node->right, d+1);
    };
    dfs(root, 0);

    auto res = 0;
    FOR(d, 0, max_d) {
      res += MinSwapsToSort(d_vals[d]);
    }

    return res;
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
