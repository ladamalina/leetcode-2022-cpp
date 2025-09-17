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

constexpr std::array<ii, 4> DIRS{ii{1,0},ii{-1,0},ii{0,1},ii{0,-1}};

bool DFS(int wi, int i, int j, int round, vvi& vis, int n, int m, const vvc& board, int wn, const std::string& word) {
  if (wi == wn)
    return true;
  if (i<0 || i>=n || j<0 || j>=m || word[wi] != board[i][j] || vis[i][j]==round)
    return false;
  vis[i][j] = round;
  for (const auto& d : DIRS) {
    if (DFS(wi+1, i+d.F, j+d.S, round, vis, n, m, board, wn, word))
      return true;
  }
  vis[i][j] = round-1;
  return false;
}

class Solution {
  public:
  static bool exist(const vvc& board, const std::string& word) {
    const auto n = CI(board.size());
    const auto m = CI(board[0].size());
    const auto wn = CI(word.size());
    vvi vis(n, vi(m));

    auto round = 0;
    FOR(i, 0, n-1) {
      FOR(j, 0, m-1) {
        const auto res = DFS(0, i, j, ++round, vis, n, m, board, wn, word);
        if (res)
          return true;
      }
    }
    return false;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvc board{{'A','B','C','E'},{'S','F','C','S'},{'A','D','E','E'}};
    const auto word = "ABCCED"s;
    const auto a_out = Solution::exist(board, word);
    assert(a_out);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvc board{{'A','B','C','E'},{'S','F','C','S'},{'A','D','E','E'}};
    const auto word = "SEE"s;
    const auto a_out = Solution::exist(board, word);
    assert(a_out);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvc board{{'A','B','C','E'},{'S','F','C','S'},{'A','D','E','E'}};
    const auto word = "ABCB"s;
    const auto a_out = Solution::exist(board, word);
    assert(!a_out);

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
