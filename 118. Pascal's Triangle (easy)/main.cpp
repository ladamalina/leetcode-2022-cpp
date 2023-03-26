#include <iostream>
#include <vector>

using Triangle = std::vector<std::vector<int>>;

class Solution {
 public:
  static Triangle generate(int numRows) {
    if (numRows == 1) {
      return {{1}};
    }

    Triangle dp{{1}, {1,1}};
    dp.reserve(numRows);
    for (int i = 2; i < numRows; ++i) {
      dp.emplace_back(i + 1, 1);
      for (int j = 1; j < i; ++j) {
        dp[i][j] = dp[i-1][j-1] + dp[i-1][j];
      }
    }

    return dp;
  }
};
