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
using ii [[maybe_unused]] = std::pair<int, int>;
using vi [[maybe_unused]] = std::vector<int>;
using vl [[maybe_unused]] = std::vector<ll>;
using vvi [[maybe_unused]] = std::vector<vi>;
using vvvi [[maybe_unused]] = std::vector<vvi>;
using vvl [[maybe_unused]] = std::vector<vl>;
using vii [[maybe_unused]] = std::vector<ii>;
using vb [[maybe_unused]] = std::vector<bool>;
using vd [[maybe_unused]] = std::vector<double>;
using vs [[maybe_unused]] = std::vector<std::string>;
using vc [[maybe_unused]] = std::vector<char>;

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

constexpr int MAX_N = 200;
std::array<std::array<int, MAX_N>, MAX_N> vis;

class Solution {
public:
  void solve(std::vector<std::vector<char>>& board) {
    const auto m = SZ(board), n = SZ(board[0]);
    FOR(i, 0, m-1) std::fill(vis[i].begin(), vis[i].begin() + n, 0);

    std::queue<ii> q;
    FOR(i, 0, m-1) {
      if (board[i][0] == 'O' && !vis[i][0]) {
        vis[i][0] = 1;
        q.emplace(i, 0);
      }
      if (board[i][n-1] == 'O' && !vis[i][n-1]) {
        vis[i][n-1] = 1;
        q.emplace(i, n-1);
      }
    }
    FOR(j, 0, n-1) {
      if (board[0][j] == 'O' && !vis[0][j]) {
        vis[0][j] = 1;
        q.emplace(0, j);
      }
      if (board[m-1][j] == 'O' && !vis[m-1][j]) {
        vis[m-1][j] = 1;
        q.emplace(m-1, j);
      }
    }

    while (!q.empty()) {
      const auto [i, j] = q.front();
      q.pop();
      for (const auto& [ui, uj] : std::array<ii, 4>{ii{i-1, j}, ii{i+1, j}, ii{i, j-1}, ii{i, j+1}}) {
        if (ui >= 0 && ui < m && uj >= 0 && uj < n && board[ui][uj] == 'O' && !vis[ui][uj]) {
          vis[ui][uj] = 1;
          q.emplace(ui, uj);
        }
      }
    }
    FOR(i, 0, m-1) {
      FOR(j, 0, n-1) {
        if (board[i][j] == 'O' && !vis[i][j])
          board[i][j] = 'X';
      }
    }
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
