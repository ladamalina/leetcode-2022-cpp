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
#include <limits>
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

class DSU {
public:
  explicit DSU(int n) : p_(vi(n)), r_(vi(n, 1)) {
    std::iota(p_.begin(), p_.end(), 0);
  }
  int Get(int a) {
    return p_[a] = (a == p_[a] ? a : Get(p_[a]));
  }
  void Union(int a, int b) {
    a = Get(a);
    b = Get(b);
    if (a == b) return;
    if (r_[a] == r_[b]) ++r_[a];
    if (r_[a] > r_[b]) p_[b] = a;
    else p_[a] = b;
  }
private:
  vi p_, r_;
};

class Solution {
public:
  int maxNumEdgesToRemove(int n, const vvi& edges) {
    const auto m = CI(edges.size());
    std::vector<vii> g_ab(n+1);
    FOR(i, 0, m-1) {
      const auto& e = edges[i];
      if (e[0] == 3) {
        g_ab[e[1]].emplace_back(e[2], i);
        g_ab[e[2]].emplace_back(e[1], i);
      }
    }
    
    vi exist(m, 1);
    DSU dsu_ab(n+1);
    
    vi vis(n+1);
    const std::function<void(int,int)> dfs_ab = [&](int v, int p) {
      for (const auto& [u, ei] : g_ab[v]) {
        if (u != p) {
          if (vis[u]) {
            exist[ei] = 0;
          } else {
            vis[u] = true;
            dsu_ab.Union(v, u);
            dfs_ab(u, v);
          }
        }
      }
    };
    FOR(v, 1, n) {
      if (!vis[v]) {
        vis[v] = 1;
        dfs_ab(v, -1);
      }
    }

    auto dsu_a = dsu_ab;
    FOR(ei, 0, m-1) {
      if (edges[ei][0] == 1) {
        const auto v = edges[ei][1], u = edges[ei][2];
        if (dsu_a.Get(v) == dsu_a.Get(u)) {
          exist[ei] = 0;
        } else {
          dsu_a.Union(v, u);
        }
      }
    }
    bool trav_a = true;
    FOR(v, 2, n) {
      if (dsu_a.Get(1) != dsu_a.Get(v)) {
        trav_a = false;
        break;
      }
    }
    if (!trav_a) return -1;

    auto dsu_b = dsu_ab;
    FOR(ei, 0, m-1) {
      if (edges[ei][0] == 2) {
        const auto v = edges[ei][1], u = edges[ei][2];
        if (dsu_b.Get(v) == dsu_b.Get(u)) {
          exist[ei] = 0;
        } else {
          dsu_b.Union(v, u);
        }
      }
    }
    bool trav_b = true;
    FOR(v, 2, n) {
      if (dsu_b.Get(1) != dsu_b.Get(v)) {
        trav_b = false;
        break;
      }
    }
    if (!trav_b) return -1;
    
    return std::count(RNG(exist), 0);
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi edges{{3,1,2},{3,2,3},{1,1,3},{1,2,4},{1,1,2},{2,3,4}};
    const auto a_out = Solution().maxNumEdgesToRemove(4, edges);
    assert(a_out == 2);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi edges{{3,1,2},{3,2,3},{1,1,4},{2,1,4}};
    const auto a_out = Solution().maxNumEdgesToRemove(4, edges);
    assert(a_out == 0);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi edges{{3,2,3},{1,1,2},{2,3,4}};
    const auto a_out = Solution().maxNumEdgesToRemove(4, edges);
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
