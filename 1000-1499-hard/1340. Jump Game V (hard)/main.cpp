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
  int maxJumps(const vi& arr, const int d) {
    const auto n = SZ(arr);
    
    vii arr_sorted(n);
    FOR(i, 0, n-1) arr_sorted[i] = {arr[i], i};
    SORT(arr_sorted);

    vi dp(n, 1);
    FOR(si, 0, n-1) {
      const auto j = arr_sorted[si].S;
      const auto min_i = std::max(j-d, 0), max_i = std::min(j+d, n-1);

      auto max_lh = 0;
      FORD(i, j-1, min_i) {
        if (arr[i] > arr[j] && arr[i] > max_lh)
          dp[i] = std::max(dp[i], dp[j] + 1);
        max_lh = std::max(max_lh, arr[i]);
      }

      auto max_rh = 0;
      FOR(i, j+1, max_i) {
        if (arr[i] > arr[j] && arr[i] > max_rh)
          dp[i] = std::max(dp[i], dp[j] + 1);
        max_rh = std::max(max_rh, arr[i]);
      }
    }

    const auto max_res = *std::max_element(RNG(dp));
    return max_res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi arr{6,4,14,6,8,13,9,7,10,6,12};
    const auto a_out = Solution().maxJumps(arr, 2);
    assert(a_out == 4);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi arr{3,3,3,3,3};
    const auto a_out = Solution().maxJumps(arr, 3);
    assert(a_out == 1);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi arr{7,6,5,4,3,2,1};
    const auto a_out = Solution().maxJumps(arr, 1);
    assert(a_out == 7);
  
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
