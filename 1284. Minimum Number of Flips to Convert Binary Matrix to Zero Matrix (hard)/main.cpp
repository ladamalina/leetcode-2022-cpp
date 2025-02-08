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

std::array<int, 512> dist;

class Solution {
public:
  int minFlips(const vvi& mat) {
    const auto n = SZ(mat), m = SZ(mat[0]);

    const auto encode_pos = [&](const int i, const int j) {
      return i * m + j;
    };
    
    const auto decode_bit = [&](const int b) {
      return ii{b/m, b%m};
    };
    
    const auto encode_mat = [&](const vvi& g) {
      auto mask = 0;
      FOR(i, 0, n-1) {
        FOR(j, 0, m-1) {
          if (g[i][j]) {
            mask |= (1 << encode_pos(i,j));
          }
        }
      }
      return mask;
    };

    const auto flip = [&](const int mask, int b) {
      const auto [i, j] = decode_bit(b);
      auto x = (mask ^ (1<<b)); // инвертирует k-й бит x
      if (i-1 >= 0 && i-1 < n) {
        const auto k = encode_pos(i-1, j);
        x ^= (1<<k);
      }
      if (i+1 >= 0 && i+1 < n) {
        const auto k = encode_pos(i+1, j);
        x ^= (1<<k);
      }
      if (j-1 >= 0 && j-1 < m) {
        const auto k = encode_pos(i, j-1);
        x ^= (1<<k);
      }
      if (j+1 >= 0 && j+1 < m) {
        const auto k = encode_pos(i, j+1);
        x ^= (1<<k);
      }
      return x;
    };

    std::fill(RNG(dist), INT_MAX);
    std::priority_queue<ii, vii, std::greater<>> pq;
    pq.emplace(0, encode_mat(mat));
    while (!pq.empty()) {
      const auto d = pq.top().F, v = pq.top().S;
      pq.pop();
      if (d >= dist[v])
        continue;
      dist[v] = d;

      FOR(b, 0, n*m-1) {
        const auto u = flip(v, b);
        if (d + 1 < dist[u])
          pq.emplace(d + 1, u);
      }
    }

    return dist[0] == INT_MAX ? -1 : dist[0];
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi mat{{0,0},{0,1}};
    const auto a_out = Solution().minFlips(mat);
    assert(a_out == 3);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi mat{{0}};
    const auto a_out = Solution().minFlips(mat);
    assert(a_out == 0);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi mat{{1,0,0},{1,0,0}};
    const auto a_out = Solution().minFlips(mat);
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
