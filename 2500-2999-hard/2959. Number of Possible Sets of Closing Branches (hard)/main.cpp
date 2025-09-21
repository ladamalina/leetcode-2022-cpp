// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;

using ll = long long;
using ii = std::pair<int, int>;
using vi = std::vector<int>;
using vvi = std::vector<vi>;
using vii = std::vector<ii>;

int d[10][10];

bool Check(int mask, int n, int max_d, const vvi& roads) {
  if (__builtin_popcount(mask) <= 1)
    return true;

  std::fill(&d[0][0], &d[0][0] + sizeof(d) / sizeof(d[0][0]), INT_MAX);
  for (int v = 0; v < n; ++v) {
    if (mask & (1<<v)) {
      d[v][v] = 0;
    }
  }
  for (const auto& r : roads) {
    if ((mask & (1<<r[0])) && (mask & (1<<r[1]))) {
      d[r[0]][r[1]] = std::min(d[r[0]][r[1]], r[2]);
      d[r[1]][r[0]] = std::min(d[r[1]][r[0]], r[2]);
    }
  }
  for (int k=0; k<n; ++k)
    for (int i=0; i<n; ++i)
      for (int j=0; j<n; ++j)
        if (d[i][k] < INT_MAX && d[k][j] < INT_MAX)
          d[i][j] = std::min(d[i][j], d[i][k] + d[k][j]);
  
  int max_dist = 0;
  for (int i=0; i<n; ++i)
    for (int j=0; j<n; ++j)
      if ((mask & (1<<i)) && (mask & (1<<j)))
        max_dist = std::max(max_dist, d[i][j]);
  
  return max_dist <= max_d;
}

int Rec(int mask, int i, int n, int max_d, const vvi& roads, std::unordered_map<int, int>& memo) {
  if (i == n)
    return Check(mask, n, max_d, roads) ? 1 : 0;
  if (memo.contains(mask))
    return memo.at(mask);

  // skip
  const auto skip_res = Rec(mask, i+1, n, max_d, roads, memo);
  // take
  const auto take_res = Rec(mask | (1<<i), i+1, n, max_d, roads, memo);

  const auto sub_res = skip_res + take_res;
  memo[mask] = sub_res;
  return sub_res;
}

class Solution {
 public:
  static int numberOfSets(int n, int max_d, const vvi& roads) {
    std::unordered_map<int, int> memo;
    const auto res = Rec(0, 0, n, max_d, roads, memo);
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const int n = 3;
    const int max_d = 5;
    const vvi roads{{0,1,2},{1,2,10},{0,2,10}};
    const auto a_out = Solution::numberOfSets(n, max_d, roads);
    assert(a_out == 5);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const int n = 3;
    const int max_d = 5;
    const vvi roads{{0,1,20},{0,1,10},{1,2,2},{0,2,2}};
    const auto a_out = Solution::numberOfSets(n, max_d, roads);
    assert(a_out == 7);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const int n = 1;
    const int max_d = 10;
    const vvi roads{};
    const auto a_out = Solution::numberOfSets(n, max_d, roads);
    assert(a_out == 2);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const int n = 3;
    const int max_d = 12;
    const vvi roads{{1,0,11},{1,0,16},{0,2,13}};
    const auto a_out = Solution::numberOfSets(n, max_d, roads);
    assert(a_out == 5);

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
