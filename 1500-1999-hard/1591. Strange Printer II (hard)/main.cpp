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

constexpr int MAX_C = 60;

struct HasCycleDir {
  int n_;
  const vvi& g_;
  vi vis_;
  bool res = false;

  HasCycleDir(const int n, const vvi& g) : n_(n), g_(g), vis_(n) {
    Solve();
  }

  void Solve() {
    FOR(v, 1, n_-1) {
      if (vis_[v] == 0) {
        res |= DFS(v);
      }
    }
  }

  bool DFS(const int v) {
    if (vis_[v] == 2)
      return false;
    if (vis_[v] == 1)
      return true;
    vis_[v] = 1;
    for (const auto u : g_[v]) {
      const auto u_res = DFS(u);
      if (u_res)
        return true;
    }
    vis_[v] = 2;
    return false;
  }
};

class Solution {
public:
  bool isPrintable(const vvi& grid) {
    const auto n = SZ(grid), m = SZ(grid[0]);
    vi i1(MAX_C+1, INT_MAX), i2(MAX_C+1, INT_MIN), j1(MAX_C+1, INT_MAX), j2(MAX_C+1, INT_MIN);
    FOR(i, 0, n-1) {
      FOR(j, 0, m-1) {
        const auto c = grid[i][j];
        i1[c] = std::min(i1[c], i);
        i2[c] = std::max(i2[c], i);
        j1[c] = std::min(j1[c], j);
        j2[c] = std::max(j2[c], j);
      }
    }

    const auto contains = [&](const int v, const int u) { // True if v-rectangle contains u-colors
      FOR(i, i1[v], i2[v]) {
        FOR(j, j1[v], j2[v]) {
          if (grid[i][j] == u)
            return true;
        }
      }
      return false;
    };

    vvi g(MAX_C+1);
    FOR(v, 1, MAX_C) {
      if (i1[v] <= i2[v] && j1[v] <= j2[v]) {
        FOR(u, v+1, MAX_C) {
          if (v != u && i1[u] <= i2[u] && j1[u] <= j2[u]) {
            if (contains(v, u))
              g[v].push_back(u);
            if (contains(u, v))
              g[u].push_back(v);
          }
        }
      }
    }

    HasCycleDir solver(MAX_C+1, g);
    return !solver.res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi grid{{1,1,1,1},{1,1,3,3},{1,1,3,4},{5,5,1,4}};
    const auto a_out = Solution().isPrintable(grid);
    assert(a_out);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi grid{{1,2,1},{2,1,2},{1,2,1}};
    const auto a_out = Solution().isPrintable(grid);
    assert(!a_out);
  
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
