#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;

using ll = long long;
using ii [[maybe_unused]] = std::pair<int, int>;
using vi [[maybe_unused]] = std::vector<int>;
using vl [[maybe_unused]] = std::vector<ll>;
using vvi [[maybe_unused]] = std::vector<vi>;
using vvl [[maybe_unused]] = std::vector<vl>;
using vii [[maybe_unused]] = std::vector<ii>;
using vb [[maybe_unused]] = std::vector<bool>;
using vd [[maybe_unused]] = std::vector<double>;
using vs [[maybe_unused]] = std::vector<std::string>;

#define FOR(_i, _a, _b) for (int _i = (_a); _i <= (_b); ++(_i))
#define FORD(_i, _a, _b) for (int _i = (_a); _i >= (_b); --(_i))
#define RNG(_l) (_l).begin(), (_l).end()
#define SORT(_l) std::sort((_l).begin(), (_l).end())
#define CI(_v) static_cast<int>(_v)
#define CL(_v) static_cast<ll>(_v)
#define CD(_v) static_cast<double>(_v)
#define SZ(_v) static_cast<int>((_v).size())
#define F first
#define S second

constexpr int MAX_N = 200;
constexpr std::array<ii, 4> DIRS{ii{0,1}, ii{0,-1}, ii{1,0}, ii{-1,0}};
std::array<std::array<int, MAX_N>, MAX_N> vis;

class Solution {
 public:
  int trapRainWater(const vvi& g) {
    const auto n = SZ(g), m = SZ(g[0]);
    std::fill(&vis[0][0], &vis[0][0] + sizeof(vis) / sizeof(vis[0][0]), 0);
    std::priority_queue<std::pair<int,ii>, std::vector<std::pair<int,ii>>, std::greater<>> pq;
    FOR(j, 0, m-1) {
      pq.emplace(g[0][j], ii{0, j});
      vis[0][j] = 1;
      pq.emplace(g[n-1][j], ii{n-1, j});
      vis[n-1][j] = 1;
    }
    FOR(i, 0, n-1) {
      pq.emplace(g[i][0], ii{i, 0});
      vis[i][0] = 1;
      pq.emplace(g[i][m-1], ii{i, m-1});
      vis[i][m-1] = 1;
    }

    auto trapped = 0, max_h = 0;
    while (!pq.empty()) {
      const auto vh = pq.top().F, vx = pq.top().S.F, vy = pq.top().S.S;
      pq.pop();
      max_h = std::max(vh, max_h);
      for (const auto& d : DIRS) {
        const auto ux = vx + d.F, uy = vy + d.S;
        if (ux >= 0 && ux < n && uy >= 0 && uy < m && !vis[ux][uy]) {
          const auto uh = g[ux][uy];
          if (uh < max_h)
            trapped += (max_h - uh);
          pq.emplace(uh, ii{ux, uy});
          vis[ux][uy] = 1;
        }
      }
    }

    return trapped;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const vvi g{
        {1,4,3,1,3,2},
        {3,2,1,3,2,4},
        {2,3,3,2,3,1},
    };
    auto start_t = std::chrono::high_resolution_clock::now();
    auto a_out = Solution().trapRainWater(g);
    auto end_t = std::chrono::high_resolution_clock::now();
    auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
    assert(a_out == 4);
  }
  {
    const vvi g{
        {3,3,3,3,3},
        {3,2,2,2,3},
        {3,2,1,2,3},
        {3,2,2,2,3},
        {3,3,3,3,3},
    };
    auto start_t = std::chrono::high_resolution_clock::now();
    auto a_out = Solution().trapRainWater(g);
    auto end_t = std::chrono::high_resolution_clock::now();
    auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
    assert(a_out == 10);
  }
  std::cerr << "TestSolution OK"sv << std::endl;
}

int main() {
#ifndef NDEBUG
  TestSolution();
#endif
  return 0;
}
