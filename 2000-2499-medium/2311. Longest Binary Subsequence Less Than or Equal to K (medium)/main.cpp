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
using ld = long double;
using ii [[maybe_unused]] = std::pair<int, int>;
using vi [[maybe_unused]] = std::vector<int>;
using vl [[maybe_unused]] = std::vector<ll>;
using vvi [[maybe_unused]] = std::vector<vi>;
using vvvi [[maybe_unused]] = std::vector<vvi>;
using vvl [[maybe_unused]] = std::vector<vl>;
using vii [[maybe_unused]] = std::vector<ii>;
using vb [[maybe_unused]] = std::vector<bool>;
using vd [[maybe_unused]] = std::vector<double>;
using vs [[maybe_unused]] = std::vector<std::string>;
using vc [[maybe_unused]] = std::vector<char>;

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
#define PB push_back

int Rec(int si, int ki, int tight, const std::string& s, const std::string& k, vvvi& dp) {
  if (si >= SZ(s) || ki >= SZ(k))
    return 0;
  // si < sn && ki < kn

  auto& max_res = dp[tight][ki][si];
  if (max_res != -1)
    return max_res;

  // take leading zero
  if (ki == 0 && s[si] == '0') {
    max_res = std::max(max_res, 1 + Rec(si + 1, ki, tight, s, k, dp));
  }

  // take
  if (k[ki] == s[si]) {
    max_res = std::max(max_res, 1 + Rec(si + 1, ki + 1, tight, s, k, dp));
  } else if (k[ki] == '0' && s[si] == '1') {
    if (!tight) {
      max_res = std::max(max_res, 1 + Rec(si + 1, ki + 1, tight, s, k, dp));
    }
  } else if (k[ki] == '1' && s[si] == '0') {
    max_res = std::max(max_res, 1 + Rec(si + 1, ki + 1, false, s, k, dp));
  }

  // skip
  max_res = std::max(max_res, Rec(si + 1, ki, tight, s, k, dp));

  return max_res;
}

class Solution {
public:
  int longestSubsequence(const std::string& s, int k) {
    const auto sn = SZ(s);

    int k_msb = 0;
    while ((1ll << (k_msb + 1)) <= k)
      ++k_msb;

    const auto kn = k_msb + 1;
    std::string k_str(kn, '0');
    FORD(b, k_msb, 0) {
      if (k & (1 << b)) k_str[k_msb - b] = '1';
    }

    auto max_res = 0, c0 = 0;
    FOR(si, 0, sn-1) {
      const auto tail = sn - si;
      if (tail < kn) {
        max_res = std::max(max_res, c0 + tail);
      }
      c0 += (s[si] == '0');
    }

    vvvi dp(2, vvi(kn, vi(sn, -1)));
    const auto res = Rec(0, 0, true, s, k_str, dp);
    max_res = std::max(max_res, res);
    return max_res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::string s = "111100010000011101001110001111000000001011101111111110111000011111011000010101110100110110001111001001011001010011010000011111101001101000000101101001110110000111101011000101";
    const auto a_out = Solution().longestSubsequence(s, 11713332);
    assert(a_out == 96);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::string s = "1011";
    const auto a_out = Solution().longestSubsequence(s, 281854076);
    assert(a_out == 4);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::string s = "1001010";
    const auto a_out = Solution().longestSubsequence(s, 5);
    assert(a_out == 5);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::string s = "00101001";
    const auto a_out = Solution().longestSubsequence(s, 1);
    assert(a_out == 6);
  
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
