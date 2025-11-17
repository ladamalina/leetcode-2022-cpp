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

class Solution {
public:
  ll minimumCost([[maybe_unused]] const int m, [[maybe_unused]] const int n, vi& h_cut, vi& v_cut) {
    SORT(h_cut);
    SORT(v_cut);
    ll res = 0;
    auto n_rows = 1, n_cols = 1;
    while (!h_cut.empty() || !v_cut.empty()) {
      const auto h_cost = h_cut.empty() ? -1ll : h_cut.back();
      const auto v_cost = v_cut.empty() ? -1ll : v_cut.back();
      if (v_cost >= h_cost) {
        res += CL(v_cut.back()) * n_rows;
        v_cut.pop_back();
        ++n_cols;
      } else {
        res += CL(h_cut.back()) * n_cols;
        h_cut.pop_back();
        ++n_rows;
      }
    }
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi h_cut{2,3,2,3,1};
    vi v_cut{1,2};
    const auto a_out = Solution().minimumCost(SZ(h_cut) + 1, SZ(v_cut) + 1, h_cut, v_cut);
    assert(a_out == 28);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi h_cut{1,3};
    vi v_cut{5};
    const auto a_out = Solution().minimumCost(SZ(h_cut) + 1, SZ(v_cut) + 1, h_cut, v_cut);
    assert(a_out == 13);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi h_cut{7};
    vi v_cut{4};
    const auto a_out = Solution().minimumCost(SZ(h_cut) + 1, SZ(v_cut) + 1, h_cut, v_cut);
    assert(a_out == 15);
  
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
