// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;

using ll = long long;
using ii [[maybe_unused]] = std::pair<int, int>;
using vi [[maybe_unused]] = std::vector<int>;
using vvi [[maybe_unused]] = std::vector<vi>;
using vii [[maybe_unused]] = std::vector<ii>;
using vb [[maybe_unused]] = std::vector<bool>;

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

template<typename T>
vi ClosestLTEL(const std::vector<T>& a) {
  const auto n = CI(a.size());
  vi lt_l(n);
  lt_l[0] = -1;
  FOR(i, 1, n-1) {
    if (a[i-1] <= a[i]) lt_l[i] = i-1;
    else {
      int j = lt_l[i-1];
      while (j != -1 && a[j] > a[i]) {
        j = lt_l[j];
      }
      lt_l[i] = j;
    }
  }
  return lt_l;
}

template<typename T>
vi ClosestLTR(const std::vector<T>& a) {
  const auto n = CI(a.size());
  vi lt_r(n);
  lt_r[n-1] = n;
  FORD(i, n-2, 0) {
    if (a[i] > a[i+1]) lt_r[i] = i+1;
    else {
      int j = lt_r[i+1];
      while (j != n && a[i] <= a[j]) {
        j = lt_r[j];
      }
      lt_r[i] = j;
    }
  }
  return lt_r;
}

class Solution {
  public:
  static int sumSubarrayMins(const vi& arr) {
    const auto n = CI(arr.size());
    const auto ltl = ClosestLTEL(arr);
    const auto ltr = ClosestLTR(arr);
    
    ll res = 0;
    FOR(i, 0, n-1) {
      const auto l_cnt = i - ltl[i];
      const auto r_cnt = ltr[i] - i;
      const auto sub_cnt = ModMult(CL(l_cnt), CL(r_cnt), MOD);
      const auto sub_sum = ModMult(sub_cnt, CL(arr[i]), MOD);
      res = ModSum(res, sub_sum, MOD);
    }

    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi arr{3,1,2,4};
    const auto a_out = Solution::sumSubarrayMins(arr);
    assert(a_out == 17);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi arr{11,81,94,43,3};
    const auto a_out = Solution::sumSubarrayMins(arr);
    assert(a_out == 444);

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
