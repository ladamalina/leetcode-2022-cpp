#include <cassert>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Solution {
public:
  static bool uniqueOccurrences(std::vector<int>& arr) {
    std::unordered_map<int , int> frequencies;
    std::for_each(arr.begin(), arr.end(), [&frequencies] (const int& n) { ++frequencies[n]; });

    std::unordered_set<int> uniq_frequencies;
    for (const auto& [n, freq] : frequencies) {
      if (uniq_frequencies.count(freq))
        return false;
      uniq_frequencies.insert(freq);
    }

    return true;
  }
};

int main() {
  std::vector v1{1,2,2,1,1,3};
  assert(Solution::uniqueOccurrences(v1));

  std::vector v2{1,2};
  assert(Solution::uniqueOccurrences(v2) == false);

  std::vector v3{-3,0,1,-3,1,1,1,-3,10,0};
  assert(Solution::uniqueOccurrences(v3));
}
