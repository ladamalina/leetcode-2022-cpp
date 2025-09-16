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
  static bool containsNearbyAlmostDuplicate(const vi& nums, const int i_diff, const int v_diff) {
    const auto n = CI(nums.size());
    std::multiset<int> win;
    FOR(i, 0, n-1) {
      // move left bound
      const auto l = i - i_diff - 1;
      if (l >= 0) win.erase(win.find(nums[l]));
    
      const auto lb_it = win.lower_bound(nums[i]);
      if (lb_it != win.end() && *lb_it - nums[i] <= v_diff) {
        return true;
      }
      if (lb_it != win.begin() && nums[i] - *std::prev(lb_it) <= v_diff) {
        return true;
      }
    
      // move right bound
      win.insert(nums[i]);
    }
    return false;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    const vi nums{1,2,3,1};
    const auto a_out = Solution::containsNearbyAlmostDuplicate(nums, 3, 0);
    assert(a_out);
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    const vi nums{1,5,9,1,5,9};
    const auto a_out = Solution::containsNearbyAlmostDuplicate(nums, 2, 3);
    assert(!a_out);
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    const vi nums{-3,3};
    const auto a_out = Solution::containsNearbyAlmostDuplicate(nums, 2, 4);
    assert(!a_out);
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    const vi nums{10,100,200,9,0,11};
    const auto a_out = Solution::containsNearbyAlmostDuplicate(nums, 2, 2);
    assert(a_out);
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    const vi nums{0,10,22,15,0,5,22,12,1,5};
    const auto a_out = Solution::containsNearbyAlmostDuplicate(nums, 3, 3);
    assert(!a_out);
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
