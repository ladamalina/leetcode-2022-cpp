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

struct QItem {
  int i, j, d;
  bool operator<(const QItem& other) const {
    return d < other.d;
  }
  bool operator>(const QItem& other) const {
    return d > other.d;
  }
};

constexpr std::array<ii, 4> DIRS{ii{1,0}, ii{0,1}, ii{-1,0}, ii{0,-1}};

class Solution {
public:
  int minimumObstacles(const vvi& g) {
    const auto n = SZ(g), m = SZ(g[0]);
    vvi dist(n, vi(m, INT_MAX));
    std::priority_queue<QItem, std::vector<QItem>, std::greater<>> pq;
    pq.push({0, 0, 0});
    while (!pq.empty()) {
      const auto i = pq.top().i, j = pq.top().j, d = pq.top().d;
      pq.pop();
      if (d >= dist[i][j])
        continue;
      dist[i][j] = d;
      
      for (const auto& dir : DIRS) {
        const auto ui = i + dir.F, uj = j + dir.S;
        if (ui >= 0 && ui < n && uj >= 0 && uj < m) {
          const auto ud = d + (g[ui][uj] == 1);
          if (ud < dist[ui][uj])
            pq.push({ui, uj, ud});
        }
      }
    }
    return dist[n-1][m-1];
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi g{{0,1,1},{1,1,0},{1,1,0}};
    const auto a_out = Solution().minimumObstacles(g);
    assert(a_out == 2);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi g{{0,1,0,0,0},{0,1,0,1,0},{0,0,0,1,0}};
    const auto a_out = Solution().minimumObstacles(g);
    assert(a_out == 0);
  
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
