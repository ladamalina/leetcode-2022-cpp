//#include <bits/stdc++.h>

#include <algorithm>
#include <cassert>
#include <chrono>
#include <cmath>
#include <deque>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <optional>
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
#define F first
#define S second

constexpr int MAX_N = 1e5;
std::array<int, MAX_N> colors; // 0 – white, 1 – grey, 2 – black
std::array<int, MAX_N> min_v_to_cycle_len;
std::array<int, MAX_N> curr_cycle;
std::array<int, MAX_N> dist_to_cycle;
std::array<int, MAX_N> cycle_enter_v;

struct Res {
  int status = -1; // -1 - unvisited, 0 – looking, 1 - collecting, 2 - collected
  int cycle_v_begin = -1;
  int curr_cycle_len = -1;
  int curr_cycle_min_v = INT_MAX;
};
std::array<Res, MAX_N> res;

void DFS(int v, const vi& fav) {
  if (res[v].status != -1)
    return;
  auto& v_res = res[v];
  
  colors[v] = 1;

  const auto u = fav[v];
  auto& u_res = res[u];
  if (colors[u] == 0) { // 0 – white
    DFS(u, fav);
    if (u_res.status == 1) {
      curr_cycle[u_res.curr_cycle_len] = u;
      dist_to_cycle[v] = 0;
      cycle_enter_v[v] = v;
      if (v == u_res.cycle_v_begin) {
        v_res = {2, u_res.cycle_v_begin, u_res.curr_cycle_len+1, std::min(v, u_res.curr_cycle_min_v)};
        min_v_to_cycle_len[v_res.curr_cycle_min_v] = v_res.curr_cycle_len;
        FOR(i, 0, v_res.curr_cycle_len-1) {
          res[curr_cycle[i]].curr_cycle_min_v = v_res.curr_cycle_min_v;
        }
      } else {
        v_res = {1, u_res.cycle_v_begin, u_res.curr_cycle_len+1, std::min(v, u_res.curr_cycle_min_v)};
      }
      u_res.status = 2;
    } else if (u_res.status == 2) {
      v_res = u_res;
      dist_to_cycle[v] = dist_to_cycle[u] + 1;
      cycle_enter_v[v] = cycle_enter_v[u];
    }
  } else if (colors[u] == 1) { // 1 – grey
    v_res = {1, u, 1, std::min(v, u)};
    curr_cycle[0] = u;
    dist_to_cycle[v] = 0;
    cycle_enter_v[v] = v;
  } else { // 2 – black
    v_res = u_res;
    dist_to_cycle[v] = dist_to_cycle[u] + 1;
    cycle_enter_v[v] = cycle_enter_v[u];
  }
  
  colors[v] = 2;
}

class Solution {
 public:
  static int maximumInvitations(const vi& fav) {
    const auto n = CI(fav.size());

    std::fill(colors.begin(), colors.begin()+n, 0);
    std::fill(min_v_to_cycle_len.begin(), min_v_to_cycle_len.begin()+n, 0);
    std::fill(res.begin(), res.begin()+n, Res{});
    
    int max_cycle_len = 0;
    std::unordered_map<int, std::map<int, int>> dists;
    FOR(v, 0, n-1) {
      DFS(v, fav);
      const auto& v_res = res[v];
      const auto cycle_id = v_res.curr_cycle_min_v;
      const auto curr_cycle_len = min_v_to_cycle_len[cycle_id];
      max_cycle_len = std::max(max_cycle_len, curr_cycle_len);
      if (curr_cycle_len == 2) {
        auto& v_dist = dists[cycle_id][cycle_enter_v[v]];
        v_dist = std::max(v_dist, dist_to_cycle[v]);
      }
    }
    int sum2 = 0;
    for (const auto& [_, enters] : dists) {
      if (enters.size() == 1) {
        sum2 += 2 + enters.rbegin()->S;
      } else if (enters.size() == 2) {
        sum2 += 2 + enters.rbegin()->S + std::prev(std::prev(enters.end()))->S;
      }
    }
    return std::max(max_cycle_len, sum2);
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    auto a_out = Solution::maximumInvitations({2,2,1,2});
    assert(a_out == 3);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    auto a_out = Solution::maximumInvitations({1,2,0});
    assert(a_out == 3);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    auto a_out = Solution::maximumInvitations({3,0,1,4,1});
    assert(a_out == 4);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    auto a_out = Solution::maximumInvitations({1,0,0,2,1,4,7,8,9,6,7,10,8});
    assert(a_out == 6);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    auto a_out = Solution::maximumInvitations({1,0,3,2,5,6,7,4,9,8,11,10,11,12,10});
    assert(a_out == 11);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    auto a_out = Solution::maximumInvitations({7,12,17,9,0,7,14,5,3,15,6,14,10,14,10,1,1,4});
    assert(a_out == 6);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    auto a_out = Solution::maximumInvitations({9,14,15,8,22,15,12,11,10,7,1,12,15,6,5,12,10,21,4,1,16,3,7});
    assert(a_out == 15);

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
