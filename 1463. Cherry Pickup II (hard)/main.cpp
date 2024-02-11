#include <bits/stdc++.h>

using namespace std::literals;

using ll [[maybe_unused]] = long long;
using ii [[maybe_unused]] = std::pair<int, int>;
using vii [[maybe_unused]] = std::vector<ii>;
using vi [[maybe_unused]] = std::vector<int>;
using vl [[maybe_unused]] = std::vector<ll>;
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
#define CL(_v) static_cast<ll>(_v)
#define F first
#define S second

constexpr int MAX_N = 70;
int dp[MAX_N][MAX_N][MAX_N];

int Rec(int i, int j1, int j2, int n, int m, const vvi& grid) {
  if (i == n)
    return 0;
  auto& memo = dp[i][j1][j2];
  if (memo != -1)
    return memo;

  const auto row_res = (j1 == j2) ? grid[i][j1] : grid[i][j1]+grid[i][j2];
  int res = 0;
  FOR(d1, -1, 1) {
    if (j1+d1 < 0 || j1+d1 >= m)
      continue;
    FOR(d2, -1, 1) {
      if (j2+d2 < 0 || j2+d2 >= m)
        continue;
      const auto sub_res = Rec(i+1, j1+d1, j2+d2, n, m, grid);
      res = std::max(res, row_res + sub_res);
    }
  }
  memo = res;
  return res;
}

class Solution {
 public:
  static int cherryPickup(const vvi& grid) {
    const auto n = CI(grid.size());
    const auto m = CI(grid[0].size());
    std::fill(&dp[0][0][0], &dp[0][0][0] + sizeof(dp) / sizeof(dp[0][0][0]), -1);
    const auto res = Rec(0, 0, m-1, n, m, grid);
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi grid{{3,1,1},{2,5,1},{1,5,5},{2,1,1}};
    const auto a_out = Solution::cherryPickup(grid);
    assert(a_out == 24);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi grid{{1,0,0,0,0,0,1},{2,0,0,0,0,3,0},{2,0,9,0,0,0,0},{0,3,0,5,4,0,0},{1,0,2,3,0,0,6}};
    const auto a_out = Solution::cherryPickup(grid);
    assert(a_out == 28);

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
