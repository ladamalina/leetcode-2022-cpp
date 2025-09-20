// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;
using ll = long long;

constexpr ll MOD = 1e9 + 7;

template <typename T>
[[maybe_unused]] T ModSum(T a, T b, T m) {
  a %= m;
  a = (a >= 0) ? a : a + m;
  b %= m;
  b = (b >= 0) ? b : b + m;
  auto c = (a + b) % m;
  c = (c >= 0) ? c : c + m;
  return c;
}

int memo[50][50][51];

ll Rec(int m, int n, int moves, int i, int j) {
  if (moves == 1)
    return (i==0) + (j==0) + (i==m-1) + (j==n-1);
  if (memo[i][j][moves] != -1)
    return memo[i][j][moves];
  ll res = (i==0) + (j==0) + (i==m-1) + (j==n-1);
  if (i > 0)
    res = ModSum(res, Rec(m, n, moves-1, i-1, j), MOD);
  if (j > 0)
    res = ModSum(res, Rec(m, n, moves-1, i, j-1), MOD);
  if (i+1 < m)
    res = ModSum(res, Rec(m, n, moves-1, i+1, j), MOD);
  if (j+1 < n)
    res = ModSum(res, Rec(m, n, moves-1, i, j+1), MOD);
  memo[i][j][moves] = res;
  return res;
}

class Solution {
 public:
  static int findPaths(int m, int n, int moves, int i, int j) {
    if (moves == 0)
      return 0;

    std::fill(&memo[0][0][0], &memo[0][0][0] + sizeof(memo) / sizeof(memo[0][0][0]), -1);
    const auto res = Rec(m, n, moves, i, j);
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto a_out = Solution::findPaths(2,2,2,0,0);
    assert(a_out == 6);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto a_out = Solution::findPaths(1,3,3,0,1);
    assert(a_out == 12);

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
