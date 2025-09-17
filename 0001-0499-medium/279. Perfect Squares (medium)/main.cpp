#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

class Solution {
 public:
  static int numSquares(int n) {
    std::vector<int> dp{0, 1, 2, 3};
    dp.reserve(n + 1);

    for (int i = 4; i < n + 1; ++i) {
      dp.push_back(i);
      auto i_sqrt = static_cast<int>(std::ceil(std::sqrt(i)));
      for (int j = 0; j < i_sqrt + 1; ++j) {
        auto tmp = j * j;
        if (tmp > i) {
          break;
        } else {
          dp[i] = std::min(dp[i], 1 + dp[i - tmp]);
        }
      }
    }

    return dp[n];
  }
};

int main() {
  assert(Solution::numSquares(0) == 0);
  assert(Solution::numSquares(1) == 1);
  assert(Solution::numSquares(2) == 2);
  assert(Solution::numSquares(3) == 3);
  assert(Solution::numSquares(12) == 3);
  assert(Solution::numSquares(13) == 2);
}
