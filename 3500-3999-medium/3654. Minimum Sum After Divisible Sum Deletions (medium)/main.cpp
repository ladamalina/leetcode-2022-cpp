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

constexpr int MAX_N = 1e5, MAX_K = 1e5;
std::array<ll, MAX_N> psum, dp;
std::array<int, MAX_N> psum_mod;
std::array<vi, MAX_K> psum_mod_ids;

ll Rec(const int i, const vi& nums) {
  if (i >= SZ(nums)) return 0ll;
  auto& res = dp[i];
  if (res != -1) return res;
  const auto mod = i > 0 ? psum_mod[i-1] : 0;
  const auto it = std::lower_bound(RNG(psum_mod_ids[mod]), i);
  if (it != psum_mod_ids[mod].end()) {
    const auto j = *it;
    res = std::min(Rec(j + 1, nums), nums[i] + Rec(i + 1, nums));
  } else {
    res = nums[i] + Rec(i + 1, nums);
  }
  return res;
}

class Solution {
public:
  ll minArraySum(const vi& nums, const int k) {
    const auto n = SZ(nums);
    std::fill(psum_mod_ids.begin(), psum_mod_ids.begin() + k, vi{});
    FOR(i, 0, n-1) {
      psum[i] = nums[i] + (i > 0 ? psum[i-1] : 0);
      psum_mod[i] = psum[i] % k;
      psum_mod_ids[psum_mod[i]].push_back(i);
    }
    std::fill(dp.begin(), dp.begin() + n, -1);
    const auto res = Rec(0, nums);
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums{30};
    const auto a_out = Solution().minArraySum(nums, 1418);
    assert(a_out == 30);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums{525, 661, 220, 213, 653, 789,  297, 214, 196, 693, 495, 661, 85,  172, 559, 226, 171, 769, 498,
                  906, 49,  361, 435, 754, 1000, 306, 934, 557, 356, 411, 291, 340, 915, 362, 722, 991, 62,  55,
                  943, 65,  126, 734, 289, 676,  45,  743, 941, 731, 484, 159, 147, 69,  40,  986, 343, 350, 444,
                  885, 735, 888, 641, 163, 431,  269, 105, 772, 130, 645, 281, 539, 456, 224, 209, 715, 132, 177,
                  148, 796, 163, 884, 490, 169,  337, 794, 93,  397, 671, 989, 635, 594, 51,  651, 691, 473, 306,
                  117, 512, 213, 163, 689, 392,  446, 954, 714, 674, 248, 275, 125, 72,  403, 927, 584, 343};
    const auto a_out = Solution().minArraySum(nums, 594);
    assert(a_out == 11407);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums{
        304, 744, 143, 845, 973, 75,  806, 885, 927, 246, 45,  21,  913, 807, 80,  300, 372, 678, 51,  928, 369, 398,
        445, 840, 378, 758, 90,  97,  319, 970, 285, 772, 649, 352, 296, 232, 270, 831, 38,  639, 534, 866, 350, 31,
        74,  825, 101, 749, 368, 240, 198, 629, 878, 332, 968, 873, 769, 326, 587, 946, 888, 343, 469, 277, 665, 339,
        150, 362, 163, 717, 869, 457, 921, 409, 298, 666, 91,  240, 117, 766, 505, 822, 930, 2,   410, 178, 207, 695,
        321, 442, 936, 463, 730, 326, 76,  956, 265, 147, 53,  575, 330, 818, 692, 672, 931, 942, 455, 789, 105, 829,
        31,  26,  96,  565, 922, 415, 501, 909, 173, 361, 295, 494, 992, 898, 326, 34,  728, 235, 96,  226, 607, 317,
        645, 697, 461, 571, 164, 639, 131, 863, 895, 907, 726, 248, 497, 739, 106, 234, 898, 177, 951, 607, 193, 144,
        806, 343, 983, 567, 728, 175, 577, 574, 940, 766, 997, 254, 914, 50,  321, 907, 722, 491, 581, 715, 220, 784,
        966, 498, 388, 810, 549, 850, 533, 661, 807, 891, 488, 551, 237, 135, 421, 547, 260, 259, 299, 399, 234, 660,
        894, 273, 499, 918, 888, 173, 148, 29,  84,  163, 252, 761, 243, 275, 87,  556, 434, 236, 407, 832, 132, 434,
        774, 415, 273, 454, 649, 272, 208, 778, 127, 823, 210, 50,  283, 618, 246, 381, 779, 707, 600, 573, 921, 232,
        564, 405, 384, 81,  471, 13,  239, 653, 693, 435, 818, 745, 603, 731, 127, 161, 875, 177, 422, 568, 700, 99,
        573, 617, 421, 993, 864, 535, 349, 23,  760, 469, 208, 744, 709, 814, 13,  353, 681, 610, 135, 195, 649, 322,
        134, 831, 828, 274, 875, 391, 547, 456, 676, 40,  535, 219, 6,   141, 857, 313, 739, 379, 866, 465, 388, 398,
        199, 913, 25,  573, 278, 615, 429, 847, 361, 835, 539, 742, 524, 810, 780, 987, 4,   562};
    const auto a_out = Solution().minArraySum(nums, 96);
    assert(a_out == 1527);
  
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
