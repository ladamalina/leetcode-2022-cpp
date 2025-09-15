#include <bits/stdc++.h>

constexpr int MAX_POW3 = 1162261467; // 3^19 < 2147483647

class Solution {
 public:
  static bool isPowerOfThree(const int n) {
    return n >= 1 && MAX_POW3 % n == 0;
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
