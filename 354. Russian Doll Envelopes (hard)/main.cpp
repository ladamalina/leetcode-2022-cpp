//#pragma GCC optimize("O3")
//#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;

using ll = long long;
using ld = long double;
using ull = unsigned long long;
using ii [[maybe_unused]] = std::pair<int, int>;
using pll [[maybe_unused]] = std::pair<ll, ll>;
using pdd [[maybe_unused]] = std::pair<double, double>;
using vi [[maybe_unused]] = std::vector<int>;
using vvi [[maybe_unused]] = std::vector<vi>;
using vvvi [[maybe_unused]] = std::vector<vvi>;
using vii [[maybe_unused]] = std::vector<ii>;
using vvii [[maybe_unused]] = std::vector<vii>;
using vb [[maybe_unused]] = std::vector<bool>;

#define FOR(_i, _a, _b) for (int _i = (_a); _i <= (_b); ++(_i))
#define FORD(_i, _a, _b) for (int _i = (_a); _i >= (_b); --(_i))
#define RNG(_l) (_l).begin(), (_l).end()
#define SORT(_l) std::sort((_l).begin(), (_l).end())
#define CI(_v) static_cast<int>(_v)
#define CL(_v) static_cast<ll>(_v)
#define CD(_v) static_cast<ld>(_v)
#define F first
#define S second
#define PB push_back

template<typename T>
class SegTree {
  public:

  explicit SegTree(const size_t size_a) {
    while (size_ < CI(size_a)) size_ *= 2;
    t_.resize(size_ * 2 - 1);
  }

  T GetMax(int l, int r) const {
    return GetMax(l, r, 0, 0, size_);
  }

  T Get(int i) const {
    return Get(i, 0, 0, size_);
  }

  void Set(int i, T v) {
    Set(i, v, 0, 0, size_);
  }

  private:
  std::vector<T> t_;
  int size_ = 1;

  T GetMax(int l, int r, int x, int lx, int rx) const {
    if (rx <= l || lx >= r) return 0;
    if (rx <= r && lx >= l) return t_[x];
    const auto m = (lx + rx) / 2;
    return std::max(GetMax(l, r, 2*x+1, lx, m), GetMax(l, r, 2*x+2, m, rx));
  }

  T Get(int i, int x, int lx, int rx) const {
    if (lx + 1 == rx) {
      return t_[x];
    }
    const auto m = (lx + rx) / 2;
    if (i < m) {
      return Get(i, 2*x+1, lx, m);
    } else {
      return Get(i, 2*x+2, m, rx);
    }
  }

  void Set(int i, T v, int x, int lx, int rx) {
    if (lx + 1 == rx) {
      t_[x] = v;
      return;
    }
    const auto m = (lx + rx) / 2;
    if (i < m) {
      Set(i, v, 2*x+1, lx, m);
    } else {
      Set(i, v, 2*x+2, m, rx);
    }
    t_[x] = std::max(t_[2*x+1], t_[2*x+2]);
  }
};

class Solution {
  public:
  static int maxEnvelopes(vvi& envelopes) {
    const auto envelopes_n = CI(envelopes.size());
    std::sort(RNG(envelopes), [](const vi& l, const vi& r) { return std::make_pair(l[0], -l[1]) < std::make_pair(r[0], -r[1]); });
    const auto max_h = (*std::max_element(RNG(envelopes), [&](const vi& l, const vi& r) { return l[1] < r[1]; }))[1];
    SegTree<int> tree(max_h+1);

    int res = 1;
    FOR(i, 0, envelopes_n-1) {
      const auto h = envelopes[i][1];
      const auto curr = tree.Get(h);
      const auto max_prev = tree.GetMax(0, h);
      if (max_prev + 1 > curr) {
        tree.Set(h, max_prev + 1);
        res = std::max(res, max_prev + 1);
      }
    }
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    vvi envelopes{{5,4},{6,4},{6,7},{2,3}};
    const auto a_out = Solution::maxEnvelopes(envelopes);
    assert(a_out == 3);
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    vvi envelopes{{1,1},{1,1},{1,1}};
    const auto a_out = Solution::maxEnvelopes(envelopes);
    assert(a_out == 1);
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    vvi envelopes{{4,5},{4,6},{6,7},{2,3},{1,1}};
    const auto a_out = Solution::maxEnvelopes(envelopes);
    assert(a_out == 4);
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    vvi envelopes{{30,50},{12,2},{3,4},{12,15}};
    const auto a_out = Solution::maxEnvelopes(envelopes);
    assert(a_out == 3);
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
