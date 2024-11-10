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

constexpr int MAX_N = 50;
std::array<std::array<ll, MAX_N>, MAX_N> dist;

struct QItem {
  int i, j;
  ll d;
  bool operator>(const QItem& other) const {
    return d > other.d;
  }
};

class Solution {
public:
  int minTimeToReach(const vvi& g) {
    const auto n = SZ(g), m = SZ(g[0]);
    std::fill(&dist[0][0], &dist[0][0] + sizeof(dist) / sizeof(dist[0][0]), LLONG_MAX);
    std::priority_queue<QItem, std::vector<QItem>, std::greater<>> pq;
    pq.push({0,0,0});
    while (!pq.empty()) {
      const auto i = pq.top().i, j = pq.top().j;
      const auto d = pq.top().d;
      pq.pop();
      if (d >= dist[i][j])
        continue;
      dist[i][j] = d;
      for (const auto& [ni, nj] : vii{{i+1, j}, {i-1, j}, {i, j+1}, {i, j-1}}) {
        if (0 <= ni && ni < n && 0 <= nj && nj < m) {
          const auto nd = (d >= g[ni][nj]) ? d + 1 : g[ni][nj] + 1;
          if (nd < dist[ni][nj])
            pq.push({ni, nj, nd});
        }
      }
    }
    return dist[n-1][m-1];
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi g{{0,4},{4,4}};
    const auto a_out = Solution().minTimeToReach(g);
    assert(a_out == 6);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi g{{0,0,0},{0,0,0}};
    const auto a_out = Solution().minTimeToReach(g);
    assert(a_out == 3);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi g{{0,1},{1,2}};
    const auto a_out = Solution().minTimeToReach(g);
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
