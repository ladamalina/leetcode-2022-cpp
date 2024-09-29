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

struct GridComponents1 {
  static constexpr std::array<ii, 4> DIRS{ii{0,1},ii{0,-1},ii{1,0},ii{-1,0}};
  int m, n;
  const vvi& g;
  vvi comp;
  int n_comp = 0;
  // vi comp_sz;

  GridComponents1(int m, int n, const vvi& g) : m(m), n(n), g(g), comp(m, vi(n)) {
    FOR(i, 0, m-1) {
      FOR(j, 0, n-1) {
        if (g[i][j] == 1 && comp[i][j] == 0) {
          ++n_comp;
          // comp_sz.emplace_back();
          DFS(i, j);
        }
      }
    }
  }

  void DFS(int i, int j) {
    if (i<0 || i>=m || j<0 || j>=n || g[i][j]==0 || comp[i][j]==n_comp)
      return;
    comp[i][j] = n_comp;
    // ++comp_sz[n_comp-1];
    for (const auto& D : DIRS) {
      DFS(i+D.F, j+D.S);
    }
  }
};

struct GridComponents2 {
  static constexpr std::array<ii, 4> DIRS{ii{0,1},ii{0,-1},ii{1,0},ii{-1,0}};
  int m, n;
  const vvi& g;
  vvi comp;
  int n_comp = 0;
  std::vector<vii> comp_vs;

  GridComponents2(int m, int n, const vvi& g) : m(m), n(n), g(g), comp(m, vi(n)) {
    FOR(i, 0, m-1) {
      FOR(j, 0, n-1) {
        if (g[i][j] == 1 && comp[i][j] == 0) {
          ++n_comp;
          comp_vs.emplace_back();
          DFS(i, j);
        }
      }
    }
  }

  void DFS(int i, int j) {
    if (i<0 || i>=m || j<0 || j>=n || g[i][j]==0 || comp[i][j]==n_comp)
      return;
    comp[i][j] = n_comp;
    comp_vs[n_comp-1].emplace_back(i, j);
    for (const auto& D : DIRS) {
      DFS(i+D.F, j+D.S);
    }
  }
};

class Solution {
public:
  int countSubIslands(const vvi& g1, const vvi& g2) {
    const auto m = SZ(g1), n = SZ(g1[0]);
    GridComponents1 gc1(m, n, g1);
    GridComponents2 gc2(m, n, g2);

    auto res = 0;
    for (const auto& vs : gc2.comp_vs) {
      const auto comp_sz = SZ(vs);
      const auto c0 = gc1.comp[vs[0].F][vs[0].S];
      if (c0 == 0)
        continue;
      
      bool ok = true;
      FOR(i, 1, comp_sz-1) {
        if (gc1.comp[vs[i].F][vs[i].S] != c0)
          ok = false;
      }
      res += CI(ok);
    }

    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi g1{{1,1,1,0,0},{0,1,1,1,1},{0,0,0,0,0},{1,0,0,0,0},{1,1,0,1,1}};
    const vvi g2{{1,1,1,0,0},{0,0,1,1,1},{0,1,0,0,0},{1,0,1,1,0},{0,1,0,1,0}};
    const auto a_out = Solution().countSubIslands(g1, g2);
    assert(a_out == 3);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi g1{{1,0,1,0,1},{1,1,1,1,1},{0,0,0,0,0},{1,1,1,1,1},{1,0,1,0,1}};
    const vvi g2{{0,0,0,0,0},{1,1,1,1,1},{0,1,0,1,0},{0,1,0,1,0},{1,0,0,0,1}};
    const auto a_out = Solution().countSubIslands(g1, g2);
    assert(a_out == 2);
  
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
