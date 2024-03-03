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

constexpr std::array<ii, 4> DIRS = {ii{1,0}, ii{-1,0}, ii{0,1}, ii{0,-1}};

int Encode(const vvi& grid) {
  return grid[0][0]*CI(1e5) + grid[0][1]*CI(1e4) + grid[0][2]*CI(1e3)
    + grid[1][0]*CI(1e2) + grid[1][1]*10 + grid[1][2];
}

vvi Decode(int hash) {
  vvi grid(2, vi(3));
  grid[0][0] = hash / CI(1e5);
  grid[0][1] = (hash % CI(1e5)) / CI(1e4);
  grid[0][2] = (hash % CI(1e4)) / CI(1e3);
  grid[1][0] = (hash % CI(1e3)) / CI(1e2);
  grid[1][1] = (hash % CI(1e2)) / 10;
  grid[1][2] = hash % CI(10);
  return grid;
}

ii Pos0(const vvi& grid) {
  const auto it0 = std::find(RNG(grid[0]), 0);
  if (it0 != grid[0].end()) {
    return {0, CI(it0 - grid[0].begin())};
  }
  const auto it1 = std::find(RNG(grid[1]), 0);
  return {1, CI(it1 - grid[1].begin())};
}

constexpr int MAX_HASH = 543210;
std::array<int, MAX_HASH+1> dist;
constexpr int TARGET_HASH = 123450;

/*int Rec(int turn, vvi& grid) {
  const auto grid_hash = Encode(grid);
  if (grid_hash == TARGET_HASH)
    return turn-1;
  if (dist[grid_hash] != -1) {
    if ()
  }

}*/

class Solution {
public:
  static int slidingPuzzle(vvi& grid) {
    std::fill(dist.begin(), dist.end(), INT_MAX);
    std::priority_queue<ii, vii, std::greater<>> pq;
    pq.emplace(0, Encode(grid));
    while (!pq.empty()) {
      const auto v_dist = pq.top().F;
      const auto v_hash = pq.top().S;
      pq.pop();
      if (v_dist >= dist[v_hash])
        continue;
      dist[v_hash] = v_dist;
      auto v_grid = Decode(v_hash);
      const auto v = Pos0(v_grid);
      for (const auto& d : DIRS) {
        const ii u{v.F+d.F, v.S+d.S};
        if (u.F >= 0 && u.F < 2 && u.S >= 0 && u.S < 3) {
          std::swap(v_grid[v.F][v.S], v_grid[u.F][u.S]);

          const auto u_hash = Encode(v_grid);
          const auto u_dist = v_dist + 1;
          if (u_dist < dist[u_hash]) {
            pq.emplace(u_dist, u_hash);
          }

          std::swap(v_grid[v.F][v.S], v_grid[u.F][u.S]);
        }
      }
    }
    const auto res = dist[TARGET_HASH];
    return (res == INT_MAX) ? -1 : res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vvi grid{{1,2,3},{4,0,5}};
    const auto a_out = Solution::slidingPuzzle(grid);
    assert(a_out == 1);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vvi grid{{1,2,3},{5,4,0}};
    const auto a_out = Solution::slidingPuzzle(grid);
    assert(a_out == -1);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vvi grid{{4,1,2},{5,0,3}};
    const auto a_out = Solution::slidingPuzzle(grid);
    assert(a_out == 5);

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
