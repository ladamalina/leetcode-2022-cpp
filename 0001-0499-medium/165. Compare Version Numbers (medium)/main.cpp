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
#include <queue>
#include <random>
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

class Solution {
 public:
  static int compareVersion(const std::string& s1, const std::string& s2) {
    auto v1 = 0, b1 = 0;
    auto v2 = 0, b2 = 0;
    while (b1 < SZ(s1) || b2 < SZ(s2)) {
      std::tie(v1, b1) = getVersion(s1, b1);
      std::tie(v2, b2) = getVersion(s2, b2);
      if (v1 < v2) return -1;
      if (v1 > v2) return 1;
    }
    return 0;
  }

  static ii getVersion(const std::string& s, const int b) {
    auto e = b;
    while (e < SZ(s) && s[e] != '.') ++e;
    if (b == e)
      return {0, SZ(s)};

    const auto v = std::stoi(s.substr(b, e - b));
    const auto v_e = std::min(e + 1, SZ(s));
    return {v, v_e};
  }
};

int main() {
  const auto v1_1 = "1.01"s;
  const auto v1_2 = "1.001"s;
  assert(Solution::compareVersion(v1_1, v1_2) == 0);

  const auto v2_1 = "1.0"s;
  const auto v2_2 = "1.0.0"s;
  assert(Solution::compareVersion(v2_1, v2_2) == 0);

  const auto v3_1 = "0.1"s;
  const auto v3_2 = "1.1"s;
  assert(Solution::compareVersion(v3_1, v3_2) == -1);

  const auto v4_1 = "1.0.1"s;
  const auto v4_2 = "1"s;
  assert(Solution::compareVersion(v4_1, v4_2) == 1);

  return 0;
}
