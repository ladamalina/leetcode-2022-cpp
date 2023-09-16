#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;

class Solution {
 public:
  int trap(std::vector<int>& height) {
    auto n = static_cast<int>(height.size());
    
    int max_l[n];
    for (int i = 0; i < n; ++i) {
      if (i == 0) max_l[i] = -1;
      else if (max_l[i-1] == -1 || height[i-1] >= height[max_l[i-1]]) max_l[i] = i-1;
      else max_l[i] = max_l[i-1];
    }

    int max_r[n];
    for (int i = n-1; i >= 0; --i) {
      if (i == n-1) max_r[i] = n;
      else if (max_r[i+1] == n || height[i+1] >= height[max_r[i+1]]) max_r[i] = i+1;
      else max_r[i] = max_r[i+1];
    }
    
    int max_i = 0;
    for (int i = 1; i < n; ++i) {
      if (height[i] > height[max_i]) max_i = i;
    }
    
    int trapped = 0;

    // go left
    {
      auto li = max_l[max_i];
      auto ri = max_i;
      while (li != -1) {
        int h = std::min(height[li], height[ri]);
        for (int i = li+1; i < ri; ++i) {
          trapped += (h - height[i]);
        }
        ri = li;
        li = max_l[li];
      }
    }
    
    // go right
    {
      auto li = max_i;
      auto ri = max_r[max_i];
      while (ri != n) {
        int h = std::min(height[li], height[ri]);
        for (int i = li+1; i < ri; ++i) {
          trapped += (h - height[i]);
        }
        li = ri;
        ri = max_r[ri];
      }
    }
    
    return trapped;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    std::vector<int> input{0,1,0,2,1,0,1,3,2,1,2,1};
    int e_out = 6;
    auto start_t = std::chrono::high_resolution_clock::now();
    auto a_out = Solution().trap(input);
    auto end_t = std::chrono::high_resolution_clock::now();
    auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
    assert(a_out == e_out);
  }
  {
    std::vector<int> input{4,2,0,3,2,5};
    int e_out = 9;
    auto start_t = std::chrono::high_resolution_clock::now();
    auto a_out = Solution().trap(input);
    auto end_t = std::chrono::high_resolution_clock::now();
    auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
    assert(a_out == e_out);
  }
  {
    std::vector<int> input{6,1,2,1,3,1,4,1,2,1};
    int e_out = 13;
    auto start_t = std::chrono::high_resolution_clock::now();
    auto a_out = Solution().trap(input);
    auto end_t = std::chrono::high_resolution_clock::now();
    auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
    assert(a_out == e_out);
  }
  {
    std::vector<int> input{6,5,4,1,2,1,3,1,5,1,2,1};
    int e_out = 19;
    auto start_t = std::chrono::high_resolution_clock::now();
    auto a_out = Solution().trap(input);
    auto end_t = std::chrono::high_resolution_clock::now();
    auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
    assert(a_out == e_out);
  }
  {
    std::vector<int> input{2,1,2,1,3,1,4,1,2,1};
    int e_out = 5;
    auto start_t = std::chrono::high_resolution_clock::now();
    auto a_out = Solution().trap(input);
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
