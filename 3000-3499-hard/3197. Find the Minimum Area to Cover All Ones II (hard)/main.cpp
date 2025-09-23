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
using ld = long double;
using ii = std::pair<int, int>;
using vi = std::vector<int>;
using vvi = std::vector<vi>;
using vvvi = std::vector<vvi>;
using vl = std::vector<ll>;
using vvl = std::vector<vl>;
using vvvl = std::vector<vvl>;
using vii = std::vector<ii>;
using vb = std::vector<bool>;
using vd = std::vector<ld>;
using vs = std::vector<std::string>;
using vc = std::vector<char>;

#define FOR(_i, _a, _b) for (auto _i = (_a); _i <= (_b); ++(_i))
#define FORD(_i, _a, _b) for (auto _i = (_a); _i >= (_b); --(_i))
#define RNG(_l) (_l).begin(), (_l).end()
#define SORT(_l) std::sort((_l).begin(), (_l).end())
#define CI(_v) static_cast<int>(_v)
#define CL(_v) static_cast<ll>(_v)
#define CD(_v) static_cast<ld>(_v)
#define CC(_v) static_cast<char>(_v)
#define SZ(_v) static_cast<int>((_v).size())
#define F first
#define S second
#define PB push_back

int Split(const std::set<ii>& ps_ij, const std::set<ii>& ps_ji, bool split_next = false) {
  if (ps_ij.empty()) return 0;
  
  const auto ph = ps_ij.rbegin()->F - ps_ij.begin()->F + 1;
  const auto pw = ps_ji.rbegin()->F - ps_ji.begin()->F + 1;
  auto min_res = ph * pw;

  std::set<ii> a_ij, a_ji;
  auto b_ij = ps_ij, b_ji = ps_ji;

  const auto mn = ps_ij.begin()->F, mx = ps_ij.rbegin()->F;
  auto it = ps_ij.begin();
  FOR(ci, mn, mx) {
    bool upd = false;
    while (it != ps_ij.end() && it->F <= ci) {
      a_ij.insert(*it);
      b_ij.erase(*it);
      a_ji.emplace(it->S, it->F);
      b_ji.erase({it->S, it->F});
      it = std::next(it);
      upd = true;
    }
    if (!upd) continue;
    
    const auto ah = a_ij.empty() ? 0 : a_ij.rbegin()->F - a_ij.begin()->F + 1;
    const auto aw = a_ji.empty() ? 0 : a_ji.rbegin()->F - a_ji.begin()->F + 1;
    const auto bh = b_ij.empty() ? 0 : b_ij.rbegin()->F - b_ij.begin()->F + 1;
    const auto bw = b_ji.empty() ? 0 : b_ji.rbegin()->F - b_ji.begin()->F + 1;
    const auto a_res = ah * aw, b_res = bh * bw;
    min_res = std::min(min_res, a_res + b_res);
    
    if (a_res && b_res && split_next) {
      const auto asi = Split(a_ij, a_ji);
      const auto res_b_asi = b_res + asi;
      min_res = std::min(min_res, res_b_asi);

      const auto asj = Split(a_ji, a_ij);
      const auto res_b_asj = b_res + asj;
      min_res = std::min(min_res, res_b_asj);

      const auto bsi = Split(b_ij, b_ji);
      const auto res_a_bsi = a_res + bsi;
      min_res = std::min(min_res, res_a_bsi);

      const auto bsj = Split(b_ji, b_ij);
      const auto res_a_bsj = a_res + bsj;
      min_res = std::min(min_res, res_a_bsj);
    }
  }
  return min_res;
}

