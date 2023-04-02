#include <cassert>
#include <iostream>
#include <vector>

class Solution {
 public:
  static std::vector<int> getRow(int row_idx) {
    if (row_idx == 0) {
      return {1};
    }
    std::vector<int> row{1,1};
    int i = 1;
    while (i < row_idx) {
      ++i;
      std::vector<int> next_row(row.size()+1, 1);
      for (size_t j = 1; j < row.size(); ++j) {
        next_row[j] = row[j-1] + row[j];
      }
      row = std::move(next_row);
    }

    return row;
  }
};

int main() {
  {
    const std::vector<int> expected{1,3,3,1};
    assert(Solution::getRow(3) == expected);
  }
  {
    const std::vector<int> expected{1};
    assert(Solution::getRow(0) == expected);
  }
  {
    const std::vector<int> expected{1,1};
    assert(Solution::getRow(1) == expected);
  }
}
