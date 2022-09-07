#include <algorithm>
#include <iostream>
#include <vector>

class Solution {
 public:
  static int rob(std::vector<int>& nums) {
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
  std::vector<int> nums1{1,2,3,1};
  assert(Solution::rob(nums1) == 4);

  std::vector<int> nums2{2,7,9,3,1};
  assert(Solution::rob(nums2) == 12);

  return 0;
}
