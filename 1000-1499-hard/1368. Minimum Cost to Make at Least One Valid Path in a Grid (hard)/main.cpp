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

const std::array<ii, 5> DIRS{ii{}, ii{0, 1}, ii{0,-1}, ii{1,0}, ii{-1,0}};
constexpr int MAX_N = 100;
int m, n;
std::array<std::array<int, MAX_N>, MAX_N> vis;

class Solution {
public:
  int minCost(const vvi& g) {
    m = SZ(g), n = SZ(g[0]);
    std::fill(&vis[0][0], &vis[0][0] + sizeof(vis) / sizeof(vis[0][0]), INT_MAX);
    std::priority_queue<std::pair<int,ii>, std::vector<std::pair<int,ii>>, std::greater<>> pq;
    pq.emplace(0, ii{0,0});
    while (!pq.empty()) {
      const auto v_cost = pq.top().F, i = pq.top().S.F, j = pq.top().S.S;
      pq.pop();
      if (v_cost >= vis[i][j])
        continue;
      vis[i][j] = v_cost;
      if (ii{i,j} == ii{m-1,n-1})
        break;
      for (const auto& [ui, uj] : std::array<ii, 4>{ii{i,j+1},ii{i,j-1},ii{i-1,j},ii{i+1,j}}) {
        if (ui>=0 && ui<m && uj>=0 && uj<n) {
          const auto u_cost = v_cost + (ii{ui,uj} != ii{i+DIRS[g[i][j]].F, j+DIRS[g[i][j]].S});
          if (u_cost < vis[ui][uj])
            pq.emplace(u_cost, ii{ui,uj});
        }
      }
    }
    return vis[m-1][n-1];
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi g{{1,1,1,1},{2,2,2,2},{1,1,1,1},{2,2,2,2}};
    const auto a_out = Solution().minCost(g);
    assert(a_out == 3);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi g{{1,1,3},{3,2,2},{1,1,4}};
    const auto a_out = Solution().minCost(g);
    assert(a_out == 0);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi g{{1,2},{4,3}};
    const auto a_out = Solution().minCost(g);
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
