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

struct Node {
  bool is_tail_ = false;
  std::unordered_map<std::string, Node*> nested_;
};

vs Split(const std::string& s, char delim) {
  vs result;
  std::stringstream ss(s);
  std::string item;

  getline(ss, item, delim);
  while (getline(ss, item, delim)) {
    result.push_back(std::move(item));
  }
  
  return result;
}

class Solution {
public:
  vs removeSubfolders(const vs& folders) {
    auto root = new Node();
    for (const auto& f : folders) {
      const auto dirs = Split(f, '/');
      const auto n = SZ(dirs);
      auto node = root;
    
      FOR(i, 0, n-1) {
        if (node->is_tail_)
          break;
        if (!node->nested_.contains(dirs[i]))
          node->nested_[dirs[i]] = new Node();
        node = node->nested_.at(dirs[i]);
        if (i == n-1) {
          node->is_tail_ = true;
          node->nested_.clear();
        }
      }
    }

    vs res, path;
    const std::function<void(Node*)> dfs = [&](Node* node) {
      if (node->nested_.empty()) {
        std::string s;
        for (const auto& p : path)
          s += "/"s + p;
        res.push_back(s);
        return;
      }
      for (const auto& [sub_dir, sub_node] : node->nested_) {
        path.push_back(sub_dir);
        dfs(sub_node);
        path.pop_back();
      }
    };
    dfs(root);

    return res;
  }
};

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
