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
#define CD(_v) static_cast<double>(_v)
#define F first
#define S second

using Op = std::variant<char, int>;

struct ParsedOp {
  bool error = false;
  bool eol = false;
  std::optional<Op> op = std::nullopt;
  int next_pos = INT_MAX;
};

ParsedOp GetNextOp(const std::string& s, int pos, const std::optional<Op>& prev_op) {
  auto n = CI(s.size());
  if (pos >= n) return {false, true};

  while (pos < n && s[pos] == ' ') ++pos;
  if (pos >= n) return {false, true};

  bool may_be_sign = true;
  if (prev_op) {
    if (std::holds_alternative<char>(prev_op.value())) {
      auto prev_ch = std::get<char>(prev_op.value());
      if (prev_ch == ')') may_be_sign = false;
    } else {
      may_be_sign = false;
    }
  }

  if (s[pos] == '(' || s[pos] == ')' || s[pos] == '*') {
    return {false, false, s[pos], pos+1};
  } else if (s[pos] == '-' || s[pos] == '+') {
    if (may_be_sign && pos+1 < n && std::isdigit(s[pos+1])) { // Support negative numbers, 2 * -3
      int sign = (s[pos] == '+') ? 1 : -1;
      int num = 0;
      ++pos;
      while (pos < n && std::isdigit(s[pos])) {
        num = num*10 + (s[pos]-'0');
        ++pos;
      }
      num *= sign;
      return {false, false, num, pos};
    } else if (s[pos] == '-' && 
        (!prev_op || (prev_op && std::holds_alternative<char>(prev_op.value()) && 
                      std::get<char>(prev_op.value()) == '('))) {
      return {false, false, 'd', pos+1};
    } else {
      return {false, false, s[pos], pos+1};
    }
  } else if (std::isdigit(s[pos])) {
    int num = 0;
    while (pos < n && std::isdigit(s[pos])) {
      num = num*10 + (s[pos]-'0');
      ++pos;
    }
    return {false, false, num, pos};
  } else {
    return {true};
  }
}

bool CheckConseqOps(const std::optional<Op>& prev_op, const Op& op) {
  if (!prev_op) { // nullopt
    return std::holds_alternative<int>(op) || 
        (std::holds_alternative<char>(op) && (std::get<char>(op) == '(' || std::get<char>(op) == 'd'));
  } // prev_op
  if (std::holds_alternative<char>(prev_op.value())) {
    auto prev_char = std::get<char>(prev_op.value());
    if (prev_char == '+' || prev_char == '-' || prev_char == '*') {
      if (std::holds_alternative<char>(op)) {
        auto ch = std::get<char>(op);
        if (ch == '+' || ch == '-' || ch == '*' || ch == ')') {
          return false;
        } else return true;
      } else { // std::holds_alternative<int>(op)
        return true;
      }
    } else if (prev_char == '(') {
      if (std::holds_alternative<char>(op)) {
        auto ch = std::get<char>(op);
        if (ch == '+' || ch == '-' || ch == '*' || ch == ')') {
          return false;
        } else return true;
      } else { // std::holds_alternative<int>(op)
        return true;
      }
    } else if (prev_char == ')') { // prev_char == ')'
      if (std::holds_alternative<char>(op)) {
        auto ch = std::get<char>(op);
        if (ch == '+' || ch == '-' || ch == '*' || ch == ')') {
          return true;
        } else return false;
      } else { // std::holds_alternative<int>(op)
        return false;
      }
    } else { // prev_char == 'd'
      if (std::holds_alternative<char>(op)) {
        auto ch = std::get<char>(op);
        if (ch == '(') {
          return true;
        } else return false;
      } else { // std::holds_alternative<int>(op)
        return false;
      }
    }
  } else { // std::holds_alternative<int>(prev_op.value())
    if (std::holds_alternative<char>(op)) {
      auto ch = std::get<char>(op);
      if (ch == '+' || ch == '-' || ch == '*' || ch == ')') {
        return true;
      } else return false;
    } else { // std::holds_alternative<int>(op)
      return false;
    }
  }
}

std::optional<std::vector<Op>> Inf2Post(const std::string& s_post) {
  std::vector<Op> res;
  std::stack<char> st;
  int next_pos = 0;
  std::optional<Op> prev_op = std::nullopt;
  while (true) {
    auto parsed = GetNextOp(s_post, next_pos, prev_op);
    next_pos = parsed.next_pos;
    if (parsed.error) {
      return std::nullopt;
    }
    if (parsed.eol) {
      break;
    }
    auto op = parsed.op.value();
    if (!CheckConseqOps(prev_op, op)) {
      return std::nullopt;
    }
    prev_op = op;
    if (std::holds_alternative<int>(op)) {
      auto num = std::get<int>(op);
      res.emplace_back(num);
      continue;
    }
    const auto ch = std::get<char>(op);
    if (ch == '(') {
      st.push(ch);
    } else if (ch == ')') {
      while (!st.empty() && st.top() != '(') {
        res.emplace_back(st.top());
        st.pop();
      }
      if (st.empty()) return std::nullopt;
      else st.pop();
      if (!st.empty() && st.top() == 'd') {
        res.emplace_back(st.top());
        st.pop();
      }
    } else if (ch == '+' || ch == '-') {
      while (!st.empty() && (st.top() == '*' || st.top() == '+' || st.top() == '-')) {
        res.emplace_back(st.top());
        st.pop();
      }
      st.push(ch);
    } else if (ch == '*') {
      while (!st.empty() && st.top() == '*') {
        res.emplace_back(st.top());
        st.pop();
      }
      st.push(ch);
    } else { // ch == 'd'
      st.push(ch);
    }
  }
  while (!st.empty() && st.top() != '(') {
    res.emplace_back(st.top());
    st.pop();
  }
  if (st.empty()) return res;
  else return std::nullopt;
}

class Solution {
 public:
  static int calculate(const std::string& s) {
    auto post_v = Inf2Post(s);
    const auto post = std::move(post_v.value());
    const auto post_n = CI(post.size());
    
    /*for (const auto& p : post) {
      if (std::holds_alternative<int>(p))
        std::cerr << std::get<int>(p) << ' ';
      else
        std::cerr << std::get<char>(p) << ' ';
    }*/
    
    std::stack<int> st;
    FOR(i, 0, post_n-1) {
      if (std::holds_alternative<int>(post[i])) {
        auto num = std::get<int>(post[i]);
        st.push(num);
      } else {
        auto ch = std::get<char>(post[i]);
        auto num2 = st.top(); st.pop();
        if (ch == '+') {
          auto num1 = st.top(); st.pop();
          st.push(num1+num2);
        } else if (ch == '-') {
          auto num1 = st.top(); st.pop();
          st.push(num1 - num2);
        } else if (ch == '*') {
          auto num1 = st.top(); st.pop();
          st.push(num1 * num2);
        } else { // ch == 'd'
          st.push(-1 * num2);
        }
      }
    }
    return st.top();
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    auto a_out = Solution::calculate("- (3 - (- (4 + 5) ) )");
    assert(a_out == -12);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    auto a_out = Solution::calculate("- (3 + (4 + 5))");
    assert(a_out == -12);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    auto a_out = Solution::calculate("1 + 1");
    assert(a_out == 2);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    auto a_out = Solution::calculate(" 2-1 + 2 ");
    assert(a_out == 3);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    auto a_out = Solution::calculate("(1+(4+5+2)-3)+(6+8)");
    assert(a_out == 23);

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
