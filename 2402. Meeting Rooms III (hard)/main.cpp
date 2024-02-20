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

constexpr int MAX_N = 100;
std::array<int, MAX_N> cnt;

class Solution {
 public:
  static int mostBooked(const int n, vvi& meetings) {
    std::fill(cnt.begin(), cnt.begin()+n, 0);

    SORT(meetings);
    std::priority_queue<int, vi, std::greater<>> free_rooms;
    FOR(i, 0, n-1) {
      free_rooms.push(i);
    }
    std::priority_queue<std::pair<ll, int>, std::vector<std::pair<ll, int>>, std::greater<>> busy_rooms;
    for (const auto& m : meetings) {
      while (!busy_rooms.empty() && busy_rooms.top().F <= m[0]) {
        const auto room_id = busy_rooms.top().S;
        busy_rooms.pop();
        free_rooms.emplace(room_id);
      }
      if (!free_rooms.empty()) {
        const auto room_id = free_rooms.top();
        free_rooms.pop();
        ++cnt[room_id];
        busy_rooms.emplace(m[1], room_id);
      } else {
        const auto room = busy_rooms.top();
        busy_rooms.pop();
        ++cnt[room.S];
        busy_rooms.emplace(room.F+(m[1]-m[0]), room.S);
      }
    }

    int res = -1;
    int max_cnt = -1;
    FOR(i, 0, n-1) {
      if (cnt[i] > max_cnt) {
        max_cnt = cnt[i];
        res = i;
      }
    }
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vvi meetings{{0,10},{1,5},{2,7},{3,4}};
    const auto e_out = Solution::mostBooked(2, meetings);
    assert(e_out == 0);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vvi meetings{{1,20},{2,10},{3,5},{4,9},{6,8}};
    const auto e_out = Solution::mostBooked(3, meetings);
    assert(e_out == 1);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vvi meetings{{18,19},{3,12},{17,19},{2,13},{7,10}};
    const auto e_out = Solution::mostBooked(4, meetings);
    assert(e_out == 0);

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
