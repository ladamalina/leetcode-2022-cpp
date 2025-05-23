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
  int stoneGameV(const vi& stones) {
    const auto n = SZ(stones);
    vi psum(n);
    FOR(i, 0, n-1) psum[i] = stones[i] + (i > 0 ? psum[i-1] : 0);

    vvi dp(n, vi(n, -1));
    const std::function<int(int,int)> rec = [&](const int l, const int r) {
      if (l == r)
        return 0;
      if (dp[l][r] != -1)
        return dp[l][r];

      FOR(m, l, r-1) {
        const auto l_sum = psum[m] - (l > 0 ? psum[l-1] : 0);
        const auto r_sum = psum[r] - psum[m];
        if (l_sum < r_sum) {
          dp[l][r] = std::max(dp[l][r], l_sum + rec(l, m));
        } else if (l_sum > r_sum) {
          dp[l][r] = std::max(dp[l][r], r_sum + rec(m+1, r));
        } else { // ==
          dp[l][r] = std::max(dp[l][r], l_sum + std::max(rec(l, m), rec(m+1, r)));
        }
      }

      return dp[l][r];
    };
    const auto res = rec(0, n-1);
    
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi stones{6,2,3,4,5,5};
    const auto a_out = Solution().stoneGameV(stones);
    assert(a_out == 18);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi stones{7,7,7,7,7,7,7};
    const auto a_out = Solution().stoneGameV(stones);
    assert(a_out == 28);
  
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
