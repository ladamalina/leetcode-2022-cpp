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

class Solution {
public:
  static vi hitBricks(vvi& grid, const vvi& hits) {
    const auto m = SZ(grid), n = SZ(grid[0]), n_hits = SZ(hits);
    vvi h_grid(m, vi(n, 0));
    FOR(hi, 0, n_hits-1) {
      h_grid[hits[hi][0]][hits[hi][1]] = 1;
    }

    vvi comp_id(m, vi(n, -1));
    std::vector<vii> comp_cells;
    vi comp_stable;
    auto n_comps = 0;
    const std::function<void(int,int)> dfs = [&](int i, int j) {
      if (i<0 || i>=m || j<0 || j>=n || grid[i][j]==0 || h_grid[i][j]==1 || comp_id[i][j]==n_comps-1)
        return;
      comp_id[i][j] = n_comps-1;
      comp_cells[n_comps-1].emplace_back(i, j);
      if (i == 0)
        comp_stable[n_comps-1] = 1;
      for (const auto& [ui,uj] : std::array<ii,4>{ii{i+1,j}, ii{i-1,j}, ii{i,j+1}, ii{i,j-1}}) {
        dfs(ui, uj);
      }
    };
    FOR(i, 0, m-1) {
      FOR(j, 0, n-1) {
        if (grid[i][j]==1 && h_grid[i][j]==0 && comp_id[i][j]==-1) {
          ++n_comps;
          comp_cells.emplace_back();
          comp_stable.emplace_back();
          dfs(i, j);
        }
      }
    }
    
    vi res(n_hits);
    vi neigs(4);
    FORD(hi, n_hits-1, 0) {
      const auto i = hits[hi][0], j = hits[hi][1];
      if (grid[i][j] == 0)
        continue;

      int n_neigs = 0;
      int max_sz = 0, max_ci = -1;
      int stable_sz = 0, unstable_sz = 0;
      for (const auto& [ui,uj] : std::array<ii,4>{ii{i+1,j}, ii{i-1,j}, ii{i,j+1}, ii{i,j-1}}) {
        if (ui>=0 && ui<m && uj>=0 && uj<n && comp_id[ui][uj] != -1) {
          const auto ci = comp_id[ui][uj];
          if (std::find(neigs.begin(), neigs.begin()+n_neigs, ci) != neigs.begin()+n_neigs)
            continue;
          neigs[n_neigs++] = ci;
          if (comp_stable[ci]) {
            stable_sz += SZ(comp_cells[ci]);
          } else {
            unstable_sz += SZ(comp_cells[ci]);
          }
          if (SZ(comp_cells[ci]) > max_sz) {
            max_sz = SZ(comp_cells[ci]);
            max_ci = ci;
          }
        }
      }
      if (stable_sz || i == 0)
        res[hi] = unstable_sz;

      // join the components
      FOR(ni, 0, n_neigs-1) {
        const auto ci = neigs[ni];
        if (ci != max_ci) {
          while (!comp_cells[ci].empty()) {
            const auto [ic, jc] = comp_cells[ci].back();
            comp_cells[ci].pop_back();
            comp_cells[max_ci].emplace_back(ic, jc);
            comp_id[ic][jc] = max_ci;
          }
          comp_stable[max_ci] |= comp_stable[ci];
        }
      }
      // join the hitted brick
      if (max_ci >= 0) {
        comp_id[i][j] = max_ci;
        comp_cells[max_ci].emplace_back(i, j);
        comp_stable[max_ci] |= (i == 0);
      } else {
        ++n_comps;
        comp_id[i][j] = n_comps-1;
        comp_cells.emplace_back();
        comp_cells[n_comps-1].emplace_back(i, j);
        comp_stable.push_back(i == 0);
      }
    }
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vvi grid{{1,1,0,1,0},{1,1,0,1,1},{0,0,0,1,1},{0,0,0,1,0},{0,0,0,0,0},{0,0,0,0,0}};
    const vvi hits{{5,1},{1,3}};
    const auto a_out = Solution::hitBricks(grid, hits);
    const vi e_out{0,4};
    assert(a_out == e_out);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vvi grid{{1,0,0,0},{1,1,1,0}};
    const vvi hits{{1,0}};
    const auto a_out = Solution::hitBricks(grid, hits);
    const vi e_out{2};
    assert(a_out == e_out);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vvi grid{{1,0,0,0},{1,1,0,0}};
    const vvi hits{{1,1},{1,0}};
    const auto a_out = Solution::hitBricks(grid, hits);
    const vi e_out{0,0};
    assert(a_out == e_out);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vvi grid{{1},{1},{1},{1},{1}};
    const vvi hits{{3,0},{4,0},{1,0},{2,0},{0,0}};
    const auto a_out = Solution::hitBricks(grid, hits);
    const vi e_out{1,0,1,0,0};
    assert(a_out == e_out);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  std::cerr << "TestSolution OK"sv << std::endl;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
#ifndef NDEBUG
  TestSolution();
#endif
  return 0;
}
