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
using ii [[maybe_unused]] = std::pair<int, int>;
using vi [[maybe_unused]] = std::vector<int>;
using vl [[maybe_unused]] = std::vector<ll>;
using vvi [[maybe_unused]] = std::vector<vi>;
using vvvi [[maybe_unused]] = std::vector<vvi>;
using vvl [[maybe_unused]] = std::vector<vl>;
using vii [[maybe_unused]] = std::vector<ii>;
using vb [[maybe_unused]] = std::vector<bool>;
using vd [[maybe_unused]] = std::vector<double>;
using vs [[maybe_unused]] = std::vector<std::string>;
using vc [[maybe_unused]] = std::vector<char>;

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

constexpr ll MOD = 1e9 + 7;
constexpr int MAX_N = 1000;

std::array<std::array<int, MAX_N+1>, 3> dp;

int Rec(int len1, int len2) {
  if (len1 == 0 || len2 == 0)
    return CI(len1 == 0 && len2 == 0);
  if (dp[len1-len2+1][len1] != -1)
    return dp[len1-len2+1][len1];

  ll res = 0;

  if (len1 == len2 && len1 >= 2 && len2 >= 2) {
    res = (res + Rec(len1 - 2, len2 - 2)) % MOD;
    res = (res + Rec(len1 - 1, len2 - 2)) % MOD;
    res = (res + Rec(len1 - 2, len2 - 1)) % MOD;
  }

  if (len1 == len2 && len1 >= 1 && len2 >= 1) {
    res = (res + Rec(len1 - 1, len2 - 1)) % MOD;
  }

  if (len1 + 1 == len2) {
    res = (res + Rec(len1 - 1, len2 - 2)) % MOD;
    res = (res + Rec(len1, len2 - 2)) % MOD;
  }

  if (len1 == len2 + 1) {
    res = (res + Rec(len1 - 2, len2 - 1)) % MOD;
    res = (res + Rec(len1 - 2, len2)) % MOD;
  }
  
  return dp[len1-len2+1][len1] = res;
}

class Solution {
  public:
      int numTilings(int n) {
        FOR(i, 0, 2) {
          std::fill(dp[i].begin(), dp[i].begin() + n + 1, -1);
        }

        return Rec(n, n);
      }
  };

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().numTilings(3);
    assert(a_out == 5);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().numTilings(1);
    assert(a_out == 1);
  
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
