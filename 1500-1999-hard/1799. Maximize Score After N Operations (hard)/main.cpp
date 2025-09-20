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

template <typename T>
T GCD(T a, T b) {
  while (a > 0 && b > 0) {
    if (a > b) { a = a % b; } else { b = b % a; }
  }
  return (a == 0) ? b : a;
}

class Solution {
public:
  int maxScore(const vi& nums) {
    const auto n = SZ(nums);
    std::vector<std::pair<int,ii>> q;
    FOR(i, 0, n-1) {
      FOR(j, i+1, n-1) {
        q.emplace_back(GCD(nums[i], nums[j]), ii{i, j});
      }
    }
    std::sort(q.rbegin(), q.rend());
    const auto qn = SZ(q);

    vvi dp(qn, vi((1 << n), -1));
    const std::function<int(int,int,int)> rec = [&](int qi, int mask, int ops) {
      if (qi == qn || ops == 0)
        return 0;
      if (dp[qi][mask] != -1)
        return dp[qi][mask];

      auto max_res = 0;
      const auto gcd = q[qi].F, i = q[qi].S.F, j = q[qi].S.S;
      if ((mask & (1 << i)) == 0 && (mask & (1 << j)) == 0) { // possible to take
        max_res = std::max(max_res, gcd*ops + rec(qi + 1, mask|(1<<i)|(1<<j), ops-1));
      }
      // skip
      max_res = std::max(max_res, rec(qi+1, mask, ops));

      return dp[qi][mask] = max_res;
    };
    return rec(0, 0, n/2);
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums{773274,313112,131789,222437,918065,49745,321270,74163,900218,80160,325440,961730};
    const auto a_out = Solution().maxScore(nums);
    assert(a_out == 3032);
  
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
