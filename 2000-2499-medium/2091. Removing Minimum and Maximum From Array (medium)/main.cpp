#include <cassert>
#include <vector>

class Solution {
 public:
  static int minimumDeletions(const std::vector<int>& nums) {
    if (nums.size() == 1u) {
      return 1;
    } // len >= 2
    int len = static_cast<int>(nums.size());

    int min_idx = 0, min_num = nums[0];
    int max_idx = 0, max_num = nums[0];
    for (int i = 1; i < len; ++i) {
      if (nums[i] < min_num) {
        min_num = nums[i];
        min_idx = i;
      }
      if (nums[i] > max_num) {
        max_num = nums[i];
        max_idx = i;
      }
    }
    int left = std::max(min_idx, max_idx) + 1;
    int right = len - std::min(min_idx, max_idx);
    int both = (std::min(min_idx, max_idx) + 1) + (len - std::max(min_idx, max_idx));
    int result = std::min({left, right, both});

    return result;
  }
};

int main() {
  assert(Solution::minimumDeletions({2,10,7,5,4,1,8,6}) == 5);
  assert(Solution::minimumDeletions({0,-4,19,1,8,-2,-3,5}) == 3);
  assert(Solution::minimumDeletions({101}) == 1);

  return 0;
}
