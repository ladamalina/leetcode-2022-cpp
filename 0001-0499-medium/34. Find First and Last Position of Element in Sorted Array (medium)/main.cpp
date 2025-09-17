#include <cassert>
#include <vector>

class Solution {
 public:
  static std::vector<int> searchRange(const std::vector<int>& nums, const int target) {
    if (nums.empty()) {
      return {-1, -1};
    }

    return {searchLowerBound(nums, target, 0, static_cast<int>(nums.size()) - 1),
            searchUpperBound(nums, target, 0, static_cast<int>(nums.size()) - 1)};
  }

  static int searchLowerBound(const std::vector<int>& nums, const int target, const int begin_idx, const int end_idx) {
    if (target == nums[begin_idx]) {
      if (begin_idx == 0) {
        return 0;
      } // begin_idx >= 1
      if (target == nums[begin_idx - 1]) {
        return searchLowerBound(nums, target, 0, begin_idx - 1);
      } // target != nums[begin_idx - 1] && target == nums[begin_idx]
      return begin_idx;
    } // target != nums[begin_idx]

    if (target < nums[begin_idx]) {
      return -1;
    } // target > nums[begin_idx]

    if (target > nums[end_idx]) {
      return -1;
    } // target <= nums[end_idx]

    int len = end_idx - begin_idx + 1;
    if (len <= 2) { // target in (begin_idx, end_idx] && len <= 2
      if (target == nums[end_idx]) {
        return end_idx;
      } // target in (begin_idx, end_idx) && len <= 2
      return -1;
    } // len >= 3

    int mid_idx = begin_idx + len / 2;
    if (target <= nums[mid_idx]) {
      return searchLowerBound(nums, target, begin_idx, mid_idx);
    } // target > nums[mid_idx]
    if (mid_idx != end_idx) {
      return searchLowerBound(nums, target, mid_idx + 1, end_idx);
    } // target > nums[mid_idx] && mid_idx == end_idx

    return -1;
  }

  static int searchUpperBound(const std::vector<int>& nums, const int target, const int begin_idx, const int end_idx) {
    int nums_end_idx = static_cast<int>(nums.size()) - 1;

    if (target == nums[end_idx]) {
      if (end_idx == nums_end_idx) {
        return nums_end_idx;
      } // end_idx < nums_end_idx
      if (target == nums[end_idx + 1]) {
        return searchUpperBound(nums, target, end_idx + 1, nums_end_idx);
      } // target != nums[end_idx + 1] && target == nums[end_idx]
      return end_idx;
    } // target != nums[end_idx]

    if (target > nums[end_idx]) {
      return -1;
    } // target < nums[end_idx]

    if (target < nums[begin_idx]) {
      return -1;
    }

    int len = end_idx - begin_idx + 1;
    if (len <= 2) { // target in [begin_idx, end_idx) && len <= 2
      if (target == nums[begin_idx]) {
        return begin_idx;
      } // target in (begin_idx, end_idx) && len <= 2
      return -1;
    } // len >= 3

    int mid_idx = begin_idx + len / 2;
    if (target >= nums[mid_idx]) {
      return searchUpperBound(nums, target, mid_idx, end_idx);
    } // target < nums[mid_idx]
    if (mid_idx != begin_idx) {
      return searchUpperBound(nums, target, begin_idx, mid_idx - 1);
    } // target < nums[mid_idx] && mid_idx == begin_idx

    return -1;
  }
};

