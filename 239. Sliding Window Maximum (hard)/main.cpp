#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;

class Solution {
 public:
  std::vector<int> maxSlidingWindow(std::vector<int>& nums, int k) {
    auto n = static_cast<int>(nums.size());
    std::vector<int> res(n-k+1);
    std::multiset<int> w;
    for (int i = 0; i < k; ++i) w.insert(nums[i]);
    res[0] = *std::prev(w.end());
    for (int l = 0; l < n-k; ++l) {
      w.erase(w.find(nums[l]));
      auto r = l + k;
      w.insert(nums[r]);
      res[l+1] = *std::prev(w.end());
    }
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    std::vector<int> nums{1,3,-1,-3,5,3,6,7};
    auto k = 3;
    std::vector<int> e_out{3,3,5,5,6,7};
    auto start_t = std::chrono::high_resolution_clock::now();
    auto a_out = Solution().maxSlidingWindow(nums, k);
    auto end_t = std::chrono::high_resolution_clock::now();
    auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
    assert(a_out == e_out);
  }
  {
    std::vector<int> nums{1};
    auto k = 1;
    std::vector<int> e_out{1};
    auto start_t = std::chrono::high_resolution_clock::now();
    auto a_out = Solution().maxSlidingWindow(nums, k);
    auto end_t = std::chrono::high_resolution_clock::now();
    auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
    assert(a_out == e_out);
  }
  std::cerr << "TestSolution OK"sv << std::endl;
}

int main() {
#ifndef NDEBUG
  TestSolution();
#endif
  return 0;
}
