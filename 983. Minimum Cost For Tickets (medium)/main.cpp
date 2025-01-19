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

class Solution {
public:
  int mincostTickets(const vi& days, const vi& costs) {
    const auto n = SZ(days);
    vi dp(n, INT_MAX);
    const std::function<int(int)> rec = [&](int i) {
      if (i == n)
        return 0;
      if (dp[i] != INT_MAX)
        return dp[i];
      // buy 1
      dp[i] = std::min(dp[i], costs[0] + rec(i+1));
      // buy 7
      const auto j7 = CI(std::upper_bound(days.begin()+i+1, days.end(), days[i]+6) - days.begin());
      dp[i] = std::min(dp[i], costs[1] + rec(j7));
      // buy 30
      const auto j30 = CI(std::upper_bound(days.begin()+i+1, days.end(), days[i]+29) - days.begin());
      dp[i] = std::min(dp[i], costs[2] + rec(j30));

      return dp[i];
    };
    const auto res = rec(0);
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi days{1,4,6,7,8,20};
    const vi costs{2,7,15};
    const auto a_out = Solution().mincostTickets(days, costs);
    assert(a_out == 11);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi days{1,2,3,4,5,6,7,8,9,10,30,31};
    const vi costs{2,7,15};
    const auto a_out = Solution().mincostTickets(days, costs);
    assert(a_out == 17);
  
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
