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

struct TopK {
  int k;
  std::unordered_map<int, int> freq;
  std::set<ii> lt, gt;
  ll top_sum = 0;
  explicit TopK(const int k_) : k(k_) {}
  void Inc(const int x) {
    const auto f = ++freq[x];
    if (f - 1) {
      const auto lt_it = lt.find({f - 1, x});
      if (lt_it != lt.end()) {
        lt.erase(lt_it);
      } else {
        gt.erase({f - 1, x});
        top_sum -= CL(f - 1) * x;
      }
    }
    gt.emplace(f, x);
    top_sum += CL(f) * x;
    if (SZ(gt) > k) {
      const auto p_it = gt.begin();
      top_sum -= CL(p_it->F) * p_it->S;
      lt.insert(*p_it);
      gt.erase(p_it);
    }
  }
  void Dec(const int x) {
    const auto f = --freq[x];
    const auto lt_it = lt.find({f + 1, x});
    if (lt_it != lt.end()) {
      lt.erase(lt_it);
    } else {
      gt.erase({f + 1, x});
      top_sum -= CL(f + 1) * x;
    }
    if (f) lt.emplace(f, x);
    if (SZ(gt) < k && !lt.empty()) {
      const auto p_it = std::prev(lt.end());
      top_sum += CL(p_it->F) * p_it->S;
      gt.insert(*p_it);
      lt.erase(p_it);
    }
  }
};

class Solution {
public:
  vl findXSum(const vi& nums, const int k, const int x) {
    const auto n = SZ(nums);
    vl res(n - k + 1);
    TopK top_k(x);
    FOR(i, 0, k-1) top_k.Inc(nums[i]);
    res[0] = top_k.top_sum;
    FOR(i, 1, n - k) {
      top_k.Dec(nums[i - 1]);
      top_k.Inc(nums[i + k - 1]);
      res[i] = top_k.top_sum;
    }
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums{1,1,2,2,3,4,2,3};
    const auto a_out = Solution().findXSum(nums, 6, 2);
    const vl e_out{6,10,12};
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
