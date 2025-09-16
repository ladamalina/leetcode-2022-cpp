// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;

class Solution {
  public:
  static bool isSelfCrossing(const std::vector<int>& x) {
    const auto n = static_cast<int>(x.size());
    for (int i = 3; i < n; ++i){
      if(i >= 3 && x[i] >= x[i-2] && x[i-1] <= x[i-3]) return true;
      if(i >= 4 && x[i-1] == x[i-3] && x[i] + x[i-4] >= x[i-2]) return true;
      if(i >= 5 && x[i-2] >= x[i-4] && x[i-5] + x[i-1] >= x[i-3] && x[i-1] <= x[i-3] && x[i-4] + x[i] >= x[i-2]) return true;
    }
    return false;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::vector<int> distance{2,1,1,2};
    const auto a_out = Solution::isSelfCrossing(distance);
    assert(a_out);
    
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::vector<int> distance{1,2,3,4};
    const auto a_out = Solution::isSelfCrossing(distance);
    assert(!a_out);
    
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::vector<int> distance{1,1,1,2,1};
    const auto a_out = Solution::isSelfCrossing(distance);
    assert(a_out);
    
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
