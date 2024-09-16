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

constexpr int MAX_N = 15;
std::array<std::array<int, MAX_N>, MAX_N> g, d;
std::array<int, MAX_N> vis;

class Solution {
public:
  vi countSubgraphsForEachDiameter(const int n, const vvi& edges) {
    const auto build_g = [&](const int m) {
      std::fill(&g[0][0], &g[0][0] + sizeof(g) / sizeof(g[0][0]), 0);
      for (const auto& e : edges) {
        const auto v = e[0] - 1, u = e[1] - 1;
        if ((m&(1<<v)) && (m&(1<<u))) {
          g[v][u] = 1;
          g[u][v] = 1;
        }
      }
    };

    const auto is_connected = [&](const int m) {
      std::fill(vis.begin(), vis.begin() + n, 0);
      auto n_vis = 0;
      std::queue<int> q;
      FOR(v, 0, n-1) {
        if (m&(1<<v)) {
          q.push(v);
          vis[v] = 1;
          ++n_vis;
          break;
        }
      }
      while (!q.empty()) {
        const auto v = q.front();
        q.pop();
        FOR(u, 0, n-1) {
          if (!vis[u] && g[v][u]) {
            q.push(u);
            vis[u] = 1;
            ++n_vis;
          }
        }
      }
      return n_vis == __builtin_popcount(m);
    };

    const auto get_max_d = [&](const int m) {
      FOR(v, 0, n-1) {
        FOR(u, 0, n-1) {
          if (v == u) {
            d[v][u] = 0;
          } else {
            const auto exists = (m&(1<<v)) && (m&(1<<u));
            d[v][u] = (g[v][u] && exists) ? 1 : INT_MAX;
          }
        }
      }

      for (int k=0; k<n; ++k) {
        if ((m&(1<<k)) == 0) continue;
        for (int i=0; i<n; ++i) {
          if ((m&(1<<i)) == 0) continue;
          for (int j=0; j<n; ++j) {
            if ((m&(1<<j)) == 0) continue;
            if (d[i][k] < INT_MAX && d[k][j] < INT_MAX)
              d[i][j] = std::min(d[i][j], d[i][k] + d[k][j]);
          }
        }
      }

      auto max_d = 0;
      FOR(v, 0, n-1) {
        FOR(u, 0, n-1) {
          if (d[v][u] != INT_MAX)
            max_d = std::max(max_d, d[v][u]);
        }
      }
      return max_d;
    };

    vi res(n-1);
    const auto max_m = (1 << n) - 1;
    for (auto m = 0; m <= max_m; ++m) {
      if (__builtin_popcount(m) < 2)
        continue;
      build_g(m);
      if (is_connected(m)) {
        ++res[get_max_d(m)-1];
      }
    }

    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi edges{{1,2},{2,3},{2,4}};
    const auto a_out = Solution().countSubgraphsForEachDiameter(4, edges);
    const vi e_out{3,4,0};
    assert(a_out == e_out);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi edges{{1,2}};
    const auto a_out = Solution().countSubgraphsForEachDiameter(2, edges);
    const vi e_out{1};
    assert(a_out == e_out);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi edges{{1,2},{2,3}};
    const auto a_out = Solution().countSubgraphsForEachDiameter(3, edges);
    const vi e_out{2,1};
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
