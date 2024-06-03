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
#define PB push_back

int Rec(std::string_view word, const std::unordered_set<std::string_view>& w_set,
    std::unordered_map<std::string_view, int>& memo) {
  const auto w_len = CI(word.size());
  if (w_len == 0) return 0;
  if (memo.contains(word)) return memo[word];
  int max_res = -1;
  FOR(i, 0, w_len-1) {
    const auto pref = word.substr(0, i+1);
    if (w_set.contains(pref)) {
      const auto suff = word.substr(i+1, w_len-1-i);
      const auto sub_res = Rec(suff, w_set, memo);
      if (sub_res != -1) max_res = std::max(max_res, 1+sub_res);
      if (max_res >= 2) break;
    }
  }
  memo[word] = max_res;
  return max_res;
}

class Solution {
public:
  vs findAllConcatenatedWordsInADict(const vs& words) {
    const auto wn = CI(words.size());
    std::unordered_set<std::string_view> w_set(RNG(words));
    std::unordered_map<std::string_view, int> memo;

    vs res;
    FOR(wi, 0, wn-1) {
      const auto w_res = Rec(words[wi], w_set, memo);
      if (w_res > 1) {
        res.push_back(words[wi]);
      }
    }
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vs words{"cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"};
    auto a_out = Solution().findAllConcatenatedWordsInADict(words);
    SORT(a_out);
    const vs e_out{"catsdogcats","dogcatsdog","ratcatdogcat"};
    assert(a_out == e_out);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vs words{"cat","dog","catdog"};
    auto a_out = Solution().findAllConcatenatedWordsInADict(words);
    SORT(a_out);
    const vs e_out{"catdog"};
    assert(a_out == e_out);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vs words{"a","b","ab","abc"};
    auto a_out = Solution().findAllConcatenatedWordsInADict(words);
    SORT(a_out);
    const vs e_out{"ab"};
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
