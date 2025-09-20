#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;

/**
 * Your TreeAncestor object will be instantiated and called as such:
 * TreeAncestor* obj = new TreeAncestor(n, parent);
 * int param_1 = obj->getKthAncestor(node,k);
 */

class TreeAncestor {
 public:
  TreeAncestor(int n, std::vector<int>& parent)
      : n_(n)
      , h_max_(std::ceil(std::log2(n)))
      , up_(h_max_+1, std::vector<int>(n)) {
    up_[0] = parent;
    for (int h = 1; h <= h_max_; ++h) {
      for (int v = 0; v < n_; ++v) {
        up_[h][v] = up_[h-1][v] >= 0 ? up_[h-1][up_[h-1][v]] : -1;
      }
    }
  }

  [[nodiscard]] int getKthAncestor(int v, int k) const {
    for (int h = h_max_; h >= 0; --h) {
      if ((1<<h) <= k) {
        v = up_[h][v];
        k -= (1<<h);
        if (v == -1) break;
      }
    }
    return v;
  }
  
 private:
  int n_;
  int h_max_;
  std::vector<std::vector<int>> up_;
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    std::vector<int> parent{-1,0,0,1,1,2,2};
    TreeAncestor solution{7, parent};
    {
      const auto a_out = solution.getKthAncestor(3, 1);
      const auto e_out = 1;
      assert(a_out == e_out);
    }
    {
      const auto a_out = solution.getKthAncestor(5, 2);
      const auto e_out = 0;
      assert(a_out == e_out);
    }
    {
      const auto a_out = solution.getKthAncestor(6, 3);
      const auto e_out = -1;
      assert(a_out == e_out);
    }
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  std::cerr << "TestSolution OK"sv << std::endl;
}

int main() {
  TestSolution();
  return 0;
}
