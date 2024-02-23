#include <bits/stdc++.h>

class Solution {
 public:
  static bool isPowerOfTwo(int n) {
    if (n <= 0)
      return false;
    // n >= 1
    const auto bits = std::bitset<32>(n);
    return bits.count() == 1;
  }
};

int main() {
  assert(Solution::isPowerOfTwo(16));
  assert(Solution::isPowerOfTwo(5) == false);
  assert(Solution::isPowerOfTwo(1));
  assert(Solution::isPowerOfTwo(2) == true);
  assert(Solution::isPowerOfTwo(8) == true);

  return 0;
}
