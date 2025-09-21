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

struct GraphComponents {
  int n;
  const vvi& g;
  vi v_comp;
  int n_comp = 0;
  vvi comp_vs;

  GraphComponents(const int n, const vvi& g) : n(n), g(g), v_comp(n, -1) {
    FOR(v, 0, n-1) {
      if (v_comp[v] == -1) {
        ++n_comp;
        comp_vs.emplace_back();
        DFS(v, -1);
      }
    }
  }

  void DFS(const int v, const int p) {
    if (v_comp[v] == n_comp-1)
      return;
    v_comp[v] = n_comp-1;
    comp_vs[n_comp-1].push_back(v);
    
    for (const auto u : g[v]) {
      if (u != p)
        DFS(u, v);
    }
  }
};

class Solution {
public:
  int countCompleteComponents(const int n, const vvi& edges) {
    vvi g(n);
    vi deg(n);
    for (const auto& e : edges) {
      g[e[0]].push_back(e[1]);
      g[e[1]].push_back(e[0]);
      ++deg[e[0]];
      ++deg[e[1]];
    }

    GraphComponents gc(n, g);
    int res = 0;
    FOR(ci, 0, gc.n_comp-1) {
      bool ok = true;
      for (const auto v : gc.comp_vs[ci]) {
        ok &= (deg[v] == SZ(gc.comp_vs[ci])-1);
      }
      res += ok;
    }

    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  /*{
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().solve();
    assert(a_out == 6);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }*/
  std::cerr << "TestSolution OK"sv << std::endl;
}

int main() {
#ifndef NDEBUG
  TestSolution();
#endif
  return 0;
}
