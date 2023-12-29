//#pragma GCC optimize("O3")
//#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;

using ll = long long;
using ld = long double;
using ull = unsigned long long;
using ii [[maybe_unused]] = std::pair<int, int>;
using pll [[maybe_unused]] = std::pair<ll, ll>;
using pdd [[maybe_unused]] = std::pair<double, double>;
using vi [[maybe_unused]] = std::vector<int>;
using vvi [[maybe_unused]] = std::vector<vi>;
using vvvi [[maybe_unused]] = std::vector<vvi>;
using vii [[maybe_unused]] = std::vector<ii>;
using vb [[maybe_unused]] = std::vector<bool>;

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

using VChar = std::vector<char>;
using VVChar = std::vector<VChar>;

class Solution {
  public:
  static void solveSudoku(VVChar& board) {
    vi row_masks(9);
    vi col_masks(9);
    vvi block_masks(3, vi(3));
    vii free_cells;
    FOR(i, 0, 8) {
      FOR(j, 0, 8) {
        if (board[i][j] != '.') {
          row_masks[i] |= (1<<(board[i][j]-'0'));
          col_masks[j] |= (1<<(board[i][j]-'0'));
          block_masks[i/3][j/3] |= (1<<(board[i][j]-'0'));
        } else {
          free_cells.emplace_back(i, j);
        }
      }
    }
    const auto free_cells_n = CI(free_cells.size());

    std::function<bool(int)> rec = [&](int idx) {
      if (idx == free_cells_n) return true;
      const auto i = free_cells[idx].F;
      const auto j = free_cells[idx].S;
      const auto used_mask = row_masks[i] | col_masks[j] | block_masks[i/3][j/3];
      FOR(k, 1, 9) {
        if (used_mask & (1<<k)) continue;
        board[i][j] = char('0'+k);
        row_masks[i] |= (1<<k);
        col_masks[j] |= (1<<k);
        block_masks[i/3][j/3] |= (1<<k);

        auto sub_res = rec(idx+1);
        if (sub_res) return true;

        board[i][j] = '.';
        row_masks[i] &= ~(1<<k);
        col_masks[j] &= ~(1<<k);
        block_masks[i/3][j/3] &= ~(1<<k);
      }
      return false;
    };
    rec(0);
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    std::vector<std::vector<char>> board{
      {'5','3','.','.','7','.','.','.','.'},
      {'6','.','.','1','9','5','.','.','.'},
      {'.','9','8','.','.','.','.','6','.'},
      {'8','.','.','.','6','.','.','.','3'},
      {'4','.','.','8','.','3','.','.','1'},
      {'7','.','.','.','2','.','.','.','6'},
      {'.','6','.','.','.','.','2','8','.'},
      {'.','.','.','4','1','9','.','.','5'},
      {'.','.','.','.','8','.','.','7','9'}
    };
    std::vector<std::vector<char>> e_out{
      {'5','3','4','6','7','8','9','1','2'},
      {'6','7','2','1','9','5','3','4','8'},
      {'1','9','8','3','4','2','5','6','7'},
      {'8','5','9','7','6','1','4','2','3'},
      {'4','2','6','8','5','3','7','9','1'},
      {'7','1','3','9','2','4','8','5','6'},
      {'9','6','1','5','3','7','2','8','4'},
      {'2','8','7','4','1','9','6','3','5'},
      {'3','4','5','2','8','6','1','7','9'}
    };
    Solution::solveSudoku(board);
    assert(board == e_out);
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    std::vector<std::vector<char>> board{
      {'.','.','9','7','4','8','.','.','.'},
      {'7','.','.','.','.','.','.','.','.'},
      {'.','2','.','1','.','9','.','.','.'},
      {'.','.','7','.','.','.','2','4','.'},
      {'.','6','4','.','1','.','5','9','.'},
      {'.','9','8','.','.','.','3','.','.'},
      {'.','.','.','8','.','3','.','2','.'},
      {'.','.','.','.','.','.','.','.','6'},
      {'.','.','.','2','7','5','9','.','.'}
    };
    std::vector<std::vector<char>> e_out{
      {'5','1','9','7','4','8','6','3','2'},
      {'7','8','3','6','5','2','4','1','9'},
      {'4','2','6','1','3','9','8','7','5'},
      {'3','5','7','9','8','6','2','4','1'},
      {'2','6','4','3','1','7','5','9','8'},
      {'1','9','8','5','2','4','3','6','7'},
      {'9','7','5','8','6','3','1','2','4'},
      {'8','3','2','4','9','1','7','5','6'},
      {'6','4','1','2','7','5','9','8','3'}
    };
    Solution::solveSudoku(board);
    assert(board == e_out);
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
