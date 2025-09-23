// #include <bits/stdc++.h>

#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <deque>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <numeric>
#include <optional>
#include <random>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <variant>
#include <vector>

using namespace std::literals;

using ll = long long;
using ii [[maybe_unused]] = std::pair<int, int>;
using vi [[maybe_unused]] = std::vector<int>;
using vl [[maybe_unused]] = std::vector<ll>;
using vvi [[maybe_unused]] = std::vector<vi>;
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

constexpr int MAX_N = 1e5;
std::array<int, MAX_N> dist;

class Solution {
public:
  int minimumDiameterAfterMerge(const vvi& edges1, const vvi& edges2) {
    const auto g1 = BuildTree(edges1), g2 = BuildTree(edges2);
    const auto d1 = GetDiamater(g1), d2 = GetDiamater(g2);
    const auto d3 = (d1+1)/2 + (d2+1)/2 + 1;
    
    return std::max(d3, std::max(d1, d2));
  }

private:
  static vvi BuildTree(const vvi& edges) {
    vvi g;
    for (const auto& e : edges) {
      const auto v = e[0], u = e[1];
      if (SZ(g) <= std::max(v, u))
        g.resize(std::max(v, u)+1);
      g[v].push_back(u);
      g[u].push_back(v);
    }
    return g;
  }

  static ii BFS(const vvi& g, const int src) {
    const auto n = SZ(g);

    std::fill(dist.begin(), dist.begin()+n, -1);
    dist[src] = 0;
    
    std::queue<int> q;
    q.push(src);

    auto max_d = 0, max_d_v = src;
    
    while (!q.empty()) {
      const auto node = q.front();
      q.pop();
        
      for (int u : g[node]) {
        if (dist[u] == -1) {
          dist[u] = dist[node] + 1;
          q.push(u);
          if (dist[u] > max_d) {
            max_d = dist[u];
            max_d_v = u;
          }
        }
      }
    }

    return {max_d_v, max_d};
  }
  
  static int GetDiamater(const vvi& g) {
    const auto n = SZ(g);
    if (n == 0)
      return 0;

    // Находим самую удаленную вершину от произвольной начальной вершины (0)
    const auto bfs1 = BFS(g, 0);
    const auto far_v1 = bfs1.F;

    // Находим самую удаленную вершину от найденной вершины
    const auto bfs2 = BFS(g, far_v1);
    const auto d = bfs2.S;

    return d;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi edges1{{0,1},{2,0},{3,2},{3,6},{8,7},{4,8},{5,4},{3,5},{3,9}};
    const vvi edges2{{0,1},{0,2},{0,3}};
    const auto a_out = Solution().minimumDiameterAfterMerge(edges1, edges2);
    assert(a_out == 7);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi edges1{{0,1},{0,2},{0,3}};
    const vvi edges2{{0,1}};
    const auto a_out = Solution().minimumDiameterAfterMerge(edges1, edges2);
    assert(a_out == 3);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi edges1{{0,1},{0,2},{0,3},{2,4},{2,5},{3,6},{2,7}};
    const vvi edges2{{0,1},{0,2},{0,3},{2,4},{2,5},{3,6},{2,7}};
    const auto a_out = Solution().minimumDiameterAfterMerge(edges1, edges2);
    assert(a_out == 5);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi edges1{};
    const vvi edges2{};
    const auto a_out = Solution().minimumDiameterAfterMerge(edges1, edges2);
    assert(a_out == 1);
  
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
