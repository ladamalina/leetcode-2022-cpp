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

constexpr int MAX_N = 1e6;
bool init = false;
vi PRIMES;

template <typename T>
std::vector<T> PrecomputePrimes(const T high) {
  vi is_prime(high + 1, 1);
  is_prime[0] = is_prime[1] = 0;

  for (T i = 4; i <= high; i += 2) {
    is_prime[i] = 0;
  }

  for (T i = 3; i * i <= high; i += 2) {
    if (is_prime[i]) {
      for (auto j = i * i; j <= high; j += i) {
        is_prime[j] = 0;
      }
    }
  }
  std::vector<T> primes{2};
  for (T i = 3; i <= high; i += 2) {
    if (is_prime[i]) primes.push_back(i);
  }

  return primes;
}

class Solution {
public:
  vi closestPrimes(const int l, const int r) {
    if (!init) {
      PRIMES = PrecomputePrimes(MAX_N);
      init = true;
    }
    const auto li = CI(std::lower_bound(RNG(PRIMES), l) - PRIMES.begin());
    const auto ri = CI(std::upper_bound(RNG(PRIMES), r) - PRIMES.begin());
    if (li >= ri) {
      return vi{-1, -1};
    }
    
    int min_dist = INT_MAX, a = -1, b = -1;
    for (auto i = li + 1; i < ri; ++i) {
      const auto d = PRIMES[i] - PRIMES[i-1];
      if (d < min_dist) {
        min_dist = d;
        a = PRIMES[i-1];
        b = PRIMES[i];
      }
    }
    if (min_dist == INT_MAX) {
      return vi{-1, -1};
    }
    return vi{a, b};
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
