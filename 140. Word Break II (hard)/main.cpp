// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;

using vi [[maybe_unused]] = std::vector<int>;
using vvi [[maybe_unused]] = std::vector<vi>;
using vs [[maybe_unused]] = std::vector<std::string>;
using vvs [[maybe_unused]] = std::vector<vs>;

#define FOR(_i, _a, _b) for (int _i = (_a); _i <= (_b); ++(_i))
#define FORD(_i, _a, _b) for (int _i = (_a); _i >= (_b); --(_i))
#define RNG(_l) (_l).begin(), (_l).end()
#define SORT(_l) std::sort((_l).begin(), (_l).end())
#define CI(_v) static_cast<int>(_v)

using Dict = std::unordered_map<std::string_view, int>;

void Apply(vs& res, const vi& sentence, const vs& dict_vec) {
  res.emplace_back();
  auto& s = res.back();
  FOR(i, 0, CI(sentence.size())-1) {
    if (i == 0) s += dict_vec[sentence[i]];
    else s += ' ' + dict_vec[sentence[i]];
  }
}

void Rec(int i, int n, const std::string_view s, const vs& dict_vec, const Dict& dict, vs& res, vi& sentence) {
  if (i == n) {
    Apply(res, sentence, dict_vec);
    return;
  }
  FOR(j, i, n-1) {
    const auto s_word = s.substr(i, j-i+1);
    const auto it = dict.find(s_word);
    if (it != dict.end()) {
      sentence.push_back(it->second);
      Rec(j+1, n, s, dict_vec, dict, res, sentence);
      sentence.pop_back();
    }
  }
}

class Solution {
 public:
  static vs wordBreak(const std::string& s, const vs& wordDict) {
    const auto n = CI(s.size());

    Dict dict;
    FOR(i, 0, CI(wordDict.size())-1) {
      dict[wordDict[i]] = i;
    }
    
    vs res;
    vi sentence;
    Rec(0, n, s, wordDict, dict, res, sentence);
    
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::string s{"catsanddog"s};
    const vs wordDict{"cat","cats","and","sand","dog"};
    auto a_out = Solution::wordBreak(s, wordDict);
    vs e_out{"cats and dog","cat sand dog"};
    SORT(a_out);
    SORT(e_out);
    assert(a_out == e_out);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::string s{"pineapplepenapple"s};
    const vs wordDict{"apple","pen","applepen","pine","pineapple"};
    auto a_out = Solution::wordBreak(s, wordDict);
    vs e_out{"pine apple pen apple","pineapple pen apple","pine applepen apple"};
    SORT(a_out);
    SORT(e_out);
    assert(a_out == e_out);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::string s{"catsandog"s};
    const vs wordDict{"cats","dog","sand","and","cat"};
    auto a_out = Solution::wordBreak(s, wordDict);
    vs e_out{};
    SORT(a_out);
    SORT(e_out);
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
