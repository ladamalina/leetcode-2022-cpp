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

constexpr int MAX_N = 1000;
std::array<std::array<int, MAX_N>, MAX_N> dist;

class Solution {
public:
  int minimumTime(const vvi& g) {
    const auto n = SZ(g), m = SZ(g[0]);
    FOR(i, 0, n-1) std::fill(dist[i].begin(), dist[i].begin() + m, INT_MAX);
    std::priority_queue<std::pair<int,ii>, std::vector<std::pair<int,ii>>, std::greater<>> pq;
    dist[0][0] = 0;
    pq.emplace(0, ii{0, 0});
    while (!pq.empty()) {
      const auto d = pq.top().F, i = pq.top().S.F, j = pq.top().S.S;
      pq.pop();
      if (i == n-1 && j == m-1)
        break;

      bool has_back = false;
      for (const auto& [ui, uj] : std::array<ii,4>{ii{i+1,j},ii{i-1,j},ii{i,j+1},ii{i,j-1}}) {
        if (ui >= 0 && ui < n && uj >= 0 && uj < m && g[ui][uj] <= d + 1) {
          has_back = true;
          break;
        }
      }
      
      for (const auto& [ui, uj] : std::array<ii,4>{ii{i+1,j},ii{i-1,j},ii{i,j+1},ii{i,j-1}}) {
        if (ui >= 0 && ui < n && uj >= 0 && uj < m) {
          auto ud = INT_MAX;
          if (g[ui][uj] <= d + 1) {
            ud = d + 1;
          } else if (has_back) {
            ud = g[ui][uj] + ((g[ui][uj]-d) % 2 == 0);
          }
          if (ud < dist[ui][uj]) {
            dist[ui][uj] = ud;
            pq.emplace(ud, ii{ui, uj});
          }
        }
      }
    }
    return (dist[n-1][m-1] == INT_MAX) ? -1 : dist[n-1][m-1];
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi g{{0,1,99},{3,99,99},{4,5,6}};
    const auto a_out = Solution().minimumTime(g);
    assert(a_out == 6);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi g{{0,1,3,2},{5,1,2,5},{4,3,8,6}};
    const auto a_out = Solution().minimumTime(g);
    assert(a_out == 7);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi g{{0,2,4},{3,2,1},{1,0,4}};
    const auto a_out = Solution().minimumTime(g);
    assert(a_out == -1);
  
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
