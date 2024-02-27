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

class Solution {
 public:
  static int intersectionSizeTwo(vvi& lrs) {
    const auto n = CI(lrs.size());
    std::sort(RNG(lrs), [](const vi& lhs, const vi& rhs) {
      return std::tie(lhs[1], lhs[0]) < std::tie(rhs[1], rhs[0]);
    });
    
    vi res{lrs[0][1]-1, lrs[0][1]};
    FOR(i, 1, n-1) {
      const auto beg = lrs[i][0];
      const auto end = lrs[i][1];
      
      if (beg > res.back()) {
        res.push_back(end-1);
        res.push_back(end);
      } else if (beg == res.back()) {
        res.push_back(end);
      } else if (beg > res[res.size()-2]) {
        res.push_back(end);
      }
    }
    
    return res.size();
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vvi intervals{{1,3},{3,7},{8,9}};
    const auto e_out = Solution::intersectionSizeTwo(intervals);
    assert(e_out == 5);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vvi intervals{{1,3},{1,4},{2,5},{3,5}};
    const auto e_out = Solution::intersectionSizeTwo(intervals);
    assert(e_out == 3);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vvi intervals{{1,2},{2,3},{2,4},{4,5}};
    const auto e_out = Solution::intersectionSizeTwo(intervals);
    assert(e_out == 5);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vvi intervals{{2,10},{3,7},{3,15},{4,11},{6,12},{6,16},{7,8},{7,11},{7,15},{11,12}};
    const auto e_out = Solution::intersectionSizeTwo(intervals);
    assert(e_out == 5);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vvi intervals{{53,64},{91,99},{34,92},{6,89},{6,84},{17,49},{25,38},{67,87},{81,88},{2,43},{26,58},{46,52},{22,39},{69,97},{29,49},{27,95},{18,82},{40,58},{37,59},{16,72}};
    const auto e_out = Solution::intersectionSizeTwo(intervals);
    assert(e_out == 10);

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
