#include <cassert>

class Solution {
 public:
  int numTrees(int n) {
    return numTreesInRange(1, n);
  }
 private:
  int numTreesInRange(int n_min, int n_max) {
    int range = n_max - n_min;
    if (range < 0) {
      return 0;
    }
    if (range == 0) {
      return 1;
    }
    if (range == 1) {
      return 2;
    }
    // len [n_min, n_max] >= 3
    int subtrees_num = 0;
    for (int n_med = n_min; n_med <= n_max; ++n_med) {
      auto left_subtrees_num = numTreesInRange(n_min, n_med-1);
      auto right_subtrees_num = numTreesInRange(n_med+1, n_max);
      if (left_subtrees_num >= 1 && right_subtrees_num >= 1) {
        subtrees_num += left_subtrees_num * right_subtrees_num;
      } else {
        subtrees_num += left_subtrees_num + right_subtrees_num;
      }
    }
    return subtrees_num;
  }
};

int main() {
  assert(Solution().numTrees(3) == 5);
  assert(Solution().numTrees(1) == 1);

  return 0;
}
