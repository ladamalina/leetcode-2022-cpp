#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

class Solution {
public:
  static int maxSubArray(std::vector<int>& nums) {
    std::vector<int> max_sums;
    max_sums.reserve(nums.size());
    max_sums.push_back(nums[0]);
    int max_sub_sum = max_sums[0];
    for (size_t i = 1; i < nums.size(); ++i) {
      max_sums.push_back(std::max(nums[i], nums[i] + max_sums[i-1]));
      if (max_sums.back() > max_sub_sum)
        max_sub_sum = max_sums.back();
    }

    // std::cout << "max_sub_sum=" << max_sub_sum << "\n";

    return max_sub_sum;
  }
};

int main() {
  std::vector<int> nums1{-2,1,-3,4,-1,2,1,-5,4};
  assert(Solution::maxSubArray(nums1) == 6);

  std::vector<int> nums2{1};
  assert(Solution::maxSubArray(nums2) == 1);

  std::vector<int> nums3{5,4,-1,7,8};
  assert(Solution::maxSubArray(nums3) == 23);

  std::vector<int> nums4{-2,-1};
  assert(Solution::maxSubArray(nums4) == -1);

  std::vector<int> nums5{-2,1};
  assert(Solution::maxSubArray(nums5) == 1);

  return 0;
}
