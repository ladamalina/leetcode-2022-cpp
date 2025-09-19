//#pragma GCC optimize("O3")
//#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;

using ll = long long;
using ld = long double;
using ull = unsigned long long;
using ii [[maybe_unused]] = std::pair<int, int>;
using pll [[maybe_unused]] = std::pair<ll, ll>;
using vi [[maybe_unused]] = std::vector<int>;
using vvi [[maybe_unused]] = std::vector<vi>;
using vii [[maybe_unused]] = std::vector<ii>;
using vb [[maybe_unused]] = std::vector<bool>;
using vd [[maybe_unused]] = std::vector<ld>;

#define FOR(_i, _a, _b) for (int _i = (_a); _i <= (_b); ++(_i))
#define FORD(_i, _a, _b) for (int _i = (_a); _i >= (_b); --(_i))
#define RNG(_l) (_l).begin(), (_l).end()
#define SORT(_l) std::sort((_l).begin(), (_l).end())
#define CI(_v) static_cast<int>(_v)
#define CL(_v) static_cast<ll>(_v)
#define CD(_v) static_cast<ld>(_v)
#define F first
#define S second
#define PB push_back

class Solution {
public:
  static int minSwap(const vi& nums1, const vi& nums2) {
    const auto n = CI(nums1.size());
    ii prev{0, 1};
    FOR(i, 1, n-1) {
      ii curr{INT_MAX, INT_MAX};

      // not swap current
      if (nums1[i] > nums1[i-1] && nums2[i] > nums2[i-1])
        curr.F = std::min(curr.F, prev.F);
      if (nums1[i] > nums2[i-1] && nums2[i] > nums1[i-1])
        curr.F = std::min(curr.F, prev.S);

      // swap current
      if (nums1[i] > nums1[i-1] && nums2[i] > nums2[i-1] && prev.S != INT_MAX)
        curr.S = std::min(curr.S, prev.S+1);
      if (nums1[i] > nums2[i-1] && nums2[i] > nums1[i-1] && prev.F != INT_MAX)
        curr.S = std::min(curr.S, prev.F+1);

      prev = curr;
    }
    return std::min(prev.F, prev.S);
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums1{1,3,5,4};
    const vi nums2{1,2,3,7};
    const auto a_out = Solution::minSwap(nums1, nums2);
    assert(a_out == 1);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums1{0,3,5,8,9};
    const vi nums2{2,1,4,6,9};
    const auto a_out = Solution::minSwap(nums1, nums2);
    assert(a_out == 1);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  std::cerr << "TestSolution OK"sv << std::endl;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
#ifndef NDEBUG
  TestSolution();
#endif
  return 0;
}
