#include <bits/stdc++.h>

using namespace std::literals;

using ll [[maybe_unused]] = long long;
using ii [[maybe_unused]] = std::pair<int, int>;
using vii [[maybe_unused]] = std::vector<ii>;
using vi [[maybe_unused]] = std::vector<int>;
using vl [[maybe_unused]] = std::vector<ll>;
using vvi [[maybe_unused]] = std::vector<vi>;
using vs [[maybe_unused]] = std::vector<std::string>;
using vvs [[maybe_unused]] = std::vector<vs>;
using vc [[maybe_unused]] = std::vector<char>;
using vvc [[maybe_unused]] = std::vector<vc>;

#define FOR(_i, _a, _b) for (int _i = (_a); _i <= (_b); ++(_i))
#define FORD(_i, _a, _b) for (int _i = (_a); _i >= (_b); --(_i))
#define RNG(_l) (_l).begin(), (_l).end()
#define SORT(_l) std::sort((_l).begin(), (_l).end())
#define CI(_v) static_cast<int>(_v)
#define F first
#define S second

constexpr int MAX_T = 1e4;
std::array<int, MAX_T+1> dp;

class Solution {
 public:
  static int scheduleCourse(vvi& courses) {
    const auto n = CI(courses.size());

    std::sort(RNG(courses), [](const vi& lhs, const vi& rhs)
      { return std::tie(lhs[1], lhs[0]) < std::tie(rhs[1], rhs[0]); });
    const auto max_deadline = courses.back()[1];
    
    std::fill(dp.begin(), dp.begin()+max_deadline+1, -1);
    dp[0] = 0;
    
    FOR(i, 0, n-1) {
      const auto duration = courses[i][0];
      const auto deadline = courses[i][1];
      FORD(j, deadline, duration) {
        if (dp[j-duration] != -1) {
          dp[j] = std::max(dp[j], dp[j-duration]+1);
        }
      }
    }
    const auto res = *std::max_element(dp.begin(), dp.begin()+max_deadline+1);
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vvi courses{{100,200},{200,1300},{1000,1250},{2000,3200}};
    const auto a_out = Solution::scheduleCourse(courses);
    assert(a_out == 3);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vvi courses{{1,2}};
    const auto a_out = Solution::scheduleCourse(courses);
    assert(a_out == 1);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vvi courses{{3,2},{4,3}};
    const auto a_out = Solution::scheduleCourse(courses);
    assert(a_out == 0);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vvi courses{{2,5},{2,19},{1,8},{1,3}};
    const auto a_out = Solution::scheduleCourse(courses);
    assert(a_out == 4);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vvi courses{{534,5126},{462,808},{724,4547},{291,7857},{195,4299},{926,4128},{105,7531},{288,2356},{329,1514},
                {642,1781},{107,9440},{237,1504},{100,7483},{448,3333},{720,3681},{48,7454},{398,4080},{460,3358},
                {690,8454}};
    const auto a_out = Solution::scheduleCourse(courses);
    assert(a_out == 17);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vvi courses{{7,17},{3,12},{10,20},{9,10},{5,20},{10,19},{4,18}};
    const auto a_out = Solution::scheduleCourse(courses);
    assert(a_out == 4);

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
