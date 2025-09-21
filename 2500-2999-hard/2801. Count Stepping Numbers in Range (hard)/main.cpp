// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;

using ll = long long;

constexpr ll MOD = 1e9 + 7;

template <typename T>
T ModSum(T a, T b, T m) {
  a %= m;
  a = (a >= 0) ? a : a + m;
  b %= m;
  b = (b >= 0) ? b : b + m;
  auto c = (a + b) % m;
  c = (c >= 0) ? c : c + m;
  return c;
}

template <typename T>
T ModMult(T a, T b, T m) {
  a %= m;
  a = (a >= 0) ? a : a + m;
  b %= m;
  b = (b >= 0) ? b : b + m;
  auto c = (a * b) % m;
  c = (c >= 0) ? c : c + m;
  return c;
}

template <typename T>
[[maybe_unused]] T ModSub(T a, T b, T m) {
  a %= m;
  a = (a >= 0) ? a : a + m;
  b %= m;
  b = (b >= 0) ? b : b + m;
  auto c = (a - b) % m;
  c = (c >= 0) ? c : c + m;
  return c;
}

using DP = std::array<std::array<std::array<std::array<ll, 11>, 2>, 2>, 100>;
DP dp{};

ll Rec(int i, int n, const std::string& num, bool tight, bool leading, int prev) {
  if (i == n) return 1;
  if (dp[i][tight][leading][prev+1] != -1)
    return dp[i][tight][leading][prev+1];
  
  const auto up = tight ? num[i]-'0' : 9;
  ll res = 0;
  for (int d = 0; d <= up; ++d) {
    if (prev != -1 && !leading) {
      if (std::abs(prev-d) == 1) {
        const auto sub_res = Rec(i+1, n, num, tight&(d==up), leading&(d==0), d);
        res = ModSum(res, sub_res, MOD);
      }
    } else {
      const auto sub_res = Rec(i+1, n, num, tight&(d==up), leading&(d==0), d);
      res = ModSum(res, sub_res, MOD);
    }
  }
  dp[i][tight][leading][prev+1] = res;

  return res;
}

class Solution {
  public:
  static int countSteppingNumbers(const std::string& low, const std::string& high) {
    const auto low_n = static_cast<int>(low.size());
    memset(&dp, -1, sizeof(dp));
    const auto low_cnt = Rec(0, low_n, low, true, true, -1);

    const auto high_n = static_cast<int>(high.size());
    memset(&dp, -1, sizeof(dp));
    const auto high_cnt = Rec(0, high_n, high, true, true, -1);

    bool is_stepping = true;
    for (int i = 0; i+1 < low_n; ++i) {
      if (std::abs(low[i] - low[i+1]) != 1) {
        is_stepping = false;
        break;
      }
    }

    const auto res = ModSub(high_cnt, low_cnt-is_stepping, MOD);
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::string low{"1"s};
    const std::string high{"11"s};
    [[maybe_unused]] const auto a_out = Solution::countSteppingNumbers(low, high);
    assert(a_out == 10);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::string low{"90"s};
    const std::string high{"101"s};
    [[maybe_unused]] const auto a_out = Solution::countSteppingNumbers(low, high);
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
