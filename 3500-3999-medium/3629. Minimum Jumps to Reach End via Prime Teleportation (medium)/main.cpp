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
std::vector<T> GetPrimeFactors(T x) {
  std::vector<T> res;
  while (x % 2 == 0) {
    if (res.empty()) res.push_back(2);
    x /= 2;
  }
  for (T i = 3; i*i <= x; i += 2) {
    while (x % i == 0) {
      if (res.empty() || res.back() != i) res.push_back(i);
      x /= i;
    }
  }
  if (x > 2) res.push_back(x);
  return res;
}

class Solution {
public:
  int minJumps(const vi& nums) {
    const auto n = SZ(nums);

    const auto max_x = *std::max_element(RNG(nums));
    vvi x_ids(max_x + 1);
    FOR(i, 0, n-1) x_ids[nums[i]].push_back(i);

    vvi i_pfs(n); // list of prime factors of nums[i]
    vvi p_mx_ids(max_x + 1); // list of indices of multiplies if prime p
    FOR(i, 0, n-1) {
      const auto x_i0 = x_ids[nums[i]][0];
      i_pfs[i] = (x_i0 == i) ? GetPrimeFactors(nums[i]) : i_pfs[x_i0];
      for (const auto p : i_pfs[i]) {
        p_mx_ids[p].push_back(i);
      }
    }

    vb is_prime(max_x + 1, true);
    is_prime[0] = is_prime[1] = false;
    FOR(x, 2, max_x) {
      if (is_prime[x]) {
        for (auto mx = (x << 1); mx <= max_x; mx += x) {
          is_prime[mx] = false;
        }
      }
    }

    vi dist(n, INT_MAX);
    dist[0] = 0;
    std::queue<ii> q; // <dist, i>
    q.emplace(0, 0);
    while (!q.empty()) {
      const auto [d, i] = q.front();
      q.pop();
      if (i == n-1) break;
      if (i - 1 >= 0 && d + 1 < dist[i-1]) {
        dist[i-1] = d + 1;
        q.emplace(d + 1, i - 1);
      }
      if (i + 1 < n && d + 1 < dist[i+1]) {
        dist[i+1] = d + 1;
        q.emplace(d + 1, i + 1);
      }
      if (is_prime[nums[i]]) {
        for (const auto j : p_mx_ids[nums[i]]) {
          if (d + 1 < dist[j]) {
            dist[j] = d + 1;
            q.emplace(d + 1, j);
          }
        }
        p_mx_ids[nums[i]].clear();
      }
    }
    return dist[n-1];
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums{4,6,5,8};
    const auto a_out = Solution().minJumps(nums);
    assert(a_out == 3);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums{1,2,4,6};
    const auto a_out = Solution().minJumps(nums);
    assert(a_out == 2);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums{2,3,4,7,9};
    const auto a_out = Solution().minJumps(nums);
    assert(a_out == 2);
  
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
