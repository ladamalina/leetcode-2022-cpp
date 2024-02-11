#include <bits/stdc++.h>

using namespace std::literals;

using ll [[maybe_unused]] = long long;
using ii [[maybe_unused]] = std::pair<int, int>;
using vii [[maybe_unused]] = std::vector<ii>;
using vi [[maybe_unused]] = std::vector<int>;
using vl [[maybe_unused]] = std::vector<ll>;
using vvi [[maybe_unused]] = std::vector<vi>;
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

constexpr int INF = 1e5;
constexpr int MAX_N = 50;
constexpr int MAX_T_LEN = 15;

using Mask = std::array<int, 26>;
using MemoItem = std::unordered_map<std::string, int>;
using Memo = std::array<MemoItem, MAX_N>;

Mask t_mask;
std::array<Mask, MAX_N> s_masks;
Memo memo;

void CalcMask(const std::string& s, Mask& mask) {
  memset(&mask, 0, sizeof(mask));
  for (const auto ch : s) {
    ++mask[ch-'a'];
  }
}

std::string HashMask(const Mask& mask) {
  std::string h;
  FOR(i, 0, 25) {
    FOR(j, 1, mask[i]) {
      h += char('a'+i);
    }
  }
  return h;
}

int Rec(int i, int stickers_n) {
  const auto hash_mask = HashMask(t_mask);
  if (i == stickers_n) {
    return hash_mask.empty() ? 0 : INF;
  }
  const auto it = memo[i].find(hash_mask);
  if (it != memo[i].end()) {
    return it->S;
  }
  
  const auto& s_mask = s_masks[i];

  // not take
  int res = Rec(i+1, stickers_n);

  // take
  int max_need = 0;
  FOR(j, 0, 25) {
    if (t_mask[j] > 0 && s_mask[j] > 0) {
      const auto need = (t_mask[j] % s_mask[j] == 0) ? t_mask[j]/s_mask[j] : t_mask[j]/s_mask[j] + 1;
      max_need = std::max(max_need, need);
    }
  }
  
  FOR(take_cnt, 1, max_need) {
    if (take_cnt >= res)
      break;
    FOR(j, 0, 25) {
      t_mask[j] -= s_mask[j] * take_cnt;
    }
    const auto sub_res = take_cnt + Rec(i+1, stickers_n);
    res = std::min(res, sub_res);
    FOR(j, 0, 25) {
      t_mask[j] += s_mask[j] * take_cnt;
    }
  }
  
  memo[i][hash_mask] = res;
  return res;
}

class Solution {
 public:
  static int minStickers(const vs& stickers, const std::string& target) {
    const auto stickers_n = CI(stickers.size());
    
    CalcMask(target, t_mask);
    FOR(i, 0, stickers_n-1) {
      CalcMask(stickers[i], s_masks[i]);
    }
    
    std::fill(memo.begin(), memo.begin()+stickers_n, MemoItem{});
    const auto res = Rec(0, stickers_n);
    return (res == INF) ? -1 : res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto a_out = Solution::minStickers({"with","example","science"}, "thehat");
    assert(a_out == 3);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto a_out = Solution::minStickers({"notice","possible"}, "basicbasic");
    assert(a_out == -1);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto a_out = Solution::minStickers({"city","would","feel","effect","cell","paint"}, "putcat");
    assert(a_out == 3);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vs stickers{"heavy","often","just","map","door","soil","surface","high","middle","noise","during","my","yes",
                      "sugar","ship","special","late","spell","receive","silent","would","person","since","children",
                      "cell","favor","choose","listen","then","finish","north","safe","molecule","wrong","mouth","dead",
                      "ask","such","trouble","protect","last","whether","dream","act","turn","double","push","happy",
                      "where","steam"};
    const std::string target{"strangefell"s};
    const auto a_out = Solution::minStickers(stickers, target);
    assert(a_out == 3);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vs stickers{"heavy","often","just","map","door","soil","surface","high","middle","noise","during","my","yes",
                      "sugar","ship","special","late","spell","receive","silent","would","person","since","children",
                      "cell","favor","choose","listen","then","finish","north","safe","molecule","wrong","mouth","dead",
                      "ask","such","trouble","protect","last","whether","dream","act","turn","double","push","happy",
                      "where","steam"};
    const std::string target{"strangefellouts"s};
    const auto a_out = Solution::minStickers(stickers, target);
    assert(a_out == 4);

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
