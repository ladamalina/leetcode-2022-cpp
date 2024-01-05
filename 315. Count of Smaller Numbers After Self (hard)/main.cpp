//#pragma GCC optimize("O3")
//#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;

template<typename T>
class FenwickTree {
  /*
   * Point Update and Range Query
   * https://cp-algorithms.com/data_structures/fenwick.html
   */
  public:
  explicit FenwickTree(int n) : n_(n), bit_(n) {}

  explicit FenwickTree(const std::vector<T>& a) : FenwickTree(a.size()) {
    for (int i = 0; i < n_; ++i) {
      bit_[i] += a[i];
      int r = i | (i + 1);
      if (r < n_) bit_[r] += bit_[i];
    }
  }

  void Add(int idx, T delta) {
    for (; idx < n_; idx |= (idx + 1))
      bit_[idx] += delta;
  }

  T Sum(int l, int r) const {
    return Sum(r) - Sum(l - 1);
  }

  T Sum(int r) const {
    T res = 0;
    for (; r >= 0; r = (r & (r + 1)) - 1)
      res += bit_[r];
    return res;
  }
  
  private:
  int n_;
  std::vector<T> bit_;
};

class Solution {
  public:
  std::vector<int> countSmaller(const std::vector<int>& nums) {
    const int n = nums.size();
    auto nums_sorted = nums;
    std::sort(nums_sorted.begin(), nums_sorted.end());
    std::unordered_map<int, int> comp;
    for (int i = 0; i < n; ++i) {
      if (!comp.contains(nums_sorted[i])) {
        comp[nums_sorted[i]] = comp.size();
      }
    }
    FenwickTree<int> fenw(n);
    std::vector<int> res(n);
    for (int i = n-1; i >= 0; --i) {
      const auto x = comp.at(nums[i]);
      if (x > 0) {
        res[i] = fenw.Sum(0, x-1);
      }
      fenw.Add(x, 1);
    }
    return res;
  }
};

/*
[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    std::vector<int> nums{3,1,5,8};
    const auto e_out = Solution::maxCoins(nums);
    assert(e_out == 167);
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    std::vector<int> nums{1,5};
    const auto e_out = Solution::maxCoins(nums);
    assert(e_out == 10);
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  std::cerr << "TestSolution OK"sv << std::endl;
}
*/

int main() {
#ifndef NDEBUG
  // TestSolution();
#endif
  return 0;
}
