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

constexpr int MAX_N = 1e5;
vi vis(MAX_N);
vvi col_max(26, vi(MAX_N));

bool DFS(int u, const vvi& g, const std::string& colors, int& max_res) {
  if (vis[u] == 1) return true;
  if (vis[u] == 2) return false;
  vis[u] = 1;
  col_max[colors[u] - 'a'][u] = 1;
  for (const auto v : g[u]) {
    if (DFS(v, g, colors, max_res))
      return true;
    FOR(i, 0, 25) col_max[i][u] = std::max(col_max[i][u], col_max[i][v] + (colors[u] - 'a' == i));
  }
  FOR(i, 0, 25) max_res = std::max(max_res, col_max[i][u]);
  vis[u] = 2;
  return false;
}

class Solution {
public:
  int largestPathValue(const std::string& colors, const vvi& edges) {
    const auto n = SZ(colors);
    vvi g(n);
    for (const auto& e : edges)
      g[e[0]].PB(e[1]);

    std::fill(vis.begin(), vis.begin() + n, 0);
    FOR(i, 0, 25) std::fill(col_max[i].begin(), col_max[i].begin() + n, 0);

    auto max_res = 0;
    FOR(u, 0, n-1) {
      if (DFS(u, g, colors, max_res)) return -1;
    }
    return max_res;
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
