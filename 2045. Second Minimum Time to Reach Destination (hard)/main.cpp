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
  int secondMinimum(int n, const vvi& edges, int edge_t, int change_t) {
    vvi g(n+1);
    for (const auto& e : edges) {
      g[e[0]].push_back(e[1]);
      g[e[1]].push_back(e[0]);
    }
    std::queue<ii> q; // <v, t>
    q.emplace(1, 0);
    vii dist(n+1, {INT_MAX, INT_MAX});
    dist[1].F = 0;
    while (!q.empty()) {
      const auto v = q.front().F;
      const auto d = q.front().S;
      q.pop();

      for (const auto u : g[v]) {
        if (d+1 < dist[u].F) {
          dist[u].S = dist[u].F;
          dist[u].F = d+1;
          q.emplace(u, dist[u].F);
        } else if (dist[u].F < d+1 && d+1 < dist[u].S) {
          dist[u].S = d+1;
          q.emplace(u, dist[u].S);
        }
      }
    }

    auto total_t = 0;
    FOR(i, 0, dist[n].S-1) {
      total_t += edge_t;
      if (i < dist[n].S-1 && (total_t/change_t)%2 == 1) {
        total_t += change_t - (total_t % change_t);
      }
    }
    return total_t;
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
