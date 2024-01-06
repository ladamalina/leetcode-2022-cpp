//#pragma GCC optimize("O3")
//#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;

class Solution {
  public:
  static std::vector<double> medianSlidingWindow(const std::vector<int>& nums, const int k) {
    const int n = nums.size();
    std::multiset<int> l_mset;
    std::multiset<int> r_mset;
    std::vector<double> res(n-(k-1));
    for (int ri = 0; ri < n; ++ri) {
      // remove l
      const auto li = ri - k;
      if (li >= 0) {
        if (!r_mset.empty() && nums[li] >= *r_mset.begin()) {
          r_mset.erase(r_mset.find(nums[li]));
        } else if (!l_mset.empty() && nums[li] <= *l_mset.rbegin()) {
          l_mset.erase(l_mset.find(nums[li]));
        }
      }
      // add r
      if (l_mset.empty() || (nums[ri] < *l_mset.rbegin())) {
        l_mset.emplace(nums[ri]);
      } else {
        r_mset.emplace(nums[ri]);
      }
      // rebalance
      while (l_mset.size() < r_mset.size()) {
        l_mset.emplace(*r_mset.begin());
        r_mset.erase(r_mset.begin());
      }
      while (l_mset.size() > r_mset.size() + 1) {
        r_mset.emplace(*l_mset.rbegin());
        l_mset.erase(std::prev(l_mset.end()));
      }
      // get median
      if (ri >= k-1) {
        if (l_mset.size() == r_mset.size()) {
          res[ri-(k-1)] = (double(*l_mset.rbegin()) + double(*r_mset.begin())) / 2;
        } else {
          res[ri-(k-1)] = double(*l_mset.rbegin());
        }
      }
    }
    return res;
  }
};

/*
[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    std::vector<int> nums{3,1,5,8};
    const auto e_out = Solution::maxCoins(nums);
    assert(e_out == 167);
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    std::vector<int> nums{1,5};
    const auto e_out = Solution::maxCoins(nums);
    assert(e_out == 10);
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  std::cerr << "TestSolution OK"sv << std::endl;
}
*/

int main() {
#ifndef NDEBUG
  // TestSolution();
#endif
  return 0;
}
