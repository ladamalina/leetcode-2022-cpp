#include <cassert>
#include <queue>
#include <unordered_set>
#include <vector>

typedef std::pair<int, int> Point;
struct pair_hash {
  inline std::size_t operator()(const Point& v) const {
    return v.first * 31 + v.second;
  }
};

class Solution {
 public:
  int numIslands(std::vector<std::vector<char>>& grid) {
    collectOnes(grid);

    int total_islands = 0;
    auto start_point_it = ones.begin();
    while (start_point_it != ones.end()) {
      labelIsland(grid, *start_point_it);
      ++total_islands;
      start_point_it = ones.begin();
    }

    return total_islands;
  }

  void labelIsland(std::vector<std::vector<char>>& grid, const Point start_point) {
    std::queue<Point> points;
    points.push(start_point);
    while (!points.empty()) {
      auto point = points.front();
      points.pop();
      if (grid[point.first][point.second] == '1') {
        grid[point.first][point.second] = '2';
        ones.erase(point);
      } else
        continue;

      if (point.first + 1 < grid.size() && (grid[point.first + 1][point.second] == '1')) { // down
        points.push({point.first + 1, point.second});
      }

      if (point.second + 1 < grid[point.first].size() && (grid[point.first][point.second + 1] == '1')) { // right
        points.push({point.first, point.second + 1});
      }

      if (point.first - 1 >= 0 && (grid[point.first - 1][point.second] == '1')) { // up
        points.push({point.first - 1, point.second});
      }

      if (point.second - 1 >= 0 && (grid[point.first][point.second - 1] == '1')) { // left
        points.push({point.first, point.second - 1});
      }
    }
  }

  void collectOnes(std::vector<std::vector<char>>& grid) {
    for (auto it_y = grid.begin(); it_y < grid.end(); ++it_y) {
      for (auto it_x = it_y->begin(); it_x < it_y->end(); ++it_x) {
        if (*it_x == '1')
          ones.insert({(int) (it_y - grid.begin()),
                  (int) (it_x - it_y->begin())});
      }
    }
  }
private:
  std::unordered_set<Point, pair_hash> ones;
};

int main() {
  std::vector<std::vector<char>> grid1{{'1','1','1','1','0'},
                                       {'1','1','0','1','0'},
                                       {'1','1','0','0','0'},
                                       {'0','0','0','0','0'}};
  assert(Solution().numIslands(grid1) == 1);

  std::vector<std::vector<char>> grid2{{'1','1','0','0','0'},
                                       {'1','1','0','0','0'},
                                       {'0','0','1','0','0'},
                                       {'0','0','0','1','1'}};
  assert(Solution().numIslands(grid2) == 3);

  std::vector<std::vector<char>> grid3{{'1','1','1','1','1'},
                                       {'1','0','0','0','1'},
                                       {'1','0','1','0','1'},
                                       {'1','0','0','0','1'},
                                       {'1','1','1','1','1'}};
  assert(Solution().numIslands(grid3) == 2);

  return 0;
}
