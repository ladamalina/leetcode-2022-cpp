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

constexpr int MAX_N = 50;
int dp[MAX_N*2][MAX_N][MAX_N];
constexpr std::array<ii, 2> DIRS = {ii{0, 1}, ii{1, 0}};

void Rec(int d, int i1, int i2, int psum, int n, const vvi& grid) {
  const auto j1 = d-i1, j2 = d-i2;
  const auto csum = psum + grid[i1][j1] + (i1==i2 ? 0 : grid[i2][j2]);
  auto& memo = dp[d][i1][i2];
  if (memo >= csum)
    return;
  // memo < csum
  memo = csum;

  for (const auto& d1 : DIRS) {
    if (i1+d1.F == n || j1+d1.S == n || grid[i1+d1.F][j1+d1.S]==-1)
      continue;
    for (const auto& d2 : DIRS) {
      if (i2+d2.F == n || j2+d2.S == n || grid[i2+d2.F][j2+d2.S]==-1)
        continue;
      Rec(d+1, i1+d1.F, i2+d2.F, csum, n, grid);
    }
  }
}

class Solution {
 public:
  static int cherryPickup(const vvi& grid) {
    const auto n = CI(grid.size());
    std::fill(&dp[0][0][0], &dp[0][0][0] + sizeof(dp) / sizeof(dp[0][0][0]), -1);
    Rec(0, 0, 0, 0, n, grid);
    const auto res = dp[(n-1)+(n-1)][n-1][n-1];
    return std::max(res, 0);
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi grid{{0,1,-1},{1,0,-1},{1,1,1}};
    const auto a_out = Solution::cherryPickup(grid);
    assert(a_out == 5);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi grid{{1,1,-1},{1,-1,1},{-1,1,1}};
    const auto a_out = Solution::cherryPickup(grid);
    assert(a_out == 0);

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
