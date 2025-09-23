// #include <bits/stdc++.h>

#include <algorithm>
#include <cassert>
#include <chrono>
#include <cmath>
#include <deque>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <numeric>
#include <optional>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <variant>
#include <vector>

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
#define PB push_back

template<typename T>
class SegTree {
public:
  struct Node {
    T sum_LR=0, sum_Lr=0, sum_lR=0, sum_lr=0;

    Node() = default;
    explicit Node(T val) : sum_LR(val) {}
  };

  explicit SegTree(const std::vector<T>& a) {
    while (size_ < CI(a.size())) size_ *= 2;
    t_.resize(size_ * 2 - 1);
    Init(a, 0, 0, size_);
  }

  T GetSum(int l, int r) const {
    const auto res = GetSum(l, r, 0, 0, size_);
    return std::max(0, std::max(res.sum_LR, std::max(res.sum_Lr, std::max(res.sum_lR, res.sum_lr))));
  }

  void Set(int i, T v) {
    Set(i, v, 0, 0, size_);
  }

private:
  std::vector<Node> t_;
  int size_ = 1;

  static Node Combine(const Node& l, const Node& r) {
    Node res;
    res.sum_LR = std::max(l.sum_LR+r.sum_lR, l.sum_Lr+r.sum_LR);
    res.sum_Lr = std::max(l.sum_LR+r.sum_lr, l.sum_Lr+r.sum_Lr);
    res.sum_lR = std::max(l.sum_lR+r.sum_lR, l.sum_lr+r.sum_LR);
    res.sum_lr = std::max(l.sum_lR+r.sum_lr, l.sum_lr+r.sum_Lr);
    return res;
  }

  void Init(const std::vector<T>& a, int x, int lx, int rx) {
    if (lx + 1 == rx) {
      if (lx < CI(a.size())) {
        t_[x] = Node(a[lx]);
      }
    } else {
      const auto m = (lx + rx) / 2;
      Init(a, 2*x+1, lx, m);
      Init(a, 2*x+2, m, rx);
      t_[x] = Combine(t_[2*x+1], t_[2*x+2]);
    }
  }

  Node GetSum(int l, int r, int x, int lx, int rx) const {
    if (rx <= l || lx >= r) return Node{};
    if (rx <= r && lx >= l) return t_[x];
    const auto m = (lx + rx) / 2;
    return Combine(GetSum(l, r, 2*x+1, lx, m), GetSum(l, r, 2*x+2, m, rx));
  }

  void Set(int i, T v, int x, int lx, int rx) {
    if (lx + 1 == rx) {
      t_[x] = Node(v);
      return;
    }
    const auto m = (lx + rx) / 2;
    if (i < m) Set(i, v, 2*x+1, lx, m);
    else Set(i, v, 2*x+2, m, rx);
    t_[x] = Combine(t_[2*x+1], t_[2*x+2]);
  }
};

constexpr ll MOD = 1e9+7;

class Solution {
public:
  int maximumSumSubsequence(const vi& nums, const vvi& queries) {
    SegTree tree(nums);
    ll res = 0;
    for (const auto& q : queries) {
      tree.Set(q[0], q[1]);
      const auto sub_res = tree.GetSum(0, nums.size());
      res = (res+sub_res)%MOD;
    }
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums{3,5,9};
    const vvi queries{{1,-2},{0,-3}};
    const auto a_out = Solution().maximumSumSubsequence(nums, queries);
    assert(a_out == 21);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums{0,-1};
    const vvi queries{{0,-5}};
    const auto a_out = Solution().maximumSumSubsequence(nums, queries);
    assert(a_out == 0);
  
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
