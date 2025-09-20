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
using ull = unsigned long long;
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

[[maybe_unused]] constexpr ull MOD = 1e9 + 7;

constexpr int MAX_N = 1e5;
std::array<int, MAX_N> sorted;

class Solution {
public:
  int maxPerformance(int n, const vi& vel, const vi& eff, int k) {
    std::iota(sorted.begin(), sorted.begin() + n, 0);
    std::sort(sorted.begin(), sorted.begin() + n, [&](const int a, const int b) {
      return std::tie(eff[a], vel[a]) > std::tie(eff[b], vel[b]);
    });

    std::priority_queue<int, vi, std::greater<>> pq;
    pq.emplace(vel[sorted[0]]);
    ull sum_vel = vel[sorted[0]];
    ull max_res = sum_vel * eff[sorted[0]];
    FOR(si, 1, n-1) { // eff[sorted[si]] – minimum current efficiency
      const auto i = sorted[si];
      pq.emplace(vel[i]);
      sum_vel += vel[i];
      if (SZ(pq) > k) {
        sum_vel -= pq.top();
        pq.pop();
      }
      max_res = std::max(max_res, sum_vel * eff[i]);
    }

    return max_res % MOD;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi vel{2,10,3,1,5,8};
    const vi eff{5,4,3,9,7,2};
    const auto a_out = Solution().maxPerformance(6, vel, eff, 2);
    assert(a_out == 60);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi vel{2,10,3,1,5,8};
    const vi eff{5,4,3,9,7,2};
    const auto a_out = Solution().maxPerformance(6, vel, eff, 3);
    assert(a_out == 68);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi vel{2,10,3,1,5,8};
    const vi eff{5,4,3,9,7,2};
    const auto a_out = Solution().maxPerformance(6, vel, eff, 4);
    assert(a_out == 72);
  
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
