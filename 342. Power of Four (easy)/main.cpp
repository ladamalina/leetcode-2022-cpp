#include <bitset>
#include <cassert>

class Solution {
 public:
  static bool isPowerOfFour(int n) {
    if (n <= 0)
      return false;
    if (n == 1)
      return true;
    // n > 1
    auto bits = std::bitset<32>(n);
    int one_pos = -1;
    for (int i = 0; i < bits.size(); ++i) {
      if (bits[i]) {
        if (one_pos == -1) {
          one_pos = i;
          if (one_pos % 2 == 1)
            return false;
        }
        else
          return false;
      }
    }
    return true;
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
