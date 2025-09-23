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

void DFS1(int v, int p, const vvi& g, ii& oe, bool is_even) {
  oe.F += is_even;
  oe.S += !is_even;
  for (const auto u : g[v]) {
    if (u != p) {
      DFS1(u, v, g, oe, !is_even);
    }
  }
}

void DFS2(int v, int p, const vvi& g, vi& dist, int d) {
  dist[v] = d;
  for (const auto u : g[v]) {
    if (u != p) {
      DFS2(u, v, g, dist, d + 1);
    }
  }
}

class Solution {
public:
  vi maxTargetNodes(const vvi& edges1, const vvi& edges2) {
    const auto n1 = SZ(edges1) + 1, n2 = SZ(edges2) + 1;
    vvi g1(n1), g2(n2);
    for (const auto& e : edges1) {
      g1[e[0]].push_back(e[1]);
      g1[e[1]].push_back(e[0]);
    }
    for (const auto& e : edges2) {
      g2[e[0]].push_back(e[1]);
      g2[e[1]].push_back(e[0]);
    }

    ii oe1, oe2; // <even_cnt, odds_cnt> with tree rooted at node-0
    DFS1(0, -1, g1, oe1, true);
    DFS1(0, -1, g2, oe2, true);

    vi dist1(n1), dist2(n2);
    DFS2(0, -1, g1, dist1, 0);
    DFS2(0, -1, g2, dist2, 0);

    auto max_v2_even_cnt = 0, max_v2_odds_cnt = 0;
    FOR(v2, 0, n2-1) {
      const auto v2_even_cnt = dist2[v2] % 2 == 0 ? oe2.F : oe2.S;
      const auto v2_odds_cnt = dist2[v2] % 2 == 0 ? oe2.S : oe2.F;
      max_v2_even_cnt = std::max(max_v2_even_cnt, v2_even_cnt);
      max_v2_odds_cnt = std::max(max_v2_odds_cnt, v2_odds_cnt);
    }

    vi res(n1);
    FOR(v1, 0, n1-1) {
      const auto v1_even_cnt = dist1[v1] % 2 == 0 ? oe1.F : oe1.S;
      res[v1] = v1_even_cnt + max_v2_odds_cnt;
    }

    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi edges1{{0,1},{0,2},{2,3},{2,4}};
    const vvi edges2{{0,1},{0,2},{0,3},{2,7},{1,4},{4,5},{4,6}};
    const auto a_out = Solution().maxTargetNodes(edges1, edges2);
    const vi e_out{8,7,7,8,8};
    assert(a_out == e_out);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi edges1{{0,1},{0,2},{0,3},{0,4}};
    const vvi edges2{{0,1},{1,2},{2,3}};
    const auto a_out = Solution().maxTargetNodes(edges1, edges2);
    const vi e_out{3,6,6,6,6};
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
