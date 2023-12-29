//#pragma GCC optimize("O3")
//#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;

using ll = long long;
using ld = long double;
using ull = unsigned long long;
using ii [[maybe_unused]] = std::pair<int, int>;
using pll [[maybe_unused]] = std::pair<ll, ll>;
using pdd [[maybe_unused]] = std::pair<double, double>;
using vi [[maybe_unused]] = std::vector<int>;
using vvi [[maybe_unused]] = std::vector<vi>;
using vvvi [[maybe_unused]] = std::vector<vvi>;
using vii [[maybe_unused]] = std::vector<ii>;
using vvii [[maybe_unused]] = std::vector<vii>;
using vb [[maybe_unused]] = std::vector<bool>;

#define FOR(_i, _a, _b) for (int _i = (_a); _i <= (_b); ++(_i))
#define FORD(_i, _a, _b) for (int _i = (_a); _i >= (_b); --(_i))
#define RNG(_l) (_l).begin(), (_l).end()
#define SORT(_l) std::sort((_l).begin(), (_l).end())
#define CI(_v) static_cast<int>(_v)
#define CL(_v) static_cast<ll>(_v)
#define CD(_v) static_cast<ld>(_v)
#define F first
#define S second
#define PB push_back

class Solution {
  public:
  static int calculateMinimumHP(const vvi& dungeon) {
    const auto n = CI(dungeon.size());
    const auto m = CI(dungeon[0].size());
    const int INF = 1000*(m+n);

    auto check = [&](int init_p) {
      vvi dp(n, vi(m));
      dp[0][0] = std::max(0, init_p + dungeon[0][0]);
      FOR(j, 1, m-1) {
        const int i = 0;
        if (dp[i][j-1] > 0)
          dp[i][j] = std::max(0, dp[i][j-1] + dungeon[i][j]);
      }
      FOR(i, 1, n-1) {
        {
          const int j = 0;
          if (dp[i-1][j] > 0)
            dp[i][j] = std::max(0, dp[i-1][j] + dungeon[i][j]);
        }
        FOR(j, 1, m-1) {
          const auto max_prev = std::max(dp[i][j-1], dp[i-1][j]);
          if (max_prev > 0)
            dp[i][j] = std::max(0, max_prev + dungeon[i][j]);
        }
      }

      return dp[n-1][m-1] > 0;
    };
    
    int l = 1;
    int r = INF;
    while (l < r) {
      const auto mid = (l+r)/2;
      if (check(mid)) r = mid;
      else l = mid+1;
    }
    return r;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    const vvi dungeon{{-2,-3,3},{-5,-10,1},{10,30,-5}};
    const auto a_out = Solution::calculateMinimumHP(dungeon);
    assert(a_out == 7);
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    const vvi dungeon{{0}};
    const auto a_out = Solution::calculateMinimumHP(dungeon);
    assert(a_out == 1);
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    const vvi dungeon{{1,-3,3},{0,-2,0},{-3,-3,-3}};
    const auto a_out = Solution::calculateMinimumHP(dungeon);
    assert(a_out == 3);
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
