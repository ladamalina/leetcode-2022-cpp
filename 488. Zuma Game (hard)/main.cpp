// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;
using vi [[maybe_unused]] = std::vector<int>;

class Solution {
  public:
  static int findMinStep(const std::string& board, const std::string& hand) {
    const auto hand_sz = static_cast<int>(hand.size());
    
    vi h_freq(26);
    for (const auto h : hand) {
      ++h_freq[h-'A'];
    }
    std::unordered_map<std::string, int> memo;

    const auto serialize_freq = [&]() {
      std::string t;
      t.reserve(5);
      for (int i = 0; i < 26; ++i) {
        if (h_freq[i] > 0)
          t += std::string(h_freq[i], static_cast<char>('A'+i));
      }
      return t;
    };

    std::function<std::string(std::string&,int)> cut_eq_pos = [&](std::string& s, int i) {
      const auto n = static_cast<int>(s.size());
      auto b_pos = i;
      while (b_pos-1>=0 && s[b_pos-1] == s[b_pos]) --b_pos;
      auto e_pos = i+1;
      while (e_pos < n && s[e_pos-1] == s[e_pos]) ++e_pos;
      if (e_pos - b_pos >= 3) {
        s = s.substr(0, b_pos) + ((e_pos < n) ? s.substr(e_pos, n-e_pos) : ""s);
        return cut_eq_pos(s, b_pos);
      }
      return s;
    };
    
    std::function<int(std::string,int)> rec = [&](const std::string& b, int add) {
      if (b.empty())
        return add;
      if (add == hand_sz)
        return INT_MAX;
      
      const auto memo_key = b + "#" + serialize_freq();
      if (memo.contains(memo_key))
        return memo.at(memo_key);
      memo[memo_key] = INT_MAX;
      auto& res = memo[memo_key];

      const auto n = static_cast<int>(b.size());
      for (int ch_i = 0; ch_i < 26; ++ ch_i) {
        if (h_freq[ch_i] == 0) continue;
        const auto h_ch = static_cast<char>('A'+ch_i);
        for (int bi = 0; bi <= n; ++bi) {
          bool to_try = false;
          if (bi == 0) to_try = true;
          else if (bi > 0 && bi < n && b[bi-1] != b[bi] && b[bi] == h_ch) to_try = true;
          else if (bi > 0 && bi < n && b[bi-1] == b[bi] && b[bi] != h_ch) to_try = true;
          if (!to_try) continue;

          auto b_upd = b;
          b_upd.insert(b_upd.begin()+bi, h_ch);
          b_upd = cut_eq_pos(b_upd, bi);
          --h_freq[ch_i];
          const auto sub_res = rec(b_upd, add+1);
          res = std::min(res, sub_res);
          ++h_freq[ch_i];
        }
      }
      
      return res;
    };
    const auto res = rec(board, 0);
    return res == INT_MAX ? -1 : res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::string board{"WRRBBW"s};
    const std::string hand{"RB"s};
    const auto a_out = Solution::findMinStep(board, hand);
    assert(a_out == -1);
    
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::string board{"WWRRBBWW"s};
    const std::string hand{"WRBRW"s};
    const auto a_out = Solution::findMinStep(board, hand);
    assert(a_out == 2);
    
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::string board{"G"s};
    const std::string hand{"GGGGG"s};
    const auto a_out = Solution::findMinStep(board, hand);
    assert(a_out == 2);
    
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::string board{"RRWWRRBBRR"s};
    const std::string hand{"WB"s};
    const auto a_out = Solution::findMinStep(board, hand);
    assert(a_out == 2);
    
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::string board{"RRGGBBYYWWRRGGBB"s};
    const std::string hand{"RGBYW"s};
    const auto a_out = Solution::findMinStep(board, hand);
    assert(a_out == -1);
    
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
