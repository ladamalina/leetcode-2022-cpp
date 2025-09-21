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

class DSU {
public:
  explicit DSU(int n) : p_(vi(n)), r_(vi(n, 1)) {
    std::iota(p_.begin(), p_.end(), 0);
  }

  int Get(int a) {
    return p_[a] = (a == p_[a] ? a : Get(p_[a]));
  }

  void Union(int a, int b) {
    a = Get(a);
    b = Get(b);
    if (a == b) return;
    if (r_[a] == r_[b]) ++r_[a];
    if (r_[a] > r_[b]) p_[b] = a;
    else p_[a] = b;
  }

private:
  vi p_, r_;
};

constexpr int MAX_N = 1e5;
std::array<int, MAX_N> used;
std::array<ll, MAX_N> par_sum;

class Solution {
public:
  vl maximumSegmentSum(const vi& nums, const vi& queries) {
    const auto n = SZ(nums);
    std::fill(used.begin(), used.begin() + n, 0);
    std::fill(par_sum.begin(), par_sum.begin() + n, 0ll);

    vl res(n);
    std::multiset<ll> sums;
    DSU dsu(n);
    
    FORD(qi, n-1, 0) {
      const auto i = queries[qi];
      res[qi] = sums.empty() ? 0 : *sums.rbegin();

      if (i-1 >= 0 && used[i-1] && i+1 < n && used[i+1]) {
        const auto l_par = dsu.Get(i-1), r_par = dsu.Get(i+1);
        const auto l_sum = par_sum[l_par], r_sum = par_sum[r_par];
        sums.erase(sums.find(l_sum));
        sums.erase(sums.find(r_sum));
        dsu.Union(i-1, i);
        dsu.Union(i+1, i);
        const auto par = dsu.Get(i);
        par_sum[par] = l_sum + r_sum + nums[i];
        sums.insert(par_sum[par]);
      }

      else if (i-1 >= 0 && used[i-1]) {
        const auto l_par = dsu.Get(i-1);
        const auto l_sum = par_sum[l_par];
        sums.erase(sums.find(l_sum));
        dsu.Union(l_par, i);
        const auto par = dsu.Get(i);
        par_sum[par] = l_sum + nums[i];
        sums.insert(par_sum[par]);
      }

      else if (i+1 < n && used[i+1]) {
        const auto r_par = dsu.Get(i+1);
        const auto r_sum = par_sum[r_par];
        sums.erase(sums.find(r_sum));
        dsu.Union(r_par, i);
        const auto par = dsu.Get(i);
        par_sum[par] = r_sum + nums[i];
        sums.insert(par_sum[par]);
      }

      else {
        par_sum[i] = nums[i];
        sums.insert(par_sum[i]);
      }
      
      used[i] = 1;
    }

    return res;
  }
};

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
