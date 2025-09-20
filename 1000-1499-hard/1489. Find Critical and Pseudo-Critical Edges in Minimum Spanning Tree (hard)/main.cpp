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

void DFS1(const int v, const int p, const std::vector<vii>& g, const vi& is_mst,
    std::vector<std::unordered_set<int>>& sub_trees) {
  sub_trees[v].insert(v);
  for (const auto& [u, i] : g[v]) {
    if (u != p && is_mst[i]) {
      DFS1(u, v, g, is_mst, sub_trees);
      for (const auto x : sub_trees[u])
        sub_trees[v].insert(x);
    }
  }
}

void DFS2(const int v, const int p, const std::vector<vii>& g, const vvi& edges, const vi& is_mst,
    const std::vector<std::unordered_set<int>>& sub_trees,
    std::unordered_set<int>& crit, std::unordered_set<int>& non_crit) {
  for (const auto& [u, i] : g[v]) {
    if (u != p && is_mst[i]) {
      DFS2(u, v, g, edges, is_mst, sub_trees, crit, non_crit);
          
      const auto w = edges[i][2];
      bool found_eq = false;
      FOR(j, 0, SZ(edges)-1) {
        if (j != i) {
          const auto vx = edges[j][0], ux = edges[j][1], wx = edges[j][2];
          if (sub_trees[u].contains(vx) != sub_trees[u].contains(ux) && wx <= w) {
            found_eq = true;
            non_crit.insert(i);
            non_crit.insert(j);
          }
        }
      }
      if (!found_eq)
        crit.insert(i);
    }
  }
}

class Solution {
public:
  vvi findCriticalAndPseudoCriticalEdges(const int n, const vvi& edges) {
    const auto m = SZ(edges);
    
    std::vector<vii> g(n);
    std::priority_queue<ii, vii, std::greater<>> pq;
    FOR(i, 0, m-1) {
      const auto& e = edges[i];
      g[e[0]].emplace_back(e[1], i);
      g[e[1]].emplace_back(e[0], i);
      pq.emplace(e[2], i);
    }
    
    DSU dsu(n);
    vi is_mst(m);
    while (!pq.empty()) {
      const auto [w, i] = pq.top();
      pq.pop();
      const auto v = edges[i][0], u = edges[i][1];
      if (dsu.Get(v) == dsu.Get(u))
        continue;
      is_mst[i] = 1;
      dsu.Union(v, u);
    }

    std::vector<std::unordered_set<int>> sub_trees(n);
    DFS1(0, -1, g, is_mst, sub_trees);

    std::unordered_set<int> crit, non_crit;
    DFS2(0, -1, g, edges, is_mst, sub_trees, crit, non_crit);

    vi crit_vec(RNG(crit)), non_crit_vec(RNG(non_crit));
    SORT(crit_vec);
    SORT(non_crit_vec);
    return {crit_vec, non_crit_vec};
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi edges{{0,1,1},{1,2,1},{2,3,2},{0,3,2},{0,4,3},{3,4,3},{1,4,6}};
    const auto a_out = Solution().findCriticalAndPseudoCriticalEdges(5, edges);
    const vvi e_out{{0,1}, {2,3,4,5}};
    assert(a_out == e_out);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi edges{{0,1,1},{1,2,1},{2,3,1},{0,3,1}};
    const auto a_out = Solution().findCriticalAndPseudoCriticalEdges(4, edges);
    const vvi e_out{{}, {0,1,2,3}};
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