int main() {
  {
    const std::vector<int> nums = {5,7,7,8,8,10};
    const int target = 8;
    const std::vector<int> expected = {3,4};
    assert(Solution::searchLowerBound(nums, target, 0, nums.size()-1) == expected[0]);
    assert(Solution::searchUpperBound(nums, target, 0, nums.size()-1) == expected[1]);
    assert(Solution::searchRange(nums, target) == expected);
  }
  {
    const std::vector<int> nums = {5,7,7,8,9,10};
    const int target = 8;
    const std::vector<int> expected = {3,3};
    assert(Solution::searchLowerBound(nums, target, 0, nums.size()-1) == expected[0]);
    assert(Solution::searchUpperBound(nums, target, 0, nums.size()-1) == expected[1]);
    assert(Solution::searchRange(nums, target) == expected);
  }
  {
    const std::vector<int> nums = {8,8,8,8,8,10};
    const int target = 8;
    const std::vector<int> expected = {0,4};
    assert(Solution::searchLowerBound(nums, target, 0, nums.size()-1) == expected[0]);
    assert(Solution::searchUpperBound(nums, target, 0, nums.size()-1) == expected[1]);
    assert(Solution::searchRange(nums, target) == expected);
  }
  {
    const std::vector<int> nums = {8,9,10,11,12,13};
    const int target = 8;
    const std::vector<int> expected = {0,0};
    assert(Solution::searchLowerBound(nums, target, 0, nums.size()-1) == expected[0]);
    assert(Solution::searchUpperBound(nums, target, 0, nums.size()-1) == expected[1]);
    assert(Solution::searchRange(nums, target) == expected);
  }
  {
    const std::vector<int> nums = {4,5,6,8,8,8};
    const int target = 8;
    const std::vector<int> expected = {3,5};
    assert(Solution::searchLowerBound(nums, target, 0, nums.size()-1) == expected[0]);
    assert(Solution::searchUpperBound(nums, target, 0, nums.size()-1) == expected[1]);
    assert(Solution::searchRange(nums, target) == expected);
  }
  {
    const std::vector<int> nums = {4,5,6,7,8};
    const int target = 8;
    const std::vector<int> expected = {4,4};
    assert(Solution::searchLowerBound(nums, target, 0, nums.size()-1) == expected[0]);
    assert(Solution::searchUpperBound(nums, target, 0, nums.size()-1) == expected[1]);
    assert(Solution::searchRange(nums, target) == expected);
  }
  {
    const std::vector<int> nums = {8,8};
    const int target = 8;
    const std::vector<int> expected = {0,1};
    assert(Solution::searchLowerBound(nums, target, 0, nums.size()-1) == expected[0]);
    assert(Solution::searchUpperBound(nums, target, 0, nums.size()-1) == expected[1]);
    assert(Solution::searchRange(nums, target) == expected);
  }
  {
    const std::vector<int> nums = {8};
    const int target = 8;
    const std::vector<int> expected = {0,0};
    assert(Solution::searchLowerBound(nums, target, 0, nums.size()-1) == expected[0]);
    assert(Solution::searchUpperBound(nums, target, 0, nums.size()-1) == expected[1]);
    assert(Solution::searchRange(nums, target) == expected);
  }
  {
    const std::vector<int> nums = {8,9,10,11,12,13};
    const int target = 6;
    const std::vector<int> expected = {-1,-1};
    assert(Solution::searchLowerBound(nums, target, 0, nums.size()-1) == expected[0]);
    assert(Solution::searchUpperBound(nums, target, 0, nums.size()-1) == expected[1]);
    assert(Solution::searchRange(nums, target) == expected);
  }
  {
    const std::vector<int> nums = {8,9,10,11,12,13};
    const int target = 16;
    const std::vector<int> expected = {-1,-1};
    assert(Solution::searchLowerBound(nums, target, 0, nums.size()-1) == expected[0]);
    assert(Solution::searchUpperBound(nums, target, 0, nums.size()-1) == expected[1]);
    assert(Solution::searchRange(nums, target) == expected);
  }
  {
    const std::vector<int> nums = {8,9,10,12,13,14};
    const int target = 11;
    const std::vector<int> expected = {-1,-1};
    assert(Solution::searchLowerBound(nums, target, 0, nums.size()-1) == expected[0]);
    assert(Solution::searchUpperBound(nums, target, 0, nums.size()-1) == expected[1]);
    assert(Solution::searchRange(nums, target) == expected);
  }
  {
    const std::vector<int> nums = {};
    const int target = 8;
    const std::vector<int> expected = {-1,-1};
    // assert(Solution::searchLowerBound(nums, target, 0, nums.size()-1) == expected[0]);
    // assert(Solution::searchUpperBound(nums, target, 0, nums.size()-1) == expected[1]);
    assert(Solution::searchRange(nums, target) == expected);
  }

  return 0;
}
