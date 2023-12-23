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
#define CD(_v) static_cast<double>(_v)
#define F first
#define S second
#define PB push_back

const auto EPS = 1e-5;
template <typename T>
[[maybe_unused]] bool Eq(T a, T b) { return std::abs(a - b) < EPS; }

class Solution {
  public:
  static double frogPosition(int n, const vvi& edges, int t, int target) {
    vvi g(n+1);
    for (const auto& e : edges) {
      g[e[0]].PB(e[1]);
      g[e[1]].PB(e[0]);
    }
    double target_prob = 0;
    std::function<void(int, int, int, double)> dfs = [&](int v, int p, int d, double prob) {
      if (d > t) return;
      if (d == t) {
        if (v == target) {
          target_prob = prob;
        }
        return;
      } // d < t
      const auto ch_cnt = (v==1) ? CI(g[v].size()) : CI(g[v].size())-1;
      if (ch_cnt == 0) { // a leaf
        if (v == target) {
          target_prob = prob;
        }
      } else { // not a leaf
        if (v != target) {
          const auto next_prob = prob * (1 / CD(ch_cnt));
          for (auto u : g[v]) {
            if (u != p) {
              dfs(u, v, d+1, next_prob);
            }
          }
        }
      }
    };
    dfs(1, 0, 0, 1);
    return target_prob;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    const vvi edges{{1,2},{1,3},{1,7},{2,4},{2,6},{3,5}};
    const auto a_cout = Solution::frogPosition(7, edges, 2, 4);
    assert(Eq(a_cout, 0.16666666666666666));
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    const vvi edges{{1,2},{1,3},{1,7},{2,4},{2,6},{3,5}};
    const auto a_cout = Solution::frogPosition(7, edges, 1, 7);
    assert(Eq(a_cout, 0.3333333333333333));
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  std::cerr << "TestSolution OK"sv << std::endl;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
#ifndef NDEBUG
  TestSolution();
#endif
  return 0;
}
