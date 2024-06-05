// #include <bits/stdc++.h>

#include <algorithm>
#include <cassert>
#include <chrono>
#include <cmath>
#include <deque>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <numeric>
#include <optional>
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
using vii [[maybe_unused]] = std::vector<ii>;
using vb [[maybe_unused]] = std::vector<bool>;
using vd [[maybe_unused]] = std::vector<double>;
using vs [[maybe_unused]] = std::vector<std::string>;
using vs [[maybe_unused]] = std::vector<std::string>;

#define FOR(_i, _a, _b) for (int _i = (_a); _i <= (_b); ++(_i))
#define FORD(_i, _a, _b) for (int _i = (_a); _i >= (_b); --(_i))
#define RNG(_l) (_l).begin(), (_l).end()
#define SORT(_l) std::sort((_l).begin(), (_l).end())
#define CI(_v) static_cast<int>(_v)
#define CL(_v) static_cast<ll>(_v)
#define CD(_v) static_cast<double>(_v)
#define F first
#define S second
#define PB push_back

using Freq = std::array<int, 26>;

class Solution {
public:
  int maxScoreWords(const vs& ws, const std::vector<char>& ls, const vi& sc) {
    const auto wn = CI(ws.size());

    std::vector<Freq> ws_freq(wn, Freq{});
    FOR(i, 0, wn-1) {
      for (const auto ch : ws[i]) ++ws_freq[i][ch-'a'];
    }

    Freq ls_freq{};
    for (const auto l : ls) ++ls_freq[l-'a'];

    auto max_m = (1<<wn)-1;
    int max_score = 0;
    FOR(m, 1, max_m) {
      int score = 0;
      Freq set_freq{};
      FOR(i, 0, wn-1) {
        if (m & (1<<i)) {
          FOR(j, 0, 25) {
            set_freq[j] += ws_freq[i][j];
          }
        }
      }
      FOR(j, 0, 25) {
        if (set_freq[j] <= ls_freq[j]) score += set_freq[j]*sc[j];
        else {
          score = -1;
          break;
        }
      }
      max_score = std::max(max_score, score);
    }
    return max_score;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vs words{"dog","cat","dad","good"};
    const std::vector<char> letters{'a','a','c','d','d','d','g','o','o'};
    const vi score{1,0,9,5,0,0,3,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0};
    const auto a_out = Solution().maxScoreWords(words, letters, score);
    assert(a_out == 23);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vs words{"xxxz","ax","bx","cx"};
    const std::vector<char> letters{'z','a','b','c','x','x','x'};
    const vi score{4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,10};
    const auto a_out = Solution().maxScoreWords(words, letters, score);
    assert(a_out == 27);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vs words{"leetcode"};
    const std::vector<char> letters{'l','e','t','c','o','d'};
    const vi score{0,0,1,1,1,0,0,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,0,0,0,0};
    const auto a_out = Solution().maxScoreWords(words, letters, score);
    assert(a_out == 0);

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
