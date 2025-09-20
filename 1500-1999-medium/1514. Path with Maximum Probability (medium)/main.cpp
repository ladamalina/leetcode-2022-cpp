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

class Solution {
public:
  double maxProbability(int n, const vvi& edges, const vd& succProb, int start_node, int end_node) {
    const auto en = SZ(edges);
    std::vector<std::vector<std::pair<int, double>>> g(n);
    FOR(i, 0, en-1) {
      const auto v = edges[i][0], u = edges[i][1];
      g[v].emplace_back(u, succProb[i]);
      g[u].emplace_back(v, succProb[i]);
    }

    vd prob(n);
    std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, std::less<>> pq;
    pq.emplace(1, start_node);
    while (!pq.empty()) {
      const auto v_prob = pq.top().F;
      const auto v = pq.top().S;
      pq.pop();
      if (v_prob <= prob[v])
        continue;
      prob[v] = v_prob;
      if (v == end_node)
        break;
      for (const auto& [u, vu_prob] : g[v]) {
        const auto u_prob = v_prob * vu_prob;
        if (u_prob > prob[u])
          pq.emplace(u_prob, u);
      }
    }

    return prob[end_node];
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi edges{{0,1},{1,2},{0,2}};
    const vd succProb{0.5,0.5,0.2};
    const auto a_out = Solution().maxProbability(3, edges, succProb, 0, 2);
    // assert(a_out == 6);
    std::cerr << a_out << '\n';
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi edges{{0,1},{1,2},{0,2}};
    const vd succProb{0.5,0.5,0.3};
    const auto a_out = Solution().maxProbability(3, edges, succProb, 0, 2);
    // assert(a_out == 6);
    std::cerr << a_out << '\n';
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi edges{{0,1}};
    const vd succProb{0.5};
    const auto a_out = Solution().maxProbability(3, edges, succProb, 0, 2);
    // assert(a_out == 6);
    std::cerr << a_out << '\n';
  
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
