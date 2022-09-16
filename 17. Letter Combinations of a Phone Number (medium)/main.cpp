#include <cassert>
#include <cmath>
#include <string>
#include <vector>

class Solution {
 public:
  static std::vector<std::string> letterCombinations(const std::string& digits) {
    if (digits.empty()) {
      return {};
    }

    const std::vector<std::string> CODES = {"","","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};
    std::vector<std::string> combinations{""};
    combinations.reserve(static_cast<int>(std::pow(3, digits.size())));

    for (const auto d_char : digits) {
      const auto& code_str = CODES[d_char - '0'];
      std::vector<std::string> next_combinations;
      next_combinations.reserve(std::min(1, static_cast<int>(combinations.size())) * code_str.size());
      for (const auto& combination_prefix : combinations) {
        for (const auto code_ch : code_str) {
          next_combinations.push_back(combination_prefix + code_ch);
        }
      }
      std::swap(combinations, next_combinations);
    }

    return combinations;
  }
};

int main() {
  {
    const std::string digits = "23";
    const std::vector<std::string> expected{"ad","ae","af","bd","be","bf","cd","ce","cf"};
    const auto actual = Solution::letterCombinations(digits);
    assert(expected == actual);
  }
  {
    const std::string digits;
    const std::vector<std::string> expected;
    const auto actual = Solution::letterCombinations(digits);
    assert(expected == actual);
  }
  {
    const std::string digits = "2";
    const std::vector<std::string> expected{"a","b","c"};
    const auto actual = Solution::letterCombinations(digits);
    assert(expected == actual);
  }

  return 0;
}
