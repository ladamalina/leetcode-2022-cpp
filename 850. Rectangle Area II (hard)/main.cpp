#include <bits/stdc++.h>

using namespace std::literals;

using ll [[maybe_unused]] = long long;
using ii [[maybe_unused]] = std::pair<int, int>;
using vii [[maybe_unused]] = std::vector<ii>;
using vi [[maybe_unused]] = std::vector<int>;
using vl [[maybe_unused]] = std::vector<ll>;
using vvi [[maybe_unused]] = std::vector<vi>;
using vs [[maybe_unused]] = std::vector<std::string>;
using vvs [[maybe_unused]] = std::vector<vs>;
using vc [[maybe_unused]] = std::vector<char>;
using vvc [[maybe_unused]] = std::vector<vc>;

#define FOR(_i, _a, _b) for (int _i = (_a); _i <= (_b); ++(_i))
#define FORD(_i, _a, _b) for (int _i = (_a); _i >= (_b); --(_i))
#define RNG(_l) (_l).begin(), (_l).end()
#define SORT(_l) std::sort((_l).begin(), (_l).end())
#define CI(_v) static_cast<int>(_v)
#define F first
#define S second

constexpr ll MOD = 1e9 + 7;

template <typename T>
[[maybe_unused]] T ModSum(T a, T b, T m) {
  a %= m;
  a = (a >= 0) ? a : a + m;
  b %= m;
  b = (b >= 0) ? b : b + m;
  auto c = (a + b) % m;
  c = (c >= 0) ? c : c + m;
  return c;
}

template <typename T>
[[maybe_unused]] T ModMult(T a, T b, T m) {
  a %= m;
  a = (a >= 0) ? a : a + m;
  b %= m;
  b = (b >= 0) ? b : b + m;
  auto c = (a * b) % m;
  c = (c >= 0) ? c : c + m;
  return c;
}

constexpr int MAX_N = 200;
int x_orig[MAX_N*4];

class Solution {
 public:
  static int rectangleArea(vvi& rs) {
    std::unordered_map<int, int> x_comp;
    {
      std::set<int> x_set;
      for (const auto& r : rs) {
        x_set.insert(r[0]);
        x_set.insert(r[1]);
        x_set.insert(r[2]);
        x_set.insert(r[3]);
      }
      for (const auto x : x_set) {
        if (!x_comp.contains(x)) {
          const auto i = CI(x_comp.size());
          x_comp[x] = i;
          x_orig[i] = x;
        }
      }
    }
    int x_comp_mn = INT_MAX, y_comp_mn = INT_MAX,
        x_comp_mx = INT_MIN, y_comp_mx = INT_MIN;
    for (auto& r : rs) {
      r = {x_comp.at(r[0]), x_comp.at(r[1]), x_comp.at(r[2]), x_comp.at(r[3])};
      x_comp_mn = std::min(x_comp_mn, r[0]);
      y_comp_mn = std::min(y_comp_mn, r[1]);
      x_comp_mx = std::max(x_comp_mx, r[2]);
      y_comp_mx = std::max(y_comp_mx, r[3]);
    }
    ll sq = 0;
    FOR(x, x_comp_mn, x_comp_mx-1) {
      FOR(y, y_comp_mn, y_comp_mx-1) {
        bool covered = std::any_of(RNG(rs), [&](const vi& r) {
          return r[0] <= x && r[1] <= y && r[2] > x && r[3] > y;
        });
        if (covered) {
          const ll w_orig = x_orig[x+1] - x_orig[x];
          const ll h_orig = x_orig[y+1] - x_orig[y];
          sq = ModSum(sq, ModMult(w_orig, h_orig, MOD), MOD);
        }
      }
    }
    return sq;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vvi rectangles{{0,0,2,2},{1,0,2,3},{1,0,3,1}};
    auto a_out = Solution::rectangleArea(rectangles);
    assert(a_out == 6);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vvi rectangles{{0,0,1000000000,1000000000}};
    auto a_out = Solution::rectangleArea(rectangles);
    assert(a_out == 49);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vvi rectangles{{0,0,1,1},{2,2,3,3}};
    auto a_out = Solution::rectangleArea(rectangles);
    assert(a_out == 2);

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
