#include <cassert>

class Solution {
 public:
  static bool isPowerOfThree(int n) {
    if (n < 1)
      return false;
    int max_int_pow3 = 1162261467; // 3^19 < 2147483647
    return max_int_pow3 % n == 0;
  }
};

int main() {
  assert(Solution::isPowerOfThree(81));
  assert(Solution::isPowerOfThree(1));
  assert(Solution::isPowerOfThree(-1) == false);
  assert(Solution::isPowerOfThree(0) == false);
  assert(Solution::isPowerOfThree(14348907));

  return 0;
}
