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

[[maybe_unused]] constexpr int MAX_S = 7;
[[maybe_unused]] constexpr int MAX_N = 1e5;
std::array<int, MAX_S+1> prev_s, next_s;
std::array<int, MAX_N> scores, prev_i, next_i;

[[maybe_unused]] constexpr ll MOD = 1e9 + 7;

template <typename T>
[[maybe_unused]] T ModPow(T a, T x, T m) {
  T ret = 1;
  while (x) {
    if (x & 1) ret = (ret * a) % m;
    x = (x >> 1);
    a = (a * a) % m;
  }
  return ret;
}

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

class Solution {
public:
  int maximumScore(const vi& nums, ll k) {
    const auto n = SZ(nums);
    std::priority_queue<ii, vii, std::less<>> pq;
    FOR(i, 0, n-1) {
      scores[i] = SZ(GetPrimeFactors(nums[i]));
      pq.emplace(nums[i], i);
    }

    std::fill(RNG(prev_s), -1);
    std::fill(RNG(next_s), n);
    std::fill(prev_i.begin(), prev_i.begin() + n, -1);
    std::fill(next_i.begin(), next_i.begin() + n, n);
    FOR(i, 1, n-1) {
      FOR(s, 1, MAX_S) prev_s[s] = (scores[i-1] == s) ? i-1 : prev_s[s];
      FOR(s, scores[i], MAX_S) prev_i[i] = std::max(prev_i[i], prev_s[s]);
    }
    FORD(i, n-2, 0) {
      FOR(s, 1, MAX_S) next_s[s] = (scores[i+1] == s) ? i+1 : next_s[s];
      FOR(s, scores[i]+1, MAX_S) next_i[i] = std::min(next_i[i], next_s[s]);
    }

    ll res = 1;
    while (!pq.empty() && k > 0) {
      const auto [x, i] = pq.top();
      pq.pop();
      const auto max_blocks = CL(i - prev_i[i]) * CL(next_i[i] - i);
      const auto pow = std::min(max_blocks, k);
      // std::cerr << x << ' ' << pow << '\n';
      res = (res * ModPow(CL(x), pow, MOD)) % MOD;
      k -= pow;
    }
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums{8,3,9,3,8};
    const auto a_out = Solution().maximumScore(nums, 2);
    assert(a_out == 81);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums{19,12,14,6,10,18};
    const auto a_out = Solution().maximumScore(nums, 3);
    assert(a_out == 4788);
  
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
