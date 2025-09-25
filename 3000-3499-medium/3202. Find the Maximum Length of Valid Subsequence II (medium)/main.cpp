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

class Solution {
public:
  int maximumLength(const vi& nums, const int k) {
    const auto n = SZ(nums);
    if (k == 1) return n;
    
    vvi mod_ids(k);
    FOR(i, 0, n-1) mod_ids[nums[i] % k].push_back(i);
    
    auto max_res = 0;
    FOR(mod1, 0, k-1) {
      FOR(mod2, mod1, k-1) {
        if (mod_ids[mod1].empty() || mod_ids[mod2].empty())
          continue;
        auto m = mod_ids[mod1][0] < mod_ids[mod2][0] ? mod1 : mod2;
        const auto n1 = SZ(mod_ids[mod1]), n2 = SZ(mod_ids[mod2]);
        auto res = 0, pos = -1, i1 = 0, i2 = 0;
        while (i1 < n1 || i2 < n2) {
          if (m == mod1) {
            while (i1 < n1 && mod_ids[mod1][i1] <= pos) ++i1;
            if (i1 == n1) break;
            pos = mod_ids[mod1][i1];
            ++res;
            ++i1;
            m = mod2;
          } else { // m == mod2
            while (i2 < n2 && mod_ids[mod2][i2] <= pos) ++i2;
            if (i2 == n2) break;
            pos = mod_ids[mod2][i2];
            ++res;
            ++i2;
            m = mod1;
          }
        }
        max_res = std::max(res, max_res);
      }
    }
    return max_res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi nums{1,2,3,4,5};
    const auto a_out = Solution().maximumLength(nums, 2);
    assert(a_out == 5);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi nums{1,4,2,3,1,4};
    const auto a_out = Solution().maximumLength(nums, 3);
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
