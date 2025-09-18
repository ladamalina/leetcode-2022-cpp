#include <cassert>
#include <deque>

class RecentCounter {
public:
  RecentCounter() = default;

  int ping(int t) {
    q.push_back(t);
    int t_begin = t - 3000;
    while (q.front() < t_begin)
      q.pop_front();
    return q.size();
  }
private:
  std::deque<int> q;
};

int main() {
  auto recentCounter = RecentCounter();
  assert(recentCounter.ping(1) == 1);
  assert(recentCounter.ping(100) == 2);
  assert(recentCounter.ping(3001) == 3);
  assert(recentCounter.ping(3002) == 3);

  return 0;
}
