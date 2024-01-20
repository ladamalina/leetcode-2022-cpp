// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;

using ll = long long;
using ii = std::pair<int, int>;
using vi = std::vector<int>;
using vvi = std::vector<vi>;
using vii = std::vector<ii>;

int l_cnt[100001];
int w_cnt[100001];

class Solution {
  public:
  static vvi findWinners(const vvi& matches) {
    memset(l_cnt, 0, sizeof(l_cnt));
    memset(w_cnt, 0, sizeof(w_cnt));
    int max_p = 0;
    for (const auto& m : matches) {
      ++l_cnt[m[1]];
      ++w_cnt[m[0]];
      max_p = std::max(max_p, std::max(m[0], m[1]));
    }
    
    vvi ans(2);
    for (int i = 1; i <= max_p; ++i) {
      if (l_cnt[i] == 1) {
        ans[1].push_back(i);
      } else if (l_cnt[i] == 0 && w_cnt[i] > 0) {
        ans[0].push_back(i);
      }
    }
    return ans;
  }
};

/*[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums{5,2,2};
    const auto a_out = Solution::findMaximumLength(nums);
    assert(a_out == 1);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  std::cerr << "TestSolution OK"sv << std::endl;
}*/

int main() {
#ifndef NDEBUG
  // TestSolution();
#endif
  return 0;
}
