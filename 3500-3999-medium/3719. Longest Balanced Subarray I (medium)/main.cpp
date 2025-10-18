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
using ii = std::pair<int, int>;
using vi = std::vector<int>;
using vvi = std::vector<vi>;
using vvvi = std::vector<vvi>;
using vl = std::vector<ll>;
using vvl = std::vector<vl>;
using vvvl = std::vector<vvl>;
using vii = std::vector<ii>;
using vb = std::vector<bool>;
using vd = std::vector<ld>;
using vs = std::vector<std::string>;
using vc = std::vector<char>;

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

constexpr int MAX_X = 1e5;
std::array<int, MAX_X + 1> freq;
struct Count {
  int n_even = 0, n_odds = 0;
  Count() {
    std::fill(freq.begin(), freq.end(), 0);
  }
  void Inc(const int x) {
    ++freq[x];
    if (freq[x] > 1) return;
    if (x & 1) ++n_odds;
    else ++n_even;
  }
  void Dec(const int x) {
    --freq[x];
    if (freq[x]) return;
    if (x & 1) --n_odds;
    else --n_even;
  }
};

class Solution {
public:
  int longestBalanced(const vi& nums) {
    const auto n = SZ(nums);
    auto max_res = 0;
    Count count;
    FOR(i, 0, n-1) {
      if (i & 1) {
        FORD(j, n-1, i+1) {
          if (count.n_even == count.n_odds) max_res = std::max(max_res, j-i+1);
          count.Dec(nums[j]);
        }
      } else {
        FOR(j, i, n-1) {
          count.Inc(nums[j]);
          if (count.n_even == count.n_odds) max_res = std::max(max_res, j-i+1);
        }
      }
      count.Dec(nums[i]);
    }
    return max_res;
  }
};

[[maybe_unused]] void TestSolution() {
  /*{
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().solve();
    assert(a_out == 6);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }*/
  std::cerr << "TestSolution OK"sv << std::endl;
}

int main() {
#ifndef NDEBUG
  TestSolution();
#endif
  return 0;
}
