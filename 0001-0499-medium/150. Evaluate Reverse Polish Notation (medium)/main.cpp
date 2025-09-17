#include <bits/stdc++.h>

using namespace std::literals;

using ll [[maybe_unused]] = long long;
using ii [[maybe_unused]] = std::pair<int, int>;
using vii [[maybe_unused]] = std::vector<ii>;
using vi [[maybe_unused]] = std::vector<int>;
using vvi [[maybe_unused]] = std::vector<vi>;
using vs [[maybe_unused]] = std::vector<std::string>;
using vvs [[maybe_unused]] = std::vector<vs>;
using vc [[maybe_unused]] = std::vector<char>;
using vvc [[maybe_unused]] = std::vector<vc>;

#define FOR(_i, _a, _b) for (int _i = (_a); _i <= (_b); ++(_i))
#define FORD(_i, _a, _b) for (int _i = (_a); _i >= (_b); --(_i))
#define RNG(_l) (_l).begin(), (_l).end()
#define SORT(_l) std::sort((_l).begin(), (_l).end())
#define CI(_v) static_cast<int>(_v)
#define F first
#define S second

class Solution {
 public:
  static int evalRPN(const vs& tokens) {
    std::stack<int> st;
    for (const auto& t : tokens) {
      if (t.size()==1 && (t[0]=='+' || t[0]=='-' || t[0]=='*' || t[0]=='/')) {
        const auto b = st.top(); st.pop();
        const auto a = st.top(); st.pop();
        int c;
        if (t[0] == '+') c = a+b;
        else if (t[0] == '-') c = a-b;
        else if (t[0] == '*') c = a*b;
        else if (t[0] == '/') c = a/b;
        st.push(c);
      } else {
        st.push(std::stoi(t));
      }
    }
    return st.top();
  }
};

/*[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    auto a_out = Solution::minInsertions("zzazz");
    assert(a_out == 0);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  std::cerr << "TestSolution OK"sv << std::endl;
}*/

int main() {
#ifndef NDEBUG
//  TestSolution();
#endif
  return 0;
}
