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
  int stoneGameVII(const vi& stones) {
    const auto n = SZ(stones);
    vi psum(n);
    FOR(i, 0, n-1) psum[i] = stones[i] + (i > 0 ? psum[i-1] : 0);
    
    vvi dp(n, vi(n, -1));
    const std::function<int(int,int,bool)> rec = [&](const int l, const int r, const bool a_turn) {
      if (l == r)
        return 0;
      if (dp[l][r] != -1)
        return dp[l][r];

      const auto lr_sum = psum[r] - (l > 0 ? psum[l-1] : 0);
      const auto l_sub_res = rec(l+1, r, !a_turn);
      const auto r_sub_res = rec(l, r-1, !a_turn);
      if (a_turn) {
        const auto l_res = l_sub_res + (lr_sum - stones[l]);
        const auto r_res = r_sub_res + (lr_sum - stones[r]);
        dp[l][r] = std::max(l_res, r_res);
      } else {
        const auto l_res = l_sub_res - (lr_sum - stones[l]);
        const auto r_res = r_sub_res - (lr_sum - stones[r]);
        dp[l][r] = std::min(l_res, r_res);
      }

      return dp[l][r];
    };
    const auto res = rec(0, n-1, true);
    
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi stones{5,3,1,4,2};
    const auto a_out = Solution().stoneGameVII(stones);
    assert(a_out == 6);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi stones{7,90,5,1,100,10,10,2};
    const auto a_out = Solution().stoneGameVII(stones);
    assert(a_out == 122);
  
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
