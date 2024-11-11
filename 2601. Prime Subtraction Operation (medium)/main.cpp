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

template <typename T>
std::vector<T> PrecomputePrimes(const T high) {
  vb is_prime(high + 1, true);
  is_prime[0] = is_prime[1] = false;

  for (T i = 4; i <= high; i += 2) {
    is_prime[i] = false;
  }

  for (T i = 3; i * i <= high; i += 2) {
    if (is_prime[i]) {
      for (auto j = i * i; j <= high; j += i) {
        is_prime[j] = false;
      }
    }
  }
  std::vector<T> primes{2};
  for (T i = 3; i <= high; i += 2) {
    if (is_prime[i]) primes.push_back(i);
  }

  return primes;
}

constexpr int MAX_X = 1000;
vi PRIMES;
bool init_primes = false;

class Solution {
public:
  bool primeSubOperation(vi& nums) {
    const auto n = SZ(nums);

    if (!init_primes) {
      PRIMES = PrecomputePrimes(MAX_X);
      init_primes = true;
    }
    
    FORD(i, n-2, 0) {
      if (nums[i] >= nums[i+1]) {
        const auto it = std::upper_bound(RNG(PRIMES), nums[i] - nums[i+1]);
        if (it != PRIMES.end() && *it < nums[i]) {
          nums[i] -= *it;
          continue;
        }
        return false;
      }
    }
    return true;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi nums{4,9,6,10};
    const auto a_out = Solution().primeSubOperation(nums);
    assert(a_out);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi nums{6,8,11,12};
    const auto a_out = Solution().primeSubOperation(nums);
    assert(a_out);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi nums{5,8,3};
    const auto a_out = Solution().primeSubOperation(nums);
    assert(!a_out);
  
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
