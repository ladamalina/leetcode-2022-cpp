#include <cassert>
#include <string>
#include <vector>

class Solution {
 public:
  static int compress(std::vector<char>& chars) {
    if (chars.size() == 1u) {
      return 1;
    }
    int code_end_idx = -1;
    int current_char_idx = 0;
    int current_char_len = 1;
    for (int i = 0; i + 1 < static_cast<int>(chars.size()); ++i) {
      if (chars[i] == chars[i + 1]) {
        ++current_char_len;
        continue;
      } // chars[i] != chars[i + 1]

      insertCode(chars, code_end_idx, current_char_idx, current_char_len);
      current_char_idx = i + 1;
      current_char_len = 1;
    }
    if (current_char_len > 0) {
      insertCode(chars, code_end_idx, current_char_idx, current_char_len);
    }

    return code_end_idx + 1;
  }

  static void insertCode(std::vector<char>& chars, int& code_end_idx, const int current_char_idx,
                           const int current_char_len) {
    chars[++code_end_idx] = chars[current_char_idx];
    if (current_char_len > 1) {
      std::string code_len_str = std::to_string(current_char_len);
      for (const auto ch : code_len_str) {
        chars[++code_end_idx] = ch;
      }
    }
  }
};

int main() {
  {
    std::vector<char> chars{'a','a','b','b','c','c','c'};
    std::vector<char> expected{'a','2','b','2','c','3'};
    assert(Solution::compress(chars) == 6);
    for (int i = 0; i < static_cast<int>(expected.size()); ++i) {
      assert(chars[i] == expected[i]);
    }
  }
  {
    std::vector<char> chars{'a'};
    std::vector<char> expected{'a'};
    assert(Solution::compress(chars) == 1);
    for (int i = 0; i < static_cast<int>(expected.size()); ++i) {
      assert(chars[i] == expected[i]);
    }
  }
  {
    std::vector<char> chars{'a','b','b','b','b','b','b','b','b','b','b','b','b'};
    std::vector<char> expected{'a','b','1','2'};
    assert(Solution::compress(chars) == 4);
    for (int i = 0; i < static_cast<int>(expected.size()); ++i) {
      assert(chars[i] == expected[i]);
    }
  }

  return 0;
}
