//#pragma GCC optimize("O3,unroll-loops")
// #include <bits/stdc++.h>

#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <deque>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <numeric>
#include <optional>
#include <random>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <variant>
#include <vector>

using namespace std::literals;

using ll = long long;
using ld = long double;
using ii = std::pair<int, int>;
using vi = std::vector<int>;
using vvi = std::vector<vi>;
using vvvi = std::vector<vvi>;
using vl = std::vector<ll>;
using vvl = std::vector<vl>;
using vvvl = std::vector<vvl>;
using vii = std::vector<ii>;
using vb = std::vector<bool>;
using vd = std::vector<ld>;
using vs = std::vector<std::string>;
using vc = std::vector<char>;
using vvc = std::vector<vc>;

#define FOR(_i, _a, _b) for (auto _i = (_a); _i <= (_b); ++(_i))
#define FORD(_i, _a, _b) for (auto _i = (_a); _i >= (_b); --(_i))
#define RNG(_l) (_l).begin(), (_l).end()
#define SORT(_l) std::sort((_l).begin(), (_l).end())
#define CI(_v) static_cast<int>(_v)
#define CL(_v) static_cast<ll>(_v)
#define CD(_v) static_cast<ld>(_v)
#define CC(_v) static_cast<char>(_v)
#define SZ(_v) static_cast<int>((_v).size())
#define F first
#define S second
#define PB push_back

std::array<int, 9> rows, cols, blocks;
std::array<ii, 81> dots;
int n_dots;

bool Rec(const int di, vvc& board) {
  if (di == n_dots) return true;
  const auto [i, j] = dots[di];
  const auto used_mask = rows[i] | cols[j] | blocks[i/3*3+j/3];
  FOR(k, 1, 9) {
    if (used_mask & (1 << k)) continue;
    board[i][j] = CC('0' + k);
    rows[i] |= (1 << k);
    cols[j] |= (1 << k);
    blocks[i/3*3+j/3] |= (1 << k);

    if (Rec(di + 1, board)) return true;

    board[i][j] = '.';
    rows[i] &= ~(1 << k);
    cols[j] &= ~(1 << k);
    blocks[i/3*3+j/3] &= ~(1 << k);
  }
  return false;
}

class Solution {
  public:
  static void solveSudoku(vvc& board) {
    std::fill(RNG(rows), 0);
    std::fill(RNG(cols), 0);
    std::fill(RNG(blocks), 0);
    n_dots = 0;
    FOR(i, 0, 8) {
      FOR(j, 0, 8) {
        if (board[i][j] != '.') {
          rows[i] |= (1 << (board[i][j] - '0'));
          cols[j] |= (1 << (board[i][j] - '0'));
          blocks[i/3*3+j/3] |= (1 << (board[i][j] - '0'));
        } else {
          dots[n_dots++] = {i, j};
        }
      }
    }
    [[maybe_unused]] const auto res = Rec(0, board);
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    vvc board{
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
    vvc e_out{
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
    vvc board{
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
    vvc e_out{
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
