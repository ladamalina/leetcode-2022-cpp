//#pragma GCC optimize("O3")
//#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;

int dp[100][100][100];

class Solution {
  public:
  static int removeBoxes(const std::vector<int>& boxes) {
    const auto n = static_cast<int>(boxes.size());
    memset(dp, 0, sizeof(dp));
    std::function<int(int,int,int)> rec = [&](int l, int r, int cnt) {
      if (l > r) return 0;
      auto& ans = dp[l][r][cnt];
      if (ans == 0) {
        while (l+1 <= r && boxes[l] == boxes[l+1]) {
          ++cnt;
          ++l;
        }
        ans = (cnt+1)*(cnt+1) + rec(l+1, r, 0);
        for (int m = l+1; m <= r; ++m) {
          if (boxes[l] == boxes[m]) {
            const auto m_ans = rec(m, r, cnt+1) + rec(l+1, m-1, 0);
            ans = std::max(ans, m_ans);
          }
        }
      }
      return ans;
    };
    const auto res = rec(0, n-1, 0);
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::vector<int> boxes{1,3,2,2,2,3,4,3,1};
    const auto e_out = Solution::removeBoxes(boxes);
    assert(e_out == 23);
    
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::vector<int> boxes{1,1,1};
    const auto e_out = Solution::removeBoxes(boxes);
    assert(e_out == 9);
    
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::vector<int> boxes{1};
    const auto e_out = Solution::removeBoxes(boxes);
    assert(e_out == 1);
    
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
