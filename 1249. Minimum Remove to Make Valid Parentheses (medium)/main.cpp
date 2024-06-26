#include <bits/stdc++.h>

using namespace std::literals;

using ll [[maybe_unused]] = long long;
using ii [[maybe_unused]] = std::pair<int, int>;
using vii [[maybe_unused]] = std::vector<ii>;
using vi [[maybe_unused]] = std::vector<int>;
using vl [[maybe_unused]] = std::vector<ll>;
using vvi [[maybe_unused]] = std::vector<vi>;
using vvii [[maybe_unused]] = std::vector<vii>;
using vs [[maybe_unused]] = std::vector<std::string>;
using vvs [[maybe_unused]] = std::vector<vs>;
using vc [[maybe_unused]] = std::vector<char>;
using vvc [[maybe_unused]] = std::vector<vc>;

#define FOR(_i, _a, _b) for (int _i = (_a); _i <= (_b); ++(_i))
#define FORD(_i, _a, _b) for (int _i = (_a); _i >= (_b); --(_i))
#define RNG(_l) (_l).begin(), (_l).end()
#define SORT(_l) std::sort((_l).begin(), (_l).end())
#define CI(_v) static_cast<int>(_v)
#define CL(_v) static_cast<ll>(_v)
#define F first
#define S second

class Solution {
  public:
  static std::string minRemoveToMakeValid(const std::string& s) {
    std::string t;
    auto t_cnt = 0;
    for (const auto ch : s) {
      if (ch == '(') {
        ++t_cnt;
        t += ch;
      } else if (ch == ')') {
        if (t_cnt > 0) {
          --t_cnt;
          t += ch;
        }
      } else {
        t += ch;
      }
    }
    
    std::deque<char> t2;
    auto t2_cnt = 0;
    for (auto i=static_cast<int>(t.size())-1; i>=0; --i) {
      if (t[i] == ')') {
        ++t2_cnt;
        t2.push_front(t[i]);
      } else if (t[i] == '(') {
        if (t2_cnt > 0) {
          --t2_cnt;
          t2.push_front(t[i]);
        }
      } else {
        t2.push_front(t[i]);
      }
    }
    
    const std::string res(t2.begin(), t2.end());
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  /*{
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto a_out = Solution::makeGood("leEeetcode"s);
    assert(a_out == "leetcode"s);

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
