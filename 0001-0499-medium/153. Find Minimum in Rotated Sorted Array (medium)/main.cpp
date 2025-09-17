#include <cassert>
#include <vector>

class Solution {
 public:
  static int findMin(std::vector<int>& nums) {
    return findMinOfRange(nums, 0, nums.size()-1);
  }

  static int findMinOfRange(std::vector<int>& nums, const int& begin_idx, const int& end_idx) {
    if (nums[begin_idx] < nums[end_idx])
      return nums[begin_idx];
    // nums[begin_idx] > nums[end_idx]

    if (end_idx - begin_idx <= 1)
      return std::min(nums[begin_idx], nums[end_idx]);
    // end_idx - begin_idx > 1; range len >= 3

    int mid_idx = begin_idx + (end_idx - begin_idx) / 2;

    if (nums[begin_idx] > nums[mid_idx]) // take left half
      return findMinOfRange(nums, begin_idx, mid_idx);
    else // take right half
      return findMinOfRange(nums, mid_idx, end_idx);
  }
};

int main() {
  std::vector<int> v1{3,4,5,1,2};
  assert(Solution::findMin(v1) == 1);

  std::vector<int> v2{4,5,6,7,0,1,2};
  assert(Solution::findMin(v2) == 0);

  std::vector<int> v3{11,13,15,17};
  assert(Solution::findMin(v3) == 11);

  return 0;
}
