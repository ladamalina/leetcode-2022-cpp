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

[[maybe_unused]] constexpr int MAX_N = 1e5;
std::array<int, MAX_N> b_path, v_b_num;

class Solution {
public:
  int mostProfitablePath(const vvi& edges, int bob, const vi& amount) {
    const auto n = SZ(edges) + 1;
    
    vvi g(n);
    for (const auto& e : edges) {
      g[e[0]].push_back(e[1]);
      g[e[1]].push_back(e[0]);
    }

    auto nb = 0;
    const std::function<bool(int,int,int)> dfs1 = [&](int v, int p, int d) {
      b_path[d] = v;
      if (v == bob) {
        nb = d + 1;
        return true;
      }
      for (const auto u : g[v]) {
        if (u != p) {
          const auto u_res = dfs1(u, v, d + 1);
          if (u_res)
            return true;
        }
      }
      return false;
    };
    [[maybe_unused]] const auto b_found = dfs1(0, -1, 0);
    std::reverse(b_path.begin(), b_path.begin() + nb);
    
    std::fill(v_b_num.begin(), v_b_num.begin() + n, -1);
    FOR(i, 0, nb-1) {
      v_b_num[b_path[i]] = i;
    }

    const std::function<int(int,int,int)> dfs2 = [&](int v, int p, int d) {
      int v_score = 0;
      if (v_b_num[v] != -1 && v_b_num[v] < d) {
        v_score = 0;
      } else if (v_b_num[v] == d) {
        v_score = amount[v] / 2;
      } else if (v_b_num[v] > d) {
        v_score = amount[v];
      } else { // v_b_num[v] == -1
        v_score = amount[v];
      }

      int max_u_score = INT_MIN;
      for (const auto u : g[v]) {
        if (u != p) {
          max_u_score = std::max(max_u_score, dfs2(u, v, d + 1));
        }
      }

      return v_score + (max_u_score == INT_MIN ? 0 : max_u_score);
    };
    const auto max_score = dfs2(0, -1, 0);

    return max_score;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi edges{{0,1},{1,2},{1,3},{3,4}};
    const vi amount{-2,4,2,-4,6};
    const auto a_out = Solution().mostProfitablePath(edges, 3, amount);
    assert(a_out == 6);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi edges{{0,1}};
    const vi amount{-7280,2350};
    const auto a_out = Solution().mostProfitablePath(edges, 1, amount);
    assert(a_out == -7280);
  
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
