//#pragma GCC optimize("O3")
//#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;

class Solution {
  public:
  static int findMaximizedCapital(int k, int w, const std::vector<int>& profits, const std::vector<int>& capital) {
    const auto n = static_cast<int>(profits.size());
    std::vector<int> ids(n);
    std::iota(ids.begin(), ids.end(), 0);
    std::sort(ids.begin(), ids.end(), [&](const int l, const int r) {
      return capital[l] < capital[r];
    });
    std::priority_queue<int, std::vector<int>, std::less<>> pq;
    int i = 0;
    int res_w = w;
    int done = 0;
    while (done < k) {
      while (i < n && capital[ids[i]] <= res_w) {
        pq.push(profits[ids[i]]);
        ++i;
      }
      if (!pq.empty()) {
        res_w += pq.top();
        pq.pop();
        ++done;
      } else break;
    }
    return res_w;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::vector<int> profits{1,2,3};
    const std::vector<int> capital{0,1,1};
    const auto e_out = Solution::findMaximizedCapital(2, 0, profits, capital);
    assert(e_out == 4);
    
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
