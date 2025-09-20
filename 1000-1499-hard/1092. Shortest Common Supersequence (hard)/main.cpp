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

class Solution {
public:
  std::string shortestCommonSupersequence(const std::string& str1, const std::string& str2) {
    const auto n = SZ(str1), m = SZ(str2);
    vvi dp(n+1, vi(m+1));
    FOR(i, 1, n) {
      FOR(j, 1, m) {
        if (str1[i-1] == str2[j-1])
          dp[i][j] = dp[i-1][j-1] + 1;
        else
          dp[i][j] = std::max(dp[i-1][j], dp[i][j-1]);
      }
    }
    const auto tn = n + m - dp[n][m];
    std::string t(tn, '.');
    auto ti = tn - 1;
    auto i = n, j = m;
    while (i > 0 || j > 0) {
      if (i > 0 && j > 0 && str1[i-1] == str2[j-1]) {
        t[ti--] = str1[i-1];
        --i; --j;
      } else if (i > 0 && dp[i][j] == dp[i-1][j]) {
        t[ti--] = str1[i-1];
        --i;
      } else {
        t[ti--] = str2[j-1];
        --j;
      }
    }
    return t;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::string str1("bbbaaaba");
    const std::string str2("bbababbb");
    const auto a_out = Solution().shortestCommonSupersequence(str1, str2);
    std::cerr << a_out << '\n';
    assert(SZ(a_out) == 11);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::string str1("abac");
    const std::string str2("cab");
    const auto a_out = Solution().shortestCommonSupersequence(str1, str2);
    std::cerr << a_out << '\n';
    assert(SZ(a_out) == 5);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::string str1("aaaaaaaa");
    const std::string str2("aaaaaaaa");
    const auto a_out = Solution().shortestCommonSupersequence(str1, str2);
    std::cerr << a_out << '\n';
    assert(SZ(a_out) == 8);
  
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
