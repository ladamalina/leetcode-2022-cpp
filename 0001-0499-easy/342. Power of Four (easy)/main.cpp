#include <bits/stdc++.h>

class Solution {
public:
  static bool isPowerOfFour(int n) {
    if (n < 1) return false;
    while (n % 4 == 0) n /= 4;
    return n == 1;
  }
};

int main() {
  assert(Solution::isPowerOfFour(16));
  assert(Solution::isPowerOfFour(5) == false);
  assert(Solution::isPowerOfFour(1));
  assert(Solution::isPowerOfFour(2) == false);
  assert(Solution::isPowerOfFour(8) == false);

  return 0;
}
