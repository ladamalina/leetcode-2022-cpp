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

class Graph {
public:
  Graph(const int n, const vvi& edges) : n_(n), d_(vvi(n_, vi(n_, INT_MAX))) {
    for (auto i = 0; i < n_; ++i)
      d_[i][i] = 0;
    for (const auto& e : edges)
      d_[e[0]][e[1]] = e[2];
    for (auto k = 0; k < n_; ++k)
      for (auto i = 0; i < n_; ++i)
        for (auto j = 0; j < n_; ++j)
          if (d_[i][k] < INT_MAX && d_[k][j] < INT_MAX)
            d_[i][j] = std::min(d_[i][j], d_[i][k] + d_[k][j]);
  }

  void addEdge(const vi& edge) {
    const auto v = edge[0], u = edge[1], w = edge[2];
    d_[v][u] = std::min(d_[v][u], w);
    for (auto i = 0; i < n_; ++i)
      for (auto j = 0; j < n_; ++j)
        if (d_[i][v] < INT_MAX && d_[u][j] < INT_MAX)
          d_[i][j] = std::min(d_[i][j], d_[i][v] + d_[u][j] + w);
  }

  int shortestPath(const int node1, const int node2) {
    return (d_[node1][node2] == INT_MAX) ? -1 : d_[node1][node2];
  }

private:
  int n_;
  vvi d_;
};

/**
 * Your Graph object will be instantiated and called as such:
 * Graph* obj = new Graph(n, edges);
 * obj->addEdge(edge);
 * int param_2 = obj->shortestPath(node1,node2);
 */

[[maybe_unused]] void TestSolution() {
  /*{
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().solve();
    assert(a_out == 6);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }*/
  std::cerr << "TestSolution OK"sv << std::endl;
}

int main() {
#ifndef NDEBUG
  TestSolution();
#endif
  return 0;
}
