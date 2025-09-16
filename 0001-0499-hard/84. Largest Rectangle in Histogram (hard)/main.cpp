#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;

class Solution {
 public:
  int largestRectangleArea(std::vector<int>& heights) {
    auto n = static_cast<int>(heights.size());
    
    std::vector<int> dp_l(n);
    for (int i = 0; i < n; ++i) {
      if (i == 0) dp_l[i] = -1;
      else if (heights[i-1] < heights[i]) dp_l[i] = i-1;
      else {
        auto j = dp_l[i-1];
        while (j != -1 && heights[j] >= heights[i]) {
          j = dp_l[j];
        }
        dp_l[i] = j;
      }
    }
    
    std::vector<int> dp_r(n);
    for (int i = n-1; i >= 0; --i) {
      if (i == n-1) dp_r[i] = n;
      else if (heights[i] > heights[i+1]) dp_r[i] = i+1;
      else {
        auto j = dp_r[i+1];
        while (j != n && heights[i] <= heights[j]) {
          j = dp_r[j];
        }
        dp_r[i] = j;
      }
    }
    
    int max_square = 0;
    for (int i = 0; i < n; ++i) {
      auto square = heights[i] * (dp_r[i] - dp_l[i] - 1);
      max_square = std::max(square, max_square);
    }
    
    return max_square;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    std::vector<int> input{2,1,5,6,2,3};
    int e_out = 10;
    auto start_t = std::chrono::high_resolution_clock::now();
    auto a_out = Solution().largestRectangleArea(input);
    auto end_t = std::chrono::high_resolution_clock::now();
    auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
    assert(a_out == e_out);
  }
  {
    std::vector<int> input{2,4};
    int e_out = 4;
    auto start_t = std::chrono::high_resolution_clock::now();
    auto a_out = Solution().largestRectangleArea(input);
    auto end_t = std::chrono::high_resolution_clock::now();
    auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
    assert(a_out == e_out);
  }
  {
    std::vector<int> input{0,2,0};
    int e_out = 2;
    auto start_t = std::chrono::high_resolution_clock::now();
    auto a_out = Solution().largestRectangleArea(input);
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
