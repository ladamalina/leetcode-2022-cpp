//#pragma GCC optimize("O3")
//#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;

using ll = long long;

constexpr ll m = 1e9+7;

/**
 * dp[j][k] – number of possible records
 * j – character at pos i (0=A, 1=1L in a row, 2=2L in a row, 3=P)
 * k – has A up to i pos inclusive
 */
ll dp[4][2];
ll dp2[4][2];

class Solution {
  public:
  static int checkRecord(const int n) {
    dp[0][0] = 0; dp[0][1] = 1;
    dp[1][0] = 1; dp[1][1] = 0;
    dp[2][0] = 0; dp[2][1] = 0;
    dp[3][0] = 1; dp[3][1] = 0;
    for (int i = 1; i < n; ++i) {
      dp2[0][1] = (dp[1][0] + dp[2][0] + dp[3][0]) % m;

      dp2[1][0] = dp[3][0];
      dp2[1][1] = (dp[0][1] + dp[3][1]) % m;

      dp2[2][0] = dp[1][0];
      dp2[2][1] = dp[1][1];
      
      dp2[3][0] = (dp[1][0] + dp[2][0] + dp[3][0]) % m;
      dp2[3][1] = (dp[0][1] + dp[1][1] + dp[2][1] + dp[3][1]) % m;

      std::swap(dp, dp2);
    }
    ll res = 0;
    for (const auto& dp_j : dp) {
      res = (res + dp_j[0] + dp_j[1]) % m;
    }
    return static_cast<int>(res);
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto e_out = Solution::checkRecord(2);
    assert(e_out == 8);
    
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto e_out = Solution::checkRecord(1);
    assert(e_out == 3);
    
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto e_out = Solution::checkRecord(10101);
    assert(e_out == 183236316);
    
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
