// #include <bits/stdc++.h>

#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <deque>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <numeric>
#include <optional>
#include <random>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <variant>
#include <vector>

using namespace std;
using ll = long long;

class Solution {
public:
  ll maximizeXorAndXor(const vector<int>& nums) {
    const int n = nums.size();
    
    auto all_xor = 0;
    for (const auto x : nums) all_xor ^= x;

    ll max_res = 0;
    const auto n_masks = (1 << n);

    for (auto mask = 0; mask < n_masks; ++mask) {
      auto mask_and = INT_MAX, mask_xor = 0;

      for (auto i = 0; i < n; ++i) {
        if (mask & (1 << i)) {
          mask_xor ^= nums[i];
          mask_and &= nums[i];
        }
      }
      if (mask_and == INT_MAX) mask_and = 0;

      const auto unmask_xor = all_xor ^ mask_xor;
      const auto inv_mask = ~unmask_xor;

      // Build linear basis from unselected elements after masking with ~M
      vector<int> basis;
      for (auto i = 0; i < n; ++i) {
        if (!(mask & (1 << i))) {
          auto reduced = nums[i] & inv_mask;
          for (const auto b : basis) {
            reduced = min(reduced, reduced ^ b);
          }
          if (reduced) {
            basis.push_back(reduced);
            // Keep basis sorted descending
            int k = basis.size() - 1;
            while (k > 0 && basis[k] > basis[k - 1]) {
              swap(basis[k], basis[k - 1]);
              --k;
            }
          }
        }
      }

      // Calculate max XOR using the basis
      int maxXor = 0;
      for (const auto b : basis) {
        maxXor = max(maxXor, maxXor ^ b);
      }

      const auto res = 1ll * mask_and + 1ll * unmask_xor + 2ll * maxXor;
      max_res = max(max_res, res);
    }
    return max_res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vector<int> nums{2,3};
    const auto a_out = Solution().maximizeXorAndXor(nums);
    assert(a_out == 5);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vector<int> nums{1,3,2};
    const auto a_out = Solution().maximizeXorAndXor(nums);
    assert(a_out == 6);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vector<int> nums{2,3,6,7};
    const auto a_out = Solution().maximizeXorAndXor(nums);
    assert(a_out == 15);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  std::cerr << "TestSolution OK"sv << std::endl;
}

int main() {
#ifndef NDEBUG
  TestSolution();
#endif
  return 0;
}
