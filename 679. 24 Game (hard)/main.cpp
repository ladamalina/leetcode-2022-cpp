#include <bits/stdc++.h>

using namespace std::literals;

using ll [[maybe_unused]] = long long;
using ii [[maybe_unused]] = std::pair<int, int>;
using vii [[maybe_unused]] = std::vector<ii>;
using vi [[maybe_unused]] = std::vector<int>;
using vl [[maybe_unused]] = std::vector<ll>;
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
#define CL(_v) static_cast<ll>(_v)
#define F first
#define S second

const auto EPS = 1e-6;
template <typename T>
[[maybe_unused]] bool Eq(T a, T b) { return std::abs(a - b) < EPS; }

using Op = std::variant<int, char>;

std::array<char, 4> fs = {'+', '-', '*', '/'};
std::array<Op, 7> ops;

/*
  . . . .
  (. .) . .
  (. .) (. .)
  (. . .) .
  ((. .) .) .
  (. (. .)) .
  . (. . .)
  . ((. .) .)
  . (. (. .))
*/

/*
  . . . . + + +
  . . + . . + +
  . . . + + . +
 */
const vvi P_IDS = {{0,1,2,3},{0,1,3,4},{0,1,2,5}};
const vvi F_IDS = {{4,5,6},{2,5,6},{3,4,6}};

double Solve() {
  std::stack<double> st;
  for (const auto& op : ops) {
    if (std::holds_alternative<int>(op)) {
      st.push(std::get<int>(op));
    } else {
      const auto ch = std::get<char>(op);
      const auto num2 = st.top(); st.pop();
      const auto num1 = st.top(); st.pop();
      switch (ch) {
        case '+': {
          st.push(num1 + num2);
          break;
        }
        case '-': {
          st.push(num1 - num2);
          break;
        }
        case '*': {
          st.push(num1 * num2);
          break;
        }
        case '/': {
          if (num2 == 0) return 0;
          else st.push(double(num1) / num2);
        }
      }
    }
  }
  return st.top();
}

class Solution {
 public:
  static bool judgePoint24(const vi& cards) {
    FOR(pf, 0, 2) {
      auto ps = P_IDS[pf];
      const auto& f_ids = F_IDS[pf];
      do {
        FOR(i, 0, 3) {
          ops[ps[i]] = cards[i];
        }
        FOR(i, 0, 3) {
          ops[f_ids[0]] = fs[i];
          FOR(j, 0, 3) {
            ops[f_ids[1]] = fs[j];
            FOR(k, 0, 3) {
              ops[f_ids[2]] = fs[k];
              const auto res = Solve();
              if (Eq(res, 24.))
                return true;
            }
          }
        }
      } while (std::next_permutation(RNG(ps)));
    }
    return false;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto a_out = Solution::judgePoint24({4,1,8,7});
    assert(a_out);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto a_out = Solution::judgePoint24({1,2,1,2});
    assert(!a_out);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto a_out = Solution::judgePoint24({1,9,1,2});
    assert(a_out);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  std::cerr << "TestSolution OK"sv << std::endl;
}

int main() {
#ifndef NDEBUG
  TestSolution();
#endif
  return 0;
}
