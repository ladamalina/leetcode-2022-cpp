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
#define F first
#define S second

constexpr int MAX_N = 12;
int d[MAX_N][MAX_N];
int dp[MAX_N][(1<<MAX_N)];

int Rec(int v, int vis, int max_vis, int n, const vvi& graph) {
  if (vis == max_vis)
    return 0;
  if (dp[v][vis] != -1)
    return dp[v][vis];
  
  int res = INT_MAX;
  FOR(u, 0, n-1) {
    if ((vis & (1<<u)) == 0) {
      const auto sub_res = Rec(u, vis|(1<<u), max_vis, n, graph);
      res = std::min(res, d[v][u] + sub_res);
    }
  }
  dp[v][vis] = res;
  return res;
}

class Solution {
 public:
  static int shortestPathLength(const vvi& graph) {
    const auto n = CI(graph.size());
    std::fill(&d[0][0], &d[0][0] + sizeof(d) / sizeof(d[0][0]), 1e5);
    std::fill(&dp[0][0], &dp[0][0] + sizeof(dp) / sizeof(dp[0][0]), -1);
    FOR(v, 0, n-1) {
      d[v][v] = 0;
      for (const auto u : graph[v]) {
        d[v][u] = 1;
        d[u][v] = 1;
      }
    }
    for (int k=0; k<n; ++k)
      for (int i=0; i<n; ++i)
        for (int j=0; j<n; ++j)
          d[i][j] = std::min(d[i][j], d[i][k] + d[k][j]);

    const int max_vis = (1<<n)-1;
    int res = INT_MAX;
    FOR(v, 0, n-1) {
      const auto sub_res = Rec(v, (1<<v), max_vis, n, graph);
      res = std::min(res, sub_res);
    }
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi graph{{1,2,3},{0},{0},{0}};
    auto a_out = Solution::shortestPathLength(graph);
    assert(a_out == 4);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi graph{{1},{0,2,4},{1,3,4},{2},{1,2}};
    auto a_out = Solution::shortestPathLength(graph);
    assert(a_out == 4);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi graph{{1},{0,2,4},{1,3},{2},{1,5},{4}};
    auto a_out = Solution::shortestPathLength(graph);
    assert(a_out == 6);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi graph{{1,4},{0,3,10},{3},{1,2,6,7},{0,5},{4},{3},{3},{10},{10},{1,9,8}};
    auto a_out = Solution::shortestPathLength(graph);
    assert(a_out == 15);

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
