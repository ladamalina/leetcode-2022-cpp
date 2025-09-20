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
using ii [[maybe_unused]] = std::pair<int, int>;
using vi [[maybe_unused]] = std::vector<int>;
using vl [[maybe_unused]] = std::vector<ll>;
using vvi [[maybe_unused]] = std::vector<vi>;
using vvvi [[maybe_unused]] = std::vector<vvi>;
using vvl [[maybe_unused]] = std::vector<vl>;
using vii [[maybe_unused]] = std::vector<ii>;
using vb [[maybe_unused]] = std::vector<bool>;
using vd [[maybe_unused]] = std::vector<double>;
using vs [[maybe_unused]] = std::vector<std::string>;
using vc [[maybe_unused]] = std::vector<char>;

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

class DSU {
public:
  explicit DSU(int n) : p_(vi(n))/*, r_(vi(n, 1)), cnt_(n)*/ {
    std::iota(p_.begin(), p_.end(), 0);
  }

  int Get(int a) {
    return p_[a] = (a == p_[a] ? a : Get(p_[a]));
  }

  void Union(int a, int b) {
    a = Get(a);
    b = Get(b);
    if (a == b) return;
    // if (r_[a] == r_[b]) ++r_[a];
    // if (r_[a] > r_[b]) p_[b] = a;
    // else p_[a] = b;
    if (a <= b) p_[b] = a;
    else p_[a] = b;
    // --cnt_;
  }

  // [[nodiscard]] int Count() const { return cnt_; }

private:
  vi p_/*, r_*/;
  // int cnt_ = 0;
};

class Solution {
public:
  std::string smallestEquivalentString(const std::string& s1, const std::string& s2, const std::string& base) {
    const auto n = SZ(s1);
    DSU dsu(26);
    FOR(i, 0, n-1) dsu.Union(s1[i]-'a', s2[i]-'a');

    auto t = base;
    for (auto& c : t) c = CC('a' + dsu.Get(c-'a'));
    return t;
  }
};

[[maybe_unused]] void TestSolution() {
  /*{
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().solve();
    assert(a_out == 6);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }*/
  std::cerr << "TestSolution OK"sv << std::endl;
}

int main() {
#ifndef NDEBUG
  TestSolution();
#endif
  return 0;
}
