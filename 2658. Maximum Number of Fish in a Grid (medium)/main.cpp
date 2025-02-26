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

struct GridComponents {
  int n, m;
  const vvi& g;
  vvi vis;
  int n_comp = 0;
  vi comp_sum;
  int max_comp_sum = 0;

  GridComponents(const int n, const int m, const vvi& g) : n(n), m(m), g(g), vis(n, vi(m, -1)) {
    FOR(i, 0, n-1) {
      FOR(j, 0, m-1) {
        if (g[i][j] != 0 && vis[i][j] == -1) {
          ++n_comp;
          comp_sum.emplace_back();
          DFS(i, j);
          max_comp_sum = std::max(max_comp_sum, comp_sum.back());
        }
      }
    }
  }

  void DFS(const int i, const int j) {
    if (i<0 || i>=n || j<0 || j>=m || g[i][j]==0 || vis[i][j]==n_comp-1)
      return;
    vis[i][j] = n_comp-1;
    comp_sum[n_comp-1] += g[i][j];
    for (const auto& [ui,uj] : std::array<ii,4>{ii{i+1,j},ii{i-1,j},ii{i,j+1},ii{i,j-1}}) {
      DFS(ui, uj);
    }
  }
};

class Solution {
public:
  int findMaxFish(const vvi& g) {
    GridComponents solver(SZ(g), SZ(g[0]), g);
    return solver.max_comp_sum;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi g{{0,2,1,0},{4,0,0,3},{1,0,0,4},{0,3,2,0}};
    const auto a_out = Solution().findMaxFish(g);
    assert(a_out == 7);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi g{{1,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,1}};
    const auto a_out = Solution().findMaxFish(g);
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
