#include <bits/stdc++.h>

class Solution {
public:
  static bool isPowerOfTwo(int n) {
    return n >= 1 && __builtin_popcount(n) == 1;
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
