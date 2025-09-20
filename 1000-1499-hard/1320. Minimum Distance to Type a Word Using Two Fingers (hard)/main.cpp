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

using namespace std::literals;

using ll = long long;
using ii [[maybe_unused]] = std::pair<int, int>;
using vi [[maybe_unused]] = std::vector<int>;
using vl [[maybe_unused]] = std::vector<ll>;
using vvi [[maybe_unused]] = std::vector<vi>;
using vvl [[maybe_unused]] = std::vector<vl>;
using vii [[maybe_unused]] = std::vector<ii>;
using vb [[maybe_unused]] = std::vector<bool>;
using vd [[maybe_unused]] = std::vector<double>;
using vs [[maybe_unused]] = std::vector<std::string>;

#define FOR(_i, _a, _b) for (int _i = (_a); _i <= (_b); ++(_i))
#define FORD(_i, _a, _b) for (int _i = (_a); _i >= (_b); --(_i))
#define RNG(_l) (_l).begin(), (_l).end()
#define SORT(_l) std::sort((_l).begin(), (_l).end())
#define CI(_v) static_cast<int>(_v)
#define CL(_v) static_cast<ll>(_v)
#define CD(_v) static_cast<double>(_v)
#define SZ(_v) static_cast<int>((_v).size())
#define F first
#define S second

std::array<std::array<int, 26>, 26> dp, dp2;

class Solution {
public:
  int minimumDistance(const std::string& word) {
    const auto n = SZ(word);
    std::fill(&dp[0][0], &dp[0][0] + sizeof(dp) / sizeof(dp[0][0]), 0);
    
    FOR(wi, 1, n-1) {
      std::fill(&dp2[0][0], &dp2[0][0] + sizeof(dp2) / sizeof(dp2[0][0]), INT_MAX);

      const auto c = word[wi] - 'A';
      const ii c_pos{c / 6, c % 6};

      FOR(i, 0, 25) {
        const auto j = word[wi-1] - 'A';
        
        const ii i_pos{i / 6, i % 6};
        const auto i_diff = std::abs(c_pos.F - i_pos.F) + std::abs(c_pos.S - i_pos.S);

        const ii j_pos{j / 6, j % 6};
        const auto j_diff = std::abs(c_pos.F - j_pos.F) + std::abs(c_pos.S - j_pos.S);

        // move 1st finger (i)
        dp2[c][j] = std::min(dp2[c][j], dp[i][j] + i_diff);
        // move 2nd finger (j)
        dp2[i][c] = std::min(dp2[i][c], dp[i][j] + j_diff);
      }
      
      FOR(j, 0, 25) {
        const auto i = word[wi-1] - 'A';

        const ii i_pos{i / 6, i % 6};
        const auto i_diff = std::abs(c_pos.F - i_pos.F) + std::abs(c_pos.S - i_pos.S);

        const ii j_pos{j / 6, j % 6};
        const auto j_diff = std::abs(c_pos.F - j_pos.F) + std::abs(c_pos.S - j_pos.S);
          
        // move 1st finger (i)
        dp2[c][j] = std::min(dp2[c][j], dp[i][j] + i_diff);
        // move 2nd finger (j)
        dp2[i][c] = std::min(dp2[i][c], dp[i][j] + j_diff);
      }

      dp = dp2;
    }

    auto min_res = INT_MAX;
    FOR(i, 0, 25) min_res = std::min(min_res, dp[i][word.back()-'A']);
    FOR(j, 0, 25) min_res = std::min(min_res, dp[word.back()-'A'][j]);

    return min_res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().minimumDistance("CAKE");
    assert(a_out == 3);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().minimumDistance("HAPPY");
    assert(a_out == 6);
  
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
