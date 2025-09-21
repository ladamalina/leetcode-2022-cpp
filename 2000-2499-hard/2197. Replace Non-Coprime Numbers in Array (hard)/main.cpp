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

template <typename T>
std::unordered_map<T, int> GetPrimeFactors(T x) {
  std::unordered_map<T, int> freq;

  while (x % 2 == 0) {
    ++freq[2];
    x /= 2;
  }
  for (T i = 3; i*i <= x; i += 2) {
    while (x % i == 0) {
      ++freq[i];
      x /= i;
    }
  }
  if (x > 2) ++freq[x];

  return freq;
}

ll FastPow(ll a, ll x) {
  if (x == 0) return 1;
  if (x == 1) return a;
  
  ll ret = 1;
  while (x) {
    if (x & 1) ret *= a;
    x = (x >> 1);
    a *= a;
  }
  return ret;
}

void Propagate(vi& res, std::vector<std::unordered_map<int, int>>& res_freq) {
  while (SZ(res) > 1) {
    const auto n = SZ(res);
    const auto is_coprime = std::all_of(RNG(res_freq[n-1]),
        [&](const ii& pf) { return !res_freq[n-2].contains(pf.F); });
    if (is_coprime) break;
    for (const auto& [p, f] : res_freq[n-1]) {
      const auto add = std::max(0, f - res_freq[n-2][p]);
      if (add) {
        res[n-2] *= FastPow(p, add);
        res_freq[n-2][p] += add;
      }
    }
    res.pop_back();
    res_freq.pop_back();
  }
}

