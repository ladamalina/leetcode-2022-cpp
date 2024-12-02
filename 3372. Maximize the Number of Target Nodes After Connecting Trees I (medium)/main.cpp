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

class Solution {
public:
  vi maxTargetNodes(const vvi& edges1, const vvi& edges2, const int k) {
    const auto n = SZ(edges1) + 1;
    const auto m = SZ(edges2) + 1;

    vvi g1(n);
    for (const auto& e : edges1) {
      g1[e[0]].push_back(e[1]);
      g1[e[1]].push_back(e[0]);
    }

    vvi g2(m);
    for (const auto& e : edges2) {
      g2[e[0]].push_back(e[1]);
      g2[e[1]].push_back(e[0]);
    }

    const std::function<int(int,int,int)> dfs1 = [&](const int v, const int p, const int d) {
      if (d > k)
        return 0;
      auto v_res = 1;
      for (const auto u : g1[v]) {
        if (u != p) {
          v_res += dfs1(u, v, d+1);
        }
      }
      return v_res;
    };

    vi res1(n);
    FOR(v, 0, n-1) {
      res1[v] = dfs1(v, -1, 0);
    }

    const std::function<int(int,int,int)> dfs2 = [&](const int v, const int p, const int d) {
      if (d > k-1)
        return 0;
      auto v_res = 1;
      for (const auto u : g2[v]) {
        if (u != p) {
          v_res += dfs2(u, v, d+1);
        }
      }
      return v_res;
    };

    auto max_sz = 0;
    FOR(v, 0, m-1) {
      const auto sz = dfs2(v, -1, 0);
      max_sz = std::max(max_sz, sz);
    }

    for (auto& x : res1)
      x += max_sz;

    return res1;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi edges1{{0,1},{0,2},{2,3},{2,4}};
    const vvi edges2{{0,1},{0,2},{0,3},{2,7},{1,4},{4,5},{4,6}};
    const auto a_out = Solution().maxTargetNodes(edges1, edges2, 2);
    const vi e_out{9,7,9,8,8};
    assert(a_out == e_out);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi edges1{{0,1},{0,2},{0,3},{0,4}};
    const vvi edges2{{0,1},{1,2},{2,3}};
    const auto a_out = Solution().maxTargetNodes(edges1, edges2, 1);
    const vi e_out{6,3,3,3,3};
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
