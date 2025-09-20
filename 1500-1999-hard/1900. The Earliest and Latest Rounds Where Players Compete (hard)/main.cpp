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

constexpr int MAX_N = 28;
vvi len_masks(MAX_N + 1);
bool init_masks = false;
void InitMasks() {
  if (init_masks) return;

  FOR(len, 3, MAX_N) {
    const auto h = (len >> 1);
    FOR(lm, 0, (1 << h) - 1) {
      auto rm = 0;
      FOR(lb, 0, h-1) {
        const auto rb = h - lb - 1;
        if ((lm & (1 << lb)) == 0) rm |= (1 << rb);
      }
      if (len & 1) {
        const auto mask = (lm << (h + 1)) | (1 << h) | rm;
        len_masks[len].PB(mask);
      } else {
        const auto mask = (lm << h) | rm;
        len_masks[len].PB(mask);
      }
    }
  }
  
  init_masks = true;
}

class Solution {
public:
  vi earliestAndLatest(const int n, const int p1, const int p2) {
    InitMasks();

    vi r_cnt{n};
    while (r_cnt.back() > 1)
      r_cnt.PB((r_cnt.back() + 1) / 2);
    const auto r_max = SZ(r_cnt);

    vvvi dp_min(r_max, vvi(n+1, vi(n+1, INT_MAX)));
    vvvi dp_max(r_max, vvi(n+1, vi(n+1, -1)));
    const std::function<void(int,int,int)> rec = [&](int r, int b1, int b2) {
      if (b1 == r_cnt[r] - b2 - 1) {
        dp_min[r][b1][b2] = std::min(dp_min[r][b1][b2], r);
        dp_max[r][b1][b2] = std::max(dp_max[r][b1][b2], r);
        return;
      }
      if (dp_max[r][b1][b2] != -1)
        return;
      for (const auto mask : len_masks[r_cnt[r]]) {
        if ((mask & (1 << b1)) && (mask & (1 << b2))) {
          auto gte_b1 = 0, gte_b2 = 0;
          FOR(b, std::min(b1, b2), r_cnt[r]-1) {
            if (mask & (1 << b)) {
              gte_b1 += (b >= b1);
              gte_b2 += (b >= b2);
            }
          }
          const auto nb1 = r_cnt[r+1] - gte_b1, nb2 = r_cnt[r+1] - gte_b2;
          rec(r+1, nb1, nb2);
          dp_min[r][b1][b2] = std::min(dp_min[r][b1][b2], dp_min[r+1][nb1][nb2]);
          dp_max[r][b1][b2] = std::max(dp_max[r][b1][b2], dp_max[r+1][nb1][nb2]);
        }
      }
    };
    rec(0, n-p1, n-p2);

    return vi{dp_min[0][n-p1][n-p2] + 1, dp_max[0][n-p1][n-p2] + 1};
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().earliestAndLatest(5, 1, 5);
    const vi e_out{1,1};
    assert(a_out == e_out);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().earliestAndLatest(11, 2, 4);
    const vi e_out{3,4};
    assert(a_out == e_out);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().earliestAndLatest(16, 2, 4);
    const vi e_out{3,4};
    assert(a_out == e_out);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().earliestAndLatest(28, 2, 4);
    const vi e_out{4,5};
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
