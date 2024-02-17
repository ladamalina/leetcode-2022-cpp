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
#define CD(_v) static_cast<double>(_v)
#define F first
#define S second

const auto EPS = 1e-5;
template <typename T>
[[maybe_unused]] bool Eq(T a, T b) { return std::abs(a - b) < EPS; }

constexpr int MAX_N = 1e4;
std::array<std::pair<double, int>, MAX_N> wq;

class Solution {
 public:
  static double mincostToHireWorkers(const vi& q, const vi& w, int k) {
    const auto n = CI(q.size());
    FOR(i, 0, n-1) {
      wq[i] = {CD(w[i])/CD(q[i]), i};
    }
    std::sort(wq.begin(), wq.begin()+n);
    int q_sum = 0;
    std::multiset<int> qs;
    double min_amount = DBL_MAX;
    FOR(i, 0, n-1) {
      if (i >= k) {
        const auto max_q = *std::prev(qs.end());
        qs.erase(std::prev(qs.end()));
        q_sum -= max_q;
      }
      const auto j = wq[i].S;
      qs.emplace(q[j]);
      q_sum += q[j];
      if (i >= k-1) {
        const auto amount = q_sum * wq[i].F;
        min_amount = std::min(min_amount, amount);
      }
    }
    return min_amount;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    auto a_out = Solution::mincostToHireWorkers({10,20,5}, {70,50,30}, 2);
    assert(Eq(a_out, 105.));

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    auto a_out = Solution::mincostToHireWorkers({3,1,10,10,1}, {4,8,2,2,7}, 3);
    assert(Eq(a_out, 30.66667));

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
