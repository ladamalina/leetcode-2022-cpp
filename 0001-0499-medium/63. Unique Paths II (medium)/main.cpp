#include <cassert>
#include <vector>

class Solution {
public:
    int uniquePathsWithObstacles(std::vector<std::vector<int>>& obstacleGrid) {
        uint8_t targetX = obstacleGrid[0].size() - 1;
        uint8_t targetY = obstacleGrid.size() - 1;
        auto minD = std::min(targetX, targetY);

        if (obstacleGrid[0][0] == 1 || obstacleGrid[targetY][targetX] == 1)
            return 0;
        if (targetX == 0 && targetY == 0)
            return 1;

        for (uint8_t layer = 0; layer <= minD; ++layer) {
            for (uint8_t x = layer; x <= targetX; ++x) {
                if (x == 0 && layer == 0) {
                    obstacleGrid[layer][x] = 1;
                    continue;
                }
                if (obstacleGrid[layer][x] == 1) {
                    obstacleGrid[layer][x] = 0;
                    continue;
                }
                // obstacleGrid[layer][x] == 0

                // check left cell
                if (x - 1 >= 0)
                    obstacleGrid[layer][x] += obstacleGrid[layer][x - 1];

                // check top cell
                if (layer - 1 >= 0)
                    obstacleGrid[layer][x] += obstacleGrid[layer - 1][x];
            }

            for (uint8_t y = layer + 1; y <= targetY; ++y) {
                if (obstacleGrid[y][layer] == 1) {
                    obstacleGrid[y][layer] = 0;
                    continue;
                }
                // obstacleGrid[y][layer] == 0

                // check left cell
                if (layer - 1 >= 0)
                    obstacleGrid[y][layer] += obstacleGrid[y][layer - 1];

                // check top cell
                if (y - 1 >= 0)
                    obstacleGrid[y][layer] += obstacleGrid[y - 1][layer];
            }
        }


        return obstacleGrid[targetY][targetX];
    }
};

int main() {
    std::vector<std::vector<int>> obstacleGrid3 = {{0, 0}};
    assert (Solution().uniquePathsWithObstacles(obstacleGrid3) == 1);

    std::vector<std::vector<int>> obstacleGrid1 = {{0,0,0},
                                                   {0,1,0},
                                                   {0,0,0}};
    assert (Solution().uniquePathsWithObstacles(obstacleGrid1) == 2);

    std::vector<std::vector<int>> obstacleGrid2 = {{1}};
    assert (Solution().uniquePathsWithObstacles(obstacleGrid2) == 0);

    std::vector<std::vector<int>> obstacleGrid4 = {{0,0,0,0,0,1,0,1,0,0,0,0,1,0,0,0,0,0},
                                                   {0,0,0,0,0,0,1,0,0,0,0,1,0,1,0,1,0,0},
                                                   {1,0,0,0,0,0,1,0,0,0,0,0,1,0,1,1,0,1},
                                                   {0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
                                                   {0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
                                                   {0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0},
                                                   {0,0,0,0,0,1,0,0,0,0,1,1,0,1,0,0,0,0},
                                                   {1,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0},
                                                   {0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0},
                                                   {0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0},
                                                   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                                   {1,1,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0},
                                                   {0,0,1,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0},
                                                   {0,1,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0},
                                                   {0,0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1},
                                                   {0,1,0,1,0,1,0,0,0,0,0,0,0,1,0,0,0,0},
                                                   {0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1},
                                                   {1,0,1,1,0,0,0,0,0,0,1,0,1,0,0,0,1,0},
                                                   {0,0,0,1,0,0,0,0,1,1,1,0,0,1,0,1,1,0},
                                                   {0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                                   {0,1,1,0,0,1,0,0,0,0,0,0,0,1,1,0,0,0},
                                                   {0,0,0,0,0,0,1,0,1,0,0,1,0,1,1,1,0,0},
                                                   {0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,1,1},
                                                   {0,1,0,0,0,0,0,0,0,0,1,0,1,0,1,0,1,0},
                                                   {1,0,0,1,0,1,0,0,1,0,0,0,0,0,0,0,0,0},
                                                   {0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
                                                   {0,1,0,0,0,0,0,1,0,0,0,0,0,0,1,1,1,0},
                                                   {1,0,1,0,1,0,0,0,0,0,0,1,1,0,0,0,0,1},
                                                   {1,0,0,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0}};
    assert (Solution().uniquePathsWithObstacles(obstacleGrid4) == 13594824);

    return 0;
}
