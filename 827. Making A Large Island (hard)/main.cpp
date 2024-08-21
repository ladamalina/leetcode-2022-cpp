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
#define F first
#define S second

constexpr std::array<ii, 4> DIR{ii{0,1},ii{0,-1},ii{1,0},ii{-1,0}};

void DFS(int i, int j, const vvi& g, int n, int m, int ci, vvi& comp_id, vi& comp_sz) {
  if (i<0 || i>=n || j<0 || j>=m || g[i][j]==0 || comp_id[i][j]==ci)
    return;
  comp_id[i][j] = ci;
  ++comp_sz[ci];
  for (const auto& d : DIR)
    DFS(i+d.F,j+d.S,g,n,m,ci,comp_id,comp_sz);
}

class Solution {
public:
  int largestIsland(const vvi& g) {
    const auto n = CI(g.size());
    const auto m = CI(g[0].size());
    
    auto max_res = 0;
    
    auto ci = -1;
    vvi comp_id(n, vi(m, -1));
    vi comp_sz;
    FOR(i, 0, n-1) {
      FOR(j, 0, m-1) {
        if (g[i][j]==1 && comp_id[i][j]==-1) {
          comp_sz.emplace_back();
          DFS(i,j,g,n,m,++ci,comp_id,comp_sz);
          max_res = std::max(max_res, comp_sz.back());
        }
      }
    }

    std::unordered_set<int> used_comp;
    FOR(i, 0, n-1) {
      FOR(j, 0, m-1) {
        if (g[i][j]==0) {
          if (i-1>=0 && g[i-1][j]==1) used_comp.insert(comp_id[i-1][j]);
          if (i+1<n && g[i+1][j]==1) used_comp.insert(comp_id[i+1][j]);
          if (j-1>=0 && g[i][j-1]==1) used_comp.insert(comp_id[i][j-1]);
          if (j+1<m && g[i][j+1]==1) used_comp.insert(comp_id[i][j+1]);
          auto res = 0;
          for (const auto ci : used_comp)
            res += comp_sz[ci];
          max_res = std::max(max_res, res+1);
          used_comp.clear();
        }
      }
    }
    return max_res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi g{{1,0},{0,1}};
    const auto a_out = Solution().largestIsland(g);
    assert(a_out == 3);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi g{{1,1},{1,0}};
    const auto a_out = Solution().largestIsland(g);
    assert(a_out == 4);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi g{{1,1},{1,1}};
    const auto a_out = Solution().largestIsland(g);
    assert(a_out == 4);
  
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
