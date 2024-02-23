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
using vvii [[maybe_unused]] = std::vector<vii>;
using vs [[maybe_unused]] = std::vector<std::string>;
using vvs [[maybe_unused]] = std::vector<vs>;
using vc [[maybe_unused]] = std::vector<char>;
using vvc [[maybe_unused]] = std::vector<vc>;

#define FOR(_i, _a, _b) for (int _i = (_a); _i <= (_b); ++(_i))
#define FORD(_i, _a, _b) for (int _i = (_a); _i >= (_b); --(_i))
#define RNG(_l) (_l).begin(), (_l).end()
#define SORT(_l) std::sort((_l).begin(), (_l).end())
#define CI(_v) static_cast<int>(_v)
#define CL(_v) static_cast<ll>(_v)
#define F first
#define S second

constexpr int MAX_N = 1e5;
std::array<int, MAX_N+1> prime_i;

template<typename T>
std::vector<T> GetPrimeFactors(T x) {
  std::vector<T> fs;

  while (x % 2 == 0) {
    if (fs.empty() || fs.back() != 2)
      fs.push_back(2);
    x /= 2;
  }
  for (T i = 3; i <= std::sqrt(x); i += 2) {
    while (x % i == 0) {
      if (fs.empty() || fs.back() != i)
        fs.push_back(i);
      x /= i;
    }
  }
  if (x > 2)
    if (fs.empty() || fs.back() != x)
      fs.push_back(x);

  return fs;
}

std::array<int, MAX_N> p_, r_;
class DSU {
 public:
  explicit DSU(size_t n) {
    std::iota(p_.begin(), p_.begin()+n, 0);
    std::fill(r_.begin(), r_.begin()+n, 1);
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
};

class Solution {
 public:
  static bool canTraverseAllPairs(const vi& nums) {
    const auto n = CI(nums.size());
    const auto max_num = *std::max_element(RNG(nums));
    std::fill(prime_i.begin(), prime_i.begin()+max_num+1, -1);
    DSU dsu(n);
    FOR(i, 0, n-1) {
      const auto p_freq = GetPrimeFactors(nums[i]);
      for (const auto& f : p_freq) {
        if (prime_i[f] != -1) {
          dsu.Union(i, prime_i.at(f));
        } else {
          prime_i[f] = i;
        }
      }
    }
    bool ok = true;
    FOR(i, 0, n-2) {
      if (dsu.Get(i) != dsu.Get(i+1)) {
        ok = false;
        break;
      }
    }
    return ok;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto a_out = Solution::canTraverseAllPairs({2,3,6});
    assert(a_out);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto a_out = Solution::canTraverseAllPairs({3,9,5});
    assert(!a_out);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto a_out = Solution::canTraverseAllPairs({4,3,12,8});
    assert(a_out);

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
