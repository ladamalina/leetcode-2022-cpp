#include <bits/stdc++.h>

using namespace std::literals;

class Solution {
  public:
  static bool isIsomorphic(const std::string& s, const std::string& t) {
    if (s.size() != t.size())
      return false;
    const auto n = static_cast<int>(s.size());
    std::unordered_map<char, char> st;
    std::unordered_map<char, char> ts;
    for (auto i = 0; i < n; ++i) {
      if (st.contains(s[i])) {
        if (t[i] != st.at(s[i]))
          return false;
      } else {
        if (ts.contains(t[i]))
          return false;
        st[s[i]] = t[i];
        ts[t[i]] = s[i];
      }
    }
    return true;
  }
};

int main() {
  assert(Solution::isIsomorphic("egg"s, "add"s));
  assert(!Solution::isIsomorphic("foo"s, "bar"s));
  assert(Solution::isIsomorphic("paper"s, "title"s));
  assert(!Solution::isIsomorphic("foo"s, "aaa"s));
  assert(Solution::isIsomorphic("qwertyuiop[]asdfghjkl;'\\zxcvbnm,./"s,
                                "',.pyfgcrl/=aoeuidhtns-\\;qjkxbmwvz"s));
  assert(Solution::isIsomorphic("13"s, "42"s));

  return 0;
}
