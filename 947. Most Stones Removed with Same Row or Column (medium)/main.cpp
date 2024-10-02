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

struct GraphComponents {
  int n;
  const vvi& g;
  vi vis;
  int n_comp = 0;
  vi comp_sz;

  GraphComponents(const int n, const vvi& g) : n(n), g(g), vis(n) {
    FOR(v, 0, n-1) {
      if (vis[v] == 0) {
        ++n_comp;
        comp_sz.emplace_back();
        DFS(v, -1);
      }
    }
  }

  void DFS(const int v, const int p) {
    if (vis[v] == n_comp)
      return;
    vis[v] = n_comp;
    ++comp_sz[n_comp-1];
    for (const auto u : g[v]) {
      if (u != p)
        DFS(u, v);
    }
  }
};

class Solution {
public:
  int removeStones(const vvi& stones) {
    const auto n = SZ(stones);
    vvi g(n);
    FOR(v, 0, n-1) {
      FOR(u, v+1, n-1) {
        if (stones[v][0] == stones[u][0] || stones[v][1] == stones[u][1]) {
          g[v].emplace_back(u);
          g[u].emplace_back(v);
        }
      }
    }
    GraphComponents gc_solver(n, g);
    auto res = 0;
    for (const auto x : gc_solver.comp_sz)
      res += x-1;
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi stones{{0,0},{0,1},{1,0},{1,2},{2,1},{2,2}};
    const auto a_out = Solution().removeStones(stones);
    assert(a_out == 5);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi stones{{0,0},{0,2},{1,1},{2,0},{2,2}};
    const auto a_out = Solution().removeStones(stones);
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
