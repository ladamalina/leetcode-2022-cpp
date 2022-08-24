#include <cassert>
#include <vector>

class Solution {
 public:
  static int countHillValley(std::vector<int>& nums) {
    int count = 0;
    int8_t prev_non_zero_trend = 0;
    for (size_t i = 1; i < nums.size(); ++i) {
      if (nums[i] == nums[i-1])
        continue;
      if (nums[i] > nums[i-1]) { // up
        if (prev_non_zero_trend == 0) {
          prev_non_zero_trend = 1;
          continue;
        }
        if (prev_non_zero_trend < 0) {
          ++count;
          prev_non_zero_trend = 1;
          continue;
        }
      } else { // down: nums[i] < nums[i-1]
        if (prev_non_zero_trend == 0) {
          prev_non_zero_trend = -1;
          continue;
        }
        if (prev_non_zero_trend > 0) {
          ++count;
          prev_non_zero_trend = -1;
          continue;
        }
      }
    }
    return count;
  }
};

int main() {
  std::vector<int> v1{2,4,1,1,6,5};
  assert(Solution::countHillValley(v1) == 3);

  std::vector<int> v2{6,6,5,5,4,1};
  assert(Solution::countHillValley(v2) == 0);
}
