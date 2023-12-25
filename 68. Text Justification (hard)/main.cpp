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

class Solution {
  public:
  static std::vector<std::string> fullJustify(const std::vector<std::string>& words, const int max_w) {
    const auto words_n = CI(words.size());

    vvi l_words(1);
    vi l_words_sums(1);
    {
      int lw_i = 0;
      int ls_i = 0;
      int l_used_len = 0;
      int wi = 0;
      while (wi < words_n) {
        const auto& w = words[wi];
        if (l_used_len == 0) {
          l_words[lw_i].PB(wi);
          l_words_sums[ls_i] += CI(w.size());
          l_used_len += CI(w.size());
          ++wi;
        } else if (l_used_len + 1 + CI(w.size()) <= max_w) {
          l_words[lw_i].PB(wi);
          l_words_sums[ls_i] += CI(w.size());
          l_used_len += 1 + CI(w.size());
          ++wi;
        } else {
          l_words.emplace_back();
          l_words_sums.emplace_back();
          ++lw_i;
          ++ls_i;
          l_used_len = 0;
        }
      }
    }

    const auto lines_n = CI(l_words_sums.size());
    std::vector<std::string> lines(lines_n);
    FOR(li, 0, lines_n-1) {
      auto& line = lines[li];
      const auto all_spaces_n = max_w - l_words_sums[li];
      const auto l_words_n = CI(l_words[li].size());
      if (l_words_n == 1) {
        line = words[l_words[li][0]] + std::string(all_spaces_n, ' ');
      } else if (li == lines_n-1) { // last line
        line += words[l_words[li][0]];
        FOR(i, 1, l_words_n-1) {
          line += ' ' + words[l_words[li][i]];
        }
        const auto left_spaces_n = max_w - CI(line.size());
        line += std::string(left_spaces_n, ' ');
      } else { // N words, not last line
        const auto spaces_div = all_spaces_n / (l_words_n-1);
        const auto spaces_mod = all_spaces_n % (l_words_n-1);
        const auto spaces_bg_str = std::string(spaces_div+1, ' ');
        const auto spaces_sm_str = std::string(spaces_div, ' ');
        line += words[l_words[li][0]];
        FOR(i, 1, l_words_n-1) {
          if (i <= spaces_mod) line += spaces_bg_str;
          else line += spaces_sm_str;
          line += words[l_words[li][i]];
        }
      }
    }
    return lines;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    const std::vector<std::string> words{"This", "is", "an", "example", "of", "text", "justification."};
    const std::vector<std::string> e_out{"This    is    an",
   "example  of text",
   "justification.  "};
    const auto a_out = Solution::fullJustify(words, 16);
    assert(a_out == e_out);
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    const std::vector<std::string> words{"What","must","be","acknowledgment","shall","be"};
    const std::vector<std::string> e_out{"What   must   be",
  "acknowledgment  ",
  "shall be        "};
    const auto a_out = Solution::fullJustify(words, 16);
    assert(a_out == e_out);
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    const std::vector<std::string> words{"Science","is","what","we","understand","well","enough","to","explain","to","a","computer.","Art","is","everything","else","we","do"};
    const std::vector<std::string> e_out{"Science  is  what we",
  "understand      well",
  "enough to explain to",
  "a  computer.  Art is",
  "everything  else  we",
  "do                  "};
    const auto a_out = Solution::fullJustify(words, 20);
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