class Solution {
public:
  vi replaceNonCoprimes(const vi& nums) {
    const auto n = SZ(nums);
    vi res{nums[0]};
    std::vector<std::unordered_map<int, int>> res_freq{GetPrimeFactors(nums[0])};
    FOR(i, 1, n-1) {
      res.push_back(nums[i]);
      res_freq.push_back(GetPrimeFactors(nums[i]));
      Propagate(res, res_freq);
    }

    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums{6,4,3,2,7,6,2};
    const vi e_out{12,7,6};
    const auto a_out = Solution().replaceNonCoprimes(nums);
    assert(a_out == e_out);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums{2,2,1,1,3,3,3};
    const vi e_out{2,1,1,3};
    const auto a_out = Solution().replaceNonCoprimes(nums);
    assert(a_out == e_out);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums{
        90359, 90359, 90359, 90359, 90359, 90359, 90359, 90359, 90359, 90359, 90359, 90359, 90359, 90359, 90359, 90359,
        90359, 90359, 90359, 90359, 90359, 2,     67154, 2,     2,     2,     2,     67154, 4,     67154, 4,     67154,
        33577, 33577, 33577, 2,     2,     4,     2,     2,     2,     2,     2,     2,     75323, 75323, 75323, 75323,
        75323, 75323, 75323, 75323, 75323, 75323, 75323, 75323, 75323, 75323, 75323, 75323, 75323, 75323, 75323, 75323,
        75323, 75323, 75323, 75323, 75323, 75323, 75323, 75323, 75323, 75323, 75323, 75323, 75323, 75323, 75323, 75323,
        75323, 75323, 75323, 75323, 75323, 75323, 75323, 75323, 75323, 75323, 75323, 75323, 13,    169,   13,    169,
        13,    169,   13,    221,   13,    221,   13,    13,    169,   169,   13,    13,    13,    13,    221,   221,
        169,   221,   13,    13,    13,    13,    13,    221,   221,   169,   169,   13,    13,    13,    13,    13,
        221,   169,   13,    169,   221,   13,    221,   13,    221,   169,   221,   221,   13,    13,    221,   221,
        169,   13,    13,    221,   221,   169,   169,   13,    169,   169,   169,   13,    221,   17,    221,   13,
        13,    169,   13,    169,   221,   221,   13,    221,   221,   221,   13,    169,   169,   169,   13,    221,
        221,   221,   13,    169,   221,   221,   221,   221,   221,   17,    169,   221,   13,    221,   13,    13,
        13,    169,   221,   13,    169,   221,   221,   221,   221,   17,    17,    13,    13,    169,   169,   13,
        169,   13,    13,    221,   169,   169,   13,    13,    169,   13,    13,    13,    13,    221,   221,   13,
        13,    13,    13,    221,   169,   221,   221,   13,    13,    13,    221,   169,   13,    169,   13,    221,
        13,    221,   13,    13,    13,    13,    13,    221,   221,   13,    13,    169,   13,    169,   13,    13,
        169,   13,    13,    13,    169,   13,    94,    94,    94,    2,     2,     2,     4,     4,     2,     2,
        4,     2,     2,     2,     2,     2,     4,     2,     94,    2,     2,     2,     94,    2,     2,     2,
        4,     2,     4,     2,     94,    3,     27,    3,     3,     99,    33,    9,     33,    9,     99,    9,
        3,     9,     9,     3,     9,     3,     33,    9,     33,    3,     9,     99,    3,     3,     3,     99,
        99,    99,    99,    3,     3,     27,    27,    27,    3,     27,    2,     4,     4,     4,     4,     2,
        4,     93658, 2,     2,     2,     4,     2,     4,     93658, 93658, 2,     4,     17,    289,   289,   17,
        289,   289,   493,   493,   289,   493,   289,   289,   493,   289,   17,    289,   289,   17,    289,   493,
        17,    493,   289,   17,    289,   17,    17,    289,   289,   17,    17,    12253, 12253, 12253, 12253, 12253,
        12253, 12253, 1122,  2,     4,     12,    66,    6,     66,    2,     2,     2,     34,    102,   726,   11,
        22,    2,     68,    22,    2,     204,   102,   198,   3,     23,    23,    23,    23,    23,    23,    23,
        23,    23,    23,    23,    23,    23,    23,    23,    23,    23,    23,    23,    23,    23,    23,    23,
        23,    23,    23,    23,    23,    23,    23,    23,    23,    23,    23,    23,    23,    23,    425,   3145,
        85,    2,     4,     2,     2,     2,     4,     2,     46198, 2,     2,     2,     4,     46198, 2,     4,
        2,     2,     4,     4,     2,     4,     2,     4,     46198, 46198, 2,     46198, 2,     4,     46198, 2,
        2,     46198, 2,     2,     4,     4,     4,     2,     2,     46198, 23099, 46198, 4,     4,     46198, 2,
        46198, 2,     2,     46198, 2,     2,     2,     2,     4,     4,     4,     2,     2,     2,     46198, 2,
        2,     2,     4,     4,     2,     4,     4,     2,     4,     2,     4,     2,     2,     2,     2,     46198,
        2,     2,     2,     46198, 23099, 46198, 2,     2,     2,     4,     46198, 23099, 4,     46198, 23099, 2,
        2,     2,     2,     2,     4,     4,     2,     2,     2,     2,     2,     2,     46198, 46198, 2,     2,
        2,     2,     2,     46198, 4,     2,     4,     46198, 2,     2,     2,     2,     4,     2,     46198, 2,
        2,     2,     2,     4,     2,     4,     46198, 2,     4,     46198, 46198, 23099, 4,     2,     2,     2,
        4,     2,     4,     2,     2,     46198, 2,     2,     2,     4,     4,     2,     4,     2,     2,     2,
        2,     2,     2,     4,     4,     2,     2,     2,     4,     4,     2,     46198, 4,     46198, 2,     2,
        4,     2,     4,     2,     4,     46198, 4,     4,     46198, 2,     2,     2,     2,     2,     46198, 2,
        46198, 2,     2,     46198, 23099, 23099, 23099, 46198, 46198, 46198, 4,     46198, 2,     4,     4,     2,
        4,     2,     4,     4,     46198, 2,     46198, 2,     46198, 23099, 46198, 4,     2,     4,     4,     2,
        2,     2,     2,     4,     2,     2,     2,     2,     2,     2,     2,     4,     2,     2,     2,     4,
        4,     2,     2,     4,     4,     2,     4,     46198, 23099, 2,     46198, 4,     2,     46198, 2,     46198,
        4,     46198, 46198, 4,     2,     2,     2,     46198, 46198, 4,     2,     4,     2,     46198, 2,     4,
        2,     4,     2,     2,     46198, 2,     46198, 2,     46198, 4,     2,     4,     2,     2,     2,     4,
        2,     46198, 2,     4,     2,     2,     46198, 2,     2,     4,     2,     4,     2,     4,     4,     46198,
        23099, 46198, 2,     2,     2,     46198, 2,     2,     4,     46198, 4,     2,     2,     4,     46198, 46198,
        4,     4,     46198, 2,     2,     4,     46198, 2,     2,     2,     46198, 4,     46198, 4,     2,     2,
        2,     4,     46198, 2,     2,     4,     4,     2,     2,     4,     2,     2,     2,     4,     46198, 2,
        2,     2,     46198, 4,     4,     2,     2,     2,     4,     46198, 23099, 2,     2,     2,     46198, 4,
        46198, 2,     2,     2,     2,     46198, 4,     46198, 23099, 2,     46198, 2,     46198, 2,     4,     2,
        46198, 46198, 2,     46198, 23099, 2,     2,     46198, 4,     46198, 2,     46198, 23099, 46198, 46198, 2,
        2,     2,     4,     46198, 2,     4,     2,     46198, 46198, 4,     4,     46198, 2,     2,     4,     2,
        46198, 2,     2,     4,     46198, 2,     46198, 4,     2,     2,     4,     2,     4,     2,     46198, 4,
        4,     2,     2,     2,     4,     2,     4,     46198, 2,     46198, 4,     46198, 4,     46198, 2,     2,
        4,     2,     46198, 2,     2,     4,     46198, 4,     2,     46198, 2,     46198, 2,     46198, 46198, 2,
        4,     46198, 23099, 23099, 46198, 2,     2,     2,     4,     4,     4,     2,     4,     4};
    // const vi e_out{2,1,1,3};
    const auto a_out = Solution().replaceNonCoprimes(nums);
    assert(!a_out.empty());
  
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
