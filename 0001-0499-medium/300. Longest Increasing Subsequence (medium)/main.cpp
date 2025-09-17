#include <bits/stdc++.h>

using namespace std::literals;

class Solution {
 public:
  static int lengthOfLIS(const std::vector<int>& nums) {
    int nums_n = static_cast<int>(nums.size());
    std::map<int, int> dp{{nums[0], 1}};
    int max_len = 1;
    for (int i = 1; i < nums_n; ++i) {
      auto lower_it = dp.lower_bound(nums[i]);
      int max_prefix_len = 0;
      for (auto prev_it = dp.begin(); prev_it != lower_it; ++prev_it) {
        max_prefix_len = std::max(max_prefix_len, prev_it->second);
      }
      dp[nums[i]] = max_prefix_len + 1;
      max_len = std::max(max_len, dp[nums[i]]);
    }

    return max_len;
  }
};

[[maybe_unused]] void TestSolution() {
  assert(Solution::lengthOfLIS({10,9,2,5,3,7,101,18}) == 4);
  assert(Solution::lengthOfLIS({10,9,2,5,3,7,101,100,99,18}) == 4);
  assert(Solution::lengthOfLIS({0,1,0,3,2,3}) == 4);
  assert(Solution::lengthOfLIS({7,7,7,7,7,7,7}) == 1);

  std::cerr << "TestSolution OK"sv << std::endl;
}

int main() {
#ifndef NDEBUG
  TestSolution();
#endif
  return 0;
}
