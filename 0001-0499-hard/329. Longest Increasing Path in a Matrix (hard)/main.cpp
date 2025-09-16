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

struct Cell {
  int dist = 0;
  int val = 0;
  ii pos;

  bool operator==(const Cell& other) const {
    return std::make_tuple(dist, val, pos) == std::make_tuple(other.dist, other.val, other.pos);
  }
  bool operator<(const Cell& other) const {
    return std::make_tuple(-dist, val, pos) < std::make_tuple(-other.dist, other.val, other.pos);
  }
  bool operator>(const Cell& other) const {
    return !(*this == other || *this < other);
  }
};

const vii DIRS{{1,0}, {-1,0}, {0,1}, {0,-1}};

class Solution {
  public:
  static int longestIncreasingPath(const vvi& matrix) {
    const auto h = CI(matrix.size());
    const auto w = CI(matrix[0].size());
    vvi dist(h, vi(w, 1));
    std::set<Cell> pq;
    FOR(i, 0, h-1) {
      FOR(j, 0, w-1) {
        pq.insert(Cell{1, matrix[i][j], ii{i, j}});
      }
    }
    int max_dist = 1;
    while (!pq.empty()) {
      const auto v = *pq.begin();
      pq.erase(pq.begin());
      if (v.dist < dist[v.pos.F][v.pos.S])
        continue;
      max_dist = std::max(max_dist, v.dist);
      for (const auto& d : DIRS) {
        const auto ui = v.pos.F + d.F;
        const auto uj = v.pos.S + d.S;
        if (ui >= 0 && ui < h && uj >= 0 && uj < w && matrix[ui][uj] > v.val && v.dist+1 > dist[ui][uj]) {
          pq.erase(Cell{dist[ui][uj], matrix[ui][uj], ii{ui, uj}});
          dist[ui][uj] = v.dist+1;
          pq.insert(Cell{v.dist+1, matrix[ui][uj], ii{ui, uj}});
        }
      }
    }
    return max_dist;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    const vvi matrix{{9,9,4},{6,6,8},{2,1,1}};
    const auto a_out = Solution::longestIncreasingPath(matrix);
    assert(a_out == 4);
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    const vvi matrix{{3,4,5},{3,2,6},{2,2,1}};
    const auto a_out = Solution::longestIncreasingPath(matrix);
    assert(a_out == 4);
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    const vvi matrix{{1}};
    const auto a_out = Solution::longestIncreasingPath(matrix);
    assert(a_out == 1);
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    const vvi matrix{{0,1,2,3,4,5,6,7,8,9},
      {19,18,17,16,15,14,13,12,11,10},
      {20,21,22,23,24,25,26,27,28,29},
      {39,38,37,36,35,34,33,32,31,30},
      {40,41,42,43,44,45,46,47,48,49},
      {59,58,57,56,55,54,53,52,51,50},
      {60,61,62,63,64,65,66,67,68,69},
      {79,78,77,76,75,74,73,72,71,70},
      {80,81,82,83,84,85,86,87,88,89},
      {99,98,97,96,95,94,93,92,91,90},
      {100,101,102,103,104,105,106,107,108,109},
      {119,118,117,116,115,114,113,112,111,110},
      {120,121,122,123,124,125,126,127,128,129},
      {139,138,137,136,135,134,133,132,131,130},
      {0,0,0,0,0,0,0,0,0,0}};
    const auto a_out = Solution::longestIncreasingPath(matrix);
    assert(a_out != 1);
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
