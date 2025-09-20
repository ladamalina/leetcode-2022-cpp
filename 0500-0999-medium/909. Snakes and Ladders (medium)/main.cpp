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

constexpr int MAX_N = 20, MAX_X = MAX_N * MAX_N;
std::array<ii, MAX_X + 1> x_to_ij;
std::array<int, MAX_X + 1> dist;

class Solution {
public:
  int snakesAndLadders(const vvi& board) {
    const auto n = SZ(board), max_x = n * n;

    FOR(x, 1, max_x) {
      const auto i = (x - 1) / n, j = (x - 1) % n;
      x_to_ij[x] = (i & 1) ? ii{n - 1 - i, n - 1 - j} : ii{n - 1 - i, j};
    }

    std::fill(dist.begin(), dist.begin() + max_x + 1, INT_MAX);
    dist[1] = 0;
    std::priority_queue<ii, vii, std::greater<>> pq;
    pq.emplace(0, 1);
    while (!pq.empty()) {
      const auto [d, x] = pq.top(); pq.pop();
      for (auto dice = 1; x + dice <= std::min(max_x, x + 6); ++dice) {
        auto y = std::min(max_x, x + dice);
        const auto [yi, yj] = x_to_ij[y];
        if (board[yi][yj] != -1)
          y = board[yi][yj];
        if (d + 1 < dist[y]) {
          dist[y] = d + 1;
          pq.emplace(d + 1, y);
        }
      }
    }
    
    return dist[max_x] == INT_MAX ? -1 : dist[max_x];
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi board{{-1,-1,-1,-1,-1,-1},{-1,-1,-1,-1,-1,-1},{-1,-1,-1,-1,-1,-1},{-1,35,-1,-1,13,-1},{-1,-1,-1,-1,-1,-1},{-1,15,-1,-1,-1,-1}};
    const auto a_out = Solution().snakesAndLadders(board);
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
