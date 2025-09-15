#include <bitset>
#include <cassert>

class Solution {
 public:
  static int hammingDistance(uint32_t x, uint32_t y) {
    auto bits_x = std::bitset<32>(x);
    auto bits_y = std::bitset<32>(y);
    uint8_t distance = 0;
    for (int i = 31; i >= 0; --i) {
      if (bits_x[i] != bits_y[i])
        ++distance;
    }

    return distance;
  }
};

int main() {
  assert(Solution::hammingDistance(1,4) == 2);
  assert(Solution::hammingDistance(3,1) == 1);
  assert(Solution::hammingDistance(3,3) == 0);

  return 0;
}
