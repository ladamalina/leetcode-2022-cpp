#include <cassert>
#include <vector>

class Solution {
 public:
  static int search(std::vector<int>& nums, int target) {
    return findInRange(nums, target, 0, nums.size() - 1);
  }

  static int findInRange(const std::vector<int>& nums, const int& target, const int& begin_idx, const int& end_idx) {
    if (target == nums[begin_idx])
      return begin_idx;
    if (target == nums[end_idx])
      return end_idx;

    if (end_idx - begin_idx <= 1)
      return -1;

    int mid_idx = begin_idx + (end_idx - begin_idx) / 2;
    if (target == nums[mid_idx])
      return mid_idx;

    if (nums[begin_idx] < nums[end_idx]) {
      if (target < nums[begin_idx] || target > nums[end_idx])
        return -1;
      // target is in (begin, end)

      if (target < nums[mid_idx])
        return findInRange(nums, target, begin_idx, mid_idx); // take left half
      else
        return findInRange(nums, target, mid_idx, end_idx); // take right half
    }
    // nums[begin_idx] > nums[end_idx]

    if (nums[begin_idx] < nums[mid_idx]) { // left half is strictly increasing
      if (nums[begin_idx] < target && target < nums[mid_idx])
        return findInRange(nums, target, begin_idx, mid_idx); // take left half
      else
        return findInRange(nums, target, mid_idx, end_idx); // take right half
    }
    // right half is strictly increasing
    if (nums[mid_idx] < target && target < nums[end_idx])
      return findInRange(nums, target, mid_idx, end_idx); // take right half
    else
      return findInRange(nums, target, begin_idx, mid_idx); // take left half
  }
};

int main() {
  std::vector<int> v1{4,5,6,7,0,1,2};
  assert(Solution::search(v1, 0) == 4);

  std::vector<int> v2{4,5,6,7,0,1,2};
  assert(Solution::search(v2, 3) == -1);

  std::vector<int> v3{1};
  assert(Solution::search(v3, 0) == -1);

  return 0;
}
