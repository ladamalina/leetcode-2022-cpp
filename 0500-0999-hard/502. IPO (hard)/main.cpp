//#pragma GCC optimize("O3")
//#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

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

class Solution {
  public:
  static int findMaximizedCapital(int k, int w, const vi& profits, const vi& capital) {
    const auto n = CI(profits.size());
    vi ids(n);
    std::iota(RNG(ids), 0);
    std::sort(RNG(ids), [&](int l, int r) {
      return capital[l] < capital[r];
    });
    std::priority_queue<int, vi, std::less<>> pq;
    auto i = 0;
    auto res_w = w;
    auto done = 0;
    while (done < k) {
      while (i < n && capital[ids[i]] <= res_w) {
        pq.push(profits[ids[i]]);
        ++i;
      }
      if (!pq.empty()) {
        res_w += pq.top();
        pq.pop();
        ++done;
      } else break;
    }
    return res_w;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::vector<int> profits{1,2,3};
    const std::vector<int> capital{0,1,1};
    const auto e_out = Solution::findMaximizedCapital(2, 0, profits, capital);
    assert(e_out == 4);
    
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::vector<int> profits{1,2,3};
    const std::vector<int> capital{0,1,2};
    const auto e_out = Solution::findMaximizedCapital(3, 0, profits, capital);
    assert(e_out == 6);
    
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
