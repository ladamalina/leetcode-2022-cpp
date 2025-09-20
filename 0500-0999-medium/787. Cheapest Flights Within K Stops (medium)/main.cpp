#include <bits/stdc++.h>

using namespace std::literals;

using ll [[maybe_unused]] = long long;
using ii [[maybe_unused]] = std::pair<int, int>;
using vii [[maybe_unused]] = std::vector<ii>;
using vi [[maybe_unused]] = std::vector<int>;
using vl [[maybe_unused]] = std::vector<ll>;
using vvi [[maybe_unused]] = std::vector<vi>;
using vvii [[maybe_unused]] = std::vector<vii>;
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

constexpr int MAX_N = 100;
constexpr int MAX_K = MAX_N-1;
std::array<std::array<int, MAX_K+1>, MAX_N> dp;
std::array<vii, MAX_N> g;

void DFS(int src, int dst, int spent, int k, int& res) {
  for (const auto& [v, fl_cost] : g[src]) {
    if (v == dst) {
      dp[v][k] = std::min(dp[v][k], spent + fl_cost);
      res = std::min(res, dp[v][k]);
    } else if (k > 0 && spent + fl_cost < dp[v][k-1] && spent + fl_cost < res) {
      dp[v][k-1] = spent + fl_cost;
      DFS(v, dst, spent + fl_cost, k-1, res);
    }
  }
}

class Solution {
 public:
  static int findCheapestPrice(int n, const vvi& flights, int src, int dst, int k) {
    std::fill(g.begin(), g.begin()+n, vii{});
    for (const auto& f : flights) {
      g[f[0]].emplace_back(f[1], f[2]);
    }

    std::fill(&dp[0][0], &dp[0][0] + sizeof(dp) / sizeof(dp[0][0]), 1e9);
    dp[src][k] = 0;
    int res = 1e9;
    DFS(src, dst, 0, k, res);
    
    return (res == 1e9) ? -1 : res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi flights{{0,1,100},{1,2,100},{2,0,100},{1,3,600},{2,3,200}};
    const auto e_out = Solution::findCheapestPrice(4, flights, 0, 3, 1);
    assert(e_out == 700);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi flights{{0,1,100},{1,2,100},{0,2,500}};
    const auto e_out = Solution::findCheapestPrice(3, flights, 0, 2, 1);
    assert(e_out == 200);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi flights{{0,1,100},{1,2,100},{0,2,500}};
    const auto e_out = Solution::findCheapestPrice(3, flights, 0, 2, 0);
    assert(e_out == 500);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi flights{{0,1,1},{0,2,5},{1,2,1},{2,3,1},{3,4,1}};
    const auto e_out = Solution::findCheapestPrice(5, flights, 0, 4, 2);
    assert(e_out == 7);

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
