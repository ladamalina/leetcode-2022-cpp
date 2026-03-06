// #pragma GCC optimize("O3,unroll-loops")
// #include <bits/stdc++.h>

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <cfloat>
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
#include <numbers>
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

constexpr int MAX_N = 1000;
constexpr int MIN = -1e9;
std::array<int, MAX_N> tmp;
std::array<std::array<ll, MAX_N + 1>, MAX_N + 1> dp;

void Partition(vi& nums, const int beg) {
  const auto n = SZ(nums);
  auto i = beg % n, ti = 0;
  while (ti < n) {
    tmp[ti++] = nums[i];
    i = (i + 1) % n;
  }
  std::copy(tmp.begin(), tmp.begin() + n, nums.begin());
}

ll SolveCase(const vi& nums, const int k) {
  const auto n = SZ(nums);
  FOR(i, 0, k) std::fill(dp[i].begin(), dp[i].begin() + n + 1, MIN);

  auto mn = INT_MAX, mx = INT_MIN;
  FOR(j, 0, n - 1) {
    mn = std::min(mn, nums[j]);
    mx = std::max(mx, nums[j]);
    dp[1][j+1] = mx - mn;
  }

  auto res = dp[1][n];
  FOR(i, 2, k) {
    auto x = LLONG_MIN, y = LLONG_MIN;
    FOR(j, i - 1, n - 1) {
      x = std::max(x, dp[i-1][j] - nums[j]);
      y = std::max(y, dp[i-1][j] + nums[j]);
      dp[i][j+1] = std::max({dp[i][j], x + nums[j], y - nums[j]});
    }
    res = std::max(res, dp[i][n]);
  }
  return res;
}

class Solution {
public:
  static ll maximumScore(vi& nums, const int k) {
    const auto n = SZ(nums);
    auto max_x = -1, max_i = -1;
    FOR(i, 0, n - 1) {
      if (nums[i] > max_x) {
        max_x = nums[i];
        max_i = i;
      }
    }
    Partition(nums, max_i); // partition (i-1, i)
    const auto p1_res = SolveCase(nums, k);
    
    Partition(nums, 1); // partition (i, i+1)
    const auto p2_res = SolveCase(nums, k);

    return std::max(p1_res, p2_res);
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi nums{1,2,3,3};
    const auto a_out = Solution::maximumScore(nums, 2);
    assert(a_out == 3);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi nums{1,2,3,3};
    const auto a_out = Solution::maximumScore(nums, 1);
    assert(a_out == 2);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi nums{1,2,3,3};
    const auto a_out = Solution::maximumScore(nums, 4);
    assert(a_out == 3);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi nums{314,482,772,449,506,885,631,198,320,573,534,580,557,658,656,165,640,216,184,286,128,448,362,595,910,484,448,778,602,999,782,689,589,567,108,417,288,631,182,404,63,736,17,270,521,342,182,675,318,594,908,657,465,903,622,883,764,845,959,353,342,569,546,425,893,636,867,411,86,790,183,723,160,727,255,950,116,747,571,538,693,319,255,67,486,508,12,737,301,167,19,507,546,932,964,954,109,154,411,306,617,233,718,491,379,580,412,318,521,42,44,11,371,123,191,746,686,961,680,277,789,6,920,818,270,34,432,1000,426,4,65,894,435,541,281,203,680,252,315,971,880,115,76,377,413,542,53,356,237,293,681,391,7,476,600,326,747,131,100,731,27,900,385,940,540,679,129,642,735,736,297,4,378,311,611,651,617,808,468,190,924,126,282,619,713,537,147,551,838,493,305,856,25,115,575,243,441,605,648,846,420,587,56,395,651,357,65,361,570,218,563,960,541,795,736,908,902,361,160,414,489,217,805,23,851,480,874,651,267,974,485,999,868,252,310,789,290,177,56,164,174,583,166,898,823,346,928,611,890,712,235,319,924,48,461,594,146,646,352,588,49,737,553,524,740,153,434,570,998,207,465,706,900,626,934,421,195,901,377,322,625,299,603,403,927,980,561,894,614,241,787,434,325,59,955,143,179,786,97,415,990,487,243,829,14,722,625,425,740,735,770,995,802,805,76,625,497,314,185,884,708,666,81,478,353,422,677,365,649,351,106,641,30,539,542,519,459,457,837,46,94,12,139,986,848,804,690,863,607,71,387,273,809,289,149,288,512,504,873,994,454,385,828,367,583,350,363,527,162,403,78,678,519,481,780,786,886,325,492,67,659,71,243,643,72,950,365,770,938,287,898,176,577,202,667,735,895,693,704,420,79,666,977,874,622,958,389,547,15,199,333,169,715,971,63,956,751,781,96,708,406,654,532,811,45,370,81,603,876,875,986,616,164,86,839,294,623,575,953,449,996,14,540,619,918,110,171,884,664,953,1,218,307,99,686,335,173,910,359,248,44,584,766,956,412,675,890,753,706,388,102,117,385,922,594,544,845,532,111,63,541,620,544,470,707,787,83,365,236,447,753,625,739,278,526,624,48,917,19,139,389,635,221,865,700,454,923,153,642,901,642,590,331,295,312,710,889,47,17,80,236,601,528,103,440,64,344,111,348,285,341,479,696,23,571,262,749,606,342,515,336,349,89,633,906,136,939,155,705,287,322,974,136,431,927,324,105,761,472,863,386,157,777,932,883,835,542,380,520,202,739,506,401,858,999,214,702,174,337,816,801,617,754,746,565,506,591,318,92,987,192,245,948,683,944,328,230,14,244,535,113,732,739,843,586,527,103,11,754,335,482,593,20,602,976,948,145,982,928,731,821,171,509,760,666,128,600,343,547,76,285,832,237,528,59,735,38,759,181,66,210,855,504,164,163,645,103,129,576,610,112,897,984,26,796,603,289,785,627,306,224,832,625,206,634,127,130,325,94,719,627,122,887,912,420,70,164,794,774,707,169,527,608,782,981,561,75,711,253,154,187,302,820,556,358,648,623,603,204,749,966,711,31,328,730,967,448,973,285,304,509,471,464,397,70,86,144,563,798,834,118,241,56,544,713,616,908,116,94,429,377,107,890,361,489,624,392,673,485,214,714,544,923,38,735,748,873,403,464,846,217,310,506,669,828,514,476,378,36,400,228,20,815,287,747,524,173,633,388,434,365,989,293,964,108,303,285,228,422,376,911,361,778,476,481,254,512,177,435,300,78,469,339,156,910,705,552,779,114,284,871,157,797,589,807,285,168,349,254,462,950,462,760,855,261,107,302,344,31,9,605,31,988,756,486,346,55,650,411,948,15,48,55,76,96,738,294,351,52,837,326,705,877,899,962,546,56,758,733,321,246,716,399,941,947,160,370,529,565,804,708,748,798,738,545,859,55,792,276,717,685,67,363,454,540,73,724,612,468,912,241,349,755,251,431,945,758,810,410,884,285,128,866,335,830,608,468,865,381,648,462,573,610,657,243,928,640,32,448,269,468,371,411,261,248,492,9,275,322,231,982,188,663,325,158,992,670,878,430,321,194,67,454,510,884,738,986,423,490,52,719};
    const auto a_out = Solution::maximumScore(nums, 838);
    assert(a_out == 190798);
  
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
