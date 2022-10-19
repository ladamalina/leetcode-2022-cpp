#include <cassert>
#include <iostream>
#include <set>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

class Solution {
 public:
  static std::vector<std::string> topKFrequent(const std::vector<std::string>& words, int k) {
    std::unordered_map<std::string_view, int> all_freqs;
    auto cmp = [](const std::pair<int, std::string_view>& a, const std::pair<int, std::string_view>& b) {
      return (a.first < b.first) ||
             (a.first == b.first && a.second > b.second);
    };
    std::set<std::pair<int, std::string_view>, decltype(cmp)> top_freqs(cmp);

    for (const auto& w : words) {
      auto all_freqs_it = all_freqs.find(w);
      int old_freq = 0;
      int new_freq = 1;
      if (all_freqs_it == all_freqs.end()) { // new word
        ++all_freqs[w];
      } else { // duplicate word
        old_freq = all_freqs_it->second;
        ++all_freqs_it->second;
        new_freq = all_freqs_it->second;
      }
      auto top_freqs_it = top_freqs.find({old_freq, w});
      if (top_freqs_it != top_freqs.end()) {
        top_freqs.erase(top_freqs_it);
      }
      top_freqs.insert({new_freq, w});
      if (static_cast<int>(top_freqs.size()) > k) {
        top_freqs.erase(top_freqs.begin());
      }
    }

    std::vector<std::string> top_k_words;
    top_k_words.reserve(top_freqs.size());
    for (auto it = top_freqs.rbegin(); it != top_freqs.rend(); ++it) {
      top_k_words.emplace_back(it->second);
    }

    return top_k_words;
  }
};

int main() {
  {
    const std::vector<std::string> words{"i","love","leetcode","i","love","coding"};
    const int k = 2;
    const std::vector<std::string> expected{"i","love"};
    assert(Solution::topKFrequent(words, k) == expected);
  }
  {
    const std::vector<std::string> words{"the","day","is","sunny","the","the","the","sunny","is","is"};
    const int k = 4;
    const std::vector<std::string> expected{"the","is","sunny","day"};
    assert(Solution::topKFrequent(words, k) == expected);
  }

  return 0;
}
