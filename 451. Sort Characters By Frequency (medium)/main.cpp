#include <cassert>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

class Solution {
 public:
  static std::string frequencySort(std::string& s) {
    std::unordered_map<char, int> all_freqs; // char -> frequency
    std::map<int, std::set<char>> sorted_freq; // freq -> set of chars

    for (const auto ch : s) {
      auto all_freqs_it = all_freqs.find(ch);
      int old_freq = 0;
      int new_freq = 1;
      if (all_freqs_it == all_freqs.end()) { // new word
        ++all_freqs[ch];
      } else { // duplicate number
        old_freq = all_freqs_it->second;
        ++all_freqs_it->second;
        new_freq = all_freqs_it->second;
      }
      auto sorted_freq_it = sorted_freq.find(old_freq);
      if (sorted_freq_it != sorted_freq.end()) {
        sorted_freq_it->second.erase(ch);
      }
      sorted_freq[new_freq].insert(ch);
    }

    int i = -1;
    for (auto sorted_freq_it = sorted_freq.rbegin(); sorted_freq_it != sorted_freq.rend(); ++sorted_freq_it) {
      for (const auto ch : sorted_freq_it->second) {
        for (int j = 0; j < sorted_freq_it->first; ++j) {
          s[++i] = ch;
        }
      }
    }

    return s;
  }
};

int main() {
  {
    std::string s("tree");
    const std::vector<std::string> expected{"eert", "eetr"};
    const std::string actual = Solution::frequencySort(s);
    assert(std::any_of(expected.begin(), expected.end(), [&actual](const auto& e) {
      return e == actual;
    }));
  }
  {
    std::string s("cccaaa");
    const std::vector<std::string> expected{"aaaccc", "cccaaa"};
    const std::string actual = Solution::frequencySort(s);
    assert(std::any_of(expected.begin(), expected.end(), [&actual](const auto& e) {
      return e == actual;
    }));
  }
  {
    std::string s("Aabb");
    const std::vector<std::string> expected{"bbAa", "bbaA"};
    const std::string actual = Solution::frequencySort(s);
    assert(std::any_of(expected.begin(), expected.end(), [&actual](const auto& e) {
      return e == actual;
    }));
  }

  return 0;
}
