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

class Solution {
public:
  int longestPath(const vi& parent, const std::string& s) {
    const auto n = SZ(parent);
    vvi g(n);
    FOR(i, 1, n-1) g[parent[i]].push_back(i);
    vi v_len(n);
    auto max_res = 1;
    const std::function<void(int)> rec = [&](const int u) {
      v_len[u] = 1;
      auto mx1 = 0, mx2 = 0;
      for (const auto v : g[u]) {
        rec(v);
        if (s[u] != s[v]) {
          v_len[u] = std::max(v_len[u], v_len[v] + 1);
          if (v_len[v] >= mx1) {
            mx2 = mx1;
            mx1 = v_len[v];
          } else if (v_len[v] > mx2) {
            mx2 = v_len[v];
          }
        }
      }
      max_res = std::max(max_res, v_len[u]);
      if (mx1 && mx2)
        max_res = std::max(max_res, mx1 + mx2 + 1);
    };
    rec(0);
    return max_res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi parent{-1,0,0,1,1,2};
    const std::string s("abacbe"s);
    const auto a_out = Solution().longestPath(parent, s);
    assert(a_out == 3);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi parent{-1,0,0,0};
    const std::string s("aabc"s);
    const auto a_out = Solution().longestPath(parent, s);
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
