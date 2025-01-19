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

constexpr ll MOD = 1e9 + 7;
constexpr int a = 0, e = 1, i = 2, o = 3, u = 4;

class Solution {
public:
  int countVowelPermutation(const int n) {
    std::vector<vl> dp(n, vl(5));
    dp[0] = vl(5, 1);
    FOR(j, 1, n-1) {
      // Each vowel 'a' may only be followed by an 'e'.
      dp[j][e] = (dp[j][e] + dp[j-1][a]) % MOD;

      // Each vowel e may only be followed by an a or an i.
      dp[j][a] = (dp[j][a] + dp[j-1][e]) % MOD;
      dp[j][i] = (dp[j][i] + dp[j-1][e]) % MOD;

      // Each vowel i may not be followed by another i.
      dp[j][a] = (dp[j][a] + dp[j-1][i]) % MOD;
      dp[j][e] = (dp[j][e] + dp[j-1][i]) % MOD;
      dp[j][o] = (dp[j][o] + dp[j-1][i]) % MOD;
      dp[j][u] = (dp[j][u] + dp[j-1][i]) % MOD;

      // Each vowel o may only be followed by an i or a u.
      dp[j][i] = (dp[j][i] + dp[j-1][o]) % MOD;
      dp[j][u] = (dp[j][u] + dp[j-1][o]) % MOD;

      // Each vowel u may only be followed by an a.
      dp[j][a] = (dp[j][a] + dp[j-1][u]) % MOD;
    }

    const auto res = (dp[n-1][a] + dp[n-1][e] + dp[n-1][i] + dp[n-1][o] + dp[n-1][u]) % MOD;
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
