#include <bits/stdc++.h>

class Solution {
 public:
  static int rob(std::vector<int>& nums) {
    const auto n = static_cast<int>(nums.size());
    if (n == 1)
      return nums[0];
    if (n == 2)
      return std::max(nums[0], nums[1]);
    // n >= 3
    nums[2] += nums[0];
    for (int i = 3; i < n; ++i) {
      nums[i] += std::max(nums[i-3], nums[i-2]);
    }

    return std::max(nums[n-1], nums[n-2]);
  }
};

int main() {
  std::vector<int> nums1{1,2,3,1};
  assert(Solution::rob(nums1) == 4);

  std::vector<int> nums2{2,7,9,3,1};
  assert(Solution::rob(nums2) == 12);

  return 0;
}
