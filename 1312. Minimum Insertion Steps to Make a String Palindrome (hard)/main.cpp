#include <bits/stdc++.h>

using namespace std::literals;

using ll [[maybe_unused]] = long long;
using ii [[maybe_unused]] = std::pair<int, int>;
using vii [[maybe_unused]] = std::vector<ii>;
using vi [[maybe_unused]] = std::vector<int>;
using vvi [[maybe_unused]] = std::vector<vi>;
using vs [[maybe_unused]] = std::vector<std::string>;
using vvs [[maybe_unused]] = std::vector<vs>;
using vc [[maybe_unused]] = std::vector<char>;
using vvc [[maybe_unused]] = std::vector<vc>;

#define FOR(_i, _a, _b) for (int _i = (_a); _i <= (_b); ++(_i))
#define FORD(_i, _a, _b) for (int _i = (_a); _i >= (_b); --(_i))
#define RNG(_l) (_l).begin(), (_l).end()
#define SORT(_l) std::sort((_l).begin(), (_l).end())
#define CI(_v) static_cast<int>(_v)
#define F first
#define S second

constexpr int MAX_N = 500;
int dp[MAX_N+1][MAX_N+1];

int CountLCS(const std::string& s, int n, int l, int r) {
  const auto l_len = l+1;
  const auto r_len = n-r;
  FOR(i, 1, l_len) {
    FOR(j, 1, r_len) {
      const auto li = l-i+1;
      const auto ri = r+j-1;
      if (s[li] == s[ri]) {
        dp[i][j] = dp[i-1][j-1] + 1;
      } else {
        dp[i][j] = std::max(dp[i-1][j], dp[i][j-1]);
      }
    }
  }
  return dp[l_len][r_len];
}

class Solution {
 public:
  static int minInsertions(const std::string& s) {
    memset(&dp, 0, sizeof(dp));
    const auto n = CI(s.size());
    int min_res = n-1;
    FOR(i, 0, n-1) {
      // odd
      if (i > 0 || i < n-1) {
        const auto lcs = CountLCS(s, n, i-1, i+1);
        const auto res = (n-1) - lcs*2;
        min_res = std::min(min_res, res);
      }
      // even
      if (i < n-1) {
        const auto lcs = CountLCS(s, n, i, i+1);
        const auto res = n - lcs*2;
        min_res = std::min(min_res, res);
      }
    }
    return min_res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    auto a_out = Solution::minInsertions("zzazz");
    assert(a_out == 0);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    auto a_out = Solution::minInsertions("mbadm");
    assert(a_out == 2);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    auto a_out = Solution::minInsertions("leetcode");
    assert(a_out == 5);

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
