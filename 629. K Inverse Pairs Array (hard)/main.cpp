// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;

using ll = long long;

[[maybe_unused]] constexpr ll MOD = 1e9 + 7;

template <typename T>
[[maybe_unused]] T ModSum(T a, T b, T m) {
  a %= m;
  a = (a >= 0) ? a : a + m;
  b %= m;
  b = (b >= 0) ? b : b + m;
  auto c = (a + b) % m;
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

template <typename T>
[[maybe_unused]] T ModMult(T a, T b, T m) {
  a %= m;
  a = (a >= 0) ? a : a + m;
  b %= m;
  b = (b >= 0) ? b : b + m;
  auto c = (a * b) % m;
  c = (c >= 0) ? c : c + m;
  return c;
}

int dp[1001][1001];

class Solution {
 public:
  static int kInversePairs(int n, int k) {
    memset(&dp, 0, sizeof(dp));
    for (int i = 1; i <= n; ++i) {
      for (int j = 0; j <= k; ++j) {
        if (j == 0) {
          dp[i][j] = 1;
        } else {
          const ll prev = dp[i-1][j]; // Count of arrays with (i - 1) elements and j inverse pairs

          // Count of arrays with (i - 1) elements and (j - i) inverse pairs
          const ll sub = (j-i >= 0) ? dp[i-1][j-i] : 0;

          // Adjusted count to consider negative values
          const ll adj = ModSub(prev, sub, MOD);
          
          dp[i][j] = ModSum(ll(dp[i][j-1]), adj, MOD);
        }
      }
    }
    const auto res = (k > 0) ? ModSub(ll(dp[n][k]), ll(dp[n][k-1]), MOD) : dp[n][k];
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto a_out = Solution::kInversePairs(3, 0);
    assert(a_out == 1);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto a_out = Solution::kInversePairs(3, 1);
    assert(a_out == 2);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto a_out = Solution::kInversePairs(3, 2);
    assert(a_out == 2);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto a_out = Solution::kInversePairs(10, 1);
    assert(a_out == 9);

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
