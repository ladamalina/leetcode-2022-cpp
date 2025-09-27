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
using ld = long double;
using ii = std::pair<int, int>;
using vi = std::vector<int>;
using vvi = std::vector<vi>;
using vvvi = std::vector<vvi>;
using vl = std::vector<ll>;
using vvl = std::vector<vl>;
using vvvl = std::vector<vvl>;
using vii = std::vector<ii>;
using vb = std::vector<bool>;
using vd = std::vector<ld>;
using vs = std::vector<std::string>;
using vc = std::vector<char>;

#define FOR(_i, _a, _b) for (auto _i = (_a); _i <= (_b); ++(_i))
#define FORD(_i, _a, _b) for (auto _i = (_a); _i >= (_b); --(_i))
#define RNG(_l) (_l).begin(), (_l).end()
#define SORT(_l) std::sort((_l).begin(), (_l).end())
#define CI(_v) static_cast<int>(_v)
#define CL(_v) static_cast<ll>(_v)
#define CD(_v) static_cast<ld>(_v)
#define CC(_v) static_cast<char>(_v)
#define SZ(_v) static_cast<int>((_v).size())
#define F first
#define S second
#define PB push_back

template<typename T>
class SegTree { // Дерево отрезков на максимум
public:
  explicit SegTree(const int n) {
    while (size_ < n) size_ <<= 1;
    t_.resize(size_ << 1, 0);
  }

  T GetMax(int l, int r) {
    return GetMax(l, r, 1, 0, size_);
  }

  void Set(int i, T v) {
    Set(i, v, 1, 0, size_);
  }

private:
  std::vector<T> t_;
  int size_ = 1;

  T GetMax(int l, int r, int x, int lx, int rx) {
    if (rx <= l || lx >= r) return 0;
    if (rx <= r && lx >= l) return t_[x];
    const auto m = (lx + rx) >> 1;
    return std::max(GetMax(l, r, (x<<1), lx, m), GetMax(l, r, (x<<1)|1, m, rx));
  }

  void Set(int i, T v, int x, int lx, int rx) {
    if (lx + 1 == rx) {
      t_[x] = v;
      return;
    }
    const auto m = (lx + rx) >> 1;
    if (i < m) Set(i, v, (x<<1), lx, m);
    else Set(i, v, (x<<1)|1, m, rx);
    t_[x] = std::max(t_[(x<<1)], t_[(x<<1)|1]);
  }
};

class Solution {
public:
  vi maxValue(const vi& nums) {
    const auto n = SZ(nums);

    std::unordered_map<int, int> xy;
    {
      auto xs = nums;
      SORT(xs);
      xs.erase(std::unique(RNG(xs)), xs.end());
      for (const auto x : xs) if (!xy.contains(x)) xy[x] = SZ(xy);
    }
    const auto max_y = SZ(xy) - 1;
    SegTree<int> tree(max_y + 1);

    vi res(n, -1);
    vii yi(n);
    FOR(i, 0, n-1) yi[i] = {xy[nums[i]], i};
    SORT(yi);
    auto vis_i = n;
    FORD(yii, n-1, 0) {
      const auto y = yi[yii].F, i = yi[yii].S;
      if (i < vis_i) {
        res[i] = nums[i];
        if (y > 0) {
          res[i] = std::max(res[i], tree.GetMax(0, y));
        }
        tree.Set(y, res[i]);
        FOR(j, i + 1, vis_i - 1) {
          if (nums[j] < nums[i]) {
            res[j] = res[i];
            const auto jy = xy[nums[j]];
            if (res[i] > tree.GetMax(jy, jy + 1))
              tree.Set(jy, res[i]);
          }
        }
        vis_i = i;
      }
    }
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums{2,3,1};
    const auto a_out = Solution().maxValue(nums);
    const vi e_out{3,3,3};
    assert(a_out == e_out);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums{2,1,3};
    const auto a_out = Solution().maxValue(nums);
    const vi e_out{2,2,3};
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
