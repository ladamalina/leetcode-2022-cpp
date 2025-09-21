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

constexpr int MAX_B = 29;

class Solution {
public:
  vi smallestSubarrays(const vi& nums) {
    const auto n = SZ(nums);
    vvi bit_psum(MAX_B + 1, vi(n));
    FOR(b, 0, MAX_B) {
      auto& psum = bit_psum[b];
      FOR(i, 0, n-1) psum[i] = ((nums[i] & (1 << b)) ? 1 : 0) + (i > 0 ? psum[i-1] : 0);
    }
    
    vi res(n);
    FOR(i, 0, n-1) {
      auto max_j = i;
      FOR(b, 0, MAX_B) {
        // std::cerr << "i="<<i<<"\tb=" << b << '\n';
        if (nums[i] & (1 << b)) continue;
        const auto& psum = bit_psum[b];
        const auto base = i > 0 ? psum[i-1] : 0;
        const auto esum = psum[n-1] - base;
        if (esum == 0) continue;
        auto lo = i, hi = n - 1;
        while (lo < hi) {
          const auto mi = (lo + hi) >> 1;
          const auto msum = psum[mi] - base;
          const auto check = msum > 0;
          // std::cerr << "lo="<<lo<<"\tmi="<<mi<<"\thi="<<hi<<"\tcheck="<<check<<'\n';
          if (check) hi = mi;
          else lo = mi + 1;
        }
        max_j = std::max(max_j, hi);
      }
      res[i] = max_j - i + 1;
    }
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums{1,0,2,1,3};
    const auto a_out = Solution().smallestSubarrays(nums);
    const vi e_out{3,3,2,2,1};
    assert(a_out == e_out);
  
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
