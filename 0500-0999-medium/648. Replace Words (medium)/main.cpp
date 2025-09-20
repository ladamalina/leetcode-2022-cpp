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

std::vector<std::string> Split(const std::string& text) {
  std::istringstream ss_in(text);
  std::vector<std::string> res;
  std::string w;
  while (ss_in >> w) {
    res.push_back(std::move(w));
  }
  return res;
}

class Solution {
public:
  std::string replaceWords(const vs& dict, const std::string& text_str) {
    const auto text_vec = Split(text_str);
    const int text_vec_n = text_vec.size();

    std::map<std::string_view, std::string_view> src_dst;
    for (const auto& w : text_vec) {
      src_dst[w] = w;
    }

    for (const auto& d : dict) {
      auto it = src_dst.upper_bound(d);
      while (it != src_dst.end() && it->first.starts_with(d)) {
        if (d.size() < it->second.size())
          it->second = d;
        ++it;
      }
    }

    std::ostringstream ss_out;
    for (const auto& w : text_vec) {
      ss_out << src_dst.at(w) << ' ';
    }
    auto res = ss_out.str();
    res.pop_back();
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  /*{
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().solve();
    assert(a_out == 6);
  
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
