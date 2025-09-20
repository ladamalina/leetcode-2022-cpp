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

class Solution {
public:
  int findTheCity(int n, const vvi& edges, int max_d) {
    vvi d(n, vi(n, INT_MAX));
    FOR(i, 0, n-1) {
      d[i][i] = 0;
    }
    for (const auto& e : edges) {
      d[e[0]][e[1]] = e[2];
      d[e[1]][e[0]] = e[2];
    }

    for (auto k=0; k<n; ++k)
      for (auto i=0; i<n; ++i)
        for (auto j=0; j<n; ++j)
          if (d[i][k] < INT_MAX && d[k][j] < INT_MAX)
            d[i][j] = std::min(d[i][j], d[i][k] + d[k][j]);

    auto res_cnt = INT_MAX, res_v = -1;
    FOR(v, 0, n-1) {
      auto v_cnt = 0;
      FOR(u, 0, n-1) {
        if (u != v && d[v][u] <= max_d)
          ++v_cnt;
      }
      if (v_cnt < res_cnt) {
        res_cnt = v_cnt;
        res_v = v;
      } else if (v_cnt == res_cnt) {
        res_v = v;
      }
    }
    return res_v;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi edges{{0,1,3},{1,2,1},{1,3,4},{2,3,1}};
    const auto a_out = Solution().findTheCity(4, edges, 4);
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
