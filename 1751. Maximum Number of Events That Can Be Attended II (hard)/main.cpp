// #include <bits/stdc++.h>

#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <deque>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <numeric>
#include <optional>
#include <random>
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
#define SZ(_v) static_cast<int>((_v).size())
#define F first
#define S second

template<typename T>
class SegTree { // Дерево отрезков на максимум
public:
  /*explicit SegTree(const std::vector<T>& a) : MIN(std::numeric_limits<T>::min()) {
    while (size_ < CI(a.size())) size_ *= 2;
    t_.resize(size_ * 2 - 1, MIN);
    Init(a, 0, 0, size_);
  }*/
  
  explicit SegTree(const int n) : MIN(std::numeric_limits<T>::min()) {
    while (size_ < n) size_ *= 2;
    t_.resize(size_ * 2 - 1, MIN);
  }

  T GetMax(int l, int r) {
    return GetMax(l, r, 0, 0, size_);
  }

  void Set(int i, T v) {
    Set(i, v, 0, 0, size_);
  }

private:
  std::vector<T> t_;
  int size_ = 1;
  const T MIN;

  /*void Init(const std::vector<T>& a, int x, int lx, int rx) {
    if (lx + 1 == rx) {
      if (lx < CI(a.size())) t_[x] = a[lx];
    } else {
      const auto m = (lx + rx) / 2;
      Init(a, 2*x+1, lx, m);
      Init(a, 2*x+2, m, rx);
      t_[x] = std::max(t_[2*x+1], t_[2*x+2]);
    }
  }*/

  T GetMax(int l, int r, int x, int lx, int rx) {
    if (rx <= l || lx >= r) return MIN;
    if (rx <= r && lx >= l) return t_[x];
    const auto m = (lx + rx) / 2;
    return std::max(GetMax(l, r, 2*x+1, lx, m), GetMax(l, r, 2*x+2, m, rx));
  }

  void Set(int i, T v, int x, int lx, int rx) {
    if (lx + 1 == rx) {
      t_[x] = v;
      return;
    }
    const auto m = (lx + rx) / 2;
    if (i < m) Set(i, v, 2*x+1, lx, m);
    else Set(i, v, 2*x+2, m, rx);
    t_[x] = std::max(t_[2*x+1], t_[2*x+2]);
  }
};

class Solution {
public:
  int maxValue(vvi& events, const int k) {
    const auto n = SZ(events);
    std::sort(RNG(events), [&](const vi& a, const vi& b) {
      return std::tie(a[1], a[0]) < std::tie(b[1], b[0]);
    });

    auto dp = std::make_shared<SegTree<ll>>(n);
    FOR(i, 0, n-1) {
      dp->Set(i, events[i][2]);
    }
    auto max_res = dp->GetMax(0, n);

    vi prev_j(n);
    FOR(i, 0, n-1) {
      const auto it = std::lower_bound(events.begin(), events.begin()+i, events[i][0],
          [&](const vi& e, const int x) { return e[1] < x; });
      prev_j[i] = CI(it - events.begin());
    }
    
    FOR(p, 1, k-1) {
      auto dp2 = std::make_shared<SegTree<ll>>(n);
      FOR(i, 0, n-1) {
        if (prev_j[i] > 0) {
          const auto max_prev = dp->GetMax(0, prev_j[i]);
          if (max_prev != LLONG_MIN)
            dp2->Set(i, max_prev + events[i][2]);
        }
      }
      dp = dp2;
      max_res = std::max(max_res, dp->GetMax(0, n));
    }

    return max_res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vvi events{{1,2,4},{3,4,3},{2,3,1}};
    const auto a_out = Solution().maxValue(events, 2);
    assert(a_out == 7);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vvi events{{1,2,4},{3,4,3},{2,3,10}};
    const auto a_out = Solution().maxValue(events, 2);
    assert(a_out == 10);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vvi events{{1,1,1},{2,2,2},{3,3,3},{4,4,4}};
    const auto a_out = Solution().maxValue(events, 3);
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
