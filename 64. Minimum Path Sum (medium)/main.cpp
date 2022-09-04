#include <cassert>
#include <vector>

class Solution {
 public:
  int minPathSum(std::vector<std::vector<int>>& grid) {
    if (grid.size() == 1 && grid[0].size() == 1)
      return grid[0][0];
    int max_y = (int) grid.size() - 1;
    int max_x = (int) grid[0].size() - 1;
    int min_dim = std::min(max_x, max_y);

    // layer = 0
    int layer0 = 0;
    // horizontally
    for (int x = layer0+1; x <= max_x; ++x) {
      grid[layer0][x] = grid[layer0][x] + grid[layer0][x-1];
    }
    // vertically
    for (int y = layer0+1; y <= max_y; ++y) {
      grid[y][layer0] = grid[y][layer0] + grid[y-1][layer0];
    }

    for (int layer = 1; layer <= min_dim; ++layer) {
      grid[layer][layer] = grid[layer][layer] + std::min(grid[layer-1][layer], grid[layer][layer-1]);

      // horizontally
      for (int x = layer+1; x <= max_x; ++x) {
        grid[layer][x] = grid[layer][x] + std::min(grid[layer-1][x], grid[layer][x-1]);
      }
      // vertically
      for (int y = layer+1; y <= max_y; ++y) {
        grid[y][layer] = grid[y][layer] + std::min(grid[y-1][layer], grid[y][layer-1]);
      }
    }

    return grid[max_y][max_x];
  }
};

int main() {

  std::vector<std::vector<int>> obstacleGrid1 = {{1,3,1},
                                                 {1,5,1},
                                                 {4,2,1}};
  assert (Solution().minPathSum(obstacleGrid1) == 7);

  std::vector<std::vector<int>> obstacleGrid2 = {{1,2,3},{4,5,6}};
  assert (Solution().minPathSum(obstacleGrid2) == 12);

//  std::vector<std::vector<int>> obstacleGrid3 = {{1}};
//  assert (Solution().minPathSum(obstacleGrid3) == 1);
//
//  std::vector<std::vector<int>> obstacleGrid4 = {{1,1}};
//  assert (Solution().minPathSum(obstacleGrid4) == 2);

  return 0;
}
