// #include <bits/stdc++.h>

#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <deque>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <numeric>
#include <optional>
#include <random>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <variant>
#include <vector>

using namespace std::literals;

using ll = long long;
using ii [[maybe_unused]] = std::pair<int, int>;
using vi [[maybe_unused]] = std::vector<int>;
using vl [[maybe_unused]] = std::vector<ll>;
using vvi [[maybe_unused]] = std::vector<vi>;
using vii [[maybe_unused]] = std::vector<ii>;
using vb [[maybe_unused]] = std::vector<bool>;
using vd [[maybe_unused]] = std::vector<double>;
using vs [[maybe_unused]] = std::vector<std::string>;

#define FOR(_i, _a, _b) for (int _i = (_a); _i <= (_b); ++(_i))
#define FORD(_i, _a, _b) for (int _i = (_a); _i >= (_b); --(_i))
#define RNG(_l) (_l).begin(), (_l).end()
#define SORT(_l) std::sort((_l).begin(), (_l).end())
#define CI(_v) static_cast<int>(_v)
#define CL(_v) static_cast<ll>(_v)
#define CD(_v) static_cast<double>(_v)
#define SZ(_v) static_cast<int>((_v).size())
#define F first
#define S second

class MyCalendarTwo {
public:
  MyCalendarTwo() = default;
    
  bool book(const int s, const int e) {
    if (IntersectDouble(s, e))
      return false;
    BookSingle(s, e);
    return true;
  }

private:
  std::set<ii> d_set_, s_set_;

  bool IntersectDouble(const int s, const int e) {
    const auto l_it = d_set_.lower_bound({s, e});
    if (l_it != d_set_.end() && std::max(s, l_it->F) < std::min(e, l_it->S))
      return true;
    if (l_it != d_set_.begin() && std::max(s, std::prev(l_it)->F) < std::min(e, std::prev(l_it)->S))
      return true;
    return false;
  }
  
  void BookSingle(const int s, const int e) {
    std::queue<ii> q;
    q.emplace(s, e);
    while (!q.empty()) {
      const auto qs = q.front().F, qe = q.front().S;
      q.pop();
      
      const auto l_it = s_set_.lower_bound({qs, qe});
      if (l_it != s_set_.end()) {
        const auto ss = l_it->F, se = l_it->S;
        const auto is = std::max(qs, ss), ie = std::min(qe, se);
        if (is < ie) { // intersection
          s_set_.erase(l_it);
          if (ss < is) s_set_.emplace(ss, is);
          if (qs < is) q.emplace(qs, is);
          d_set_.emplace(is, ie);
          if (ie < se) s_set_.emplace(is, se);
          if (ie < qe) q.emplace(ie, qe);
          continue;
        }
      }

      if (l_it != s_set_.begin()) {
        const auto ss = std::prev(l_it)->F, se = std::prev(l_it)->S;
        const auto is = std::max(qs, ss), ie = std::min(qe, se);
        if (is < ie) { // prev intersection
          s_set_.erase(std::prev(l_it));
          if (ss < is) s_set_.emplace(ss, is);
          if (qs < is) q.emplace(qs, is);
          d_set_.emplace(is, ie);
          if (ie < se) s_set_.emplace(is, se);
          if (ie < qe) q.emplace(ie, qe);
          continue;
        }
      }

      // no intersections
      s_set_.emplace(qs, qe);
    }
  }
};

/**
 * Your MyCalendarTwo object will be instantiated and called as such:
 * MyCalendarTwo* obj = new MyCalendarTwo();
 * bool param_1 = obj->book(start,end);
 */

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    MyCalendarTwo obj;
    assert(obj.book(10, 20));
    assert(obj.book(50, 60));
    assert(obj.book(10, 40));
    assert(!obj.book(5, 15));
    assert(obj.book(5, 10));
    assert(obj.book(25, 55));
  
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
