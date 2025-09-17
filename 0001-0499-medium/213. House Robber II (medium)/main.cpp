#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

class Solution {
 public:
  static int rob(std::vector<int>& nums) {
    if (nums.size() == 1)
      return nums[0];

    std::vector<int> houses_w_first(nums.begin(), --nums.end());
    auto sum_houses_w_first = robSeq(houses_w_first);

    std::vector<int> houses_w_last(++nums.begin(), nums.end());
    auto sum_houses_w_last = robSeq(houses_w_last);

    return std::max(sum_houses_w_first, sum_houses_w_last);
  }
 private:
  static int robSeq(std::vector<int>& nums) {
    if (nums.size() == 1)
      return nums[0];
    if (nums.size() == 2)
      return std::max(nums[0], nums[1]);
    // nums.size() >= 3
    nums[2] += nums[0];
    for (size_t i = 3; i < nums.size(); ++i) {
      nums[i] += std::max(nums[i-3], nums[i-2]);
    }

    return std::max(nums.back(), nums[nums.size()-2]);
  }
};

int main() {
  std::vector<int> nums0{0};
  assert(Solution::rob(nums0) == 0);

  std::vector<int> nums1{2,3,2};
  assert(Solution::rob(nums1) == 3);

  std::vector<int> nums2{1,2,3,1};
  assert(Solution::rob(nums2) == 4);

  std::vector<int> nums3{1,2,3};
  assert(Solution::rob(nums3) == 3);

  std::vector<int> nums4{2,3};
  assert(Solution::rob(nums4) == 3);

  return 0;
}
