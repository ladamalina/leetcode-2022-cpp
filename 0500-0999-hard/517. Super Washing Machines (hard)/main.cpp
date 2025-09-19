// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;

using vi = std::vector<int>;

class Solution {
  public:
  static int findMinMoves(vi& machines) {
    const auto n = static_cast<int>(machines.size());
    const auto m_sum = std::accumulate(machines.begin(), machines.end(), 0);
    if (m_sum % n != 0) {
      return -1;
    }
    const auto target = m_sum / n;

    vi diff_psum(n);
    for (int i = 0; i < n; ++i) {
      const auto diff_i = machines[i] - target;
      diff_psum[i] = diff_i + (i==0) ? 0 : diff_psum[i-1];
    }
    int max_turns = 0;
    for (int i = 0; i < n; ++i) {
      const auto diff_i = machines[i] - target;
      const auto diff_l = (i == 0) ? 0 : diff_psum[i-1];
      const auto diff_r = diff_psum[n-1] - diff_psum[i];
      int turns;
      if (diff_i <= 0) {
        turns = std::max(diff_l, diff_r);
      } else { // diff[i] > 0
        turns = diff_i + std::max(diff_l, 0) + std::max(diff_r, 0);
      }
      max_turns = std::max(max_turns, turns);
    }
    return max_turns;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi machines{1,0,5};
    const auto a_out = Solution::findMinMoves(machines);
    assert(a_out == 3);
    
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi machines{0,3,0};
    const auto a_out = Solution::findMinMoves(machines);
    assert(a_out == 2);
    
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi machines{0,2,0};
    const auto a_out = Solution::findMinMoves(machines);
    assert(a_out == -1);
    
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi machines{0,0,11,5};
    const auto a_out = Solution::findMinMoves(machines);
    assert(a_out == 8);
    
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
