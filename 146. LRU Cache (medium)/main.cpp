#include <list>
#include <unordered_map>

class LRUCache {
public:
  LRUCache(const int capacity) : capacity_(capacity) {};

  int get(const int key) {
    if (!map.count(key))
      return -1;

    refresh_queue(map[key].second);

    return map[key].first;
  }

  void put(const int key, const int value) {
    if (map.count(key)) {
      map[key].first = value;
      refresh_queue(map[key].second);
      return;
    }

    if (map.size() == capacity_) { // evict LRU key
      auto lru_key = queue.back();
      map.erase(lru_key);
      queue.pop_back();
    }
    // insert new key
    queue.push_front(key);
    map[key] = std::pair(value, queue.begin());
  }

private:
  int capacity_;
  std::list<int> queue;
  std::unordered_map<int, std::pair<int, std::list<int>::iterator>> map;

  void refresh_queue(std::list<int>::iterator& queue_it) {
    auto key = *queue_it;
    queue.erase(queue_it);
    queue.push_front(key);
    queue_it = queue.begin();
  }
};

int main() {
  auto obj1 = new LRUCache(2);
  obj1->put(1, 1);          // cache is {1=1}
  obj1->put(2, 2);          // cache is {1=1, 2=2}
  assert(obj1->get(1) == 1);      // return 1
  obj1->put(3, 3);          // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
  assert(obj1->get(2) == -1);     // returns -1 (not found)
  obj1->put(4, 4);          // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
  assert(obj1->get(1) == -1);;    // return -1 (not found)
  assert(obj1->get(3) == 3);      // return 3
  assert(obj1->get(4) == 4);      // return 4

  auto obj2 = new LRUCache(2);
  assert(obj2->get(2) == -1);
  obj2->put(2, 6);          // cache is {2=6}
  assert(obj2->get(1) == -1);
  obj2->put(1, 5);          // cache is {2=6,1=5}
  obj2->put(1, 2);          // cache is {2=6,1=2}
  assert(obj2->get(1) == 2);
  assert(obj2->get(2) == 6);

  return 0;
}
