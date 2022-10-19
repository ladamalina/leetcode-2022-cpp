#include <cassert>
#include <iostream>
#include <set>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

class Solution {
 public:
  static std::vector<int> topKFrequent(const std::vector<int>& nums, int k) {
    std::unordered_map<int, int> all_freqs; // number -> frequency
    std::set<std::pair<int, int>> top_freqs; // top k of pair<frequency, number>
    for (const auto n : nums) {
      auto all_freqs_it = all_freqs.find(n);
      int old_freq = 0;
      int new_freq = 1;
      if (all_freqs_it == all_freqs.end()) { // new word
        ++all_freqs[n];
      } else { // duplicate number
        old_freq = all_freqs_it->second;
        ++all_freqs_it->second;
        new_freq = all_freqs_it->second;
      }
      auto top_freqs_it = top_freqs.find({old_freq, n});
      if (top_freqs_it != top_freqs.end()) {
        top_freqs.erase(top_freqs_it);
      }
      top_freqs.insert({new_freq, n});
      if (static_cast<int>(top_freqs.size()) > k) {
        top_freqs.erase(top_freqs.begin());
      }
    }

    std::vector<int> top_k_frequent;
    top_k_frequent.reserve(top_freqs.size());
    for (const auto& [freq, n] : top_freqs) {
      top_k_frequent.push_back(n);
    }

    return top_k_frequent;
  }
};

int main() {
  {
    const std::vector<int> nums{1,1,1,2,2,3};
    const int k = 2;
    const std::vector<int> expected{1,2};
    auto actual = Solution::topKFrequent(nums, k);
    std::sort(actual.begin(), actual.end());
    assert(actual == expected);
  }
  {
    const std::vector<int> nums{1};
    const int k = 1;
    const std::vector<int> expected{1};
    auto actual = Solution::topKFrequent(nums, k);
    std::sort(actual.begin(), actual.end());
    assert(actual == expected);
  }

  return 0;
}
