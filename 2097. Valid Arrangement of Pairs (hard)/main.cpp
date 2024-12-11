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

class EulerianPathDir {
  // A Eulerian path is a path in a graph that passes through all of its edges exactly once.
public:
  using Adj = std::unordered_map<int, std::unordered_set<int>>;

  Adj& adj_; // Список смежности
  int beg_ = -1, end_ = -1;
  vi rev_;

  explicit EulerianPathDir(Adj& adj) : adj_(adj) {}
  
  bool Solve() {
    const auto pre_check = PreCheck();
    if (!pre_check)
      return false;

    std::stack<int> st;
    st.push((beg_ == -1) ? adj_.begin()->F : beg_);
    while (!st.empty()) {
      const auto v = st.top();
      if (adj_[v].empty()) {
        rev_.push_back(v);
        st.pop();
      } else {
        const auto u = *adj_[v].begin();
        adj_[v].erase(adj_[v].begin());
        st.push(u);
      }
    }

    return true;
  }

private:
  bool PreCheck() {
    std::unordered_map<int, int> deg_out, deg_in;
    for (const auto& [v, us] : adj_) {
      deg_out[v] += SZ(us);
      for (const auto u : us)
        ++deg_in[u];
    }
    for (const auto& [v, _] : adj_) {
      if (deg_out[v] == deg_in[v] + 1 && beg_ == -1)
        beg_ = v;
      else if (deg_out[v] + 1 == deg_in[v] && end_ == -1)
        end_ = v;
      else if (deg_out[v] != deg_in[v])
        return false;
      // deg_out[v] == deg_in[v]
    }
    return true;
  }
};

class Solution {
public:
  vvi validArrangement(const vvi& pairs) {
    const auto pn = SZ(pairs);
    EulerianPathDir::Adj adj;
    FOR(pi, 0, pn-1) {
      const auto& p = pairs[pi];
      adj[p[0]].insert(p[1]);
      adj[p[1]];
    }
    EulerianPathDir solver(adj);
    [[maybe_unused]] const auto possible = solver.Solve();

    vvi res;
    while (SZ(solver.rev_) >= 2) {
      const auto v = solver.rev_.back();
      solver.rev_.pop_back();
      res.push_back({v, solver.rev_.back()});
    }

    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi pairs{{5,1},{4,5},{11,9},{9,4}};
    const auto a_out = Solution().validArrangement(pairs);
    const vvi e_out{{11,9},{9,4},{4,5},{5,1}};
    assert(a_out == e_out);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi pairs{{1,2},{1,3},{2,1}};
    const auto a_out = Solution().validArrangement(pairs);
    const vvi e_out{{1,2},{2,1},{1,3}};
    assert(a_out == e_out);
  
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
