//#pragma GCC optimize("O3")
//#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;

using ll = long long;
using ld = long double;
using ull = unsigned long long;
using ii [[maybe_unused]] = std::pair<int, int>;
using pll [[maybe_unused]] = std::pair<ll, ll>;
using vi [[maybe_unused]] = std::vector<int>;
using vvi [[maybe_unused]] = std::vector<vi>;
using vii [[maybe_unused]] = std::vector<ii>;
using vb [[maybe_unused]] = std::vector<bool>;
using vd [[maybe_unused]] = std::vector<ld>;

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

struct [[maybe_unused]] HashPair {
  size_t operator()(const ii& x) const {
    return (x.F) * 37 + (x.S) * 37 * 37;
  }
};

const vii DIRS{{0,0},{0,1},{0,-1},{1,0},{1,1},{1,-1},{-1,0},{-1,1},{-1,-1}};

class Solution {
  public:
  static vi gridIllumination([[maybe_unused]] int n, const vvi& lamps, const vvi& queries) {
    std::unordered_map<int, int> on_r;
    std::unordered_map<int, int> on_c;
    std::unordered_map<int, int> on_d1;
    std::unordered_map<int, int> on_d2;
    std::unordered_set<ii, HashPair> on;
    for (const auto& lamp : lamps) {
      if (!on.contains({lamp[0], lamp[1]})) {
        on.emplace(lamp[0], lamp[1]);
        ++on_r[lamp[0]];
        ++on_c[lamp[1]];
        ++on_d1[lamp[0]+lamp[1]];
        ++on_d2[lamp[0]-lamp[1]];
      }
    }
    vi res(queries.size());
    FOR(qi, 0, CI(queries.size())-1) {
      const auto qr = queries[qi][0];
      const auto qc = queries[qi][1];
      if (on_r.contains(qr) || on_c.contains(qc) || on_d1.contains(qr+qc) || on_d2.contains(qr-qc)) {
        res[qi] = 1;
      }
      for (const auto& d : DIRS) {
        const auto cr = qr+d.F;
        const auto cc = qc+d.S;
        if (on.contains({cr, cc})) {
          on.erase({cr, cc});
          --on_r[cr];
          if (on_r.at(cr) == 0) on_r.erase(cr);
          --on_c[cc];
          if (on_c.at(cc) == 0) on_c.erase(cc);
          --on_d1[cr+cc];
          if (on_d1.at(cr+cc) == 0) on_d1.erase(cr+cc);
          --on_d2[cr-cc];
          if (on_d2.at(cr-cc) == 0) on_d2.erase(cr-cc);
        }
      }
    }
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    const vvi lamps{{2,5},{4,2},{0,3},{0,5},{1,4},{4,2},{3,3},{1,0}};
    const vvi queries{{4,3},{3,1},{5,3},{0,5},{4,4},{3,3}};
    const vi e_out{1,0,1,1,0,1};
    const auto a_out = Solution::gridIllumination(6, lamps, queries);
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
