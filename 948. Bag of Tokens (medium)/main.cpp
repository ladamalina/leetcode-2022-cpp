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

int Rec(const vi& tokens, int l, int r, int n, int power, int score, const vi& psum) {
  while (l < n && l <= r && tokens[l] <= power) {
    power -= tokens[l];
    ++score;
    ++l;
  }

  if (l > r)
    return score;

  FOR(r_cnt, 1, score) {
    const auto ri = r - r_cnt + 1;
    const auto r_power = psum[r] - (ri>0 ? psum[ri-1] : 0);
    FOR(li, l+1, ri-1) {
      const auto l_cnt = li - l + 1;
      const auto l_power = psum[li] - psum[l-1];
      if (l_cnt > r_cnt && l_power <= power+r_power) {
        const auto sub_res = Rec(tokens, li+1, ri-1, n, power+r_power-l_power, score-r_cnt+l_cnt, psum);
        return sub_res;
      }
    }
  }
  return score;
}

class Solution {
public:
  static int bagOfTokensScore(vi& tokens, int power) {
    if (tokens.empty())
      return 0;
    const auto n = CI(tokens.size());

    SORT(tokens);
    int li = 0;
    int ri = n-1;
    int score = 0;

    vi psum(n);
    psum[0] = tokens[0];
    FOR(i, 1, n-1) psum[i] = psum[i-1] + tokens[i];

    // 0 1 2 3 4 5 6 7 8
    //   .             .

    const auto res = Rec(tokens, li, ri, n, power, score, psum);
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi tokens{26};
    const auto a_out = Solution::bagOfTokensScore(tokens, 51);
    assert(a_out == 1);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi tokens{100};
    const auto a_out = Solution::bagOfTokensScore(tokens, 50);
    assert(a_out == 0);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi tokens{200,100};
    const auto a_out = Solution::bagOfTokensScore(tokens, 150);
    assert(a_out == 1);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi tokens{100,200,300,400};
    const auto a_out = Solution::bagOfTokensScore(tokens, 200);
    assert(a_out == 2);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi tokens{245,449,2257,6538,665,624,9720,4226,8924,2165,4352,3580,1769,3288,9867,7473,3826,4092,2637,5313};
    const auto a_out = Solution::bagOfTokensScore(tokens, 7356);
    assert(a_out == 11);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  std::cerr << "TestSolution OK"sv << std::endl;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
#ifndef NDEBUG
  TestSolution();
#endif
  return 0;
}
