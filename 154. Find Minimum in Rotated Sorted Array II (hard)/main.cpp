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
using vvvi [[maybe_unused]] = std::vector<vvi>;
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
  static int findMin(const vi& nums) {
    std::function<int(int,int)> rec = [&](int l, int r) {
      if (l == r) return nums[l];
      if (nums[l] < nums[r]) return nums[l];
      // nums[l] >= nums[r]
      const auto m = (l+r+1)/2;
      return std::min(rec(l,m-1), rec(m,r));
    };
    return rec(0, CI(nums.size())-1);
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    const vi& nums{1,3,5};
    const auto a_out = Solution::findMin(nums);
    assert(a_out == 1);
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    const vi& nums{2,2,2,0,1};
    const auto a_out = Solution::findMin(nums);
    assert(a_out == 0);
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    const vi& nums{4,5,5,6,1,1,2,2,3,3,4,4};
    const auto a_out = Solution::findMin(nums);
    assert(a_out == 1);
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    const vi& nums{1,1,2,2,3,3,4,4,4,5,5,6};
    const auto a_out = Solution::findMin(nums);
    assert(a_out == 1);
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    const vi& nums{1};
    const auto a_out = Solution::findMin(nums);
    assert(a_out == 1);
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    const vi& nums{2,1};
    const auto a_out = Solution::findMin(nums);
    assert(a_out == 1);
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    const vi& nums{2,1,2,2,2,2,2};
    const auto a_out = Solution::findMin(nums);
    assert(a_out == 1);
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
