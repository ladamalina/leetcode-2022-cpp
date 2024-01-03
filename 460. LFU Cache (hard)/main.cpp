//#pragma GCC optimize("O3")
//#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;

using ll = long long;
using ld = long double;
using ull = unsigned long long;
using ii [[maybe_unused]] = std::pair<int, int>;
using pll [[maybe_unused]] = std::pair<ll, ll>;
using pdd [[maybe_unused]] = std::pair<double, double>;
using vi [[maybe_unused]] = std::vector<int>;
using vvi [[maybe_unused]] = std::vector<vi>;
using vvvi [[maybe_unused]] = std::vector<vvi>;
using vii [[maybe_unused]] = std::vector<ii>;
using vvii [[maybe_unused]] = std::vector<vii>;
using vb [[maybe_unused]] = std::vector<bool>;

#define FOR(_i, _a, _b) for (int _i = (_a); _i <= (_b); ++(_i))
#define FORD(_i, _a, _b) for (int _i = (_a); _i >= (_b); --(_i))
#define RNG(_l) (_l).begin(), (_l).end()
#define SORT(_l) std::sort((_l).begin(), (_l).end())
#define CI(_v) static_cast<int>(_v)
#define CL(_v) static_cast<ll>(_v)
#define CD(_v) static_cast<ld>(_v)
#define F first
#define S second
#define PB push_back

class LFUCache {
  public:
  const int MAX_KEY = 1e5;
  const int MAX_FREQ = 2*1e5;
  
  explicit LFUCache(int capacity)
    : capacity_(capacity)
    , map_(MAX_KEY+1)
    , key_2_freq_(MAX_KEY+1)
    , freq_2_kq_(MAX_FREQ+1)
    , key_2_kq_it_(MAX_KEY+1)
    , size_(0)
    , min_freq_(0)
    {}
    
  int get(int key) {
    if (!map_[key].has_value()) return -1;
    bump(key);
    return map_[key].value();
  }
    
  void put(int key, int value) {
    if (map_[key].has_value()) {
      map_[key] = value;
      bump(key);
    } else {
      if (size_ == capacity_) {
        const auto ev_it = std::prev(freq_2_kq_[min_freq_].end());
        const auto ev_key = *ev_it;
        const auto ev_freq = key_2_freq_[ev_key];
        map_[ev_key] = std::nullopt;
        key_2_freq_[ev_key] = 0;
        freq_2_kq_[ev_freq].erase(ev_it);
        --size_;
      } // size_ < capacity_
      map_[key] = value;
      key_2_freq_[key] = 1;
      freq_2_kq_[1].emplace_front(key);
      key_2_kq_it_[key] = freq_2_kq_[1].begin();
      ++size_;
      min_freq_ = 1;
    }
  }

  private:
  const int capacity_;
  std::vector<std::optional<int>> map_;
  std::vector<int> key_2_freq_;
  std::vector<std::list<int>> freq_2_kq_;
  std::vector<std::list<int>::iterator> key_2_kq_it_;
  int size_;
  int min_freq_;

  void bump(int key) {
    const auto old_freq = key_2_freq_[key];
    const auto new_freq = old_freq + 1;
    key_2_freq_[key] = new_freq;

    const auto old_it = key_2_kq_it_[key];
    freq_2_kq_[old_freq].erase(old_it);
    freq_2_kq_[new_freq].emplace_front(key);
    key_2_kq_it_[key] = freq_2_kq_[new_freq].begin();

    if (old_freq == min_freq_ && freq_2_kq_[old_freq].empty()) {
      ++min_freq_;
    }
  }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    LFUCache lfu(2);
    lfu.put(1, 1);   // cache=[1,_], cnt(1)=1
    lfu.put(2, 2);   // cache=[2,1], cnt(2)=1, cnt(1)=1
    assert(1 == lfu.get(1));      // return 1
    // cache=[1,2], cnt(2)=1, cnt(1)=2
    lfu.put(3, 3);   // 2 is the LFU key because cnt(2)=1 is the smallest, invalidate 2.
    // cache=[3,1], cnt(3)=1, cnt(1)=2
    assert(-1 == lfu.get(2));      // return -1 (not found)
    assert(3 == lfu.get(3));      // return 3
    // cache=[3,1], cnt(3)=2, cnt(1)=2
    lfu.put(4, 4);   // Both 1 and 3 have the same cnt, but 1 is LRU, invalidate 1.
    // cache=[4,3], cnt(4)=1, cnt(3)=2
    assert(-1 == lfu.get(1));      // return -1 (not found)
    assert(3 == lfu.get(3));      // return 3
    // cache=[3,4], cnt(4)=1, cnt(3)=3
    assert(4 == lfu.get(4));      // return 4
    // cache=[4,3], cnt(4)=2, cnt(3)=3
    
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
