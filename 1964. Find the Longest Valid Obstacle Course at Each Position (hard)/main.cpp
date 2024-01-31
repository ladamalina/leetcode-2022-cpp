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

template<typename T>
class FenwickTreeMax {
 public:
  explicit FenwickTreeMax(int n) : n_(n), bit_(n_) {}

  explicit FenwickTreeMax(const std::vector<T>& a) : FenwickTreeMax(a.size()) {
    for (size_t i = 0; i < a.size(); ++i)
      Update(i, a[i]);
  }

  T GetMax(int r) {
    auto res = 0;
    for (; r >= 0; r = (r & (r + 1)) - 1)
      res = std::max(res, bit_[r]);
    return res;
  }

  void Update(int idx, T val) {
    for (; idx < n_; idx = idx | (idx + 1))
      bit_[idx] = std::max(bit_[idx], val);
  }

 private:
  int n_;
  std::vector<T> bit_;
};

class Solution {
 public:
  static vi longestObstacleCourseAtEachPosition(const vi& obstacles) {
    const auto n = CI(obstacles.size());
    const auto max_h = *std::max_element(RNG(obstacles));

    vi res(n);
    FenwickTreeMax<int> tree_l(max_h+1);
    FOR(i, 0, n-1) {
      const auto max_l = tree_l.GetMax(obstacles[i]);
      res[i] = max_l+1;
      tree_l.Update(obstacles[i], max_l+1);
    }
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi obstacles{1,2,3,2};
    auto a_out = Solution::longestObstacleCourseAtEachPosition(obstacles);
    const vi e_out{1,2,3,3};
    assert(a_out == e_out);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi obstacles{2,2,1};
    auto a_out = Solution::longestObstacleCourseAtEachPosition(obstacles);
    const vi e_out{1,2,1};
    assert(a_out == e_out);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi obstacles{3,1,5,6,4,2};
    auto a_out = Solution::longestObstacleCourseAtEachPosition(obstacles);
    const vi e_out{1,1,2,3,2,2};
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
