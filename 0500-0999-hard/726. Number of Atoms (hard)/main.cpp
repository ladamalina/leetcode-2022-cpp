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

using Freq = std::unordered_map<std::string, int>;
using Atom = std::pair<std::string, int>;

std::pair<Atom, int> ParseAtom(int i, int n, const std::string& s) {
  std::string a;
  a += s[i];
  ++i;
  while (i < n && 'a' <= s[i] && s[i] <= 'z') {
    a += s[i];
    ++i;
  }
  std::string c;
  while (i < n && '0' <= s[i] && s[i] <= '9') {
    c += s[i];
    ++i;
  }
  const auto cnt = c.empty() ? 1 : std::stoi(c);
  return {{a, cnt}, i};
}

std::pair<int, int> ParseCnt(int i, int n, const std::string& s) {
  std::string c;
  while (i < n && '0' <= s[i] && s[i] <= '9') {
    c += s[i];
    ++i;
  }
  const auto cnt = c.empty() ? 1 : std::stoi(c);
  return {cnt, i};
}

Freq operator+(Freq& freq, const Atom& atom) {
  freq[atom.F] += atom.S;
  return freq;
}

Freq operator+(Freq& freq_l, const Freq& freq_r) {
  for (const auto& [a, cnt] : freq_r) {
    freq_l[a] += cnt;
  }
  return freq_l;
}

Freq operator*(Freq& freq, int m) {
  for (auto& [_, cnt] : freq) {
    cnt *= m;
  }
  return freq;
}

std::pair<Freq, int> Rec(int i, int n, const std::string& s) {
  Freq freq;
  if (i == n)
    return {freq, i};
  while (i < n) {
    if (s[i] == '(') {
      auto sub_freq = Rec(i+1, n, s);
      i = sub_freq.S;
      if (i < n && s[i] == ')') {
        const auto sub_cnt = ParseCnt(i+1, n, s);
        if (sub_cnt.F > 1)
          sub_freq.F = sub_freq.F * sub_cnt.F;
        i = sub_cnt.S;
      }
      freq = freq + sub_freq.F;
      continue;
    }
    if (s[i] == ')') {
      return {freq, i};
    }
    const auto atom_res = ParseAtom(i, n, s);
    freq = freq + atom_res.F;
    i = atom_res.S;
  }
  return {freq, i};
}

class Solution {
 public:
  static std::string countOfAtoms(const std::string& s) {
    const auto n = CI(s.size());
    const auto freq_res = Rec(0, n, s);
    std::vector<std::pair<std::string, int>> res_vec;
    for (const auto& [a, cnt] : freq_res.F) {
      res_vec.emplace_back(a, cnt);
    }
    SORT(res_vec);
    std::string res_str;
    for (const auto& [a, cnt] : res_vec) {
      res_str += a;
      if (cnt > 1)
        res_str += std::to_string(cnt);
    }
    return res_str;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto e_out = Solution::countOfAtoms("H2O");
    assert(e_out == "H2O");

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto e_out = Solution::countOfAtoms("Mg(OH)2");
    assert(e_out == "H2MgO2");

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto e_out = Solution::countOfAtoms("K4(ON(SO3)2)2");
    assert(e_out == "K4N2O14S4");

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
