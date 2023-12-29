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
using vvvi [[maybe_unused]] = std::vector<vvi>;
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
    // const auto h_max = std::ceil(std::log2(n));
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

std::string Construct(const std::string& s, int n, const vi& removed_ids) {
  const auto removed_n = CI(removed_ids.size());
  std::string t;
  int ri = 0;
  FOR(i, 0, n-1) {
    if (ri == removed_n || i != removed_ids[ri]) {
      t += s[i];
    } else {
      ++ri;
    }
  }
  return t;
}

void Rec(int i, int prev_b, int n, const std::string& s, const vi& balance, const SparseTable<int>& rmq,
         std::unordered_set<std::string>& res, int& min_removed_n, vi& removed_ids) {
  const auto removed_n = CI(removed_ids.size());
  if (i == n) {
    if (balance.back() + prev_b == 0) {
      if (removed_n < min_removed_n) {
        min_removed_n = removed_n;
        res = {Construct(s, n, removed_ids)};
      } else if (removed_n == min_removed_n) {
        res.insert(std::move(Construct(s, n, removed_ids)));
      }
    }
    return;
  } // i < n
  if (s[i] == '(') {
    const auto next_min_b = rmq.GetMin(i, n-1) + prev_b;
    if (next_min_b > 0) {
      // take
      Rec(i+1, prev_b, n, s, balance, rmq, res, min_removed_n, removed_ids);
      // remove
      removed_ids.PB(i);
      Rec(i+1, prev_b-1, n, s, balance, rmq, res, min_removed_n, removed_ids);
      removed_ids.pop_back();
    } else { // <= 0
      Rec(i+1, prev_b, n, s, balance, rmq, res, min_removed_n, removed_ids);
    }
  } else if (s[i] == ')') {
    const auto next_min_b = rmq.GetMin(i, n-1) + prev_b;
    if (next_min_b < 0) {
      // take
      if (i > 0 && balance[i-1] + prev_b > 0) {
        Rec(i+1, prev_b, n, s, balance, rmq, res, min_removed_n, removed_ids);
      }
      // remove
      removed_ids.PB(i);
      Rec(i+1, prev_b+1, n, s, balance, rmq, res, min_removed_n, removed_ids);
      removed_ids.pop_back();
    } else { // >= 0
      Rec(i+1, prev_b, n, s, balance, rmq, res, min_removed_n, removed_ids);
    }
  } else {
    Rec(i+1, prev_b, n, s, balance, rmq, res, min_removed_n, removed_ids);
  }
}

class Solution {
  public:
  static std::vector<std::string> removeInvalidParentheses(const std::string& s) {
    const auto n = CI(s.size());
    vi balance(n);
    balance[0] = s[0]=='(' ? 1 : (s[0] == ')' ? -1 : 0);
    FOR(i, 1, n-1) {
      balance[i] = balance[i-1] + (s[i]=='(' ? 1 : (s[i] == ')' ? -1 : 0));
    }
    const SparseTable rmq(balance);

    std::unordered_set<std::string> res;
    int min_removed_n = INT_MAX;
    vi removed_ids;
    Rec(0, 0, n, s, balance, rmq, res, min_removed_n, removed_ids);
    return {RNG(res)};
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    const std::string s("()())()"s);
    const std::vector<std::string> e_out{"(())()","()()()"};
    const auto a_out = Solution::removeInvalidParentheses(s);
    assert(a_out == e_out);
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    const std::string s("(a)())()"s);
    const std::vector<std::string> e_out{"(a())()","(a)()()"};
    const auto a_out = Solution::removeInvalidParentheses(s);
    assert(a_out == e_out);
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    const std::string s(")("s);
    const std::vector<std::string> e_out{""};
    const auto a_out = Solution::removeInvalidParentheses(s);
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
