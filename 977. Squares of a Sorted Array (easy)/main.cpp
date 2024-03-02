#include <cassert>
#include <iostream>
#include <vector>

class Solution {
 public:
  static std::vector<int> sortedSquares(const std::vector<int>& nums) {
    const auto n = nums.size();
    int l = 0;
    int r = n-1;
    std::vector<int> res(n);
    for (int i=n-1; i>=0; --i) {
      if (std::abs(nums[l]) >= std::abs(nums[r])) {
        res[i] = nums[l] * nums[l];
        ++l;
      } else {
        res[i] = nums[r] * nums[r];
        --r;
      }
    }
    return res;
  }
};

int main() {
    std::vector<int> nums1 = {-4,-1,0,3,10};
    std::vector<int> expected_nums1 = {0,1,9,16,100};
    assert(expected_nums1 == Solution::sortedSquares(nums1));

    std::vector<int> nums2 = {-7,-3,2,3,11};
    std::vector<int> expected_nums2 = {4,9,9,49,121};
    assert(expected_nums2 == Solution::sortedSquares(nums2));

    std::vector<int> nums3 = {-7,-3};
    std::vector<int> expected_nums3 = {9,49};
    assert(expected_nums3 == Solution::sortedSquares(nums3));

    std::vector<int> nums4 = {3,4};
    std::vector<int> expected_nums4 = {9,16};
    assert(expected_nums4 == Solution::sortedSquares(nums4));

    std::vector<int> nums5 = {};
    std::vector<int> expected_nums5 = {};
    assert(expected_nums5 == Solution::sortedSquares(nums5));

    std::vector<int> nums6 = {-3};
    std::vector<int> expected_nums6 = {9};
    assert(expected_nums6 == Solution::sortedSquares(nums6));

    std::vector<int> nums7 = {3};
    std::vector<int> expected_nums7 = {9};
    assert(expected_nums7 == Solution::sortedSquares(nums7));
}
