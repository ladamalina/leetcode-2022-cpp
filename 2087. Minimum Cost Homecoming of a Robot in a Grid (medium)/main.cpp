#include <cassert>
#include <chrono>
#include <numeric>
#include <iostream>
#include <vector>

class Solution {
public:
  static int minCost(std::vector<int>& startPos, std::vector<int>& homePos,
                     std::vector<int>& rowCosts, std::vector<int>& colCosts) {
    if (startPos[0] == homePos[0] && startPos[1] == homePos[1])
      return 0;

    int min_cost = 0;

    if (startPos[0] < homePos[0]) {
      auto endIt = rowCosts.end();
      if (homePos[0] + 1 < rowCosts.size())
        endIt = rowCosts.begin() + homePos[0] + 1;
      min_cost += std::accumulate(rowCosts.begin() + startPos[0] + 1, endIt, 0);
    } else if (startPos[0] > homePos[0]) {
      auto endIt = rowCosts.begin() + startPos[0];
      min_cost += std::accumulate(rowCosts.begin() + homePos[0], endIt, 0);
    }

    if (startPos[1] < homePos[1]) {
      auto endIt = colCosts.end();
      if (homePos[1] + 1 < colCosts.size())
        endIt = colCosts.begin() + homePos[1] + 1;
      min_cost += std::accumulate(colCosts.begin() + startPos[1] + 1, endIt, 0);
    } else if (startPos[1] > homePos[1]) {
      auto endIt = colCosts.begin() + startPos[1];
      min_cost += std::accumulate(colCosts.begin() + homePos[1], endIt, 0);
    }

    return min_cost;
  }
};

int main() {
  std::vector<int> startPos1{1,0};
  std::vector<int> homePos1{2,3};
  std::vector<int> rowCosts1{5,4,3};
  std::vector<int> colCosts1{8,2,6,7};
  assert(Solution::minCost(startPos1,homePos1,rowCosts1,colCosts1) == 18);

  std::vector<int> startPos2{5,5};
  std::vector<int> homePos2{5,2};
  std::vector<int> rowCosts2{7,1,3,3,5,3,22,10,23};
  std::vector<int> colCosts2{5,5,6,2,0,16};
  assert(Solution::minCost(startPos2,homePos2,rowCosts2,colCosts2) == 8);

  auto start = std::chrono::high_resolution_clock::now();
  std::vector<int> startPos3{29,65};
  std::vector<int> homePos3{6,73};
  std::vector<int> rowCosts3{7,1,4,8,10,7,4,5,3,6,4,1,0,1,10,0,8,3,3,2,6,0,7,0,9,6,9,1,10,6238,5418,5107,5181,5115,7168,
                             8546,9178,8007,6374,5264,9276,5572,9158,8094,9203,7925,8943,9064,8681,9631,7673,8044,7413,
                             5492,8080,8818,7211,6565,5148,6540,5720,6499,8002};
  std::vector<int> colCosts3{10,2,1,1,1,3,8,5,2,3,1,1,1,4,3,2,7,10,6,5,2,1,5,4,3,6,9,6,10,7,10,9,8,4,7,4,10,3,10,0,0,2,
                             0,5,9,4,9,4,1,7,2,9,0,3,1,6,10,4,4,4,0,10,6,10,0,8,5,1,10,3,5,8,0,9540,5989,8067,7913,9109,
                             9875,9844,7985,5393,7853,9586,8834,7008,8004,5243,6392,5258};
  assert(Solution::minCost(startPos3,homePos3,rowCosts3,colCosts3) == 9670);
  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = duration_cast<std::chrono::microseconds>(stop - start);
  std::cout << "duration: " << duration.count() << std::endl;

  return 0;
}
