#include <cassert>
#include <vector>

class Solution {
 public:
  static void nextPermutation(std::vector<int>& nums) {
    int nums_size = static_cast<int>(nums.size());
    if (1 == nums_size) {
      return;
    }
    // nums_size >= 2

    int i = nums_size - 2;
    while (i >= 0 && nums[i] >= nums[i+1]) {
      --i;
    }
    if (i >= 0) {
      int j = nums_size - 1;
      while (nums[j] <= nums[i]) {
        --j;
      }
      std::iter_swap(nums.begin()+i, nums.begin()+j);
    }
    std::reverse(nums.begin()+i+1, nums.end());
  }
};

int main() {
  {
    std::vector<int> nums{1,2,3};
    std::vector<int> expected_nums{1,3,2};
    Solution::nextPermutation(nums);
    assert(nums == expected_nums);
  }
  {
    std::vector<int> nums{3,2,1};
    std::vector<int> expected_nums{1,2,3};
    Solution::nextPermutation(nums);
    assert(nums == expected_nums);
  }
  {
    std::vector<int> nums{1,1,5};
    std::vector<int> expected_nums{1,5,1};
    Solution::nextPermutation(nums);
    assert(nums == expected_nums);
  }
}
