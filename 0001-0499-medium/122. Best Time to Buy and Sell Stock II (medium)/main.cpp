#include <vector>

class Solution {
 public:
  static int maxProfit(const std::vector<int>& prices) {
    if (static_cast<int>(prices.size()) <= 1) {
      return 0;
    }
    int buy_price = -1;
    int max_profit = 0;
    for (auto it = prices.begin(); it != prices.end()-1; ++it) {
      int tomorrow_trend = trend(*it, *(it+1));
      if (tomorrow_trend > 0) { // price goes up
        if (buy_price == -1) {
          buy_price = *it; // buy today
        }
      } else if (tomorrow_trend < 0) { // price goes down
        if (buy_price >= 0) { // sell today
          max_profit += (*it - buy_price);
          buy_price = -1;
        }
      }
    }
    if (buy_price >= 0) {
      max_profit += (prices.back() - buy_price);
    }

    return max_profit;
  }
 private:
  static int trend(const int price_today, const int price_tomorrow) {
    if (price_today < price_tomorrow) {
      return 1;
    }
    if (price_today > price_tomorrow) {
      return -1;
    }
    return 0;
  }
};

int main() {
  {
    std::vector<int> prices{7,1,5,3,6,4};
    assert(Solution::maxProfit(prices) == 7);
  }
  {
    std::vector<int> prices{1,2,3,4,5};
    assert(Solution::maxProfit(prices) == 4);
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
  {
    std::vector<int> prices{1,2,1,2,1,2,1};
    assert(Solution::maxProfit(prices) == 3);
  }
  {
    std::vector<int> prices{1,2,2,2,1,1,1,2,1,2,1};
    assert(Solution::maxProfit(prices) == 3);
  }
  {
    std::vector<int> prices{3,2,2,2,1,1,1,2,1,2,1};
    assert(Solution::maxProfit(prices) == 2);
  }
  return 0;
}
