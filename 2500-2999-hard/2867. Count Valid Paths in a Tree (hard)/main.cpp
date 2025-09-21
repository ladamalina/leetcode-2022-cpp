// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;

using ll = long long;
using ii = std::pair<int, int>;
using vi = std::vector<int>;
using vii = std::vector<ii>;

constexpr int MAX_N = 100000;

std::bitset<MAX_N+1> PrecomputePrimes() {
  std::bitset<MAX_N+1> is_prime{};
  is_prime.set();
  is_prime[0] = is_prime[1] = false;

  for (int i = 4; i <= MAX_N; i += 2) {
    is_prime[i] = false;
  }

  for (int i = 3; i * i <= MAX_N; i += 2) {
    if (is_prime[i]) {
      for (auto j = i * i; j <= MAX_N; j += i) {
        is_prime[j] = false;
      }
    }
  }
  return is_prime;
}

bool init_primes = false;
std::bitset<MAX_N+1> IS_PRIME;

struct QItem {
  int v, p, prev_sz;
  QItem(int v_, int p_, int prev_sz_) : v(v_), p(p_), prev_sz(prev_sz_) {}
};

class Solution {
  public:
  Solution() {
    if (!init_primes) {
      IS_PRIME = PrecomputePrimes();
      init_primes = true;
    }
  }

  ll countPaths(const int n, const std::vector<std::vector<int>>& edges) {
    if (n == 1) return 0;
    
    std::vector<std::vector<int>> g(n+1);
    for (const auto& e : edges) {
      g[e[0]].push_back(e[1]);
      g[e[1]].push_back(e[0]);
    }

    ll res = 0;
    std::queue<QItem> q;
    vii prime_vs;
    prime_vs.reserve(n);

    std::function<int(int,int)> dfs = [&](int v, int p) {
      if (IS_PRIME[v]) {
        prime_vs.emplace_back(v, p);
        return 0;
      }
      int sub_res = 1;
      for (const auto u : g.at(v)) {
        if (u != p) {
          sub_res += dfs(u, v);
        }
      }
      return sub_res;
    };
    
    q.emplace(2, -1, 0);
    while (!q.empty()) {
      const auto v = q.front().v;
      const auto p = q.front().p;
      const auto prev_sz = q.front().prev_sz;
      q.pop();

      res += prev_sz;
      int v_sub = prev_sz;
      for (const auto u : g.at(v)) {
        if (u == p) continue;
        prime_vs.clear();
        
        const auto u_sub = dfs(u, v);
        res += u_sub + u_sub*v_sub;
        v_sub += u_sub;

        for (const auto& prime_v : prime_vs) {
          q.emplace(prime_v.first, prime_v.second, u_sub);
        }
      }
    }

    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::vector<std::vector<int>> edges{{1,2},{1,3},{2,4},{2,5}};
    const auto a_out = Solution().countPaths(edges.size()+1, edges);
    assert(a_out == 4);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::vector<std::vector<int>> edges{{1,2},{1,3},{2,4},{3,5},{3,6}};
    const auto a_out = Solution().countPaths(edges.size()+1, edges);
    assert(a_out == 6);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    std::vector<std::vector<int>> edges(10000);
    for (int i = 1; i <= 100000; ++i)
      edges[i-1] = {1, i};
    const auto a_out = Solution().countPaths(edges.size()+1, edges);
    assert(a_out == 97016031);

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
