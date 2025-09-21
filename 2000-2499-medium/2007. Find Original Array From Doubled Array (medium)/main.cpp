#include <cassert>
#include <set>
#include <unordered_set>
#include <vector>

class Solution {
 public:
  static std::vector<int> findOriginalArray(std::vector<int>& changed) {
    if (changed.size() % 2) {
      return {};
    }
    std::vector<int> original;
    original.reserve(changed.size() / 2);

    std::unordered_multiset<int> original_nums;
    std::unordered_multiset<int> unknown_even_nums;
    int zeroes_count = 0;
    for (const int num : changed) {
      if (num % 2) { // num is odd
        int doubled_num = num * 2;
        auto unknown_even_it = unknown_even_nums.find(doubled_num);
        if (unknown_even_it != unknown_even_nums.end()) { // changes contains num * 2
          original.push_back(num);
          unknown_even_nums.erase(unknown_even_it);
        } else { // new odd without pair
          original_nums.insert(num);
        }
        continue;
      } // num is even

      if (num == 0) {
        ++zeroes_count;
        continue;
      }

      int half_num = num / 2;
      if (half_num % 2) { // num == odd * 2
        auto original_it = original_nums.find(half_num);
        if (original_it != original_nums.end()) { // half of num found
          original.push_back(half_num);
          original_nums.erase(original_it);
        } else { // new even without pair
          unknown_even_nums.insert(num);
        }
        continue;
      } // num == even * 2

      unknown_even_nums.insert(num);
    }
    if (!original_nums.empty()) {
      return {};
    } // all the odds have pair
    if (zeroes_count % 2) { // odd number of zeroes
      return {};
    } else {
      original.insert(original.end(), zeroes_count/2, 0);
    }
    if (unknown_even_nums.empty()) { // all the evens have pair
      return original;
    }
    std::multiset<int> left_even_nums(unknown_even_nums.begin(), unknown_even_nums.end());
    while (!left_even_nums.empty()) {
      auto min_num = *left_even_nums.begin();
      auto doubled_num_it = left_even_nums.find(min_num * 2);
      if (doubled_num_it == left_even_nums.end()) {
        return {};
      }
      original.push_back(min_num);
      left_even_nums.erase(doubled_num_it);
      left_even_nums.erase(left_even_nums.begin());
    }
    return original;
  }
};

int main() {
  {
    std::vector<int> changed{1,3,4,2,6,8};
    std::vector<int> expected_original{1,3,4};
    auto original = Solution::findOriginalArray(changed);
    std::sort(original.begin(), original.end());
    assert(original == expected_original);
  }
  {
    std::vector<int> changed{6,3,0,1};
    std::vector<int> expected_original{};
    auto original = Solution::findOriginalArray(changed);
    std::sort(original.begin(), original.end());
    assert(original == expected_original);
  }
  {
    std::vector<int> changed{1};
    std::vector<int> expected_original{};
    auto original = Solution::findOriginalArray(changed);
    std::sort(original.begin(), original.end());
    assert(original == expected_original);
  }
  {
    std::vector<int> changed{0,3,2,4,6,0};
    std::vector<int> expected_original{0,2,3};
    auto original = Solution::findOriginalArray(changed);
    std::sort(original.begin(), original.end());
    assert(original == expected_original);
  }
  {
    std::vector<int> changed{1,2,3,2,4,6,2,4,6,4,8,12};
    std::vector<int> expected_original{1,2,2,3,4,6};
    auto original = Solution::findOriginalArray(changed);
    std::sort(original.begin(), original.end());
    assert(original == expected_original);
  }
}
