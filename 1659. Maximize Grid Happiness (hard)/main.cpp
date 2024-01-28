// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;

int memo[25][7][7][64][64] = {};

constexpr int IN_BASE = 120;
constexpr int IN_LOSE = -30;
constexpr int EX_BASE = 40;
constexpr int EX_GAIN = 20;

int Estimate([[maybe_unused]] int m, int n, int i, int j, int in_mask, int ex_mask, int base, int gain) {
  int diff = base;
  if (j > 0) {
    if (in_mask & 1) { diff += IN_LOSE; diff += gain; }
    if (ex_mask & 1) { diff += EX_GAIN; diff += gain; }
  }
  const auto up = (1 << (n - 1));
  if (i > 0) {
    if (in_mask & up) { diff += IN_LOSE; diff += gain; }
    if (ex_mask & up) { diff += EX_GAIN; diff += gain; }
  }
  return diff;
}

int Rec(int pos, int m, int n, int in_cnt, int ex_cnt, int in_mask, int ex_mask) {
  const auto i = pos / n;
  const auto j = pos % n;
  if (i >= m) return 0;

  if (memo[pos][in_cnt][ex_cnt][in_mask][ex_mask] != -1)
    return memo[pos][in_cnt][ex_cnt][in_mask][ex_mask];
  
  const auto i_in_mask = (in_mask << 1) & 63;
  const auto i_ex_mask = (ex_mask << 1) & 63;
  auto res = Rec(pos+1, m, n, in_cnt, ex_cnt, i_in_mask, i_ex_mask);
  
  if (in_cnt > 0) {
    const auto add = Estimate(m, n, i, j, in_mask, ex_mask, IN_BASE, IN_LOSE);
    const auto sub_res = add + Rec(pos+1, m, n, in_cnt-1, ex_cnt, i_in_mask+1, i_ex_mask);
    res = std::max(res, sub_res);
  }
  if (ex_cnt > 0) {
    const auto add = Estimate(m, n, i, j, in_mask, ex_mask, EX_BASE, EX_GAIN);
    const auto sub_res = add + Rec(pos+1, m, n, in_cnt, ex_cnt-1, i_in_mask, i_ex_mask+1);
    res = std::max(res, sub_res);
  }

  memo[pos][in_cnt][ex_cnt][in_mask][ex_mask] = res;
  return res;
}

class Solution {
 public:
  static int getMaxGridHappiness(int m, int n, int in_cnt, int ex_cnt) {
    std::fill(&memo[0][0][0][0][0], &memo[0][0][0][0][0] + sizeof(memo) / sizeof(memo[0][0][0][0][0]), -1);
    const auto res = Rec(0, m, n, in_cnt, ex_cnt, 0, 0);
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto a_out = Solution::getMaxGridHappiness(2, 3, 1, 2);
    assert(a_out == 240);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto a_out = Solution::getMaxGridHappiness(3, 1, 2, 1);
    assert(a_out == 260);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto a_out = Solution::getMaxGridHappiness(2, 2, 4, 0);
    assert(a_out == 240);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto a_out = Solution::getMaxGridHappiness(3, 1, 1, 3);
    assert(a_out == 230);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto a_out = Solution::getMaxGridHappiness(5, 4, 6, 3);
    assert(a_out == 920);

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
