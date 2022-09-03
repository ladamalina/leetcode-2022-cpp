#include <cassert>
#include <vector>

class Solution {
public:
  static int jump(std::vector<int>& nums) {
    std::vector<int> jumps(nums.size());
    for (size_t i = 0; i < nums.size() - 1; ++i) {
      int max_jumps = nums[i];
      for (size_t j = i+1; j <= i+max_jumps && j < jumps.size(); ++j) {
        if (jumps[j] == 0)
          jumps[j] = jumps[i] + 1;
        else
          jumps[j] = std::min(jumps[j], jumps[i] + 1);
      }
    }

    return jumps.back();
  }
};

int main() {
  std::vector<int> v1 = {2,3,1,1,4};
  assert(Solution::jump(v1) == 2);

  std::vector<int> v2 = {2,3,0,1,4};
  assert(Solution::jump(v2) == 2);

  return 0;
}
