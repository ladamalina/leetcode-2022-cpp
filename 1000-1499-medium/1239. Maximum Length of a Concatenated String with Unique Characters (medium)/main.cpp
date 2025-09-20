// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;

using ll = long long;
using ii = std::pair<int, int>;
using vi = std::vector<int>;
using vvi = std::vector<vi>;
using vii = std::vector<ii>;

using DP = std::unordered_set<int>;

class Solution {
 public:
  static int maxLength(const std::vector<std::string>& arr) {
    const auto n = static_cast<int>(arr.size());

    const auto get_mask = [&](const std::string& s) {
      int mask = 0;
      const auto len = static_cast<int>(s.size());
      for (int i = 0; i < len; ++i) {
        if (mask & (1<<(s[i]-'a')))
          return -1;
        mask |= (1<<(s[i]-'a'));
      }
      return mask;
    };
    
    DP dp0{0};
    for (int i = 0; i < n; ++i) {
      DP dp = dp0;

      const auto mask = get_mask(arr[i]);
      if (mask != -1) {
        for (const auto p_mask : dp0) {
          if ((mask | p_mask) == (mask ^ p_mask)) {
            dp.insert(mask | p_mask);
          }
        }
      }
      
      std::swap(dp, dp0);
    }
    int max_res = 0;
    for (const auto mask : dp0) {
      max_res = std::max(max_res, __builtin_popcount(mask));
    }
    return max_res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::vector<std::string> arr{"un","iq","ue"};
    const auto a_out = Solution::maxLength(arr);
    assert(a_out == 4);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::vector<std::string> arr{"cha","r","act","ers"};
    const auto a_out = Solution::maxLength(arr);
    assert(a_out == 6);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::vector<std::string> arr{"aa","bb"};
    const auto a_out = Solution::maxLength(arr);
    assert(a_out == 0);

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
