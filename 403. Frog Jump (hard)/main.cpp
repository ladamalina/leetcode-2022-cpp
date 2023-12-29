//#pragma GCC optimize("O3")
//#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;

using ll = long long;
using ld = long double;
using ull = unsigned long long;
using ii [[maybe_unused]] = std::pair<int, int>;
using pll [[maybe_unused]] = std::pair<ll, ll>;
using vi [[maybe_unused]] = std::vector<int>;
using vvi [[maybe_unused]] = std::vector<vi>;
using vvvi [[maybe_unused]] = std::vector<vvi>;
using vii [[maybe_unused]] = std::vector<ii>;
using vb [[maybe_unused]] = std::vector<bool>;
using vd [[maybe_unused]] = std::vector<ld>;

#define FOR(_i, _a, _b) for (int _i = (_a); _i <= (_b); ++(_i))
#define FORD(_i, _a, _b) for (int _i = (_a); _i >= (_b); --(_i))
#define RNG(_l) (_l).begin(), (_l).end()
#define SORT(_l) std::sort((_l).begin(), (_l).end())
#define CI(_v) static_cast<int>(_v)
#define CL(_v) static_cast<ll>(_v)
#define CD(_v) static_cast<ld>(_v)
#define F first
#define S second
#define PB push_back

class Solution {
  public:
  static bool canCross(const vi& stones) {
    const auto n = CI(stones.size());
    std::map<int, std::unordered_set<int>> dp;
    FOR(i, 0, n-1) {
      dp[stones[i]] = {};
    }
    dp[stones[0]] = {0};
    const auto last_it = dp.find(stones.back());
    for (const auto& [pos, steps] : dp) {
      for (const auto s : steps) {
        if (s-1 > 0) {
          auto it = dp.find(pos+s-1);
          if (it != dp.end()) {
            it->S.insert(s-1);
          }
        }
        if (s > 0 && dp.contains(pos+s)) {
          auto it = dp.find(pos+s);
          if (it != dp.end()) {
            it->S.insert(s);
          }
        }
        auto it = dp.find(pos+s+1);
        if (it != dp.end()) {
          it->S.insert(s+1);
        }
        if (!last_it->S.empty()) break;
      }
    }
    return !dp[stones.back()].empty();
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    const vi stones{0,1,3,5,6,8,12,17};
    const auto a_out = Solution::canCross(stones);
    assert(a_out);
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    const vi stones{0,1,2,3,4,8,9,11};
    const auto a_out = Solution::canCross(stones);
    assert(!a_out);
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
