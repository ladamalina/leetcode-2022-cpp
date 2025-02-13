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

constexpr int MAX_N = 3 * 1e4;
std::array<vi, MAX_N> g;
std::array<int, MAX_N> sub_mod;

void DFS(const int v, const int p, const vi& values, const int k, int& res) {
  sub_mod[v] = (sub_mod[v] + values[v]) % k;
  for (const auto u : g[v]) {
    if (u != p) {
      DFS(u, v, values, k, res);
      sub_mod[v] = (sub_mod[v] + sub_mod[u]) % k;
      res += (sub_mod[u] == 0);
    }
  }
}

class Solution {
public:
  int maxKDivisibleComponents(const int n, const vvi& edges, const vi& values, const int k) {
    std::fill(g.begin(), g.begin() + n, vi{});
    std::fill(sub_mod.begin(), sub_mod.begin() + n, 0);

    for (const auto& e : edges) {
      g[e[0]].push_back(e[1]);
      g[e[1]].push_back(e[0]);
    }
    
    auto res = 1;
    DFS(0, -1, values, k, res);
    
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi edges{{0,2},{1,2},{1,3},{2,4}};
    const vi values{1,8,1,4,4};
    const auto a_out = Solution().maxKDivisibleComponents(5, edges, values, 6);
    assert(a_out == 2);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi edges{{0,1},{0,2},{1,3},{1,4},{2,5},{2,6}};
    const vi values{3,0,6,1,5,2,1};
    const auto a_out = Solution().maxKDivisibleComponents(7, edges, values, 3);
    assert(a_out == 3);
  
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
