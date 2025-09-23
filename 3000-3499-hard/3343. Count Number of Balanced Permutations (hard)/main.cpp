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
using ld = long double;
using ii [[maybe_unused]] = std::pair<int, int>;
using vi [[maybe_unused]] = std::vector<int>;
using vl [[maybe_unused]] = std::vector<ll>;
using vvi [[maybe_unused]] = std::vector<vi>;
using vvvi [[maybe_unused]] = std::vector<vvi>;
using vvl [[maybe_unused]] = std::vector<vl>;
using vvvl [[maybe_unused]] = std::vector<vvl>;
using vii [[maybe_unused]] = std::vector<ii>;
using vb [[maybe_unused]] = std::vector<bool>;
using vd [[maybe_unused]] = std::vector<double>;
using vs [[maybe_unused]] = std::vector<std::string>;
using vc [[maybe_unused]] = std::vector<char>;

#define FOR(_i, _a, _b) for (auto _i = (_a); _i <= (_b); ++(_i))
#define FORD(_i, _a, _b) for (auto _i = (_a); _i >= (_b); --(_i))
#define RNG(_l) (_l).begin(), (_l).end()
#define SORT(_l) std::sort((_l).begin(), (_l).end())
#define CI(_v) static_cast<int>(_v)
#define CL(_v) static_cast<ll>(_v)
#define CD(_v) static_cast<ld>(_v)
#define CC(_v) static_cast<char>(_v)
#define SZ(_v) static_cast<int>((_v).size())
#define F first
#define S second
#define PB push_back

constexpr ll MOD = 1e9 + 7;
constexpr int MAX_N = 80, MAX_D = 9, MAX_TARGET_SUM = ((MAX_N * MAX_D) >> 1), MAX_NO = ((MAX_N + 1) >> 1);
std::array<int, MAX_D+1> d_freq, suff_d_freq;
std::array<std::array<ll, MAX_NO+1>, MAX_NO+1> comb;
bool init_comb = false;
std::array<std::array<std::array<ll, MAX_NO+1>, MAX_TARGET_SUM+1>, MAX_D+1> dp;

ll Rec(int d, int sum, int no, int target_sum) {
  if (no < 0 || (d <= 9 && suff_d_freq[d] < no) || sum > target_sum)
    return 0ll;
  if (d > 9)
    return CL(sum == target_sum && no == 0);
  if (dp[d][sum][no] != -1)
    return dp[d][sum][no];
  const auto ne = suff_d_freq[d] - no;
  ll res = 0;
  for (auto co = std::max(0, d_freq[d] - ne); co <= std::min(d_freq[d], no); ++co) {
    const auto ways = (comb[no][co] * comb[ne][d_freq[d] - co]) % MOD;
    const auto sub_res = Rec(d+1, sum + co * d, no - co, target_sum);
    res = (res + ((ways * sub_res) % MOD)) % MOD;
  }
  return dp[d][sum][no] = res;
}

class Solution {
public:
  int countBalancedPermutations(const std::string& num) {
    if (!init_comb) {
      FOR(i, 0, MAX_NO) {
        comb[i][i] = comb[i][0] = 1;
        FOR(j, 1, i-1) {
          comb[i][j] = (comb[i-1][j] + comb[i-1][j-1]) % MOD;
        }
      }
      init_comb = true;
    }
    
    const auto n = SZ(num);

    std::fill(RNG(d_freq), 0);
    auto d_sum = 0;
    for (const auto c : num) {
      ++d_freq[c - '0'];
      d_sum += (c - '0');
    }
    if (d_sum & 1) return 0;
    // d_sum is even
    const auto target_sum = (d_sum >> 1);
    const auto max_no = (n + 1) / 2;

    FORD(i, 9, 0) suff_d_freq[i] = d_freq[i] + (i < 9 ? suff_d_freq[i+1] : 0);

    std::fill(&dp[0][0][0], &dp[0][0][0] + sizeof(dp) / sizeof(dp[0][0][0]), -1);
    return Rec(0, 0, max_no, target_sum);
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto num = "123"s;
    const auto a_out = Solution().countBalancedPermutations(num);
    assert(a_out == 2);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto num = "112"s;
    const auto a_out = Solution().countBalancedPermutations(num);
    assert(a_out == 1);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto num = "12345"s;
    const auto a_out = Solution().countBalancedPermutations(num);
    assert(a_out == 0);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto num = "1234567890"s;
    const auto a_out = Solution().countBalancedPermutations(num);
    assert(a_out == 0);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto num = std::string(4, '2') + std::string(4, '4') + std::string(4, '1') + std::string(4, '5');
    const auto a_out = Solution().countBalancedPermutations(num);
    assert(a_out == 9025800);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto num = "097215945290203859445732218144293669557017918937"s;
    const auto a_out = Solution().countBalancedPermutations(num);
    assert(a_out == 820460648);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto num = std::string(10, '1') + std::string(10, '4') + std::string(10, '5') + std::string(10, '8')
      + std::string(10, '2') + std::string(10, '3') + std::string(10, '6') + std::string(10, '7');
    const auto a_out = Solution().countBalancedPermutations(num);
    assert(a_out == 53125280);
  
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
