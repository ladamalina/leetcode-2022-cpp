//#pragma GCC optimize("O3")
//#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;

int dp[300][300];

class Solution {
  public:
  static int maxCoins(const std::vector<int>& nums) {
    const int n = nums.size();
    memset(dp, -1, sizeof dp);
    
    std::function<int(int,int)> rec = [&](int l, int r) {
      if (l > r) return 0;
      
      auto& dp_lr = dp[l][r];
      if (dp_lr == -1) {
        const auto prev = (l-1 >= 0) ? nums[l-1] : 1;
        const auto post = (r+1 < n) ? nums[r+1] : 1;
        if (l == r) {
          dp_lr = prev * nums[l] * post;
        } else {
          for (int i = l; i <= r; ++i) {
            const auto i_res = prev * nums[i] * post + rec(l, i-1) + rec(i+1, r);
            dp_lr = std::max(dp_lr, i_res);
          }
        }
      }

      return dp_lr;
    };
    
    return rec(0, n-1);
  }
};

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

int main() {
#ifndef NDEBUG
  TestSolution();
#endif
  return 0;
}
