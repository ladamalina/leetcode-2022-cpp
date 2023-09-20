//#pragma GCC optimize("O3")
//#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

class Solution {
 public:
  int candy(std::vector<int>& ratings) {
    auto n = static_cast<int>(ratings.size());
    std::vector<std::vector<int>> lt(n); // i-th is less than i-val
    std::vector<std::vector<int>> gt(n); // i-th is less than i-val
    for (int i = 1; i < n; ++i) {
      if (ratings[i-1] < ratings[i]) {
        lt[i-1].push_back(i);
        gt[i].push_back(i-1);
      } else if (ratings[i-1] > ratings[i]) {
        lt[i].push_back(i-1);
        gt[i-1].push_back(i);
      }
    }
    std::vector<int> candies(n, 1);
    for (int i = 0; i < n; ++i) {
      if (candies[i] == 1 && gt[i].empty()) {
        for (auto max_i : lt[i]) {
          auto min_i = i;
          while (true) {
            candies[max_i] = std::max(candies[max_i], candies[min_i]+1);
            if (lt[max_i].empty()) break;
            else {
              min_i = max_i;
              max_i = lt[max_i].front();
            }
          }
        }
      }
    }
    auto candies_sum = std::accumulate(candies.begin(), candies.end(), 0);
    return candies_sum;
  }
};

int main() {
  {
    std::vector<int> ratings{1,0,2};
    int e_out = 5;
    auto a_out = Solution().candy(ratings);
    assert(a_out == e_out);
  }
  {
    std::vector<int> ratings{1,2,2};
    int e_out = 4;
    auto a_out = Solution().candy(ratings);
    assert(a_out == e_out);
  }
}
