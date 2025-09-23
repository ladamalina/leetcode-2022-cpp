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
#define PB push_back

template<typename T>
class SegTree {
public:
  struct Node {
    T val = std::numeric_limits<T>::max();
  };

  explicit SegTree(const std::vector<T>& a) {
    while (size_ < CI(a.size())) size_ *= 2;
    t_.resize(size_ * 2 - 1);
    Init(a, 0, 0, size_);
  }

  T GetAND(int l, int r) const {
    return GetAND(l, r, 0, 0, size_).val;
  }

  void Set(int i, T v) {
    Set(i, v, 0, 0, size_);
  }

private:
  std::vector<Node> t_;
  int size_ = 1;

  static Node Combine(const Node& l, const Node& r) {
    return {l.val & r.val};
  }

  void Init(const std::vector<T>& a, int x, int lx, int rx) {
    if (lx + 1 == rx) {
      if (lx < CI(a.size())) {
        t_[x].val = a[lx];
      }
    } else {
      const auto m = (lx + rx) / 2;
      Init(a, 2*x+1, lx, m);
      Init(a, 2*x+2, m, rx);
      t_[x] = Combine(t_[2*x+1], t_[2*x+2]);
    }
  }

  Node GetAND(int l, int r, int x, int lx, int rx) const {
    if (rx <= l || lx >= r) return Node{};
    if (rx <= r && lx >= l) return t_[x];
    const auto m = (lx + rx) / 2;
    return Combine(GetAND(l, r, 2*x+1, lx, m), GetAND(l, r, 2*x+2, m, rx));
  }

  void Set(int i, T v, int x, int lx, int rx) {
    if (lx + 1 == rx) {
      t_[x].val = v;
      return;
    }
    const auto m = (lx + rx) / 2;
    if (i < m) Set(i, v, 2*x+1, lx, m);
    else Set(i, v, 2*x+2, m, rx);
    t_[x] = Combine(t_[2*x+1], t_[2*x+2]);
  }
};

class Solution {
public:
  int minimumDifference(const vi& nums, int k) {
    const auto n = CI(nums.size());
    SegTree tree(nums);
    auto min_res = INT_MAX;
    FOR(i, 0, n-1) {
      const auto val_i = nums[i];
      if (val_i > k) {
        // max gte
        auto li = i, ri = n-1;
        while (li < ri) {
          const auto mi = (li+ri+1)/2;
          const auto sub_and = tree.GetAND(i, mi+1);
          if (sub_and >= k) li = mi;
          else ri = mi-1;
        }
        const auto gte_i = ri;
        const auto gte_and = tree.GetAND(i, gte_i+1);
        const auto gte_res = std::abs(gte_and - k);
        min_res = std::min(min_res, gte_res);
        if (gte_i+1 < n) {
          const auto lt_i = gte_i+1;
          const auto lt_and = tree.GetAND(i, lt_i+1);
          const auto lt_res = std::abs(lt_and - k);
          min_res = std::min(min_res, lt_res);
        }
      } else if (val_i == k) {
        min_res = 0;
      } else { // val_i < k
        const auto res = std::abs(val_i - k);
        min_res = std::min(min_res, res);
      }
      if (min_res == 0) break;
    }
    return min_res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums{1,2,4,5};
    const auto a_out = Solution().minimumDifference(nums, 3);
    assert(a_out == 1);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums{1,2,1,2};
    const auto a_out = Solution().minimumDifference(nums, 2);
    assert(a_out == 0);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums{1};
    const auto a_out = Solution().minimumDifference(nums, 10);
    assert(a_out == 9);

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
