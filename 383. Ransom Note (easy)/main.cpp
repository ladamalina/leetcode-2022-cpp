#include <string>
#include <unordered_map>

class Solution {
public:
  static bool canConstruct(std::string& ransomNote, std::string& magazine) {
    if (ransomNote.size() > magazine.size())
      return false;

    std::unordered_map<char, uint16_t> chars_note;
    std::for_each(ransomNote.begin(), ransomNote.end(),
                  [&chars_note](const char& ch){++chars_note[ch];});

    std::unordered_map<char, uint16_t> chars_magazine;
    for (const char& ch : magazine) {
      if (chars_note.count(ch) == 0)
        continue;
      // chars_note.count(ch) == 1
      ++chars_magazine[ch];
      if (chars_magazine[ch] >= chars_note[ch]) {
        chars_note.erase(ch);
        chars_magazine.erase(ch);
      }
    }

    return chars_note.empty();
  }
};

int main() {
  std::string s1_note = "a";
  std::string s1_magazine = "b";
  assert(Solution::canConstruct(s1_note, s1_magazine) == false);

  std::string s2_note = "aa";
  std::string s2_magazine = "ab";
  assert(Solution::canConstruct(s2_note, s2_magazine) == false);

  std::string s3_note = "aa";
  std::string s3_magazine = "aab";
  assert(Solution::canConstruct(s3_note, s3_magazine));

  return 0;
}
