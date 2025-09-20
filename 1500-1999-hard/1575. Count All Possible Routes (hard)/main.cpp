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

constexpr ll MOD = 1e9 + 7;

class Solution {
public:
  int countRoutes(vi& locations, int start, int finish, const int fuel) {
    const auto n = SZ(locations);
    const auto start_loc = locations[start], finish_loc = locations[finish];
    SORT(locations);
    start = CI(std::lower_bound(RNG(locations), start_loc) - locations.begin());
    finish = CI(std::lower_bound(RNG(locations), finish_loc) - locations.begin());
    
    vvl dp(n, vl(fuel+1, -1));
    const std::function<ll(int,int)> rec = [&](const int i, const int f) {
      if (dp[i][f] != -1)
        return dp[i][f];
      ll i_res = (i == finish);
      const auto lo_it = std::lower_bound(RNG(locations), locations[i] - f),
        up_it = std::upper_bound(RNG(locations), locations[i] + f);
      for (auto it = lo_it; it != up_it; ++it) {
        const auto j = CI(it - locations.begin());
        if (j != i) {
          const auto sub_res = rec(j, f - std::abs(locations[i] - locations[j]));
          i_res = (i_res + sub_res) % MOD;
        }
      }
      dp[i][f] = i_res;
      return i_res;
    };
    const auto res = rec(start, fuel);

    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi locations{2,3,6,8,4};
    const auto a_out = Solution().countRoutes(locations, 1, 3, 5);
    assert(a_out == 4);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi locations{4,3,1};
    const auto a_out = Solution().countRoutes(locations, 1, 0, 6);
    assert(a_out == 5);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi locations{5,2,1};
    const auto a_out = Solution().countRoutes(locations, 0, 2, 3);
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
