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

constexpr int MAX_N = 1000;
std::array<int, MAX_N+1> in_deg;
std::bitset<MAX_N+1> vis;

bool DFS(int v, const std::vector<vii>& g, int exc_ei) {
  vis[v] = true;
  for (const auto& [u, ei] : g[v]) {
    if (ei == exc_ei) continue;
    if (vis[u]) {
      return false;
    } else {
      const auto u_res = DFS(u, g, exc_ei);
      if (!u_res)
        return false;
    }
  }
  return true;
}

class Solution {
 public:
  static vi findRedundantDirectedConnection(const vvi& edges) {
    const auto n = CI(edges.size());
    std::fill(in_deg.begin()+1, in_deg.begin()+n+1, 0);
    std::vector<vii> g(n+1);
    FOR(ei, 0, n-1) {
      const auto& e = edges[ei];
      g[e[0]].emplace_back(e[1], ei);
      ++in_deg[e[1]];
    }
    
    int red_ei = -1;
    
    const auto root_v = CI(std::find(in_deg.begin()+1, in_deg.begin()+n+1, 0) - in_deg.begin());
    if (root_v <= n) { // has root
      FOR(ei, 0, n-1) {
        vis.reset();
        const auto v_res = DFS(root_v, g, ei);
        const auto vis_cnt = CI(vis.count());
        if (v_res && vis_cnt == n)
          red_ei = std::max(red_ei, ei);
      }
    } else { // root in cycle
      FOR(ei, 0, n-1) {
        const auto& e = edges[ei];
        const auto to_v = e[1];
        if (in_deg[to_v] == 1) {
          vis.reset();
          const auto v_res = DFS(to_v, g, ei);
          const auto vis_cnt = CI(vis.count());
          if (v_res && vis_cnt == n)
            red_ei = std::max(red_ei, ei);
        }
      }
    }
    return {edges[red_ei][0], edges[red_ei][1]};
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi edges{{1,2},{1,3},{2,3}};
    const auto a_out = Solution::findRedundantDirectedConnection(edges);
    const vi e_out{2,3};
    assert(a_out == e_out);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi edges{{1,2},{2,3},{3,4},{4,1},{1,5}};
    const auto a_out = Solution::findRedundantDirectedConnection(edges);
    const vi e_out{4,1};
    assert(a_out == e_out);

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
