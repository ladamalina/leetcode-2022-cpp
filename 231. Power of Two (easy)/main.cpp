#include <bitset>
#include <cassert>

class Solution {
 public:
  static bool isPowerOfTwo(int n) {
    if (n <= 0)
      return false;
    // n > 1
    auto bits = std::bitset<32>(n);
    int one_pos = -1;
    for (int i = 0; i < bits.size(); ++i) {
      if (bits[i]) {
        if (one_pos == -1) {
          one_pos = i;
        }
        else
          return false;
      }
    }
    return true;
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
