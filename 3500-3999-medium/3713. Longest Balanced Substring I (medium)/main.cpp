// #pragma GCC optimize("O3,unroll-loops")
// #include <bits/stdc++.h>

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <cfloat>
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
#include <numbers>
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
using ld = long double;
using ii = std::pair<int, int>;
using vi = std::vector<int>;
using vvi = std::vector<vi>;
using vvvi = std::vector<vvi>;
using vl = std::vector<ll>;
using vvl = std::vector<vl>;
using vvvl = std::vector<vvl>;
using vii = std::vector<ii>;
using vb = std::vector<bool>;
using vd = std::vector<ld>;
using vs = std::vector<std::string>;
using vc = std::vector<char>;

#define FOR(_i, _a, _b) for (auto _i = (_a); _i <= (_b); ++(_i))
#define FORD(_i, _a, _b) for (auto _i = (_a); _i >= (_b); --(_i))
#define RNG(_l) (_l).begin(), (_l).end()
#define SORT(_l) std::sort((_l).begin(), (_l).end())
#define CI(_v) static_cast<int>(_v)
#define CL(_v) static_cast<ll>(_v)
#define CD(_v) static_cast<ld>(_v)
#define CC(_v) static_cast<char>(_v)
#define SZ(_v) static_cast<int>((_v).size())
#define F first
#define S second

constexpr int MAX_N = 1000;

using Freq = std::array<int, 26>;
std::array<Freq, MAX_N> pfreq;

bool IsGood(const int l, const int r) {
  auto p = -1;
  FOR(j, 0, 25) {
    const auto f = pfreq[r][j] - (l ? pfreq[l-1][j] : 0);
    if (f > 0) {
      if (p == -1) p = f;
      else if (p != f) return false;
    }
  }
  return true;
}

class Solution {
 public:
  int longestBalanced(const std::string& s) {
    const auto n = SZ(s);
    FOR(i, 0, n-1) {
      FOR(j, 0, 25) {
        pfreq[i][j] = (s[i] - 'a' == j) + (i ? pfreq[i-1][j] : 0);
      }
    }
    auto max_res = 0;
    FOR(l, 0, n-1) {
      FORD(r, n-1, l) {
        if (IsGood(l, r)) {
          max_res = std::max(max_res, r - l + 1);
          break;
        }
      }
    }
    return max_res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    std::string s("abbac"s);
    const auto a_out = Solution().longestBalanced(s);
    assert(a_out == 4);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    std::string s("zzabccy"s);
    const auto a_out = Solution().longestBalanced(s);
    assert(a_out == 4);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    std::string s("aba"s);
    const auto a_out = Solution().longestBalanced(s);
    assert(a_out == 2);
  
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
