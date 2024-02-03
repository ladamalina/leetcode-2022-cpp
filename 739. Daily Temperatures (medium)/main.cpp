#include <bits/stdc++.h>

using namespace std::literals;

using ll [[maybe_unused]] = long long;
using ii [[maybe_unused]] = std::pair<int, int>;
using vii [[maybe_unused]] = std::vector<ii>;
using vi [[maybe_unused]] = std::vector<int>;
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

constexpr int MAX_N = 1e5;
int gt_r[MAX_N];

template<typename T>
void ClosestGTR(const std::vector<T>& a, const int n) {
  gt_r[n-1] = n;
  FORD(i, n-2, 0) {
    if (a[i] < a[i+1]) gt_r[i] = i+1;
    else {
      int j = gt_r[i+1];
      while (j != n && a[i] >= a[j]) {
        j = gt_r[j];
      }
      gt_r[i] = j;
    }
  }
}

class Solution {
 public:
  static vi dailyTemperatures(const vi& ts) {
    const auto n = CI(ts.size());
    ClosestGTR(ts, n);
    vi res(ts.size());
    FOR(i, 0, CI(ts.size())-1)
      res[i] = (gt_r[i] < n) ? (gt_r[i] - i) : 0;
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi ts{73,74,75,71,69,72,76,73};
    auto a_out = Solution::dailyTemperatures(ts);
    const vi e_out{1,1,4,2,1,1,0,0};
    assert(a_out == e_out);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi ts{30,40,50,60};
    auto a_out = Solution::dailyTemperatures(ts);
    const vi e_out{1,1,1,0};
    assert(a_out == e_out);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi ts{30,60,90};
    auto a_out = Solution::dailyTemperatures(ts);
    const vi e_out{1,1,0};
    assert(a_out == e_out);

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
