#include <cassert>
#include <vector>

class Solution {
public:
  static bool isMonotonic(std::vector<int>& nums) {
    int8_t seen_difference = 0;
    for (size_t i = 1; i < nums.size(); ++i) {
      if (nums[i] == nums[i-1])
        continue;
      if (nums[i] > nums[i-1]) {
        if (seen_difference == 0) {
          seen_difference = 1;
          continue;
        }
        if (seen_difference < 0)
          return false;
      } else { // nums[i] < nums[i-1]
        if (seen_difference == 0) {
          seen_difference = -1;
          continue;
        }
        if (seen_difference > 0)
          return false;
      }
    }
    return true;
  }
};

int main() {
  std::vector<int> v1{1,2,2,3};
  assert(Solution::isMonotonic(v1));

  std::vector<int> v2{6,5,4,4};
  assert(Solution::isMonotonic(v2));

  std::vector<int> v3{1,3,2};
  assert(Solution::isMonotonic(v3) == false);

  std::vector<int> v4{1};
  assert(Solution::isMonotonic(v4));
}
