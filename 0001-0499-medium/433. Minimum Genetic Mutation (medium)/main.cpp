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

const std::string CS("ACGT");
constexpr int LEN = 8;

class Solution {
public:
  int minMutation(std::string& src, const std::string& dst, vs& bank) {
    if (src == dst)
      return 0;
    const auto bn = SZ(bank);
    std::unordered_map<std::string, int> bank_i;
    FOR(i, 0, bn-1) bank_i[bank[i]] = i;
    if (!bank_i.contains(dst))
      return -1;
    vi dist(bn, INT_MAX);
    std::priority_queue<ii, vii, std::less<>> pq;
    FOR(i, 0, LEN-1) {
      const auto src_c = src[i];
      for (const auto c : CS) {
        if (c != src_c) {
          src[i] = c;
          const auto it = bank_i.find(src);
          if (it != bank_i.end()) {
            dist[it->S] = 1;
            pq.emplace(1, it->S);
          }
          src[i] = src_c;
        }
      }
    }
    while (!pq.empty()) {
      const auto [d, bi] = pq.top();
      pq.pop();
      FOR(i, 0, LEN-1) {
        const auto src_c = bank[bi][i];
        for (const auto c : CS) {
          if (c != src_c) {
            bank[bi][i] = c;
            const auto it = bank_i.find(bank[bi]);
            if (it != bank_i.end()) {
              const auto j = it->S;
              if (d + 1 < dist[j]) {
                dist[j] = d + 1;
                pq.emplace(d + 1, j);
              }
            }
            bank[bi][i] = src_c;
          }
        }
      }
    }
    const auto dst_dist = dist[bank_i[dst]];
    return dst_dist == INT_MAX ? -1 : dst_dist;
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
