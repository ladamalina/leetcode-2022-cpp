#include <bits/stdc++.h>

using namespace std::literals;

using ll [[maybe_unused]] = long long;
using ii [[maybe_unused]] = std::pair<int, int>;
using vii [[maybe_unused]] = std::vector<ii>;
using vi [[maybe_unused]] = std::vector<int>;
using vl [[maybe_unused]] = std::vector<ll>;
using vvi [[maybe_unused]] = std::vector<vi>;
using vvii [[maybe_unused]] = std::vector<vii>;
using vs [[maybe_unused]] = std::vector<std::string>;
using vvs [[maybe_unused]] = std::vector<vs>;
using vc [[maybe_unused]] = std::vector<char>;
using vvc [[maybe_unused]] = std::vector<vc>;

#define FOR(_i, _a, _b) for (int _i = (_a); _i <= (_b); ++(_i))
#define FORD(_i, _a, _b) for (int _i = (_a); _i >= (_b); --(_i))
#define RNG(_l) (_l).begin(), (_l).end()
#define SORT(_l) std::sort((_l).begin(), (_l).end())
#define CI(_v) static_cast<int>(_v)
#define CL(_v) static_cast<ll>(_v)
#define F first
#define S second

int Check(int target, const vi& nums, int n, int k) {
  [[maybe_unused]] int lt = 0, eq = 0;
  FOR(i, 0, n-2) {
    const auto l_id = CI(std::upper_bound(nums.begin()+i+1, nums.end(), nums[i]+target) - nums.begin());
    const auto u_id = CI(std::upper_bound(nums.begin()+i+1, nums.end(), nums[i]+target) - nums.begin());
    lt += l_id - (i+1);
    eq += u_id - l_id;
  }
  if (lt >= k)
    return -1;
  else if (lt+eq < k)
    return 1;
  else
    return 0;
}

class Solution {
 public:
  static int smallestDistancePair(vi& nums, int k) {
    const auto n = CI(nums.size());
    SORT(nums);
    int l = INT_MAX;
    FOR(i, 1, n-1) {
      l = std::min(l, nums[i]-nums[i-1]);
    }
    int r = nums.back() - nums.front();
    while (l < r) {
      const auto m = (l + r) / 2;
      const auto check = Check(m, nums, n, k);
      if (check > 0)
        l = m+1;
      else if (check < 0)
        r = m;
      else
        return m;
    }
    return r;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi nums{1,3,1};
    const auto e_out = Solution::smallestDistancePair(nums, 1);
    assert(e_out == 0);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi nums{1,1,1};
    const auto e_out = Solution::smallestDistancePair(nums, 2);
    assert(e_out == 0);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi nums{1,6,1};
    const auto e_out = Solution::smallestDistancePair(nums, 3);
    assert(e_out == 5);

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
