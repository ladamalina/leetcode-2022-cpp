#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

class CountIntervals {
 public:
  CountIntervals() = default;

  void add(int left, int right) {
    auto [it, inserted] = blocks_.insert({left, right});
    if (!inserted) return;
    auto new_cnt = cnt_ + (right - left + 1);
    if (it != blocks_.begin()) {
      auto prev_it = std::prev(it);
      bool intersected = std::max(prev_it->first, it->first) <= std::min(prev_it->second, it->second);
      if (intersected) {
        auto dec_cnt = std::min(prev_it->second, it->second) - std::max(prev_it->first, it->first) + 1;
        new_cnt -= dec_cnt;
        std::pair<int, int> prev_union{std::min(prev_it->first, it->first), std::max(prev_it->second, it->second)};
        blocks_.erase(prev_it);
        blocks_.erase(it);
        blocks_.insert(prev_union);
        it = blocks_.find(prev_union);
      }
    }
    if (std::next(it) != blocks_.end()) {
      auto next_it = std::next(it);
      bool intersected = std::max(it->first, next_it->first) <= std::min(it->second, next_it->second);
      while (intersected) {
        auto dec_cnt = std::min(it->second, next_it->second) - std::max(it->first, next_it->first) + 1;
        new_cnt -= dec_cnt;
        std::pair<int, int> next_union{std::min(it->first, next_it->first), std::max(it->second, next_it->second)};
        blocks_.erase(it);
        blocks_.erase(next_it);
        blocks_.insert(next_union);
        it = blocks_.find(next_union);
        if (std::next(it) != blocks_.end()) {
          next_it = std::next(it);
          intersected = std::max(it->first, next_it->first) <= std::min(it->second, next_it->second);
        } else break;
      }
    }
    cnt_ = new_cnt;
  }

  [[nodiscard]] int count() const {
    return cnt_;
  }
  
 private:
  std::set<std::pair<int, int>> blocks_;
  int cnt_ = 0;
};

/**
 * Your CountIntervals object will be instantiated and called as such:
 * CountIntervals* obj = new CountIntervals();
 * obj->add(left,right);
 * int param_2 = obj->count();
 */

int main() {
  {
    auto* obj = new CountIntervals();
    obj->add(2, 3);
    obj->add(7, 10);
    auto res1 = obj->count();
    assert(res1 == 6);
    obj->add(5, 8);
    auto res2 = obj->count();
    assert(res2 == 8);
  }
  return 0;
}
