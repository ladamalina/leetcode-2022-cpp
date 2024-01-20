// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;

using ll = long long;
using ii = std::pair<int, int>;
using vi = std::vector<int>;
using vvi = std::vector<vi>;
using vii = std::vector<ii>;

constexpr int MAX_N = 100000;
std::array<ll, MAX_N> psum{};
std::array<std::pair<int, ll>, MAX_N> dp{};

class Solution {
  public:
  static int findMaximumLength(const vi& nums) {
    const auto n = static_cast<int>(nums.size());
    std::fill(dp.begin(), dp.begin()+n, std::pair<int, ll>{0, LLONG_MAX});

    psum[0] = nums[0];
    for (int i = 1; i < n; ++i) {
      psum[i] = psum[i-1] + nums[i];
    }

    dp[0] = {1, nums[0]};
    
    for (int i = 1; i < n; ++i) {
      const auto prev_len = dp[i-1].first;
      const auto prev_val = dp[i-1].second;
      
      if (nums[i] >= prev_val) { // new subarray = 1 element
        if (prev_len+1 > dp[i].first || (prev_len+1 == dp[i].first && nums[i] < dp[i].second))
          dp[i] = {prev_len+1, nums[i]};
      } else { // continue subarray
        if (prev_len > dp[i].first || (prev_len == dp[i].first && prev_val+nums[i] < dp[i].second))
          dp[i] = {prev_len, prev_val+nums[i]};
      }

      // next subarray
      const auto target = (i>0 ? psum[i-1] : 0) + prev_val;
      const auto j = std::lower_bound(psum.begin()+i, psum.begin()+n, target) - psum.begin();
      if (j < n) {
        const auto dp_len = prev_len+1;
        const auto dp_val = psum[j] - (i>0 ? psum[i-1] : 0);
        if (dp_len > dp[j].first || (dp_len == dp[j].first && dp_val < dp[j].second))
          dp[j] = {dp_len, dp_val};
      }
    }
    return dp[n-1].first;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums{5,2,2};
    const auto a_out = Solution::findMaximumLength(nums);
    assert(a_out == 1);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums{1,2,3,4};
    const auto a_out = Solution::findMaximumLength(nums);
    assert(a_out == 4);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums{4,3,2,6};
    const auto a_out = Solution::findMaximumLength(nums);
    assert(a_out == 3);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const vi nums{272,482,115,925,983};
    const auto a_out = Solution::findMaximumLength(nums);
    assert(a_out == 4);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums{482,115,925,983};
    const auto a_out = Solution::findMaximumLength(nums);
    assert(a_out == 3);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums{147,633,535,183,886};
    const auto a_out = Solution::findMaximumLength(nums);
    assert(a_out == 4);

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
