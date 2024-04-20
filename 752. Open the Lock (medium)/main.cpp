#include <bits/stdc++.h>

using namespace std::literals;

using ll [[maybe_unused]] = long long;
using ii [[maybe_unused]] = std::pair<int, int>;
using vii [[maybe_unused]] = std::vector<ii>;
using vi [[maybe_unused]] = std::vector<int>;
using vl [[maybe_unused]] = std::vector<ll>;
using vvi [[maybe_unused]] = std::vector<vi>;
using vvii [[maybe_unused]] = std::vector<vii>;
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

char RotateR(char ch) {
  return (ch == '9') ? '0' : ++ch;
}

char RotateL(char ch) {
  return (ch == '0') ? '9' : --ch;
}

std::string RotateWheelR(int i, const std::string& s) {
  auto t = s;
  t[i] = RotateR(t[i]);
  return t;
}

std::string RotateWheelL(int i, const std::string& s) {
  auto t = s;
  t[i] = RotateL(t[i]);
  return t;
}

class Solution {
  public:
  static int openLock(const vs& deadends, const std::string& target) {
    std::unordered_set<std::string> deadends_set(RNG(deadends));
    if (deadends_set.contains("0000"s)) {
      return -1;
    }

    vi dist(10000, INT_MAX);
    std::priority_queue<ii, std::vector<ii>, std::greater<>> pq;
    pq.emplace(0, 0);
    while (!pq.empty()) {
      const auto v_dist = pq.top().F;
      const auto v = pq.top().S;
      const auto v_str = std::string(4-std::to_string(v).size(), '0') + std::to_string(v);
      pq.pop();

      if (v_dist >= dist[v])
        continue;
      dist[v] = v_dist;
      if (v_str == target)
        break;

      FOR(i, 0, 3) {
        const auto ul_str = RotateWheelL(i, v_str);
        if (!deadends_set.contains(ul_str)) {
          const auto ul = std::stoi(ul_str);
          if (v_dist+1 < dist[ul]) {
            pq.emplace(v_dist+1, std::stoi(ul_str));
          }
        }

        const auto ur_str = RotateWheelR(i, v_str);
        if (!deadends_set.contains(ur_str)) {
          const auto ur = std::stoi(ur_str);
          if (v_dist+1 < dist[ur]) {
            pq.emplace(v_dist+1, std::stoi(ur_str));
          }
        }
      }
    }

    const auto target_num = std::stoi(target);
    return (dist[target_num] == INT_MAX) ? -1 : dist[target_num];
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vs deadends{"0201","0101","0102","1212","2002"};
    auto a_out = Solution::openLock(deadends, "0202"s);
    assert(a_out == 6);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vs deadends{"8887","8889","8878","8898","8788","8988","7888","9888"};
    auto a_out = Solution::openLock(deadends, "8888"s);
    assert(a_out == -1);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vs deadends{"0000"};
    auto a_out = Solution::openLock(deadends, "8888"s);
    assert(a_out == -1);

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
