#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;

class Solution {
 public:
  int maximalRectangle(std::vector<std::vector<char>>& matrix) {
    auto n = static_cast<int>(matrix.size());
    auto m = static_cast<int>(matrix[0].size());

    std::vector<std::vector<int>> dp_h(n, std::vector<int>(m));
    for (int i = n-1; i >= 0; --i) {
      for (int j = 0; j < m; ++j) {
        if (i == n-1) dp_h[i][j] = (matrix[i][j] == '1') ? 1 : 0;
        else if (matrix[i][j] == '1') dp_h[i][j] = dp_h[i+1][j] + 1;
      }
    }
    std::vector<std::vector<int>> dp_l(n, std::vector<int>(m));
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (j == 0) dp_l[i][j] = -1;
        else if (dp_h[i][j-1] < dp_h[i][j]) dp_l[i][j] = j-1;
        else {
          auto uj = dp_l[i][j-1];
          while (uj != -1 && dp_h[i][uj] >= dp_h[i][j]) {
            uj = dp_l[i][uj];
          }
          dp_l[i][j] = uj;
        }
      }
    }
    std::vector<std::vector<int>> dp_r(n, std::vector<int>(m));
    for (int i = 0; i < n; ++i) {
      for (int j = m-1; j >= 0; --j) {
        if (j == m-1) dp_r[i][j] = m;
        else if (dp_h[i][j] > dp_h[i][j+1]) dp_r[i][j] = j+1;
        else {
          auto uj = dp_r[i][j+1];
          while (uj != m && dp_h[i][j] <= dp_h[i][uj]) {
            uj = dp_r[i][uj];
          }
          dp_r[i][j] = uj;
        }
      }
    }
    int max_square = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        auto square = dp_h[i][j] * (dp_r[i][j] - dp_l[i][j] - 1);
        max_square = std::max(square, max_square);
      }
    }
    
    return max_square;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    std::vector<std::vector<char>> matrix{
      {'1','0','1','0','0'},
      {'1','0','1','1','1'},
      {'1','1','1','1','1'},
      {'1','0','0','1','0'}};
    int e_out = 6;
    auto start_t = std::chrono::high_resolution_clock::now();
    auto a_out = Solution().maximalRectangle(matrix);
    auto end_t = std::chrono::high_resolution_clock::now();
    auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
    assert(a_out == e_out);
  }
  {
    std::vector<std::vector<char>> matrix{
      {'1','0','1','0','0'},
      {'1','0','1','1','1'},
      {'1','1','1','1','1'},
      {'1','0','1','0','0'}};
    int e_out = 6;
    auto start_t = std::chrono::high_resolution_clock::now();
    auto a_out = Solution().maximalRectangle(matrix);
    auto end_t = std::chrono::high_resolution_clock::now();
    auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
    assert(a_out == e_out);
  }
  {
    std::vector<std::vector<char>> matrix{
      {'1','1','1','1','1'},
      {'1','1','1','1','0'},
      {'1','1','0','0','0'},
      {'1','0','0','0','0'}};
    int e_out = 8;
    auto start_t = std::chrono::high_resolution_clock::now();
    auto a_out = Solution().maximalRectangle(matrix);
    auto end_t = std::chrono::high_resolution_clock::now();
    auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
    assert(a_out == e_out);
  }
  {
    std::vector<std::vector<char>> matrix{{'0'}};
    int e_out = 0;
    auto start_t = std::chrono::high_resolution_clock::now();
    auto a_out = Solution().maximalRectangle(matrix);
    auto end_t = std::chrono::high_resolution_clock::now();
    auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
    assert(a_out == e_out);
  }
  {
    std::vector<std::vector<char>> matrix{{'1'}};
    int e_out = 1;
    auto start_t = std::chrono::high_resolution_clock::now();
    auto a_out = Solution().maximalRectangle(matrix);
    auto end_t = std::chrono::high_resolution_clock::now();
    auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
    assert(a_out == e_out);
  }
  {
    std::vector<std::vector<char>> matrix{{'0','1'},{'1','0'}};
    int e_out = 1;
    auto start_t = std::chrono::high_resolution_clock::now();
    auto a_out = Solution().maximalRectangle(matrix);
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
