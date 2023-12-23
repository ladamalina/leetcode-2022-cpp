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

template<typename T>
class SparseTable {
  public:
  explicit SparseTable(const std::vector<T>& a) {
    const auto n = CI(a.size());
    const auto h_max = 31 - __builtin_clz(n);
    rmq_ = std::vector<std::vector<T>>(h_max+1, std::vector<T>(n));
    rmq_[0] = a;
    FOR(h, 1, h_max) {
      FOR(i, 0, n-(1<<h)) {
        rmq_[h][i] = std::min(rmq_[h-1][i], rmq_[h-1][i+(1<<(h-1))]);
      }
    }
  }

  T GetMin(int l, int r) const {
    const auto len = r - l + 1;
    const auto h = 31 - __builtin_clz(len);
    return std::min(rmq_[h][l], rmq_[h][r-(1<<h)+1]);
  }

  private:
  std::vector<std::vector<T>> rmq_;
};

class Solution {
  public:
  static int longestValidParentheses(const std::string& s) {
    if (s.empty())
      return 0;
    const auto n = CI(s.size());
    std::unordered_map<int, vi> val_ids;
    vi a(n);
    FOR(i, 0, n-1) {
      if (i == 0) {
        a[i] = (s[i]=='(') ? 1 : -1;
      } else {
        a[i] = a[i-1] + ((s[i]=='(') ? 1 : -1);
      }
      val_ids[a[i]].PB(i);
    }
    const SparseTable rmq(a);
    int max_len = 0;
    FOR(i, 0, n-1) {
      if (s[i] == ')')
        continue;
      // s[i] == '('
      const auto pref_val = (i==0) ? 0 : a[i-1];
      const auto& ids = val_ids[pref_val];
      auto id_it = std::upper_bound(RNG(ids), i);
      while (id_it != ids.end()) {
        const auto min_val = rmq.GetMin(i, *id_it);
        if (min_val >= pref_val) {
          const auto len = *id_it - i + 1;
          max_len = std::max(max_len, len);
        } else break;
        ++id_it;
      }
    }
    return max_len;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    const std::string s("(()"s);
    assert(Solution::longestValidParentheses(s) == 2);
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    const std::string s(")()())"s);
    const auto a_out = Solution::longestValidParentheses(s);
    assert(a_out == 4);
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
