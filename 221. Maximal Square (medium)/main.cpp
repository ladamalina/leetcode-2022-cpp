#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;

class Solution {
 public:
  int maximalSquare(std::vector<std::vector<char>>& matrix) {
    auto n = static_cast<int>(matrix.size());
    auto m = static_cast<int>(matrix[0].size());
    
    int dp_h[n][m];
    for (int i = n-1; i >= 0; --i) {
      for (int j = 0; j < m; ++j) {
        if (i == n-1) dp_h[i][j] = (matrix[i][j] == '1') ? 1 : 0;
        else dp_h[i][j] = (matrix[i][j] == '1') ? dp_h[i+1][j] + 1 : 0;
      }
    }

    int dp_l[n][m];
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (j == 0) dp_l[i][j] = -1;
        else if (dp_h[i][j-1] < dp_h[i][j]) dp_l[i][j] = j-1;
        else {
          auto k = j-1;
          while (k >= 0 && dp_h[i][k] >= dp_h[i][j]) {
            k = dp_l[i][k];
          }
          dp_l[i][j] = k;
        }
      }
    }

    int dp_r[n][m];
    for (int i = 0; i < n; ++i) {
      for (int j = m-1; j >= 0; --j) {
        if (j == m-1) dp_r[i][j] = m;
        else if (dp_h[i][j] > dp_h[i][j+1]) dp_r[i][j] = j+1;
        else {
          auto k = j+1;
          while (k < m && dp_h[i][j] <= dp_h[i][k]) {
            k = dp_r[i][k];
          }
          dp_r[i][j] = k;
        }
      }
    }
    
    int max_square = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        auto width = dp_r[i][j] - dp_l[i][j] - 1;
        auto side_len = std::min(width, dp_h[i][j]);
        max_square = std::max(max_square, side_len*side_len);
      }
    }
    
    return max_square;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    std::vector<std::vector<char>> input{
      {'1','0','1','0','0'},
      {'1','0','1','1','1'},
      {'1','1','1','1','1'},
      {'1','0','0','1','0'}};
    int e_out = 4;
    auto start_t = std::chrono::high_resolution_clock::now();
    auto a_out = Solution().maximalSquare(input);
    auto end_t = std::chrono::high_resolution_clock::now();
    auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
    assert(a_out == e_out);
  }
  {
    std::vector<std::vector<char>> input{
      {'1','1','1','1','1'},
      {'1','1','1','1','0'},
      {'1','1','1','0','0'},
      {'1','0','0','0','0'}};
    int e_out = 9;
    auto start_t = std::chrono::high_resolution_clock::now();
    auto a_out = Solution().maximalSquare(input);
    auto end_t = std::chrono::high_resolution_clock::now();
    auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
    assert(a_out == e_out);
  }
  {
    std::vector<std::vector<char>> input{
      {'0','1'},
      {'1','0'}};
    int e_out = 1;
    auto start_t = std::chrono::high_resolution_clock::now();
    auto a_out = Solution().maximalSquare(input);
    auto end_t = std::chrono::high_resolution_clock::now();
    auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
    assert(a_out == e_out);
  }
  std::cerr << "TestSolution OK"sv << std::endl;
}

int main() {
#ifndef NDEBUG
  TestSolution();
#endif
  return 0;
}
