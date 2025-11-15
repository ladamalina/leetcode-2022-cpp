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

constexpr std::array<int, 35> PRIMES{2,  3,  5,  7,  11, 13, 17, 19,  23,  29,  31,  37,  41,  43,  47,  53,  59, 61,
                                     67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149};
constexpr int N_PRIMES = SZ(PRIMES);
constexpr int MOD = 1e9 + 7;

class Solution {
public:
  int countCoprime(const vvi& mat) {
    const auto m = SZ(mat), n = SZ(mat[0]);
    vvl g(m, vl(n));
    FOR(i, 0, m-1) {
      FOR(j, 0, n-1) {
        ll mask = 0;
        auto x = mat[i][j];
        FOR(pi, 0, N_PRIMES - 1) {
          while (x % PRIMES[pi] == 0) {
            mask |= (1ll << pi);
            x /= PRIMES[pi];
          }
        }
        g[i][j] = mask;
      }
    }
    
    std::unordered_map<ll, int> dp{{(1ll << N_PRIMES) - 1, 1}};
    FOR(i, 0, m-1) {
      std::unordered_map<ll, int> dp2;
      for (const auto& [mask, cnt] : dp) {
        FOR(j, 0, n-1) {
          auto& v = dp2[mask & g[i][j]];
          v = (v + cnt) % MOD;
        }
      }
      dp = std::move(dp2);
    }
    return dp[0];
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi mat{{94,  130, 106, 105, 14,  52,  8,   44,  136, 141, 19,  107, 80,  36,  7,  123, 140, 93,  150,
                   21,  137, 67,  42,  114, 81,  98,  30,  71,  27,  38,  65,  114, 132, 95, 82,  52,  52,  10,
                   10,  99,  116, 108, 23,  133, 40,  85,  123, 137, 119, 50,  142, 122, 13, 79,  7,   131, 114,
                   139, 39,  19,  18,  25,  32,  37,  21,  84,  28,  112, 98,  111, 124, 48, 88,  35,  108, 71,
                   44,  94,  21,  40,  120, 147, 101, 20,  108, 96,  133, 9,   39,  6,   30, 31,  16,  107, 58,
                   136, 113, 116, 142, 123, 18,  38,  12,  23,  115, 33,  137, 131, 43,  78, 29,  130, 52,  28,
                   136, 115, 55,  55,  92,  71,  135, 22,  64,  60,  142, 58,  83,  68,  17, 31,  13,  141, 81,
                   55,  27,  45,  140, 101, 15,  140, 120, 8,   28,  15,  56,  94,  69,  93, 80,  62}};
    const auto a_out = Solution().countCoprime(mat);
    assert(a_out == 0);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi mat{{1,2},{3,4}};
    const auto a_out = Solution().countCoprime(mat);
    assert(a_out == 3);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi mat{{2,2},{2,2}};
    const auto a_out = Solution().countCoprime(mat);
    assert(a_out == 0);
  
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
