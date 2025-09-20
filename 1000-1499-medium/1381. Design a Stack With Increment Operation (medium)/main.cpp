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

class CustomStack {
public:
  struct Item {
    int val = 0;
    vii ops;
  };
  
  CustomStack(int maxSize) : capacity_(maxSize) {}
    
  void push(int x) {
    if (st_.size() < capacity_)
      st_.emplace(x);
  }
    
  int pop() {
    if (st_.empty())
      return -1;
    Propagate();
    const auto x = st_.top().val;
    st_.pop();
    return x;
  }
    
  void increment(int k, int val) {
    if (!st_.empty())
      st_.top().ops.emplace_back(k, val);
  }
private:
  int capacity_ = 0;
  std::stack<Item> st_;
  
  void Propagate() {
    auto top_dep = SZ(st_);
    auto top_val = st_.top().val;
    auto top_ops = std::move(st_.top().ops);
    st_.pop();
    
    while (!top_ops.empty()) {
      const auto [ops_dep, ops_val] = top_ops.back();
      if (top_dep <= ops_dep)
        top_val += ops_val;
      if (!st_.empty())
        st_.top().ops.emplace_back(ops_dep, ops_val);
      top_ops.pop_back();
    }
    st_.emplace(top_val);
  }
};

/**
 * Your CustomStack object will be instantiated and called as such:
 * CustomStack* obj = new CustomStack(maxSize);
 * obj->push(x);
 * int param_2 = obj->pop();
 * obj->increment(k,val);
 */

[[maybe_unused]] void TestSolution() {
  /*{
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().solve();
    assert(a_out == 6);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }*/
  std::cerr << "TestSolution OK"sv << std::endl;
}

int main() {
#ifndef NDEBUG
  TestSolution();
#endif
  return 0;
}
