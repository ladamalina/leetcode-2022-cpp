#include <bits/stdc++.h>



using namespace std::literals;

using ll [[maybe_unused]] = long long;
using ii [[maybe_unused]] = std::pair<int, int>;
using vii [[maybe_unused]] = std::vector<ii>;
using vi [[maybe_unused]] = std::vector<int>;
using vl [[maybe_unused]] = std::vector<ll>;
using vvi [[maybe_unused]] = std::vector<vi>;
using vvii [[maybe_unused]] = std::vector<vii>;
using vb [[maybe_unused]] = std::vector<bool>;
using vvb [[maybe_unused]] = std::vector<vb>;
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

constexpr std::array<ii, 4> DIRS = {ii{-1,0}, ii{0,1}, ii{1,0}, ii{0,-1}};

struct HashPair {
  size_t operator()(const ii& x) const {
    return (x.F) * 37 + (x.S) * 37 * 37;
  }
};

struct Cluster {
  std::unordered_set<ii, HashPair> cells;
  std::unordered_set<ii, HashPair> next_cells;
  int ws = 0;
  bool operator<(const Cluster& other) const {
    return next_cells.size() < other.next_cells.size();
  }
};

void DFS(int i, int j, int n, int m, vvi& grid, vvb& vis, Cluster& cl) {
  if (vis[i][j] || grid[i][j] == -1)
    return;
  if (grid[i][j] == 0) {
    ++cl.ws;
    cl.next_cells.emplace(i,j);
    return;
  } // !vis[i][j] && grid[i][j] == 1
  cl.cells.emplace(i,j);
  vis[i][j] = true;
  
  for (const auto& d : DIRS) {
    if (i+d.F>=0 && i+d.F<n && j+d.S>=0 && j+d.S<m) {
      DFS(i+d.F, j+d.S, n, m, grid, vis, cl);
    }
  }
}

class Solution {
 public:
  static int containVirus(vvi& grid) {
    const auto n = CI(grid.size());
    const auto m = CI(grid[0].size());
    
    int res = 0;
    while (true) {
      vvb vis(n, vb(m, false));
      std::priority_queue<Cluster, std::vector<Cluster>, std::less<>> pq;
      FOR(i, 0, n-1) {
        FOR(j, 0, m-1) {
          if (!vis[i][j] && grid[i][j] == 1) {
            Cluster cl;
            DFS(i, j, n, m, grid, vis, cl);
            pq.push(cl);
          }
        }
      }
      if (pq.empty())
        break;
      
      const auto top_cl = pq.top();
      pq.pop();
      for (const auto& v: top_cl.cells) {
        grid[v.F][v.S] = -1;
      }
      res += top_cl.ws;

      while(!pq.empty()) {
        const auto cl = pq.top();
        pq.pop();
        for (const auto& v : cl.next_cells) {
          grid[v.F][v.S] = 1;
        }
      }
    }
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vvi is_inf{{0,1,0,0,0,0,0,1},{0,1,0,0,0,0,0,1},{0,0,0,0,0,0,0,1},{0,0,0,0,0,0,0,0}};
    const auto a_out = Solution::containVirus(is_inf);
    assert(a_out == 10);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vvi is_inf{{1,1,1},{1,0,1},{1,1,1}};
    const auto a_out = Solution::containVirus(is_inf);
    assert(a_out == 4);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vvi is_inf{{0,0,1,1,1,0,1,0,0,0},{1,1,1,0,0,0,1,1,0,1},{0,0,0,0,0,0,1,0,0,0},{0,0,0,0,1,0,1,0,0,0},{1,0,0,0,1,1,1,0,0,0},{0,0,0,1,0,1,1,0,0,0},{1,0,0,0,0,1,0,0,0,1},{1,0,0,0,0,0,0,0,0,1},{0,1,0,0,0,0,0,0,1,0},{1,1,0,0,0,1,0,1,0,0}};
    const auto a_out = Solution::containVirus(is_inf);
    assert(a_out == 59);

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
