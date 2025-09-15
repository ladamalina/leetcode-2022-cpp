#include <bitset>
#include <cassert>

class Solution {
 public:
  static int hammingWeight(uint32_t n) {
    auto bits = std::bitset<32>(n);
    uint32_t ones = 0;
    for (size_t i = 0; i < bits.size(); ++i) {
      if (bits[i]) {
        ++ones;
      }
    }
    return ones;
  }
};

int main() {
  assert(Solution::hammingWeight(13) == 3);
  assert(Solution::hammingWeight(0) == 0);
  assert(Solution::hammingWeight(8388621) == 4);

  return 0;
}
