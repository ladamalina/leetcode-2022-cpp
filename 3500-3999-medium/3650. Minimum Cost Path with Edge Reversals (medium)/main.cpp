// #pragma GCC optimize("O3,unroll-loops")
// #include <bits/stdc++.h>

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <cfloat>
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
#include <numbers>
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
using ii = std::pair<int, int>;
using vi = std::vector<int>;
using vvi = std::vector<vi>;
using vvvi = std::vector<vvi>;
using vl = std::vector<ll>;
using vvl = std::vector<vl>;
using vvvl = std::vector<vvl>;
using vii = std::vector<ii>;
using vb = std::vector<bool>;
using vd = std::vector<ld>;
using vs = std::vector<std::string>;
using vc = std::vector<char>;

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

constexpr int MAX_N = 5e4;
std::array<vii, MAX_N> g;
std::array<int, MAX_N> dist;

class Solution {
public:
  int minCost(int n, const vvi& edges) {
    std::fill(g.begin(), g.begin() + n, vii{});
    std::fill(dist.begin(), dist.begin() + n, INT_MAX);
    for (const auto& e : edges) {
      const auto u = e[0], v = e[1], w = e[2];
      g[u].emplace_back(v, w);
      g[v].emplace_back(u, w << 1);
    }
    std::priority_queue<ii, vii, std::greater<>> pq;
    dist[0] = 0;
    pq.emplace(0, 0);
    while (!pq.empty()) {
      const auto [d, u] = pq.top();
      pq.pop();
      if (d > dist[u]) continue;
      if (u == n-1) break;
      for (const auto& [v, w] : g[u]) {
        if (d + w < dist[v]) {
          dist[v] = d + w;
          pq.emplace(dist[v], v);
        }
      }
    }
    return dist[n-1] == INT_MAX ? -1 : dist[n-1];
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
