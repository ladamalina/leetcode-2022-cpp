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
  vvi highestPeak(const vvi& is_water) {
    const auto n = SZ(is_water), m = SZ(is_water[0]);
    vvi g(n, vi(m, -1));
    std::queue<ii> q;
    FOR(i, 0, n-1) {
      FOR(j, 0, m-1) {
        if (is_water[i][j] == 1) {
          g[i][j] = 0;
          for (const auto& [ui, uj] : std::array<ii,4>{ii{i+1,j},ii{i-1,j},ii{i,j+1},ii{i,j-1}}) {
            if (ui>=0 && ui<n && uj>=0 && uj<m && is_water[ui][uj]==0) {
              q.emplace(ui, uj);
            }
          }
        }
      }
    }
    while (!q.empty()) {
      const auto [i, j] = q.front();
      q.pop();

      auto mn = INT_MAX;
      for (const auto& [ui, uj] : std::array<ii,4>{ii{i+1,j},ii{i-1,j},ii{i,j+1},ii{i,j-1}}) {
        if (ui>=0 && ui<n && uj>=0 && uj<m && g[ui][uj]!=-1) {
          mn = std::min(mn, g[ui][uj]);
        }
      }
      if (g[i][j] != mn+1) {
        g[i][j] = mn+1;
        for (const auto& [ui, uj] : std::array<ii,4>{ii{i+1,j},ii{i-1,j},ii{i,j+1},ii{i,j-1}}) {
          if (ui>=0 && ui<n && uj>=0 && uj<m && g[ui][uj]==-1) {
            q.emplace(ui, uj);
          }
        }
      }
    }
    
    return g;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vvi g{{0,1},{0,0}};
    const vvi e_out{{1,0},{2,1}};
    const auto a_out = Solution().highestPeak(g);
    assert(a_out == e_out);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vvi g{{0,0,1},{1,0,0},{0,0,0}};
    const vvi e_out{{1,1,0},{0,1,1},{1,2,2}};
    const auto a_out = Solution().highestPeak(g);
    assert(a_out == e_out);
  
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
