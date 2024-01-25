// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

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

using ll = long long;
using ii = std::pair<int, int>;
using vi = std::vector<int>;
using vvi = std::vector<vi>;
using vii = std::vector<ii>;

int dp[1001][1001];

class Solution {
 public:
  static int longestCommonSubsequence(const std::string& s1, const std::string& s2) {
    const auto n1 = static_cast<int>(s1.size());
    const auto n2 = static_cast<int>(s2.size());

    for (int i = 1; i <= n1; ++i) {
      for (int j = 1; j <= n2; ++j) {
        if (s1[i-1] == s2[j-1]) {
          dp[i][j] = dp[i-1][j-1] + 1;
        } else {
          dp[i][j] = std::max(dp[i-1][j], dp[i][j-1]);
        }
      }
    }
    
    return dp[n1][n2];
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto a_out = Solution::longestCommonSubsequence("abcde"s, "ace"s);
    assert(a_out == 3);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto a_out = Solution::longestCommonSubsequence("abc"s, "abc"s);
    assert(a_out == 3);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto a_out = Solution::longestCommonSubsequence("abc"s, "def"s);
    assert(a_out == 0);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto a_out = Solution::longestCommonSubsequence("bsbininm"s, "jmjkbkjkv"s);
    assert(a_out == 1);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto a_out = Solution::longestCommonSubsequence("fcvqfcnglshwpgxujwrylqzejmdubkxs"s, "bctsfwdelkdqzshupmrufyxklsjurevip"s);
    assert(a_out == 11);

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
