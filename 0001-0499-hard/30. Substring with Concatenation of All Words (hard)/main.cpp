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

class Solution {
public:
  vi findSubstring(const std::string& s, const vs& words) {
    const auto sn = CI(s.size());
    const auto wn = CI(words.size());
    const auto wl = CI(words[0].size());
    std::unordered_map<std::string, int> w_freq;
    for (const auto& w : words) {
      ++w_freq[w];
    }
    vi res;
    auto si = 0;
    while (si < sn) {
      auto wi = 0;
      while (wi < wn && si + wn*wl <= sn) {
        const auto it = w_freq.find(s.substr(si+wi*wl, wl));
        if (it != w_freq.end() && it->S) {
          --it->S;
          ++wi;
        } else break;
      }
      if (wi == wn) {
        res.push_back(si);
      }
      FOR(i, 0, wi-1) {
        const auto it = w_freq.find(s.substr(si+i*wl, wl));
        ++it->S;
      }
      ++si;
    }
    
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::string s{"barfoothefoobarman"};
    const vs words{"foo","bar"};
    const auto a_out = Solution().findSubstring(s, words);
    const vi e_out{0,9};
    assert(a_out == e_out);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::string s{"wordgoodgoodgoodbestword"};
    const vs words{"word","good","best","word"};
    const auto a_out = Solution().findSubstring(s, words);
    const vi e_out{};
    assert(a_out == e_out);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::string s{"barfoofoobarthefoobarman"};
    const vs words{"bar","foo","the"};
    const auto a_out = Solution().findSubstring(s, words);
    const vi e_out{6,9,12};
    assert(a_out == e_out);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::string s{"wordgoodgoodgoodbestword"};
    const vs words{"word","good","best","good"};
    const auto a_out = Solution().findSubstring(s, words);
    const vi e_out{8};
    assert(a_out == e_out);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::string s{"aaaaaaaaaaaaaa"};
    const vs words{"aa","aa"};
    const auto a_out = Solution().findSubstring(s, words);
    const vi e_out{0,1,2,3,4,5,6,7,8,9,10};
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
