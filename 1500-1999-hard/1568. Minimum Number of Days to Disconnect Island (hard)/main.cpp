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

struct GridComponents {
  constexpr std::array<ii, 4> DIRS{ii{0,1},ii{0,-1},ii{1,0},ii{-1,0}};
  int m, n;
  const vvi& g;
  vvi vis;
  int n_comp = 0;
  vi comp_sz;

  GridComponents(int m, int n, const vvi& g) : m(m), n(n), g(g), vis(m, vi(n)) {
    FOR(i, 0, m-1) {
      FOR(j, 0, n-1) {
        if (g[i][j] == 1 && vis[i][j] == 0) {
          ++n_comp;
          comp_sz.emplace_back();
          DFS(i, j);
        }
      }
    }
  }

  void DFS(int i, int j) {
    if (i<0 || i>=m || j<0 || j>=n || g[i][j]==0 || vis[i][j]==n_comp)
      return;
    vis[i][j] = n_comp;
    ++comp_sz[n_comp-1];
    for (const auto& D : DIRS) {
      DFS(i+D.F, j+D.S);
    }
  }
};

struct GridCutpoints {
  /* Finding articulation points in a graph in O(N+M)
   * https://cp-algorithms.com/graph/cutpoints.html
   */
  constexpr std::array<ii, 4> DIRS{ii{0,1},ii{0,-1},ii{1,0},ii{-1,0}};
  int m, n;
  const vvi& g;
  vvi vis;
  vvi tin, low;
  int timer;
  vii cutpoints;

  GridCutpoints(int m, int n, const vvi& g) : m(m), n(n), g(g), vis(m, vi(n)), tin(m, vi(n, -1)),
    low(m, vi(n, -1)), timer(0) {
    FOR(i, 0, m-1) {
      FOR(j, 0, n-1) {
        if (g[i][j] == 1 && vis[i][j] == 0) {
          DFS(i, j, -1, -1);
        }
      }
    }
  }
  
  void DFS(int i, int j, int pi = -1, int pj = -1) {
    vis[i][j] = 1;
    tin[i][j] = low[i][j] = timer++;
    auto n_children = 0;

    for (const auto& D : DIRS) {
      if (i+D.F<0 || i+D.F>=m || j+D.S<0 || j+D.S>=n || g[i+D.F][j+D.S]==0)
        continue;
      if (i+D.F == pi && j+D.S == pj)
        continue;
      if (vis[i+D.F][j+D.S]) {
        low[i][j] = std::min(low[i][j], tin[i+D.F][j+D.S]);
      } else {
        DFS(i+D.F, j+D.S, i, j);
        low[i][j] = std::min(low[i][j], low[i+D.F][j+D.S]);
        if (low[i+D.F][j+D.S] >= tin[i][j] && pi != -1)
          cutpoints.emplace_back(i, j);
        ++n_children;
      }
    }
    if (pi == -1 && n_children > 1)
      cutpoints.emplace_back(i, j);
  }
};

class Solution {
public:
  int minDays(const vvi& grid) {
    const auto m = SZ(grid);
    const auto n = SZ(grid[0]);

    // count connected components
    GridComponents comp_solver(m, n, grid);
    if (comp_solver.n_comp != 1)
      return 0;
    // n_comp == 1
    if (comp_solver.comp_sz[0] == 1)
      return 1;

    // find cutpoints
    GridCutpoints cutp_solver(m, n, grid);
    if (!cutp_solver.cutpoints.empty())
      return 1;

    return 2;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi grid{{0,1,1,0},{0,1,1,0},{0,0,0,0}};
    const auto a_out = Solution().minDays(grid);
    assert(a_out == 2);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi grid{{1,1}};
    const auto a_out = Solution().minDays(grid);
    assert(a_out == 2);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi grid{{0,0,0},{0,1,0},{0,0,0}};
    const auto a_out = Solution().minDays(grid);
    assert(a_out == 1);
  
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
