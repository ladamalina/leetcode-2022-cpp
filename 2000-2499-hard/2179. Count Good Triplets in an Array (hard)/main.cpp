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
using vvvi [[maybe_unused]] = std::vector<vvi>;
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

class Solution {
public:
  ll goodTriplets(const vi& nums1, const vi& nums2) {
    const auto n = SZ(nums1);
    vi x_pos1(n), x_pos2(n);
    FOR(i, 0, n-1) x_pos1[nums1[i]] = i;
    FOR(i, 0, n-1) x_pos2[nums2[i]] = i;

    vii pairs(n);
    FOR(x, 0, n-1) pairs[x] = {x_pos1[x], x_pos2[x]};

    const auto n_sqrt = std::max(1, CI(std::sqrt(n)));
    std::sort(RNG(pairs), [&](const ii& a, const ii& b) {
      const auto ca = a.F / n_sqrt, cb = b.F / n_sqrt;
      const auto fa = (ca & 1) ? -1 : 1, fb = (cb & 1) ? -1 : 1;
      return std::make_pair(ca, fa*a.S) < std::make_pair(cb, fb*b.S);
    });

    vi freq_l(n), freq_r(n);
    std::fill(RNG(freq_r), 2);
    int cnt_l = 0, cnt_r = n;
    const auto move_right = [&](int& i, const vi& arr) {
      if (i >= 0) {
        ++freq_l[arr[i]];
        if (freq_l[arr[i]] == 2) ++cnt_l;
      }
      ++i;
      if (freq_r[arr[i]] == 2) --cnt_r;
      --freq_r[arr[i]];
    };
    const auto move_left = [&](int& i, const vi& arr) {
      ++freq_r[arr[i]];
      if (freq_r[arr[i]] == 2) ++cnt_r;
      --i;
      if (freq_l[arr[i]] == 2) --cnt_l;
      --freq_l[arr[i]];
    };

    ll res = 0;
    int i1 = -1, i2 = -1;
    FOR(pi, 0, n-1) {
      while (i1 < pairs[pi].F) move_right(i1, nums1);
      while (i1 > pairs[pi].F) move_left(i1, nums1);
      while (i2 < pairs[pi].S) move_right(i2, nums2);
      while (i2 > pairs[pi].S) move_left(i2, nums2);

      const auto y_res = CL(cnt_l) * CL(cnt_r);
      res += y_res;
    }
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums1{2,0,1,3};
    const vi nums2{0,1,2,3};
    const auto a_out = Solution().goodTriplets(nums1, nums2);
    assert(a_out == 1);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums1{4,0,1,3,2};
    const vi nums2{4,1,0,2,3};
    const auto a_out = Solution().goodTriplets(nums1, nums2);
    assert(a_out == 4);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums1{13,14,10,2,12,3,9,11,15,8,4,7,0,6,5,1};
    const vi nums2{8,7,9,5,6,14,15,10,2,11,4,13,3,12,1,0};
    const auto a_out = Solution().goodTriplets(nums1, nums2);
    assert(a_out == 77);

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
