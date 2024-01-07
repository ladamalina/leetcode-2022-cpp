//#pragma GCC optimize("O3")
//#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;

int psum[1000];
int dp[1000][50];

class Solution {
  public:
  static int splitArray(const std::vector<int>& nums, const int k) {
    memset(psum, 0, sizeof psum);
    memset(dp, -1, sizeof dp);
    
    const auto n = static_cast<int>(nums.size());
    psum[0] = nums[0];
    for (int i = 1; i < n; ++i) {
      psum[i] = psum[i-1] + nums[i];
    }
    
    dp[0][0] = nums[0];
    for (int i = 1; i < n; ++i) {
      dp[i][0] = psum[i];
      for (int j = 0; j < i; ++j) {
        const auto psum_ji = psum[i] - psum[j];
        for (int g = 0; g+1 < k; ++g) {
          if (dp[j][g] != -1) {
            const auto i_res = std::max(dp[j][g], psum_ji);
            if (dp[i][g+1] == -1) dp[i][g+1] = i_res;
            else dp[i][g+1] = std::min(dp[i][g+1], i_res);
          }
        }
      }
    }
    return dp[n-1][k-1];
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::vector<int> nums{7,2,5,10,8};
    const auto e_out = Solution::splitArray(nums, 2);
    assert(e_out == 18);
    
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::vector<int> nums{1,2,3,4,5};
    const auto e_out = Solution::splitArray(nums, 2);
    assert(e_out == 9);
    
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
