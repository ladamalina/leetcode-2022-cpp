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

using Graph = std::vector<std::unordered_set<int>>;

struct HasCycleDir {
  int n_;
  const Graph& g_;
  vi vis_;
  bool res = false;

  HasCycleDir(const int n, const Graph& g) : n_(n), g_(g), vis_(n) {
    Solve();
  }

  void Solve() {
    FOR(v, 0, n_-1) {
      if (vis_[v] == 0) {
        res |= DFS(v);
      }
    }
  }

  bool DFS(const int v) {
    if (vis_[v] == 2)
      return false;
    if (vis_[v] == 1)
      return true;
    vis_[v] = 1;
    for (const auto u : g_[v]) {
      const auto u_res = DFS(u);
      if (u_res)
        return true;
    }
    vis_[v] = 2;
    return false;
  }
};

class Solution {
public:
  vi sortItems(const int n, int m, vi& group, const vvi& bef) {
    FOR(i, 0, n-1) {
      if (group[i] == -1) {
        group[i] = m++;
      }
    }
    Graph gm(m); // directed graph of groups
    Graph gn(n); // directed graph of items in group
    FOR(i, 0, n-1) {
      for (const auto j : bef[i]) {
        if (group[i] == group[j]) {
          gn[j].insert(i);
        } else {
          gm[group[j]].insert(group[i]);
        }
      }
    }

    HasCycleDir cycle_solver_gm(m, gm), cycle_solver_gn(n, gn);
    if (cycle_solver_gm.res || cycle_solver_gn.res)
      return {};

    vi gr_in_deg(m), it_in_deg(n);
    FOR(i, 0, m-1) {
      for (const auto j : gm[i])
        ++gr_in_deg[j];
    }
    FOR(i, 0, n-1) {
      for (const auto j : gn[i]) {
        ++it_in_deg[j];
      }
    }

    const std::function<void(int,const Graph&,vi&,vi&)> top_dfs = [&](int v, const Graph& g, vi& ord, vi& vis) {
      vis[v] = 1;
      for (const auto u : g[v]) {
        if (vis[u] == 0) {
          vis[u] = 1;
          top_dfs(u, g, ord, vis);
        }
      }
      ord.push_back(v);
    };
    
    vi gr_ord, gr_ord_vis(m);
    FOR(i, 0, m-1) {
      if (gr_in_deg[i] == 0) {
        top_dfs(i, gm, gr_ord, gr_ord_vis);
      }
    }

    vvi gr_to_items(m);
    FOR(i, 0, n-1) {
      gr_to_items[group[i]].push_back(i);
    }
    vvi gr_it_ord(m);
    vi it_ord_vis(n);
    FOR(gi, 0, m-1) {
      for (const auto it : gr_to_items[gi]) {
        if (it_in_deg[it] == 0) {
          top_dfs(it, gn, gr_it_ord[gi], it_ord_vis);
        }
      }
    }

    vi res;
    for (const auto gr : gr_ord) {
      for (const auto it : gr_it_ord[gr]) {
        res.push_back(it);
      }
    }
    std::reverse(RNG(res));
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    auto n = 8, m = 2;
    vi group{-1,-1,1,0,0,1,0,-1};
    const vvi bef{{},{6},{5},{6},{3,6},{},{},{}};
    const auto a_out = Solution().sortItems(n, m, group, bef);
    assert(!a_out.empty());
  
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
