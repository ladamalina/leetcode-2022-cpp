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

std::multiset<int> b_set;

class Solution {
 public:
  static int furthestBuilding(const vi& heights, int bricks, int ladders) {
    const auto n = CI(heights.size());

    b_set.clear();
    int res = 0;
    FOR(i, 0, n-2) {
      if (heights[i] >= heights[i+1]) {
        ++res;
        continue;
      }
      const auto diff = heights[i+1] - heights[i];
      while (diff > bricks && !b_set.empty() && *b_set.rbegin() >= diff && ladders > 0) {
        const auto max_prev_h = *b_set.rbegin();
        b_set.erase(std::prev(b_set.end()));
        bricks += max_prev_h;
        --ladders;
      }
      if (diff <= bricks) {
        b_set.emplace(diff);
        bricks -= diff;
        ++res;
      } else if (ladders > 0) {
        --ladders;
        ++res;
      } else {
        break;
      }
    }
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi heights{4,2,7,6,9,14,12};
    const auto e_out = Solution::furthestBuilding(heights, 5, 1);
    assert(e_out == 4);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi heights{4,12,2,7,3,18,20,3,19};
    const auto e_out = Solution::furthestBuilding(heights, 10, 2);
    assert(e_out == 7);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi heights{14,3,19,3};
    const auto e_out = Solution::furthestBuilding(heights, 17, 0);
    assert(e_out == 3);

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
