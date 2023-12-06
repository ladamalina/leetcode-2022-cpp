//#pragma GCC optimize("O3")
//#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;

using ll = long long;
using ld = long double;
using ull = unsigned long long;
using ii [[maybe_unused]] = std::pair<int, int>;
using pll [[maybe_unused]] = std::pair<ll, ll>;
using vi [[maybe_unused]] = std::vector<int>;
using vvi [[maybe_unused]] = std::vector<vi>;
using vii [[maybe_unused]] = std::vector<ii>;
using vb [[maybe_unused]] = std::vector<bool>;
using vd [[maybe_unused]] = std::vector<ld>;

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

void Rec(int sem, int taken, int n, int k, const vi& g_rev, vvi& dp) {
  if (dp[sem][taken] != -1)
    return;
  
  if (__builtin_popcount(taken) == n) {
    dp[sem][taken] = sem;
    return;
  }
  
  vi avail;
  FOR(v, 1, n) {
    if (!(taken & (1 << v)) && ((taken|g_rev[v]) == taken)) {
      avail.PB(v);
    }
  }
  const auto avail_n = CI(avail.size());
  const int to_take_cnt = std::min(avail_n, k);
  const int to_skip_cnt = avail_n - to_take_cnt;
  std::string take_mask = std::string(to_skip_cnt, '0') + std::string(to_take_cnt, '1');
  
  int min_sub_res = INT_MAX;
  do {
    auto sub_taken = taken;
    FOR(i, 0, avail_n-1) {
      if (take_mask[i]=='1') {
        sub_taken |= (1 << avail[i]);
      }
    }
    Rec(sem+1, sub_taken, n, k, g_rev, dp);
    min_sub_res = std::min(min_sub_res, dp[sem+1][sub_taken]);
  } while (std::next_permutation(RNG(take_mask)));

  dp[sem][taken] = min_sub_res;
}

class Solution {
 public:
  static int minNumberOfSemesters(const int n, const vvi& relations, const int k) {
    vi g_rev(n+1);
    for (const auto& rel : relations) {
      const auto v = rel[0];
      const auto u = rel[1];
      g_rev[u] |= (1<<v);
    }
    const auto max_taken = (1<<(n+1))-2;
    vvi dp(n+1, vi(max_taken+1, -1));
    Rec(0, 0, n, k, g_rev, dp);
    return dp[0][0];
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    {
      const int n = 4;
      const vvi relations{{2,1},{3,1},{1,4}};
      const int k = 2;
      const auto a_out = Solution::minNumberOfSemesters(n, relations, k);
      const int e_out = 3;
      assert(a_out == e_out);
    }
    {
      const int n = 5;
      const vvi relations{{2,1},{3,1},{4,1},{1,5}};
      const int k = 4;
      const auto a_out = Solution::minNumberOfSemesters(n, relations, k);
      const int e_out = 3;
      assert(a_out == e_out);
    }
    {
      const int n = 11;
      const vvi relations{};
      const int k = 2;
      const auto a_out = Solution::minNumberOfSemesters(n, relations, k);
      const int e_out = 6;
      assert(a_out == e_out);
    }
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  std::cerr << "TestSolution OK"sv << std::endl;
}

int main() {
  TestSolution();
  return 0;
}
