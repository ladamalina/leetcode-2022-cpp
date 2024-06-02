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

constexpr int INF = 1e9;
constexpr int MAX_X = 5*1e4;

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
  vb getResults(const vvi& queries) {
    SegTree<int> tree(MAX_X+1);
    std::map<int, int> x_dist{{0,0},{INF, INF}};
    vb res;
    for (const auto& q : queries) {
      if (q[0]==1) {
        const auto x = q[1];
        const auto it = x_dist.upper_bound(x);
        const auto next_x = it->F;
        const auto next_dist = it->S;
        const auto prev_x = next_x - next_dist;
        x_dist[x] = x-prev_x;
        x_dist[next_x] = next_x-x;
        tree.Set(x, x-prev_x);
        if (next_x < INF) tree.Set(next_x, next_x-x);
      } else {
        if (q[1] < q[2]) {
          res.push_back(false);
          continue;
        }
        if (x_dist.size() == 1) {
          res.push_back(true);
          continue;
        }
        const auto it = std::prev(x_dist.lower_bound(q[1]));
        const auto tail_dist = q[1]-it->F;
        const auto max_dist = tree.GetMax(0, q[1]+1);
        res.push_back(max_dist >= q[2] || tail_dist >= q[2]);
      }
    }
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi queries{{1,7},{2,7,6},{1,2},{2,7,5},{2,7,6}};
    const auto a_out = Solution().getResults(queries);
    assert(!a_out.empty());
  
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
