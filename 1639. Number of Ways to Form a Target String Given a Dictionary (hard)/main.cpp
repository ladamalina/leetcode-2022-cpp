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

constexpr ll MOD = 1e9 + 7;
using Freq = std::array<int, 26>;

class Solution {
public:
  int numWays(const vs& words, const std::string& target) {
    const auto n_target = SZ(target), /*n_words = SZ(words),*/ n_word = SZ(words[0]);
    if (n_word < n_target)
      return 0;
    std::vector<Freq> chars(n_word, Freq{});
    for (const auto& w : words) {
      FOR(i, 0, n_word-1) ++chars[i][w[i]-'a'];
    }

    vvl dp(n_target, vl(n_word, -1));
    const std::function<ll(int,int)> rec = [&](const int ti, const int ci) {
      if (n_word - ci < n_target - ti)
        return 0ll;
      if (ti == n_target)
        return 1ll;
      if (dp[ti][ci] != -1)
        return dp[ti][ci];
      
      dp[ti][ci] = 0ll;
      const auto tc = target[ti]-'a';
      FOR(cj, ci, n_word-1) {
        const auto freq = chars[cj][tc];
        if (freq > 0) {
          const auto sub_res = (freq * rec(ti+1, cj+1)) % MOD;
          dp[ti][ci] = (dp[ti][ci] + sub_res) % MOD;
        }
      }

      return dp[ti][ci];
    };
    const auto res = rec(0, 0);

    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vs words{"acca","bbbb","caca"};
    const std::string target("aba"s);
    const auto a_out = Solution().numWays(words, target);
    assert(a_out == 6);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vs words{"abba","baab"};
    const std::string target("bab"s);
    const auto a_out = Solution().numWays(words, target);
    assert(a_out == 4);
  
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
