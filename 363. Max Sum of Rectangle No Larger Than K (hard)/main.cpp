//#pragma GCC optimize("O3")
//#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;

class Solution {
  public:
  static int maxSumSubmatrix(std::vector<std::vector<int>>& a, int k) {
    const int n = a.size();
    const int m = a[0].size();
    
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (i-1 >= 0) a[i][j] += a[i-1][j];
        if (j-1 >= 0) a[i][j] += a[i][j-1];
        if (i-1 >= 0 && j-1 >= 0) a[i][j] -= a[i-1][j-1];
      }
    }

    int max_sum = -1e6;
    for (int j1 = 0; j1 < m; ++j1) {
      for (int j2 = j1; j2 < m; ++j2) {
        std::set<int> p_sums;
        for (int i = 0; i < n; ++i) {
          auto i_sum = a[i][j2];
          if (j1-1 >= 0) i_sum -= a[i][j1-1];

          if (i_sum <= k) max_sum = std::max(max_sum, i_sum);

          const auto it = p_sums.lower_bound(i_sum - k);
          if (it != p_sums.end()) {
            const auto s = i_sum - *it;
            if (s <= k) max_sum = std::max(max_sum, s);
          }

          p_sums.insert(i_sum);
        }
      }
    }

    return max_sum;
  }
};

/*
[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    std::vector<int> nums{3,1,5,8};
    const auto e_out = Solution::maxCoins(nums);
    assert(e_out == 167);
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    std::vector<int> nums{1,5};
    const auto e_out = Solution::maxCoins(nums);
    assert(e_out == 10);
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  std::cerr << "TestSolution OK"sv << std::endl;
}
*/

int main() {
#ifndef NDEBUG
  // TestSolution();
#endif
  return 0;
}
