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

class Solution {
public:
  vvi fourSum(vi& nums, int target) {
    const auto n = CI(nums.size());
    SORT(nums);
    vvi res;
    FOR(i, 0, n-4) {
      FOR(j, i+1, n-3) {
        const auto tar2 = CL(target) - (CL(nums[i]) + CL(nums[j]));
        auto l = j + 1, r = n - 1;
        while (l < r) {
          if (nums[l] + nums[r] < tar2) {
            ++l;
          } else if (nums[l] + nums[r] > tar2) {
            --r;
          } else {
            res.push_back({nums[i], nums[j], nums[l], nums[r]});
            auto l0 = l, r0 = r;
            while (l < r && nums[l] == nums[l0]) ++l;
            while (l < r && nums[r] == nums[r0]) --r;
          }
        }
        while (j + 1 < n && nums[j] == nums[j + 1]) ++j;
      }
      while (i + 1 < n && nums[i] == nums[i + 1]) ++i;
    }

    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi nums{1, 0, -1, 0, -2, 2};
    const auto a_out = Solution().fourSum(nums, 0);
    // const vvi e_out{{-2, -1, 1, 2}, {-2, 0, 0, 2}, {-1, 0, 0, 1}};
    // assert(a_out == e_out);
    assert(a_out.size() == 3);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi nums{2, 2, 2, 2, 2};
    const auto a_out = Solution().fourSum(nums, 8);
    // const vvi e_out{{2, 2, 2, 2}};
    // assert(a_out == e_out);
    assert(a_out.size() == 1);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi nums{10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 20, 20, 20, 20, 20,
            20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30,
            30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40,
            40, 40, 40, 40, 40, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50,
            60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 70, 70, 70, 70, 70,
            70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80,
            80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90,
            90, 90, 90, 90, 90};
    const auto a_out = Solution().fourSum(nums, 200);
    // const vvi e_out{{2,2,2,2}};
    assert(!a_out.empty());

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi nums{-493, -487, -480, -464, -456, -449, -445, -439, -437, -427, -415, -403, -400, -398, -372, -349, -347,
            -332, -330, -324, -287, -282, -273, -254, -249, -243, -220, -219, -217, -217, -214, -199, -198, -170,
            -153, -150, -143, -136, -113, -93, -91, -88, -87, -78, -58, -58, -55, -51, -49, -42, -38, -36, -26, 0,
            13, 28, 54, 61, 85, 90, 90, 111, 118, 136, 138, 167, 170, 172, 195, 198, 205, 209, 241, 263, 290, 302,
            324, 328, 347, 359, 373, 390, 406, 417, 435, 439, 443, 446, 464, 465, 468, 484, 486, 492, 493};
    const auto a_out = Solution().fourSum(nums, -4437);
    // const vvi e_out{{2,2,2,2}};
    assert(a_out.empty());

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi nums{-491, -468, -450, -415, -414, -374, -357, -333, -305, -292, -274, -272, -271, -258, -241, -240, -227,
            -217, -196, -184, -161, -120, -116, -110, -110, -98, -92, -47, -27, -10, -8, -7, -4, -1, 19, 30, 53,
            62, 64, 65, 137, 138, 145, 160, 178, 179, 209, 221, 243, 270, 279, 283, 290, 291, 305, 308, 322, 345,
            354, 357, 365, 366, 368, 371, 376, 381, 381, 394, 400, 406, 429, 433, 445, 446, 449, 470, 471, 472};
    const auto a_out = Solution().fourSum(nums, 2873);
    // const vvi e_out{{2,2,2,2}};
    assert(a_out.empty());

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi nums{91277418, 66271374, 38763793, 4092006, 11415077, 60468277, 1122637, 72398035, -62267800, 22082642,
            60359529, -16540633, 92671879, -64462734, -55855043, -40899846, 88007957, -57387813, -49552230,
            -96789394, 18318594, -3246760, -44346548, -21370279, 42493875, 25185969, 83216261, -70078020,
            -53687927, -76072023, -65863359, -61708176, -29175835, 85675811, -80575807, -92211746, 44755622,
            -23368379, 23619674, -749263, -40707953, -68966953, 72694581, -52328726, -78618474, 40958224,
            -2921736, -55902268, -74278762, 63342010, 29076029, 58781716, 56045007, -67966567, -79405127,
            -45778231, -47167435, 1586413, -58822903, -51277270, 87348634, -86955956, -47418266, 74884315,
            -36952674, -29067969, -98812826, -44893101, -22516153, -34522513, 34091871, -79583480, 47562301,
            6154068, 87601405, -48859327, -2183204, 17736781, 31189878, -23814871, -35880166, 39204002, 93248899,
            -42067196, -49473145, -75235452, -61923200, 64824322, -88505198, 20903451, -80926102, 56089387,
            -58094433, 37743524, -71480010, -14975982, 19473982, 47085913, -90793462, -33520678, 70775566,
            -76347995, -16091435, 94700640, 17183454, 85735982, 90399615, -86251609, -68167910, -95327478,
            90586275, -99524469, 16999817, 27815883, -88279865, 53092631, 75125438, 44270568, -23129316, -846252,
            -59608044, 90938699, 80923976, 3534451, 6218186, 41256179, -9165388, -11897463, 92423776, -38991231,
            -6082654, 92275443, 74040861, 77457712, -80549965, -42515693, 69918944, -95198414, 15677446,
            -52451179, -50111167, -23732840, 39520751, -90474508, -27860023, 65164540, 26582346, -20183515,
            99018741, -2826130, -28461563, -24759460, -83828963, -1739800, 71207113, 26434787, 52931083,
            -33111208, 38314304, -29429107, -5567826, -5149750, 9582750, 85289753, 75490866, -93202942, -85974081,
            7365682, -42953023, 21825824, 68329208, -87994788, 3460985, 18744871, -49724457, -12982362, -47800372,
            39958829, -95981751, -71017359, -18397211, 27941418, -34699076, 74174334, 96928957, 44328607,
            49293516, -39034828, 5945763, -47046163, 10986423, 63478877, 30677010, -21202664, -86235407, 3164123,
            8956697, -9003909, -18929014, -73824245};
    const auto a_out = Solution().fourSum(nums, -236727523);
    // const vvi e_out{{2,2,2,2}};
    assert(a_out.size() == 2);

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