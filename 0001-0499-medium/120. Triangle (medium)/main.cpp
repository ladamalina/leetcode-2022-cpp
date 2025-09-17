#include <cassert>
#include <vector>

using Row = std::vector<int>;
using Triangle = std::vector<Row>;

class Solution {
 public:
  static int minimumTotal(Triangle& triangle) {
    Row dp_prev = triangle[0];

    for (size_t i = 1; i < triangle.size(); ++i) {
      Row dp(dp_prev.size()+1);
      for (size_t j = 0; j < dp.size(); ++j) {
        if (j >= 1 && j+1 < dp.size()) { // mid number
          dp[j] = std::min(dp_prev[j-1], dp_prev[j]) + triangle[i][j];
        } else if (j == 0) { // left number
          dp[j] = dp_prev[j] + triangle[i][j];
        } else { // right number
          dp[j] = dp_prev[j-1] + triangle[i][j];
        }
      }
      dp_prev = std::move(dp);
    }

    auto best_sum = *std::min_element(dp_prev.begin(), dp_prev.end());
    return best_sum;
  }
};

int main() {
  {
    Triangle input{{2},{3,4},{6,5,7},{4,1,8,3}};
    assert(Solution::minimumTotal(input) == 11);
  }
  {
    Triangle input{{-10}};
    assert(Solution::minimumTotal(input) == -10);
  }
}
