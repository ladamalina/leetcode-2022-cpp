// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;

using ii = std::pair<int, int>;
using vi = std::vector<int>;
using vvi = std::vector<vi>;

class SummaryRanges {
  public:
  SummaryRanges() = default;
    
  void addNum(int value) {
    auto [it, _] = s.emplace(value, value);
    if (it != s.begin()) {
      const auto prev_it = std::prev(it);
      if (prev_it->first <= value && value <= prev_it->second) {
        s.erase(it);
        return;
      }
      if (prev_it->second + 1 == value) {
        s.erase(it);
        auto [upd_it, _] = s.emplace(prev_it->first, value);
        s.erase(prev_it);
        it = upd_it;
      }
    }
    if (std::next(it) != s.end()) {
      const auto next_it = std::next(it);
      if (it->second == next_it->first) {
        s.erase(it);
      } else if (it->second+1 == next_it->first) {
        s.emplace(it->first, next_it->second);
        s.erase(it);
        s.erase(next_it);
      }
    }
  }
    
  vvi getIntervals() const {
    vvi res;
    res.reserve(s.size());
    for (const auto& x : s)
      res.push_back(vi{x.first, x.second});
    return res;
  }

  private:
  std::set<ii> s;
};

/**
 * Your SummaryRanges object will be instantiated and called as such:
 * SummaryRanges* obj = new SummaryRanges();
 * obj->addNum(value);
 * vector<vector<int>> param_2 = obj->getIntervals();
 */

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    SummaryRanges summaryRanges{};
    summaryRanges.addNum(1);      // arr = [1]
    {
      const vvi e_out{{1,1}};
      const auto a_out = summaryRanges.getIntervals(); // return [[1, 1]]
      assert(a_out == e_out);
    }
    summaryRanges.addNum(3);      // arr = [1, 3]
    {
      const vvi e_out{{1,1},{3,3}};
      const auto a_out = summaryRanges.getIntervals(); // return [[1, 1], [3, 3]]
      assert(a_out == e_out);
    }
    summaryRanges.addNum(7);      // arr = [1, 3, 7]
    {
      const vvi e_out{{1,1},{3,3},{7,7}};
      const auto a_out = summaryRanges.getIntervals(); // return [[1, 1], [3, 3], [7, 7]]
      assert(a_out == e_out);
    }
    summaryRanges.addNum(2);      // arr = [1, 2, 3, 7]
    {
      const vvi e_out{{1,3},{7,7}};
      const auto a_out = summaryRanges.getIntervals(); // return [[1, 3], [7, 7]]
      assert(a_out == e_out);
    }
    summaryRanges.addNum(6);      // arr = [1, 2, 3, 6, 7]
    {
      const vvi e_out{{1,3},{6,7}};
      const auto a_out = summaryRanges.getIntervals(); // return [[1, 3], [7, 7]]
      assert(a_out == e_out);
    }
    
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    SummaryRanges summaryRanges{};
    summaryRanges.addNum(6);
    summaryRanges.addNum(6);
    summaryRanges.addNum(0);
    summaryRanges.addNum(4);
    summaryRanges.addNum(8);
    summaryRanges.addNum(7);
    {
      const vvi e_out{{0,0},{4,4},{6,8}};
      const auto a_out = summaryRanges.getIntervals();
      assert(a_out == e_out);
    }
    summaryRanges.addNum(6);
    {
      const vvi e_out{{0,0},{4,4},{6,8}};
      const auto a_out = summaryRanges.getIntervals();
      assert(a_out == e_out);
    }
    
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
