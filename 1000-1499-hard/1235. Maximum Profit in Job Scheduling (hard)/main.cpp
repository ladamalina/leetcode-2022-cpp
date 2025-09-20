//#pragma GCC optimize("O3")
//#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;

template<typename T>
class FenwickTreeMax {
  public:
  explicit FenwickTreeMax(int n) : n_(n), bit_(n_) {}

  explicit FenwickTreeMax(const std::vector<T>& a) : FenwickTreeMax(a.size()) {
    for (size_t i = 0; i < a.size(); ++i)
      Update(i, a[i]);
  }

  T GetMax(int r) {
    auto res = INF;
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
  const T INF = 0;
};

class Solution {
  public:
  struct Job {
    int start_x, end_x, profit;
    Job() = default;
    Job(int s, int e, int p) : start_x(s), end_x(e), profit(p) {}
  };
  
  static int jobScheduling(const std::vector<int>& start_tm, const std::vector<int>& end_tm,
    const std::vector<int>& profit) {

    const int n = static_cast<int>(start_tm.size());
    
    std::set<int> tm_set;
    for (const auto x : start_tm) tm_set.insert(x);
    for (const auto x : end_tm) tm_set.insert(x);

    std::unordered_map<int, int> tm_comp;
    for (const auto x : tm_set) {
      if (!tm_comp.contains(x)) {
        tm_comp[x] = static_cast<int>(tm_comp.size());
      }
    }
    const int max_tm_comp = static_cast<int>(tm_comp.size())-1;

    std::vector<Job> jobs(n);
    for (int i = 0; i < n; ++i) {
      jobs[i] = {tm_comp.at(start_tm[i]), tm_comp.at(end_tm[i]), profit[i]};
    }
    std::sort(jobs.begin(), jobs.end(), [](const Job& l, const Job& r) {
      return std::tie(l.end_x, l.start_x) < std::tie(r.end_x, r.start_x);
    });

    FenwickTreeMax<int> fenw(max_tm_comp+1);
    std::vector<int> dp(max_tm_comp+1);
    for (const auto& j : jobs) {
      const auto prev_profit = fenw.GetMax(j.start_x);
      const auto next_profit = prev_profit + j.profit;
      if (next_profit > dp[j.end_x]) {
        dp[j.end_x] = next_profit;
        fenw.Update(j.end_x, next_profit);
      }
    }
    const auto max_profit = fenw.GetMax(max_tm_comp);
    return max_profit;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::vector<int> start_tm{1,2,3,3};
    const std::vector<int> end_tm{3,4,5,6};
    const std::vector<int> profit{50,10,40,70};
    const auto e_out = Solution::jobScheduling(start_tm, end_tm, profit);
    assert(e_out == 120);
    
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::vector<int> start_tm{1,2,3,4,6};
    const std::vector<int> end_tm{3,5,10,6,9};
    const std::vector<int> profit{20,20,100,70,60};
    const auto e_out = Solution::jobScheduling(start_tm, end_tm, profit);
    assert(e_out == 150);
    
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::vector<int> start_tm{1,1,1};
    const std::vector<int> end_tm{2,3,4};
    const std::vector<int> profit{5,6,4};
    const auto e_out = Solution::jobScheduling(start_tm, end_tm, profit);
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
