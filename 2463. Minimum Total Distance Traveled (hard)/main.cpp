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
  ll minimumTotalDistance(vi& robots, vvi& factories) {
    const auto m = SZ(robots);
    const auto n = SZ(factories);

    SORT(robots);
    SORT(factories);

    std::vector<vl> dp(m+1, vl(n+1)); // dp[i][j]: minimum total distance for robots[i:] using factories[j:]
    // Base case: if no factories are available, distance is infinity
    FOR(i, 0, m-1) {
      dp[i][n] = LLONG_MAX;
    }

    // Process each factory from right to left
    FORD(j, n-1, 0) {
      ll prefix = 0; // Cumulative distance from current factory to robots
      std::deque<std::pair<int, ll>> q; // <robot index, minimum distance>
      q.emplace_back(m, 0);

      // Process each robot from right to left
      FORD(i, m-1, 0) {
        prefix += std::abs(robots[i] - factories[j][0]); // Add distance from current robot to current factory

        while (!q.empty() && q.front().F > i + factories[j][1]) { // Remove entries that exceed factory capacity
          q.pop_front();
        }

        while (!q.empty() && q.back().S >= dp[i][j + 1] - prefix) { // Maintain monotonic property of deque
          q.pop_back();
        }

        q.emplace_back(i, dp[i][j + 1] - prefix); // Add current state to deque
        dp[i][j] = q.front().S + prefix; // Calculate minimum distance for current state
      }
    }

    return dp[0][0];
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
