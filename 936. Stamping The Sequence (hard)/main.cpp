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
using vvl [[maybe_unused]] = std::vector<vl>;
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

bool Match(const std::string& stamp, const std::string& target, const int pos) {
  const auto sn = SZ(stamp);
  bool has_non_q = false;
  FOR(ti, pos, pos + sn - 1) {
    if (target[ti] == '?')
      continue;
    has_non_q = true;
    if (stamp[ti-pos] != target[ti])
      return false;
  }
  return has_non_q;
}

class Solution {
public:
  vi movesToStamp(const std::string& stamp, std::string& target) {
    const auto sn = SZ(stamp), tn = SZ(target);
    std::deque<int> q;
    auto it = std::find_if(RNG(target), [](char c) { return c != '?'; });
    while (it != target.end()) {
      bool has_math = false;
      FOR(i, 0, tn-sn) {
        if (Match(stamp, target, i)) {
          has_math = true;
          q.push_front(i);
          FOR(j, i, i + sn - 1) {
            target[j] = '?';
          }
          break;
        }
      }
      if (!has_math)
        return {};
      it = std::find_if(RNG(target), [&](char c) { return c != '?'; });
    }
    return vi(RNG(q));
  }
};

/*class Solution {
public:
  vi movesToStamp(const std::string& stamp, const std::string& target) {
    const auto sn = SZ(stamp), tn = SZ(target);
    const std::string s(tn, '?');
    
    std::unordered_set<std::string> vis;
    vi res_path, path;
    const std::function<bool(std::string)> rec = [&](const std::string& t) {
      if (SZ(path) > 10 * tn)
        return false;
      if (t == target) {
        res_path = path;
        return true;
      }
      if (vis.contains(t))
        return false;
      vis.insert(t);
      FOR(i, 0, tn - sn) {
        auto next_t = t;
        std::copy(RNG(stamp), next_t.begin() + i);
        path.push_back(i);
        const auto sub_res = rec(next_t);
        path.pop_back();
        if (sub_res)
          return true;
      }
      return false;
    };
    [[maybe_unused]] const auto res = rec(s);
    return res_path;
  }
};*/

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    std::string target("ababc"s);
    const auto a_out = Solution().movesToStamp("abc", target);
    assert(!a_out.empty());
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    std::string target("aabcaca"s);
    const auto a_out = Solution().movesToStamp("abca", target);
    assert(!a_out.empty());

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    std::string target("frffrffrfrfrfrfrfrfr"s);
    const auto a_out = Solution().movesToStamp("fr", target);
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
