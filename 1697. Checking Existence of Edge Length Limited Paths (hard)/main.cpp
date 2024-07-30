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

constexpr int MAX_QN = 1e5;
vi tmp_qs(MAX_QN);

class Solution {
public:
  vb distanceLimitedPathsExist(const int n, vvi& edges, const vvi& queries) {
    const auto qn = SZ(queries), en = SZ(edges);
    std::sort(RNG(edges), [](const vi& a, const vi& b) { return a[2] < b[2]; });

    vi v_group(n);
    std::iota(RNG(v_group), 0);
    vvi group_vs(n);
    FOR(i, 0, n-1) group_vs[i].push_back(i);
    vvi group_qs(n);
    FOR(qi, 0, qn-1) {
      const auto v = queries[qi][0], u = queries[qi][1];
      group_qs[v_group[v]].push_back(qi);
      group_qs[v_group[u]].push_back(qi);
    }

    vb res(qn, false);

    const auto merge_qs = [&](int src_g, int dst_g, int ew) {
      const auto& src_qs = group_qs[src_g];
      auto& dst_qs = group_qs[dst_g];
      auto si = 0, di = 0, sn = SZ(src_qs), dn = SZ(dst_qs), tn = 0;
      while (si < sn && di < dn) {
        if (src_qs[si] < dst_qs[di]) {
          tmp_qs[tn++] = src_qs[si++];
        } else if (src_qs[si] > dst_qs[di]) {
          tmp_qs[tn++] = dst_qs[di++];
        } else {
          const auto qi = src_qs[si];
          res[qi] = ew < queries[qi][2];
          ++si;
          ++di;
        }
      }
      while (si < sn) {
        tmp_qs[tn++] = src_qs[si++];
      }
      while (di < dn) {
        tmp_qs[tn++] = dst_qs[di++];
      }
      dst_qs.resize(tn);
      dst_qs.assign(tmp_qs.begin(), tmp_qs.begin() + tn);
    };
    
    const auto merge_gs = [&](int src_g, int dst_g, const int ew) {
      if (SZ(group_vs[src_g]) > SZ(group_vs[dst_g]))
        std::swap(src_g, dst_g);

      while (!group_vs[src_g].empty()) {
        const auto v = group_vs[src_g].back();
        group_vs[src_g].pop_back();
        group_vs[dst_g].push_back(v);
        v_group[v] = dst_g;
      }

      merge_qs(src_g, dst_g, ew);
    };

    FOR(ei, 0, en-1) {
      const auto ev = edges[ei][0], eu = edges[ei][1], ew = edges[ei][2];
      if (v_group[ev] != v_group[eu]) {
        merge_gs(v_group[ev], v_group[eu], ew);
      }
    }

    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const int n = 3;
    vvi edges{{0,1,2},{1,2,4},{2,0,8},{1,0,16}};
    const vvi queries{{0,1,2},{0,2,5}};
    const auto a_out = Solution().distanceLimitedPathsExist(n, edges, queries);
    const vb e_out{false, true};
    assert(a_out == e_out);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const int n = 5;
    vvi edges{{0,1,10},{1,2,5},{2,3,9},{3,4,13}};
    const vvi queries{{0,4,14},{1,4,13}};
    const auto a_out = Solution().distanceLimitedPathsExist(n, edges, queries);
    const vb e_out{true, false};
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
