#include <bits/stdc++.h>

using namespace std::literals;

using ll = long long;
using ii [[maybe_unused]] = std::pair<int, int>;
using vi [[maybe_unused]] = std::vector<int>;
using vl [[maybe_unused]] = std::vector<ll>;
using vvi [[maybe_unused]] = std::vector<vi>;
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
#define F first
#define S second

ii Rec(int s1i, int s2i, const std::string& s1, int s1n, const std::string& s2, int s2n) {
  if (s2i == s2n)
    return {s1i, 0};

  auto it = std::find(s1.begin()+s1i, s1.end(), s2[s2i]);
  if (it != s1.end()) {
    const auto next_s1i = CI(it - s1.begin());
    const auto sub_res = Rec(next_s1i+1, s2i+1, s1, s1n, s2, s2n);
    return sub_res;
  }
  it = std::find(s1.begin(), s1.end(), s2[s2i]);
  const auto next_s1i = CI(it - s1.begin());
  const auto sub_res = Rec(next_s1i+1, s2i+1, s1, s1n, s2, s2n);
  return {sub_res.F, sub_res.S+1};
}

class Solution {
public:
  int getMaxRepetitions(const std::string& s1, int n1, const std::string& s2, int n2) {
    for (const auto c2 : s2) {
      const auto c_pos = s1.find(c2);
      if (c_pos == std::string::npos)
        return 0;
    }
    
    const auto s1n = CI(s1.size());
    const auto s2n = CI(s2.size());
    vii beg(s1n);
    FOR(s1i, 0, s1n-1) {
      beg[s1i] = Rec(s1i, 0, s1, s1n, s2, s2n);
    }

    int cnt1=1, cnt2=0;
    int i1 = 0;
    while (cnt1 <= n1) {
      if (i1 < s1n) {
        const auto next_i1 = beg[i1].F;
        const auto add_cnt1 = beg[i1].S;
        if (cnt1 + add_cnt1 <= n1) {
          i1 = next_i1;
          cnt1 += add_cnt1;
          ++cnt2;
        } else {
          break;
        }
      } else {
        i1 = 0;
        const auto next_i1 = beg[i1].F;
        const auto add_cnt1 = 1 + beg[i1].S;
        if (cnt1 + add_cnt1 <= n1) {
          i1 = next_i1;
          cnt1 += add_cnt1;
          ++cnt2;
        } else {
          break;
        }
      }
    }
    return cnt2/n2;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto s1 = "acb"s;
    const auto s2 = "ab"s;
    const auto a_out = Solution().getMaxRepetitions(s1, 4, s2, 2);
    assert(a_out == 2);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto s1 = "acb"s;
    const auto s2 = "acb"s;
    const auto a_out = Solution().getMaxRepetitions(s1, 1, s2, 1);
    assert(a_out == 1);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto s1 = "aaa"s;
    const auto s2 = "aa"s;
    const auto a_out = Solution().getMaxRepetitions(s1, 3, s2, 1);
    assert(a_out == 4);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto s1 = "baba"s;
    const auto s2 = "baab"s;
    const auto a_out = Solution().getMaxRepetitions(s1, 11, s2, 1);
    assert(a_out == 7);
  
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
