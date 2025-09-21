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

class Solution {
public:
  std::string longestSubsequenceRepeatedK(const std::string& s, int k) {
    std::array<int, 26> s_freq{};
    for (const auto c : s) ++s_freq[c - 'a'];

    std::string t;
    FOR(i, 0, 25) {
      const auto lim = s_freq[i] / k;
      if (lim) {
        t += std::string(lim, CC('a' + i));
      }
    }

    std::string res;
    do {
      FORD(tn, SZ(t), std::max(SZ(res), 1)) {
        if (tn > SZ(res) || (tn == SZ(res) && t.substr(0, tn) > res)) {
          auto si = 0, ti = 0, ki = 0;
          while (si < SZ(s) && ki < k) {
            if (s[si] == t[ti]) {
              ti = (ti + 1) % tn;
              if (ti == 0) ++ki;
            }
            ++si;
          }
          if (ki == k) {
            res = t.substr(0, tn);
            // std::cerr << t.substr(0, tn) << '\n';
          }
        }
      }
    } while (std::next_permutation(RNG(t)));

    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::string s = "letsleetcode";
    const auto a_out = Solution().longestSubsequenceRepeatedK(s, 2);
    assert(a_out == "let");
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::string s = "bb";
    const auto a_out = Solution().longestSubsequenceRepeatedK(s, 2);
    assert(a_out == "b");
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::string s = "ab";
    const auto a_out = Solution().longestSubsequenceRepeatedK(s, 2);
    assert(a_out == "");
  
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
