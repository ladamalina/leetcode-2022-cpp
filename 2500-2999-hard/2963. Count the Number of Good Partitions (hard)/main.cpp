// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;

using ll = long long;
using ii = std::pair<int, int>;
using vi = std::vector<int>;
using vvi = std::vector<vi>;
using vii = std::vector<ii>;

const ll MOD = 1e9 + 7;

template <typename T>
[[maybe_unused]] T ModPow(T a, T x, T m) {
  T ret = 1;
  while (x) {
    if (x & 1) (ret *= a) %= m;
    x >>= 1;
    (a *= a) %= m;
  }
  return ret;
}

class Solution {
 public:
  static int numberOfGoodPartitions(const vi& nums) {
    const auto n = static_cast<int>(nums.size());
    
    std::unordered_map<int, ii> num_lr;
    for (int i = 0; i < n; ++i) {
      const auto it = num_lr.find(nums[i]);
      if (it != num_lr.end()) {
        it->second.second = std::max(it->second.second, i);
      } else {
        num_lr[nums[i]] = {i, i};
      }
    }
    
    vii blocks;
    blocks.reserve(num_lr.size());
    for (const auto& [_, lr] : num_lr) {
      blocks.emplace_back(lr);
    }
    std::sort(blocks.begin(), blocks.end());
    
    int max_r = -1;
    ll cnt = 0;
    for (const auto& [l, r] : blocks) {
      if (l > max_r) {
        ++cnt;
        max_r = r;
      } else {
        max_r = std::max(max_r, r);
      }
    }
    
    ll res = ModPow(2ll, cnt-1, MOD);
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums{1,2,3,4};
    const auto a_out = Solution::numberOfGoodPartitions(nums);
    assert(a_out == 8);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums{1,1,1,1};
    const auto a_out = Solution::numberOfGoodPartitions(nums);
    assert(a_out == 1);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums{1,2,1,3};
    const auto a_out = Solution::numberOfGoodPartitions(nums);
    assert(a_out == 2);

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
