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

using QItem = std::pair<int, std::pair<int, int>>;

constexpr std::array<std::pair<int, int>, 4> DIRS = {
  std::pair<int, int>{1,0},
  std::pair<int, int>{-1,0},
  std::pair<int, int>{0,1},
  std::pair<int, int>{0,-1}};

class Solution {
public:
  static int swimInWater(const std::vector<std::vector<int>>& grid) {
    const auto n = grid.size();
    std::vector<std::vector<int>> dist(n, std::vector<int>(n, INT_MAX));

    std::priority_queue<QItem, std::vector<QItem>, std::greater<>> pq;
    pq.emplace(grid[0][0], std::pair<int, int>{0,0});

    while (!pq.empty()) {
      const auto v_dist = pq.top().first;
      const auto v = pq.top().second;
      pq.pop();
      if (v_dist >= dist[v.first][v.second])
        continue;
      dist[v.first][v.second] = v_dist;
      for (const auto& d : DIRS) {
        const std::pair<int, int> u{v.first+d.first, v.second+d.second};
        if (u.first >= 0 && u.first < n && u.second >= 0 && u.second < n) {
          const auto u_dist = std::max(v_dist, grid[u.first][u.second]);
          if (u_dist < dist[u.first][u.second]) {
            pq.emplace(u_dist, u);
          }
        }
      }
    }
    return dist[n-1][n-1];
  }
};

[[maybe_unused]] void TestSolution() {
  /*{
    const auto start_t = std::chrono::high_resolution_clock::now();
    const vvi edges{{0,1},{1,2},{1,3},{4,2}};
    const vvi guesses{{1,3},{0,1},{1,0},{2,4}};
    const int k = 3;
    assert(Solution::rootCount(edges, guesses, k) == 3);
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }*/
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
