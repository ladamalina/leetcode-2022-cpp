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

bool Check(const std::string& s) {
  const auto n = static_cast<int>(s.size());
  if (n==0)
    return true;
  auto l = s.begin();
  auto r = std::prev(s.end());
  while (l < r && *l == *r) {
    ++l; --r;
  }
  return l>=r || (l+1==r && *l == *r);
}

class Solution {
 public:
  static std::string firstPalindrome(const std::vector<std::string>& words) {
    const auto it = std::find_if(words.begin(), words.end(),
                                 [&](const std::string& w) { return Check(w); });
    return (it == words.end()) ? ""s : *it;
  }
};

[[maybe_unused]] void TestSolution() {
  /*{
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi blacklist{1,2,3,4,5};
    const Solution obj(6, blacklist);
    vi a_out;
    FOR(i, 1, 10) {
      a_out.push_back(obj.pick());
    }
    const vi e_out{0,0,0,0,0,0,0,0,0,0};
    assert(a_out == e_out);

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
