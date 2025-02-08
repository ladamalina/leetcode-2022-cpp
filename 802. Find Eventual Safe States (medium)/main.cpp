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

constexpr int MAX_N = 1e4;
std::array<int, MAX_N> vis, safe;

class Solution {
public:
  vi eventualSafeNodes(const vvi& g) {
    const auto n = SZ(g);
    std::fill(vis.begin(), vis.begin()+n, 0);
    std::fill(safe.begin(), safe.begin()+n, 1);

    const std::function<bool(int)> dfs = [&](const int v) {
      if (vis[v] == 2)
        return safe[v] == 1;
      if (vis[v] == 1)
        return false;
      vis[v] = 1;
      for (const auto u : g[v])
        safe[v] &= dfs(u);
      vis[v] = 2;
      return safe[v] == 1;
    };

    FOR(v, 0, n-1) {
      if (vis[v] == 0) {
        dfs(v);
      }
    }

    vi res;
    res.reserve(n);
    FOR(v, 0, n-1) {
      if (safe[v])
        res.push_back(v);
    }

    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi g{{1,2},{2,3},{5},{0},{5},{},{}};
    const vi e_out{2,4,5,6};
    const auto a_out = Solution().eventualSafeNodes(g);
    assert(a_out == e_out);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi g{{1,2,3,4},{1,2},{3,4},{0,4},{}};
    const vi e_out{4};
    const auto a_out = Solution().eventualSafeNodes(g);
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