class Solution {
public:
  int minimumSum(const vvi& g) {
    const auto n = SZ(g), m = SZ(g[0]); // [1..30]
    std::set<ii> ps_ij, ps_ji;
    FOR(i, 0, n-1) {
      FOR(j, 0, m-1) {
        if (g[i][j] == 1) {
          ps_ij.emplace(i, j);
          ps_ji.emplace(j, i);
        }
      }
    }
    
    auto min_res = n * m;
    const auto si = Split(ps_ij, ps_ji, true);
    min_res = std::min(min_res, si);
    const auto sj = Split(ps_ji, ps_ij, true);
    min_res = std::min(min_res, sj);
    
    return min_res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi g{{1,0,1,0},{0,1,0,1}};
    const auto a_out = Solution().minimumSum(g);
    assert(a_out == 5);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi g{{1,0,1},{1,1,1}};
    const auto a_out = Solution().minimumSum(g);
    assert(a_out == 5);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi g{
          {0,0,0,0,0,0,0,0,0,0},
          {0,0,0,0,0,1,0,1,0,1},
          {0,0,0,0,0,0,0,0,0,0},
          {0,0,1,0,1,0,0,1,1,0},
          {1,0,1,1,1,0,0,0,0,0},
          {1,0,0,1,0,1,0,0,1,0},
          {0,0,1,1,0,1,0,1,1,0},
          {0,0,0,0,0,0,0,0,0,0},
          {0,0,0,0,0,0,0,0,0,0},
          {0,0,1,1,1,1,0,1,1,0}};
    const auto a_out = Solution().minimumSum(g);
    assert(a_out == 48);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi g{
      {0,1,1,0,0,0,0,0,1,1,1,1,1,1,0,1,0,1,0,0,0,0,0,1,1,1,0,1,1,1},
      {0,1,1,0,0,0,1,1,0,1,0,1,1,1,1,1,0,0,1,1,0,1,1,1,0,1,0,0,0,0},
      {1,1,0,1,0,1,1,0,0,0,1,0,0,1,1,0,0,0,1,0,1,0,0,1,1,0,1,1,1,1},
      {0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,1,0,1,0,0,1,1,1,1,0,1,0,1},
      {0,0,0,1,0,0,0,1,0,1,1,0,1,1,0,1,0,1,0,0,0,1,1,0,1,0,1,1,1,1},
      {1,0,1,1,1,0,0,1,0,1,0,0,0,1,1,0,0,0,0,0,0,0,0,1,0,1,0,0,1,1},
      {0,1,0,0,1,0,0,1,1,1,0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,1,0,0},
      {1,1,0,0,0,1,0,1,0,1,1,1,0,0,0,1,1,1,1,1,1,1,1,0,0,1,1,0,1,1},
      {0,1,0,0,1,0,0,1,1,0,0,0,0,0,0,1,1,0,1,1,1,0,1,1,1,1,0,0,1,1},
      {1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,0,0,0,0,0,0,0,1,1,0,1},
      {0,1,1,0,0,1,0,0,0,0,0,1,1,1,1,1,1,0,1,1,0,0,1,1,1,1,0,0,1,0},
      {0,1,1,0,1,1,0,0,0,1,0,1,1,1,1,1,1,1,0,1,0,1,1,1,0,0,1,1,1,0},
      {0,1,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,1,0,0,0,1,0,0,0,0,0,1,0,0},
      {1,1,1,0,1,1,0,1,1,0,0,1,0,1,0,0,1,0,1,0,1,1,0,0,0,1,0,0,0,0},
      {0,1,0,0,1,1,0,0,1,0,1,0,0,0,0,1,1,0,1,0,1,1,0,1,0,1,1,0,1,0},
      {1,0,1,0,0,0,1,1,1,1,0,0,1,0,1,1,0,1,0,0,0,1,1,1,0,0,1,1,0,0},
      {0,0,1,0,0,1,1,0,0,1,0,1,0,0,0,1,0,0,1,1,0,1,0,1,1,0,0,0,0,0},
      {0,1,0,1,0,0,0,0,1,1,0,0,0,0,1,0,0,1,0,0,0,0,0,1,1,1,0,0,0,1},
      {0,1,1,1,1,1,1,0,1,0,0,1,1,0,1,0,0,1,0,0,1,0,0,0,0,1,0,1,1,1},
      {1,1,0,0,0,0,0,0,1,0,0,1,1,1,0,0,1,0,1,0,1,0,0,1,1,1,0,0,1,0},
      {0,0,1,1,0,0,1,0,1,1,1,1,1,0,0,0,1,1,0,1,1,0,1,1,0,0,1,0,0,0},
      {0,0,1,1,0,0,0,0,0,0,0,1,0,1,1,1,1,1,1,0,0,1,1,0,0,0,1,0,1,1},
      {1,1,0,0,1,1,0,0,0,0,0,0,1,1,0,1,0,0,0,0,0,0,1,0,0,0,1,0,1,0},
      {0,1,0,1,0,1,0,1,0,0,1,1,0,0,1,1,1,1,1,0,0,0,1,0,1,1,0,1,1,0},
      {0,1,0,1,1,0,1,1,0,0,0,1,0,1,0,1,0,0,0,1,0,0,1,1,1,0,0,1,1,1},
      {1,1,0,0,1,1,0,1,0,1,1,1,0,1,0,0,1,1,0,1,1,0,1,0,1,1,1,0,1,1},
      {0,0,0,1,0,1,1,1,1,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,1,0,1,1,1,1},
      {0,1,0,0,0,1,0,0,0,0,0,0,1,0,0,1,0,1,0,1,1,1,1,0,0,1,0,1,1,0},
      {0,1,0,1,0,1,0,0,0,0,0,1,1,1,0,0,0,0,0,1,0,0,0,0,0,0,1,1,0,0},
      {1,1,1,1,1,0,0,1,0,1,0,1,0,0,0,1,1,1,0,0,0,1,1,1,0,1,0,0,1,0}};
    const auto a_out = Solution().minimumSum(g);
    assert(a_out == 890);
  
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
