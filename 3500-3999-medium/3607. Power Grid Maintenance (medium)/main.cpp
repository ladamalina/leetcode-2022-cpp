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
using ld = long double;
using ii [[maybe_unused]] = std::pair<int, int>;
using vi [[maybe_unused]] = std::vector<int>;
using vl [[maybe_unused]] = std::vector<ll>;
using vvi [[maybe_unused]] = std::vector<vi>;
using vvvi [[maybe_unused]] = std::vector<vvi>;
using vvl [[maybe_unused]] = std::vector<vl>;
using vii [[maybe_unused]] = std::vector<ii>;
using vb [[maybe_unused]] = std::vector<bool>;
using vd [[maybe_unused]] = std::vector<double>;
using vs [[maybe_unused]] = std::vector<std::string>;
using vc [[maybe_unused]] = std::vector<char>;

#define FOR(_i, _a, _b) for (auto _i = (_a); _i <= (_b); ++(_i))
#define FORD(_i, _a, _b) for (auto _i = (_a); _i >= (_b); --(_i))
#define RNG(_l) (_l).begin(), (_l).end()
#define SORT(_l) std::sort((_l).begin(), (_l).end())
#define CI(_v) static_cast<int>(_v)
#define CL(_v) static_cast<ll>(_v)
#define CD(_v) static_cast<ld>(_v)
#define CC(_v) static_cast<char>(_v)
#define SZ(_v) static_cast<int>((_v).size())
#define F first
#define S second
#define PB push_back

struct GraphComponents {
  int n;
  const vvi& g;
  vi v_comp;
  int n_comp = 0;
  std::vector<std::set<int>> comp_vs;

  GraphComponents(const int n, const vvi& g) : n(n), g(g), v_comp(n, -1) {
    FOR(v, 1, n-1) {
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
    comp_vs[n_comp-1].insert(v);
    
    for (const auto u : g[v]) {
      if (u != p)
        DFS(u, v);
    }
  }
};

class Solution {
public:
  vi processQueries(const int n, const vvi& edges, const vvi& qs) {
    vvi g(n + 1);
    for (const auto& e : edges) {
      g[e[0]].PB(e[1]);
      g[e[1]].PB(e[0]);
    }
    GraphComponents gc(n+1, g);
    const auto qn = SZ(qs);
    vi res;
    vb used(n + 1, true);
    FOR(qi, 0, qn-1) {
      const auto u = qs[qi][1];
      if (qs[qi][0] == 1) {
        if (used[u]) res.PB(u);
        else {
          const auto& vs = gc.comp_vs[gc.v_comp[u]];
          res.PB(vs.empty() ? -1 : *vs.begin());
        }
      } else if (qs[qi][0] == 2) {
        used[u] = false;
        auto& vs = gc.comp_vs[gc.v_comp[u]];
        vs.erase(u);
      }
    }

    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi& edges{{1,2},{2,3},{3,4},{4,5}};
    const vvi& qs{{1,3},{2,1},{1,1},{2,2},{1,2}};
    const auto a_out = Solution().processQueries(5, edges, qs);
    const vi e_out{3,2,3};
    assert(a_out == e_out);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi& edges{};
    const vvi& qs{{1,1},{2,1},{1,1}};
    const auto a_out = Solution().processQueries(3, edges, qs);
    const vi e_out{1,-1};
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
