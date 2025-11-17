// #pragma GCC optimize("O3,unroll-loops")
// #include <bits/stdc++.h>

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <cfloat>
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
#include <numbers>
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

struct GraphComponents {
  int n;
  const vvi& g;
  vi v_comp;
  int n_comp = 0;
  vvi comp_vs;

  GraphComponents(const int n, const vvi& g) : n(n), g(g), v_comp(n, -1) {
    FOR(v, 0, n-1) {
      if (v_comp[v] == -1) {
        ++n_comp;
        comp_vs.emplace_back();
        DFS(v, -1);
      }
    }
  }

  void DFS(const int v, const int p) {
    if (v_comp[v] == n_comp-1)
      return;
    v_comp[v] = n_comp-1;
    comp_vs[n_comp-1].push_back(v);
    
    for (const auto u : g[v]) {
      if (u != p)
        DFS(u, v);
    }
  }
};

constexpr int MAX_N = 1e5;
std::array<int, MAX_N> vals;

class Solution {
public:
  ll maxAlternatingSum(const vi& nums, const vvi& swaps) {
    const auto n = SZ(nums);
    vvi g(n);
    for (const auto& e : swaps) {
      g[e[0]].push_back(e[1]);
      g[e[1]].push_back(e[0]);
    }
    GraphComponents gc(n, g);
    ll res = 0;
    for (const auto& comp : gc.comp_vs) {
      auto n_odds = 0, m = 0;
      for (const auto v : comp) {
        if (v & 1) ++n_odds;
        vals[m++] = nums[v];
      }
      std::sort(vals.begin(), vals.begin() + m);
      FOR(i, 0, n_odds - 1) res -= vals[i];
      FOR(i, n_odds, m - 1) res += vals[i];
    }
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums{1,2,3};
    const vvi swaps{{0,2},{1,2}};
    const auto a_out = Solution().maxAlternatingSum(nums, swaps);
    assert(a_out == 4);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums{1,2,3};
    const vvi swaps{{1,2}};
    const auto a_out = Solution().maxAlternatingSum(nums, swaps);
    assert(a_out == 2);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums{1,1000000000,1,1000000000,1,1000000000};
    const vvi swaps{};
    const auto a_out = Solution().maxAlternatingSum(nums, swaps);
    assert(a_out == -2999999997);
  
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
