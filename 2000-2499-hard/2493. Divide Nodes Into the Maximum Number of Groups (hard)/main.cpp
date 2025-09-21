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

bool IsGraphBipartite(const int n, const vvi& g) {
  vi vis(n, -1);

  const std::function<bool(int)> dfs = [&](const int v) {
    for (const auto u : g[v]) {
      if (vis[u] == vis[v])
        return false;
      if (vis[u] == -1) {
        vis[u] = 1 - vis[v];
        if (!dfs(u))
          return false;
      }
    }
    return true;
  };
  
  auto res = true;
  FOR(v, 0, n-1) {
    if (vis[v] == -1) {
      vis[v] = 0;
      res &= dfs(v);
    }
  }

  return res;
}

int GetLongestShortestPath(const int v0, const int n, const vvi& g) {
  vi vis(n);
  std::queue<int> q;
  
  q.push(v0);
  vis[v0] = 1;
  auto res = 0;

  while (!q.empty()) {
    const auto n_nodes = SZ(q);
    FOR(i, 0, n_nodes-1) {
      const auto v = q.front();
      q.pop();
      for (const auto u : g[v]) {
        if (!vis[u]) {
          vis[u] = 1;
          q.push(u);
        }
      }
    }
    ++res;
  }

  return res;
}

class Solution {
public:
  int magnificentSets(int n, const vvi& edges) {
    vvi g(n);
    for (const auto& e : edges) {
      g[e[0]-1].push_back(e[1]-1);
      g[e[1]-1].push_back(e[0]-1);
    }

    const auto is_bipartite = IsGraphBipartite(n, g);
    if (!is_bipartite)
      return -1;

    vi dist(n);
    FOR(v, 0, n-1) {
      dist[v] = GetLongestShortestPath(v, n, g);
    }

    vi vis(n);
    const std::function<int(int)> dfs = [&](const int v) {
      vis[v] = 1;
      auto v_res = dist[v];
      for (const auto u : g[v]) {
        if (!vis[u]) {
          v_res = std::max(v_res, dfs(u));
        }
      }
      return v_res;
    };

    auto res = 0;
    FOR(v, 0, n-1) {
      if (!vis[v]) {
        res += dfs(v);
      }
    }

    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi edges{{1,2},{1,4},{1,5},{2,6},{2,3},{4,6}};
    const auto a_out = Solution().magnificentSets(6, edges);
    assert(a_out == 4);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi edges{{1,2},{2,3},{3,1}};
    const auto a_out = Solution().magnificentSets(3, edges);
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
