// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;

using vi = std::vector<int>;
using vvi = std::vector<vi>;

constexpr int INF = 1e9;
int memo[100][100];

class Solution {
  public:
  static int minFallingPathSum(const vvi& matrix) {
    const auto n = static_cast<int>(matrix.size());
    const auto m = static_cast<int>(matrix[0].size());
    std::fill(&memo[0][0], &memo[0][0] + sizeof(memo) / sizeof(memo[0][0]), INF);

    std::function<int(int,int)> rec = [&](int row, int col) {
      if (col < 0 || col >= m) return INF;
      if (row == n-1) return matrix[row][col];

      auto& memo_val = memo[row][col];
      if (memo_val == INF) {
        memo_val = matrix[row][col] + std::min(rec(row+1, col-1), std::min(rec(row+1, col), rec(row+1, col+1)));
      }
      return memo_val;
    };
    int min_res = INF;
    for (int col = 0; col < n; ++col) {
      const auto res = rec(0, col);
      min_res = std::min(min_res, res);
    }
    return min_res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi& matrix{{2,1,3},{6,5,4},{7,8,9}};
    const auto a_out = Solution::minFallingPathSum(matrix);
    assert(a_out == 13);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi& matrix{{-19,57},{-40,-5}};
    const auto a_out = Solution::minFallingPathSum(matrix);
    assert(a_out == -59);

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
