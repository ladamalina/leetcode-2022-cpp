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

struct TrieNode {
  std::array<TrieNode*, 26> nested_;
  int cnt_ = 0;
};

class Solution {
public:
  vi sumPrefixScores(const vs& words) {
    auto root = new TrieNode();
    
    for (const auto& w : words) {
      auto node = root;
      for (const auto c : w) {
        if (!node->nested_[c-'a'])
          node->nested_[c-'a'] = new TrieNode();
        node = node->nested_[c-'a'];
      }
      ++node->cnt_;
    }

    const std::function<void(TrieNode*)> dfs = [&](TrieNode* node) {
      node->cnt_ = node->cnt_;
      for (auto sub_node : node->nested_) {
        if (sub_node) {
          dfs(sub_node);
          node->cnt_ += sub_node->cnt_;
        }
      }
    };
    dfs(root);

    const auto n = SZ(words);
    vi res(n);
    FOR(i, 0, n-1) {
      auto node = root;
      for (const auto c : words[i]) {
        node = node->nested_[c-'a'];
        res[i] += node->cnt_;
      }
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
