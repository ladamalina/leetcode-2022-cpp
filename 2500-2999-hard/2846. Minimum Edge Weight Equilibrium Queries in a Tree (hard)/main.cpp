//#pragma GCC optimize("O3")
//#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;

using ii [[maybe_unused]] = std::pair<int, int>;
using vi [[maybe_unused]] = std::vector<int>;
using vvi [[maybe_unused]] = std::vector<vi>;
using vii [[maybe_unused]] = std::vector<ii>;
using vvii [[maybe_unused]] = std::vector<vii>;

const int N_MAX = 10000;
const int H_MAX = 31 - __builtin_clz(N_MAX);
int timer = 0;
int t_in[N_MAX];
int t_out[N_MAX];
int up[H_MAX+1][N_MAX];
int r_weights[27][N_MAX];

class Solution {
 public:
  static vi minOperationsQueries(int n, const vvi& edges, const vvi& queries) {
    vvii g(n);
    for (int i = 0; i < n-1; ++i) {
      const auto v = edges[i][0];
      const auto u = edges[i][1];
      g[v].emplace_back(u, i);
      g[u].emplace_back(v, i);
    }

    const auto h_max = 31 - __builtin_clz(n);

    std::function<void(int, int, int)> dfs = [&](int v, int p, int e_id) {
      t_in[v] = ++timer;

      up[0][v] = p;
      for (int h = 1; h <= h_max; ++h) {
        up[h][v] = up[h-1][up[h-1][v]];
      }
      
      if (e_id != -1) {
        for (int w = 1; w <= 26; ++w) {
          r_weights[w][v] = r_weights[w][p] + (edges[e_id][2] == w ? 1 : 0);
        }
      }

      for (const auto& [u, vu_id] : g[v]) {
        if (u != p) {
          dfs(u, v, vu_id);
        }
      }
      
      t_out[v] = ++timer;
    };

    timer = 0;
    dfs(0, 0, -1);

    auto is_ancestor = [&](int v, int anc) {
      return t_in[anc] <= t_in[v] && t_out[anc] >= t_out[v];
    };

    auto lca = [&](int v, int u) {
      if (is_ancestor(v, u))
        return u;
      if (is_ancestor(u, v))
        return v;
      for (int h = h_max; h >= 0; --h) {
        if (!is_ancestor(v, up[h][u]))
          u = up[h][u];
      }
      return up[0][u];
    };

    std::vector<int> res_ops(queries.size());
    for (int i = 0; i < static_cast<int>(queries.size()); ++i) {
      const auto v = queries[i][0];
      const auto u = queries[i][1];
      const auto x = lca(v, u);

      int max_cnt = 0;
      int max_cnt_w = 0;
      for (int w = 1; w <= 26; ++w) {
        const auto cnt = r_weights[w][v] + r_weights[w][u] - 2*r_weights[w][x];
        if (cnt > max_cnt) {
          max_cnt = cnt;
          max_cnt_w = w;
        }
      }
      int ops = 0;
      for (int w = 1; w <= 26; ++w) {
        if (w != max_cnt_w) {
          const auto cnt = r_weights[w][v] + r_weights[w][u] - 2*r_weights[w][x];
          ops += cnt;
        }
      }

      res_ops[i] = ops;
    }

    return res_ops;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    {
      const int n = 7;
      const std::vector<std::vector<int>> edges{{0,1,1},{1,2,1},{2,3,1},{3,4,2},{4,5,2},{5,6,2}};
      const std::vector<std::vector<int>> queries{{0,3},{3,6},{2,6},{0,6}};
      const auto a_out = Solution::minOperationsQueries(n, edges, queries);
      const std::vector<int> e_out{0,0,1,3};
      assert(a_out == e_out);
    }
    {
      const int n = 8;
      const std::vector<std::vector<int>> edges{{1,2,6},{1,3,4},{2,4,6},{2,5,3},{3,6,6},{3,0,8},{7,0,2}};
      const std::vector<std::vector<int>> queries{{4,6},{0,4},{6,5},{7,4}};
      const auto a_out = Solution::minOperationsQueries(n, edges, queries);
      const std::vector<int> e_out{1,2,2,3};
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
