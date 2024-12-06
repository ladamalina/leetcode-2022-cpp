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

constexpr ll MOD = 998'244'353;
constexpr int MAX_N = 1000;
constexpr ll X1 = 37, X2 = 43;
std::array<ll, MAX_N> x1_pow, x2_pow;

template <typename T>
[[maybe_unused]] T ModSum(T a, T b, T m) {
  a %= m;
  a = (a >= 0) ? a : a + m;
  b %= m;
  b = (b >= 0) ? b : b + m;
  auto c = (a + b) % m;
  return (c >= 0) ? c : c + m;
}

template <typename T>
[[maybe_unused]] T ModMult(T a, T b, T m) {
  a %= m;
  a = (a >= 0) ? a : a + m;
  b %= m;
  b = (b >= 0) ? b : b + m;
  auto c = (a * b) % m;
  return (c >= 0) ? c : c + m;
}

void InitXPow(std::array<ll, MAX_N>& x_pow, ll x) {
  x_pow[0] = 1;
  for (int i = 1; i < MAX_N; ++i) {
    x_pow[i] = (x_pow[i-1] * x) % MOD;
  }
}
bool init_x_pow = false;

std::array<ll, MAX_N> s_hash1, s_hash2;

void CalcHash(std::array<ll, MAX_N>& h, const std::string& s, ll x) {
  const auto n = CI(s.size());
  h[0] = s[0]-'a'+1;
  for (auto i = 1; i < n; ++i) {
    h[i] = ModSum((h[i-1] * x) % MOD, CL(s[i]-'a'+1), MOD);
  }
}

bool Eq(const std::array<ll, MAX_N>& hs, const std::array<ll, MAX_N>& ht, int si, int ti, int len,
    const std::array<ll, MAX_N>& x_pow) {
  const auto s_end = si + len - 1;
  const auto t_end = ti + len - 1;

  const auto s_tail = hs[s_end];
  const auto t_tail = ht[t_end];

  const auto s_pref = (si > 0) ? ModMult(hs[si-1], x_pow[len], MOD) : 0;
  const auto t_pref = (ti > 0) ? ModMult(ht[ti-1], x_pow[len], MOD) : 0;

  // s_tail - s_pref == t_tail - t_pref
  return ModSum(s_tail, t_pref, MOD) == ModSum(t_tail, s_pref, MOD);
}

std::array<int, MAX_N> dp;

class Solution {
public:
  int Rec(const int l, const int r) {
    if (l == r)
      return 1;
    if (l == r + 1)
      return 0;
    if (dp[l] != -1)
      return dp[l];
    const auto min_len = 1, max_len = (r - l + 1) / 2;
    auto max_res = 1;
    FOR(len, min_len, max_len) {
      if (Eq(s_hash1, s_hash1, l, r-len+1, len, x1_pow)
        && Eq(s_hash2, s_hash2, l, r-len+1, len, x2_pow)) {
        max_res = std::max(max_res, 2 + Rec(l+len, r-len));
      }
    }

    return dp[l] = max_res;
  }
  
  int longestDecomposition(const std::string& s) {
    if (!init_x_pow) {
      InitXPow(x1_pow, X1);
      InitXPow(x2_pow, X2);
      init_x_pow = true;
    }

    CalcHash(s_hash1, s, X1);
    CalcHash(s_hash2, s, X2);

    std::fill(dp.begin(), dp.begin() + SZ(s), -1);
    return Rec(0, SZ(s)-1);
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::string s("ghiabcdefhelloadamhelloabcdefghi");
    const auto a_out = Solution().longestDecomposition(s);
    assert(a_out == 7);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::string s("merchant");
    const auto a_out = Solution().longestDecomposition(s);
    assert(a_out == 1);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::string s("antaprezatepzapreanta");
    const auto a_out = Solution().longestDecomposition(s);
    assert(a_out == 11);
  
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
