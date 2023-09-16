#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;

struct Node {
  int x, y, h;
  Node(int x_, int y_, int h_) : x(x_), y(y_), h(h_) {}
  bool operator>(const Node& other) const {
    return std::tie(h, x, y) > std::tie(other.h, other.x, other.y);
  }
};

const std::vector<std::pair<int, int>> DIRS{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

class Solution {
 public:
  int trapRainWater(std::vector<std::vector<int>>& heightMap) {
    auto n = static_cast<int>(heightMap.size());
    auto m = static_cast<int>(heightMap[0].size());

    std::priority_queue<Node, std::vector<Node>, std::greater<>> pq;
    std::vector<std::vector<bool>> visited(n, std::vector<bool>(m));
    {
      int i = 0;
      for (int j = 0; j < m; ++j) {
        pq.emplace(i, j, heightMap[i][j]);
        visited[i][j] = true;
      }
    }
    {
      int i = n-1;
      for (int j = 0; j < m; ++j) {
        pq.emplace(i, j, heightMap[i][j]);
        visited[i][j] = true;
      }
    }
    {
      int j = 0;
      for (int i = 0; i < n; ++i) {
        pq.emplace(i, j, heightMap[i][j]);
        visited[i][j] = true;
      }
    }
    {
      int j = m-1;
      for (int i = 0; i < n; ++i) {
        pq.emplace(i, j, heightMap[i][j]);
        visited[i][j] = true;
      }
    }

    int trapped = 0;
    int max_height = 0;
    while (!pq.empty()) {
      auto v = pq.top();
      pq.pop();
      max_height = std::max(v.h, max_height);
      for (const auto& d : DIRS) {
        auto x = v.x + d.first;
        auto y = v.y + d.second;
        if (x >= 0 && x < n && y >= 0 && y < m && !visited[x][y]) {
          auto h = heightMap[x][y];
          if (h < max_height) trapped += (max_height - h);
          pq.emplace(x, y, h);
          visited[x][y] = true;
        }
      }
    }
    
    return trapped;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    std::vector<std::vector<int>> input{
        {1,4,3,1,3,2},
        {3,2,1,3,2,4},
        {2,3,3,2,3,1},
    };
    int e_out = 4;
    auto start_t = std::chrono::high_resolution_clock::now();
    auto a_out = Solution().trapRainWater(input);
    auto end_t = std::chrono::high_resolution_clock::now();
    auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
    assert(a_out == e_out);
  }
  {
    std::vector<std::vector<int>> input{
        {3,3,3,3,3},
        {3,2,2,2,3},
        {3,2,1,2,3},
        {3,2,2,2,3},
        {3,3,3,3,3},
    };
    int e_out = 10;
    auto start_t = std::chrono::high_resolution_clock::now();
    auto a_out = Solution().trapRainWater(input);
    auto end_t = std::chrono::high_resolution_clock::now();
    auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
    assert(a_out == e_out);
  }
  std::cerr << "TestSolution OK"sv << std::endl;
}

int main() {
#ifndef NDEBUG
  TestSolution();
#endif
  return 0;
}
