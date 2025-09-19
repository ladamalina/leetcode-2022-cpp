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
#define SZ(_v) static_cast<int>((_v).size())
#define F first
#define S second

constexpr int MAX_N = 30;
std::array<std::array<int,MAX_N>,MAX_N> dist;

class Solution {
public:
  int shortestPathAllKeys(const vs& g) {
    const auto n = SZ(g), m = SZ(g[0]);
    
    auto n_keys = 0, init_i = 0, init_j = 0;
    FOR(i, 0, n-1) {
      FOR(j, 0, m-1) {
        n_keys += ('a' <= g[i][j] && g[i][j] <= 'z');
        if (g[i][j] == '@') {
          init_i = i; init_j = j;
        }
      }
    }

    vi ord(n_keys), has(n_keys);
    std::iota(RNG(ord), 0);
    auto min_res = INT_MAX;
    do {
      std::fill(RNG(has), 0);
      auto res = 0, i0 = init_i, j0 = init_j;;
      for (const auto ki : ord) {
        std::fill(&dist[0][0], &dist[0][0] + sizeof(dist) / sizeof(dist[0][0]), INT_MAX);
        std::queue<std::pair<int,ii>> q;
        q.emplace(0, ii{i0, j0});
        while (!q.empty()) {
          const auto d = q.front().F, i = q.front().S.F, j = q.front().S.S;
          q.pop();
          if (d >= dist[i][j])
            continue;
          dist[i][j] = d;
          if (g[i][j] == static_cast<char>('a' + ki)) {
            has[ki] = 1;
            res += d;
            i0 = i;
            j0 = j;
            break;
          }
          for (const auto& [ui, uj] : std::array<ii,4>{ii{i+1,j},ii{i-1,j},ii{i,j+1},ii{i,j-1}}) {
            if (0 <= ui && ui < n && 0 <= uj && uj < m && g[ui][uj] != '#') {
              if ('A' <= g[ui][uj] && g[ui][uj] <= 'Z' && !has[g[ui][uj] - 'A']) // a lock
                continue;
              if (d + 1 < dist[ui][uj])
                q.emplace(d + 1, ii{ui, uj});
            }
          }
        }
        if (!has[ki] || res >= min_res)
          break;
      }
      if (std::find(RNG(has), 0) == has.end())
        min_res = std::min(min_res, res);
      
    } while (std::next_permutation(RNG(ord)));

    return (min_res == INT_MAX) ? -1 : min_res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vs g{"@.a..","###.#","b.A.B"};
    const auto a_out = Solution().shortestPathAllKeys(g);
    assert(a_out == 8);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vs g{"@..aA","..B#.","....b"};
    const auto a_out = Solution().shortestPathAllKeys(g);
    assert(a_out == 6);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vs g{"@Aa"};
    const auto a_out = Solution().shortestPathAllKeys(g);
    assert(a_out == -1);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vs g{".##......#.#f.....#.....#..#..","....#.....#..##......c..e#....",".....#..........#.....#..##.#.","..#..##.#...#..#.......##.##.#","##......#..#......#....##..#..",".#.#........#...#..#...#....#.","......#.##...#......#.......#.",".###.#.##.#..##.......#.......","..#...#.....D.#####....#......",".####.#.....#.#.##....#.....#.",".........##.................#.","#..........#.#..#.............","....##.#..##...#.....#..#.#...","...#...#.#..A....#..#..#.##..#","#.#...#...###.##...E.#....#...",".#...#....#.####....#..#.#....","..#......##..#......#B......##","..##..#.#.#...#.#....#........",".....#..###....#.....#d.#..#..",".#...@.#..##..#..#.....#....#.","#.#.....###...#...#.#.#..#..##","#..#.......#............#.....","....#..#..###.#........a......",".....#....b.......#.......#...","##...#...#..#..#.#..#...#.#.#C","....#....#.....#..#....#..#..#","......#.#...........#...#..#..","....#...#..##.#..###.#..F.....","....#..........#.#............",".##.....##.#..............#..."};
    const auto a_out = Solution().shortestPathAllKeys(g);
    assert(a_out == 64);
  
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
