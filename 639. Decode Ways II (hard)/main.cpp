#include <bits/stdc++.h>

using namespace std::literals;

using ll [[maybe_unused]] = long long;
using ii [[maybe_unused]] = std::pair<int, int>;
using vii [[maybe_unused]] = std::vector<ii>;
using vi [[maybe_unused]] = std::vector<int>;
using vl [[maybe_unused]] = std::vector<ll>;
using vvi [[maybe_unused]] = std::vector<vi>;
using vs [[maybe_unused]] = std::vector<std::string>;
using vvs [[maybe_unused]] = std::vector<vs>;
using vc [[maybe_unused]] = std::vector<char>;
using vvc [[maybe_unused]] = std::vector<vc>;

#define FOR(_i, _a, _b) for (int _i = (_a); _i <= (_b); ++(_i))
#define FORD(_i, _a, _b) for (int _i = (_a); _i >= (_b); --(_i))
#define RNG(_l) (_l).begin(), (_l).end()
#define SORT(_l) std::sort((_l).begin(), (_l).end())
#define CI(_v) static_cast<int>(_v)
#define F first
#define S second

constexpr ll MOD = 1e9 + 7;

std::array<ll, 10> dp2, dp3; 

class Solution {
 public:
  static int numDecodings(const std::string& s) {
    const auto n = CI(s.size());

    ll dp1_sum = 1;

    std::fill(RNG(dp2), 0);
    if (s[0] == '*') {
      // 1-digit
      FOR(d, 1, 9) dp2[d] = dp1_sum;
    } else {
      const auto d = s[0]-'0';
      // 1-digit
      if (d >= 1 && d <= 9) dp2[d] = dp1_sum;
    }
    ll dp2_sum = std::accumulate(RNG(dp2), 0ll) % MOD;
    
    FOR(i, 1, n-1) {
      std::fill(RNG(dp3), 0);
      
      if (s[i] == '*') {
        // 1-digit
        FOR(d, 1, 9) dp3[d] = dp2_sum;
        // 2-digit
        if (s[i-1] == '*') { // **
          FOR(d2, 1, 9) {
            FOR(d3, 1, 9) {
              const auto num = d2*10 + d3;
              if (num >= 1 && num <= 26)
                dp3[d3] = (dp3[d3] + dp1_sum) % MOD;
            }
          }
        } else { // d*
          const auto d2 = s[i-1]-'0';
          if (d2 != 0) {
            FOR(d3, 1, 9) {
              const auto num = d2*10 + d3;
              if (num >= 1 && num <= 26)
                dp3[d3] = (dp3[d3] + dp1_sum) % MOD;
            }
          }
        }
      } else {
        const auto d3 = s[i]-'0';
        // 1-digit
        if (d3 >= 1 && d3 <= 9) dp3[d3] = dp2_sum;
        // 2-digit
        if (s[i-1] == '*') { // *d
          FOR(d2, 1, 9) {
            const auto num = d2*10 + d3;
            if (num >= 1 && num <= 26)
              dp3[d3] = (dp3[d3] + dp1_sum) % MOD;
          }
        } else { // dd
          const auto d2 = s[i-1]-'0';
          if (d2 != 0) {
            const auto num = d2*10 + d3;
            if (num >= 1 && num <= 26)
              dp3[d3] = (dp3[d3] + dp1_sum) % MOD;
          }
        }
      }

      dp1_sum = dp2_sum;
      dp2 = dp3;
      dp2_sum = std::accumulate(RNG(dp2), 0ll) % MOD;
    }
    
    return dp2_sum;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    auto a_out = Solution::numDecodings("*0**0");
    assert(a_out == 36);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    auto a_out = Solution::numDecodings("*1*");
    assert(a_out == 180);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    auto a_out = Solution::numDecodings("*");
    assert(a_out == 9);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    auto a_out = Solution::numDecodings("1*");
    assert(a_out == 18);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    auto a_out = Solution::numDecodings("2*");
    assert(a_out == 15);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    auto a_out = Solution::numDecodings("**");
    assert(a_out == 96);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    auto a_out = Solution::numDecodings("***");
    assert(a_out == 999);

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
