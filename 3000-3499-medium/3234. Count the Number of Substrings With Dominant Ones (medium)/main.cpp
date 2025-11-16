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

class Solution {
public:
  int numberOfSubstrings(const std::string& s) {
    const auto n = SZ(s);
    vi pcnt0(n), pcnt1(n);
    vi pcnt0_idx(n + 1, n), pcnt1_idx(n + 1, n);
    FOR(i, 0, n-1) {
      pcnt0[i] = (s[i] == '0') + (i > 0 ? pcnt0[i - 1] : 0);
      pcnt1[i] = (s[i] == '1') + (i > 0 ? pcnt1[i - 1] : 0);
      pcnt0_idx[pcnt0[i]] = std::min(pcnt0_idx[pcnt0[i]], i);
      pcnt1_idx[pcnt1[i]] = std::min(pcnt1_idx[pcnt1[i]], i);
    }

    ll res = 0;
    FOR(i, 0, n-1) {
      const auto p0 = i > 0 ? pcnt0[i - 1] : 0;
      const auto p1 = i > 0 ? pcnt1[i - 1] : 0;
      for (auto c0 = 0; c0 + c0 * c0 <= n - i; ++c0) {
        if (p0 + c0 > n) break;
        // p0 + c0 <= n
        const auto i0 = c0 > 0 ? pcnt0_idx[p0 + c0] : i - 1;
        if (i0 >= n) break;
        // i0 < n
        const auto j0 = p0 + c0 + 1 <= n ? pcnt0_idx[p0 + c0 + 1] : n;
        // j0 <= n
        const auto c1 = c0 ? c0 * c0 : 1;
        const auto i1 = p1 + c1 <= n ? pcnt1_idx[p1 + c1] : n;
        if (i1 >= n) break;
        if (i1 >= j0) continue;
        const auto l = std::max(i0, i1);
        res += j0 - l;
      }
    }
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::string s("00011"s);
    const auto a_out = Solution().numberOfSubstrings(s);
    assert(a_out == 5);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::string s("101101"s);
    const auto a_out = Solution().numberOfSubstrings(s);
    assert(a_out == 16);
  
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
