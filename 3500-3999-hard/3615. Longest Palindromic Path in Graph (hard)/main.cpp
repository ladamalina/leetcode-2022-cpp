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

class Solution {
public:
  int maxLen(const int n, const vvi& edges, const std::string& label) {
    vvvi g(n, vvi(26));
    for (const auto& e : edges) {
      g[e[0]][label[e[1]] - 'a'].PB(e[1]);
      g[e[1]][label[e[0]] - 'a'].PB(e[0]);
    }
    
    auto max_res = 1;
    vvvi dp(n, vvi(n, vi((1 << n), -1)));
    const std::function<int(int,int,int)> rec = [&](int v1, int v2, int m) {
      auto& res = dp[v1][v2][m];
      if (res != -1) return res;
      res = 0;
      FOR(c, 0, 25) {
        for (const auto u1 : g[v1][c]) {
          if (m & (1 << u1)) continue;
          for (const auto u2 : g[v2][c]) {
            if (m & (1 << u2)) continue;
            if (u1 != u2) {
              const auto sub_res = rec(u1, u2, m|(1<<u1)|(1<<u2));
              res = std::max(res, 2 + sub_res);
            }
          }
        }
      }
      return res;
    };
    
    FOR(v, 0, n-1) {
      const auto res = 1 + rec(v, v, (1 << v));
      max_res = std::max(max_res, res);
    }
    for (const auto& e : edges) {
      const auto v1 = e[0], v2 = e[1];
      if (label[v1] == label[v2]) {
        const auto res = 2 + rec(v1, v2, (1 << v1)|(1 << v2));
        max_res = std::max(max_res, res);
      }
    }
    return max_res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi edges{{0,1},{1,2}};
    const std::string label("aba"s);
    const auto a_out = Solution().maxLen(3, edges, label);
    assert(a_out == 3);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi edges{{0,1},{0,2}};
    const std::string label("abc"s);
    const auto a_out = Solution().maxLen(3, edges, label);
    assert(a_out == 1);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi edges{{0,2},{0,3},{3,1}};
    const std::string label("bbac"s);
    const auto a_out = Solution().maxLen(4, edges, label);
    assert(a_out == 3);
  
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
