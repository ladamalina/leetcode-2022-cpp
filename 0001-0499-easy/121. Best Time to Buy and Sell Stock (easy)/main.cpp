#include <vector>

class Solution {
 public:
  static int maxProfit(const std::vector<int>& prices) {
    if (static_cast<int>(prices.size()) <= 1) {
      return 0;
    }
    int prev_min = prices[0];
    int max_profit = 0;
    for (auto it = prices.begin()+1; it != prices.end(); ++it) {
      if (*it < prev_min) {
        prev_min = *it;
        continue;
      }

      int current_max_profit = *it - prev_min;
      if (current_max_profit > max_profit) {
        max_profit = current_max_profit;
      }
    }

    return max_profit;
  }
};

int main() {
  {
    std::vector<int> prices{7,1,5,3,6,4};
    assert(Solution::maxProfit(prices) == 5);
  }
  {
    std::vector<int> prices{7,6,4,3,1};
    assert(Solution::maxProfit(prices) == 0);
  }
  {
    std::vector<int> prices{1};
    assert(Solution::maxProfit(prices) == 0);
  }
  {
    std::vector<int> prices{1,2};
    assert(Solution::maxProfit(prices) == 1);
  }
  {
    std::vector<int> prices{3,2};
    assert(Solution::maxProfit(prices) == 0);
  }
  return 0;
}
