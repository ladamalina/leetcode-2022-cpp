#include <cassert>
#include <iostream>
#include <map>
#include <string>

std::ostream& operator<<(std::ostream& out, const std::map<int, std::string>& container) {
  out << "{";
  for (auto it = container.begin(); it != container.end(); ++it) {
    out << it->first << ": " << it->second;
    if (std::next(it) != container.end()) {
      out << ", ";
    }
  }
  out << "}";
  return out;
}

class Solution {
 public:
  static int minDeletions(const std::string& s) {
//    std::cout << s << std::endl;
    if (s.size() == 1u) {
      return 0;
    }

    std::map<char, int> ch_freqs;
    std::map<int, std::string> freqs;
    for (const auto& ch : s) {
      ++ch_freqs[ch];
    }
    for (const auto& [ch, freq] : ch_freqs) {
      freqs[freq] += ch;
    }

    int to_delete = 0;
    auto current_it = freqs.rbegin();
//    std::cout << freqs << " - initial" << std::endl;
    while (current_it != freqs.rend()) {
      while (current_it->second.size() > 1u) {
        const auto& ch_to_move = current_it->second.back();
        const auto& current_freq = current_it->first;
        int new_freq = current_freq - 1;
        while (new_freq > 0 && freqs.count(new_freq) > 0) {
          --new_freq;
        }
        if (new_freq > 0) {
          freqs[new_freq] += ch_to_move;
        }
        to_delete += (current_freq - new_freq);
        current_it->second.pop_back();
//        std::cout << freqs << std::endl;
      }
      std::advance(current_it, 1);
    }
//    std::cout << std::string(40, '.') << std::endl;

    return to_delete;
  }
};

int main() {
    assert(Solution::minDeletions("aab") == 0);
    assert(Solution::minDeletions("aaabbbcc") == 2);
    assert(Solution::minDeletions("ceabaacb") == 2);
    assert(Solution::minDeletions("aabbccdd") == 5);
}
