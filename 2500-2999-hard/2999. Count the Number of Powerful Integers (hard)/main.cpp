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

ll CountLTE(ll hi, int limit, const std::string& s) {
  const auto hi_str = std::to_string(hi);
  const auto n = SZ(hi_str), sn = SZ(s);
  if (n < sn) return 0;
  // n >= sn
  const auto si_beg = n - sn;
  vvl dp(n, vl(2, -1));
  const std::function<ll(int,int)> rec = [&](int i, int lo) {
    if (i == n) return 1ll;
    if (dp[i][lo] != -1)
      return dp[i][lo];
    dp[i][lo] = 0;
    const auto hi_d = hi_str[i] - '0';
    const auto max_d = lo ? limit : std::min(limit, hi_d);
    if (i >= si_beg) {
      const auto si = i - si_beg;
      const auto si_d = s[si] - '0';
      if (si_d > max_d)
        return 0ll;
      dp[i][lo] += rec(i+1, lo || si_d < hi_d);
    } else {
      FOR(d, 0, max_d) {
        dp[i][lo] += rec(i+1, lo || d < hi_d);
      }
    }
    return dp[i][lo];
  };
  const auto res = rec(0, 0);
  return res;
}

class Solution {
public:
  ll numberOfPowerfulInt(ll start, ll finish, int limit, const std::string& s) {
    const auto lte_hi = CountLTE(finish, limit, s);
    const auto lte_lo = CountLTE(start, limit, s);

    const auto lo_str = std::to_string(start);
    bool lo_is_pow = std::all_of(RNG(lo_str), [&](const char c) { return c-'0' <= limit; });
    int i1 = SZ(lo_str)-1, i2 = SZ(s)-1;
    while (i1 >= 0 && i2 >= 0) {
      if (lo_str[i1] == s[i2]) {
        --i1; --i2;
      } else {
        lo_is_pow = false;
        break;
      }
    }
    lo_is_pow &= (i2 < 0);

    return lo_is_pow ? (lte_hi - lte_lo + 1) : (lte_hi - lte_lo);
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto a_out = Solution().numberOfPowerfulInt(63935267123ll, 334359420935946ll, 6, "3"s);
    assert(a_out == 340924566339ll);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().numberOfPowerfulInt(1, 971, 9, "41"s);
    assert(a_out == 10);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto a_out = Solution().numberOfPowerfulInt(15, 215, 6, "10"s);
    assert(a_out == 2);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto a_out = Solution().numberOfPowerfulInt(1, 6000, 4, "124"s);
    assert(a_out == 5);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto a_out = Solution().numberOfPowerfulInt(1000, 2000, 4, "3000"s);
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
